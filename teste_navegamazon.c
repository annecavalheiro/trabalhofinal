/* navegamazon.c
   NavegAmazon - Guia Turístico do Centro de Manaus (Console)
   Nome estilizado: N (vermelho) a primeira letra do "Naveg" e A (vermelho) depois do "g",
   o restante em amarelo (cores ANSI).
   Funcionalidades:
    - Cadastro de usuários (azul)
    - Lista de locais (históricos com valores) (amarelo)
    - Restaurantes / Lanches / Bares (verde)
    - Avaliação por usuário (roxo)
    - Informação de periculosidade (vermelho)
    - Como chegar (GPS / hotéis) (simulado)
    - Export CSV para Canva
   Compilar: gcc -o navegamazon navegamazon.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_DEST 100
#define MAX_NAME 120
#define MAX_DESC 512
#define MAX_USERS 300
#define MAX_RATINGS 1000
#define MAX_EVENTS 200
#define MAX_LINE 1024
#define INF 1000000000

/* ANSI colors */
#define CLR_RESET "\033[0m"
#define CLR_RED "\033[1;31m"
#define CLR_GREEN "\033[1;32m"
#define CLR_YELLOW "\033[1;33m"
#define CLR_BLUE "\033[1;34m"
#define CLR_MAGENTA "\033[1;35m"
#define CLR_CYAN "\033[1;36m"
#define CLR_WHITE "\033[1;37m"

/* Entities */
typedef struct {
    int id;
    char name[MAX_NAME];
    char category[40]; /* Historico, Restaurante, Bar, Info, Perigoso */
    char address[200];
    char hours[80];
    double lat, lon;
    double price; /* for historical sites */
    int danger; /* 0 = safe, 1 = caution */
    char description[MAX_DESC];
} Destination;

typedef struct {
    int id;
    char username[50];
    char fullname[120];
} User;

typedef struct {
    int user_id;
    int dest_id;
    int rating; /* 1..5 */
    char comment[256];
} Rating;

typedef struct {
    int id;
    char title[120];
    int dest_id;
    char datetime[80];
    char location[120];
} Event;

typedef struct {
    int id;
    char name[120];
    double lat, lon;
} Hotel;

/* Data storage */
Destination dests[MAX_DEST]; int n_dest = 0;
int adj[MAX_DEST][MAX_DEST];
User users[MAX_USERS]; int n_users = 0;
Rating ratings[MAX_RATINGS]; int n_ratings = 0;
Event events[MAX_EVENTS]; int n_events = 0;
Hotel hotels[10]; int n_hotels = 0;

/* Utilities */
void init_graph(){
    for (int i=0;i<MAX_DEST;i++) for (int j=0;j<MAX_DEST;j++) adj[i][j] = (i==j?0:INF);
}

double haversine(double lat1,double lon1,double lat2,double lon2){
    const double R = 6371.0;
    double dlat = (lat2-lat1) * M_PI/180.0;
    double dlon = (lon2-lon1) * M_PI/180.0;
    double a = sin(dlat/2)*sin(dlat/2) + cos(lat1*M_PI/180.0)*cos(lat2*M_PI/180.0)*sin(dlon/2)*sin(dlon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return R * c;
}

/* Safe input helpers */
void clear_stdin(){ int c; while ((c=getchar())!='\n' && c!=EOF); }
int read_int(){
    int x;
    if (scanf("%d", &x) != 1){ clear_stdin(); return -1; }
    clear_stdin();
    return x;
}
double read_double(){
    double d;
    if (scanf("%lf", &d) != 1){ clear_stdin(); return NAN; }
    clear_stdin();
    return d;
}

/* Persistence */
void save_users(){
    FILE *f = fopen("users.csv","w");
    if (!f) return;
    for (int i=0;i<n_users;i++){
        fprintf(f,"%d,%s,%s\n", users[i].id, users[i].username, users[i].fullname);
    }
    fclose(f);
}
void load_users(){
    FILE *f = fopen("users.csv","r");
    if (!f) return;
    char line[MAX_LINE];
    while (fgets(line,sizeof(line),f)){
        int id; char uname[100], fname[200];
        if (sscanf(line,"%d,%99[^,],%199[^\n]", &id, uname, fname)==3){
            users[n_users].id = id;
            strncpy(users[n_users].username, uname, sizeof(users[n_users].username)-1);
            strncpy(users[n_users].fullname, fname, sizeof(users[n_users].fullname)-1);
            n_users++;
        }
    }
    fclose(f);
}

void save_ratings(){
    FILE *f = fopen("ratings.csv","w");
    if (!f) return;
    for (int i=0;i<n_ratings;i++){
        fprintf(f,"%d,%d,%d,%s\n", ratings[i].user_id, ratings[i].dest_id, ratings[i].rating, ratings[i].comment);
    }
    fclose(f);
}
void load_ratings(){
    FILE *f = fopen("ratings.csv","r");
    if (!f) return;
    char line[MAX_LINE];
    while (fgets(line,sizeof(line),f)){
        int uid,did,rt; char cmt[256];
        if (sscanf(line,"%d,%d,%d,%255[^\n]", &uid, &did, &rt, cmt)==4){
            ratings[n_ratings].user_id = uid;
            ratings[n_ratings].dest_id = did;
            ratings[n_ratings].rating = rt;
            strncpy(ratings[n_ratings].comment, cmt, 255);
            n_ratings++;
        }
    }
    fclose(f);
}

void save_events(){
    FILE *f = fopen("events.csv","w");
    if (!f) return;
    for (int i=0;i<n_events;i++){
        fprintf(f,"%d,%s,%d,%s,%s\n", events[i].id, events[i].title, events[i].dest_id, events[i].datetime, events[i].location);
    }
    fclose(f);
}
void load_events(){
    FILE *f = fopen("events.csv","r");
    if (!f) return;
    char line[MAX_LINE];
    while (fgets(line,sizeof(line),f)){
        int id,did; char title[200], dt[200], loc[200];
        if (sscanf(line,"%d,%199[^,],%d,%199[^,],%199[^\n]", &id, title, &did, dt, loc)==5){
            events[n_events].id = id;
            strncpy(events[n_events].title, title, 119);
            events[n_events].dest_id = did;
            strncpy(events[n_events].datetime, dt, 99);
            strncpy(events[n_events].location, loc, 119);
            n_events++;
        }
    }
    fclose(f);
}

/* Add destination */
void add_destination(const char *name,const char *cat,const char *addr,const char *hours,double lat,double lon,double price,int danger,const char *desc){
    if (n_dest >= MAX_DEST) return;
    dests[n_dest].id = n_dest;
    strncpy(dests[n_dest].name, name, MAX_NAME-1);
    strncpy(dests[n_dest].category, cat, 39);
    strncpy(dests[n_dest].address, addr, 199);
    strncpy(dests[n_dest].hours, hours, 79);
    dests[n_dest].lat = lat; dests[n_dest].lon = lon;
    dests[n_dest].price = price;
    dests[n_dest].danger = danger;
    strncpy(dests[n_dest].description, desc, MAX_DESC-1);
    n_dest++;
}

/* Seed sample data (Centro de Manaus) */
void seed_data(){
    init_graph();
    n_dest = 0; n_users = 0; n_ratings = 0; n_events = 0; n_hotels = 0;
    add_destination("Teatro Amazonas", "Historico", "Praça São Sebastião, Centro", "09:00-17:00", -3.1019, -60.0250, 10.0, 0, "Teatro do ciclo da borracha; visitas guiadas.");
    add_destination("Palácio Rio Negro", "Historico", "Av. Sete de Setembro, Centro", "09:00-16:00", -3.1045, -60.0190, 0.0, 0, "Espaço cultural com exibições.");
    add_destination("Museu do Índio", "Historico", "Rua do Comércio, Centro", "09:00-16:00", -3.0970, -60.0240, 5.0, 0, "Acervo etnográfico sobre povos indígenas.");
    add_destination("Restaurante Regional - Centro", "Restaurante", "Rua 1, Centro", "11:00-23:00", -3.1185, -60.0230, 0.0, 0, "Tacacá, tambaqui e pratos regionais.");
    add_destination("Lanches Rápidos - Praça", "Restaurante", "Praça Central", "08:00-22:00", -3.1188, -60.0215, 0.0, 0, "Lanchonetes e pratos rápidos.");
    add_destination("Bar do Porto", "Bar", "Av. do Comércio, Centro", "17:00-02:00", -3.1175, -60.0220, 0.0, 0, "Bar tradicional com música local.");
    add_destination("Beco Perigoso - Atenção", "Perigoso", "Beco X, Centro", "24h (evitar à noite)", -3.1160, -60.0240, 0.0, 1, "Área com histórico de furtos à noite; evite andar sozinho.");
    add_destination("Ponto de Informações - Praça Central", "Info", "Praça Central", "08:00-18:00", -3.1180, -60.0210, 0.0, 0, "Posto de informações turísticas.");

    /* build adjacency costs by distance */
    for (int i=0;i<n_dest;i++){
        for (int j=0;j<n_dest;j++){
            if (i==j) adj[i][j]=0;
            else {
                double d = haversine(dests[i].lat, dests[i].lon, dests[j].lat, dests[j].lon);
                int cost = (int)(d*10)+5;
                adj[i][j] = cost;
            }
        }
    }

    /* hotels */
    hotels[n_hotels].id = n_hotels; strncpy(hotels[n_hotels].name, "Hotel Centro Plaza", 119); hotels[n_hotels].lat = -3.1170; hotels[n_hotels].lon = -60.0220; n_hotels++;
    hotels[n_hotels].id = n_hotels; strncpy(hotels[n_hotels].name, "Hotel Amazonas Inn", 119); hotels[n_hotels].lat = -3.1050; hotels[n_hotels].lon = -60.0260; n_hotels++;
}

/* Dijkstra */
void dijkstra(int src,int dist[],int prev[]){
    int used[MAX_DEST];
    for (int i=0;i<n_dest;i++){ dist[i]=INF; prev[i]=-1; used[i]=0; }
    dist[src]=0;
    for (int iter=0; iter<n_dest; iter++){
        int u=-1, best=INF;
        for (int i=0;i<n_dest;i++) if (!used[i] && dist[i]<best){ best=dist[i]; u=i; }
        if (u==-1) break;
        used[u]=1;
        for (int v=0; v<n_dest; v++){
            if (adj[u][v] < INF){
                int nd = dist[u] + adj[u][v];
                if (nd < dist[v]){ dist[v] = nd; prev[v] = u; }
            }
        }
    }
}

void print_path(int prev[], int dest_id){
    int stack[MAX_DEST], top=0;
    int cur = dest_id;
    while (cur != -1){ stack[top++]=cur; cur = prev[cur]; }
    for (int i=top-1;i>=0;i--){
        printf("%s%s", dests[stack[i]].name, (i>0) ? " -> " : "\n");
    }
}

/* Display title with styled NavegAmazon: N and A red, others yellow */
void print_title(){
    /* "N a v e g A m a z o n" styling: N and A red, rest yellow */
    printf("\n");
    printf(CLR_RED "N" CLR_YELLOW "aveg" CLR_RED "A" CLR_YELLOW "mazon" CLR_RESET "\n");
    printf(CLR_CYAN "Guia turístico - Centro de Manaus (para Manauaras)\n" CLR_RESET);
}

/* List and show functions (with colors) */
void list_all(){
    printf("\n--- %sLista de locais%s ---\n", CLR_YELLOW, CLR_RESET);
    for (int i=0;i<n_dest;i++){
        const char *cat = dests[i].category;
        const char *color = CLR_YELLOW;
        if (strcasecmp(cat,"Bar")==0 || strcasecmp(cat,"Restaurante")==0) color = CLR_GREEN;
        else if (strcasecmp(cat,"Perigoso")==0) color = CLR_RED;
        else if (strcasecmp(cat,"Historico")==0) color = CLR_YELLOW;
        else if (strcasecmp(cat,"Info")==0) color = CLR_CYAN;
        /* print */
        if (dests[i].price > 0.0)
            printf("[%d] %s%s%s | %sHorário:%s %s | %sEndereço:%s %s | %sValor:%s R$ %.2f\n",
                dests[i].id, color, dests[i].name, CLR_RESET, CLR_WHITE, CLR_RESET, dests[i].hours,
                CLR_WHITE, CLR_RESET, dests[i].address, CLR_WHITE, CLR_RESET, dests[i].price);
        else
            printf("[%d] %s%s%s | %sHorário:%s %s | %sEndereço:%s %s | %sValor:%s Gratuito\n",
                dests[i].id, color, dests[i].name, CLR_RESET, CLR_WHITE, CLR_RESET, dests[i].hours,
                CLR_WHITE, CLR_RESET, dests[i].address, CLR_WHITE, CLR_RESET);
        if (dests[i].danger) printf(CLR_RED " (!) Atenção: área com risco. Evite à noite.\n" CLR_RESET);
    }
}

void list_by_category(const char *cat){
    printf("\n--- %sLocais: %s%s ---\n", CLR_YELLOW, cat, CLR_RESET);
    int found=0;
    for (int i=0;i<n_dest;i++){
        if (strcasecmp(dests[i].category, cat)==0){
            found++;
            if (dests[i].price>0.0)
                printf("[%d] %s | Horário: %s | Endereço: %s | Valor: R$ %.2f\n",
                    dests[i].id, dests[i].name, dests[i].hours, dests[i].address, dests[i].price);
            else
                printf("[%d] %s | Horário: %s | Endereço: %s | Valor: Gratuito\n",
                    dests[i].id, dests[i].name, dests[i].hours, dests[i].address);
            if (dests[i].danger) printf(CLR_RED "    (!) Atenção: área com risco.\n" CLR_RESET);
        }
    }
    if (!found) printf("Nenhum local nesta categoria.\n");
}

void show_details(int id){
    if (id<0 || id>=n_dest){ printf("ID inválido.\n"); return; }
    Destination *d = &dests[id];
    const char *catcolor = CLR_YELLOW;
    if (strcasecmp(d->category,"Bar")==0 || strcasecmp(d->category,"Restaurante")==0) catcolor = CLR_GREEN;
    else if (strcasecmp(d->category,"Perigoso")==0) catcolor = CLR_RED;
    printf("\n=== %s%s%s ===\n", catcolor, d->name, CLR_RESET);
    printf("%sCategoria:%s %s\n", CLR_WHITE, CLR_RESET, d->category);
    printf("%sEndereço:%s %s\n", CLR_WHITE, CLR_RESET, d->address);
    printf("%sHorário:%s %s\n", CLR_WHITE, CLR_RESET, d->hours);
    if (d->price>0.0) printf("%sValor:%s R$ %.2f\n", CLR_WHITE, CLR_RESET, d->price);
    else printf("%sValor:%s Gratuito/Não aplicável\n", CLR_WHITE, CLR_RESET);
    printf("%sDescrição:%s %s\n", CLR_WHITE, CLR_RESET, d->description);
    if (d->danger) printf(CLR_RED "Atenção: este local possui índice de periculosidade. Evite horários noturnos.\n" CLR_RESET);
    /* ratings */
    int count=0; double sum=0;
    for (int i=0;i<n_ratings;i++){
        if (ratings[i].dest_id == id){ printf(CLR_MAGENTA "- Usuário %d: %d estrelas. %s\n" CLR_RESET, ratings[i].user_id, ratings[i].rating, ratings[i].comment); sum += ratings[i].rating; count++; }
    }
    if (count>0) printf("Média: %.2f (%d avaliações)\n", sum/count, count);
    else printf("Nenhuma avaliação registrada.\n");
}

/* Users */
int find_user_by_username(const char *uname){
    for (int i=0;i<n_users;i++) if (strcmp(users[i].username, uname)==0) return users[i].id;
    return -1;
}

void register_user(){
    printf(CLR_BLUE "\n--- Cadastro de usuário ---\n" CLR_RESET);
    if (n_users >= MAX_USERS){ printf("Limite de usuários atingido.\n"); return; }
    char uname[50], fullname[120];
    printf("Nome de usuário (sem espaços): ");
    if (scanf("%49s", uname) != 1){ clear_stdin(); printf("Entrada inválida.\n"); return; }
    clear_stdin();
    if (find_user_by_username(uname) != -1){ printf("Usuário já existe.\n"); return; }
    printf("Nome completo: ");
    fgets(fullname, sizeof(fullname), stdin); fullname[strcspn(fullname,"\n")] = 0;
    users[n_users].id = n_users;
    strncpy(users[n_users].username, uname, sizeof(users[n_users].username)-1);
    strncpy(users[n_users].fullname, fullname, sizeof(users[n_users].fullname)-1);
    n_users++;
    save_users();
    printf(CLR_BLUE "Usuário cadastrado com sucesso! ID: %d\n" CLR_RESET, n_users-1);
}

/* Ratings */
void rate_place(){
    printf(CLR_MAGENTA "\n--- Avaliar local ---\n" CLR_RESET);
    if (n_users == 0){ printf("Nenhum usuário cadastrado. Cadastre-se primeiro.\n"); return; }
    char uname[50];
    printf("Seu nome de usuário: ");
    if (scanf("%49s", uname) != 1){ clear_stdin(); printf("Entrada inválida.\n"); return; }
    clear_stdin();
    int uid = find_user_by_username(uname);
    if (uid == -1){ printf("Usuário não encontrado.\n"); return; }
    list_all();
    printf("ID do local a avaliar: ");
    int did = read_int();
    if (did < 0 || did >= n_dest){ printf("Destino inválido.\n"); return; }
    printf("Nota (1-5): ");
    int rt = read_int();
    if (rt <1 || rt>5){ printf("Nota inválida.\n"); return; }
    char comment[256];
    printf("Comentário (opcional): ");
    fgets(comment, sizeof(comment), stdin); comment[strcspn(comment,"\n")] = 0;
    ratings[n_ratings].user_id = uid;
    ratings[n_ratings].dest_id = did;
    ratings[n_ratings].rating = rt;
    strncpy(ratings[n_ratings].comment, comment, sizeof(ratings[n_ratings].comment)-1);
    n_ratings++;
    save_ratings();
    printf(CLR_MAGENTA "Avaliação registrada. Obrigado!\n" CLR_RESET);
}

/* Events */
void add_event(){
    if (n_events >= MAX_EVENTS){ printf("Limite de eventos atingido.\n"); return; }
    char title[120], datetime[80], loc[120];
    printf("Título do evento: "); fgets(title, sizeof(title), stdin); title[strcspn(title,"\n")] = 0;
    list_all();
    printf("ID do local (onde ocorrerá): ");
    int did = read_int(); if (did<0||did>=n_dest){ printf("ID inválido.\n"); return; }
    printf("Data e hora (ex: 2025-11-20 19:00): "); fgets(datetime, sizeof(datetime), stdin); datetime[strcspn(datetime,"\n")] = 0;
    printf("Local (descrição): "); fgets(loc, sizeof(loc), stdin); loc[strcspn(loc,"\n")] = 0;
    events[n_events].id = n_events;
    strncpy(events[n_events].title, title, sizeof(events[n_events].title)-1);
    events[n_events].dest_id = did;
    strncpy(events[n_events].datetime, datetime, sizeof(events[n_events].datetime)-1);
    strncpy(events[n_events].location, loc, sizeof(events[n_events].location)-1);
    n_events++;
    save_events();
    printf("Evento adicionado.\n");
}

void list_events(){
    printf("\n--- %sEventos futuros%s ---\n", CLR_CYAN, CLR_RESET);
    if (n_events==0){ printf("Nenhum evento cadastrado.\n"); return; }
    for (int i=0;i<n_events;i++){
        printf("[%d] %s | Data/Hora: %s | Local: %s | No local: %s\n", events[i].id, events[i].title, events[i].datetime, events[i].location, dests[events[i].dest_id].name);
    }
}

/* How to get: GPS or hotel */
void how_to_get(){
    printf("\nDeseja usar:\n1) GPS (digitar suas coordenadas)\n2) Hotel (escolher hotel)\nEscolha: ");
    int opt = read_int();
    if (opt != 1 && opt != 2){ printf("Opção inválida.\n"); return; }
    int start = 0;
    if (opt == 1){
        double lat, lon;
        printf("Latitude (ex: -3.1170): "); lat = read_double(); if (isnan(lat)){ printf("Inválido.\n"); return; }
        printf("Longitude (ex: -60.0220): "); lon = read_double(); if (isnan(lon)){ printf("Inválido.\n"); return; }
        double bestd = 1e18;
        for (int i=0;i<n_dest;i++){
            double d = haversine(lat, lon, dests[i].lat, dests[i].lon);
            if (d < bestd){ bestd = d; start = i; }
        }
    } else {
        printf("\nHotéis disponíveis:\n");
        for (int i=0;i<n_hotels;i++) printf("[%d] %s\n", hotels[i].id, hotels[i].name);
        printf("Escolha ID do hotel: ");
        int hid = read_int();
        if (hid<0 || hid>=n_hotels){ printf("Hotel inválido.\n"); return; }
        double bestd = 1e18;
        for (int i=0;i<n_dest;i++){
            double d = haversine(hotels[hid].lat, hotels[hid].lon, dests[i].lat, dests[i].lon);
            if (d < bestd){ bestd = d; start = i; }
        }
    }
    list_all();
    printf("Escolha ID do destino: ");
    int did = read_int();
    if (did<0||did>=n_dest){ printf("Destino inválido.\n"); return; }
    int dist[MAX_DEST], prev[MAX_DEST];
    dijkstra(start, dist, prev);
    if (dist[did] >= INF){ printf("Rota não encontrada.\n"); return; }
    printf("\nRota sugerida (ponto de acesso inicial: %s):\n", dests[start].name);
    print_path(prev, did);
    printf("Distância aproximada (entre pontos): %.2f km\n", haversine(dests[start].lat,dests[start].lon,dests[did].lat,dests[did].lon));
}

/* Export CSV for Canva */
void export_canva(const char *file){
    FILE *f = fopen(file,"w");
    if (!f){ printf("Erro ao criar %s\n", file); return; }
    fprintf(f,"name,category,address,hours,price,description\n");
    for (int i=0;i<n_dest;i++){
        char pricebuf[64];
        if (dests[i].price>0.0) snprintf(pricebuf,sizeof(pricebuf),"R$ %.2f", dests[i].price);
        else snprintf(pricebuf,sizeof(pricebuf),"Gratuito");
        /* escape quotes in desc */
        char desc_safe[MAX_DESC*2]; int k=0;
        for (int p=0;p<(int)strlen(dests[i].description) && k < (int)sizeof(desc_safe)-2; p++){
            if (dests[i].description[p] == '"'){ desc_safe[k++] = '"'; desc_safe[k++] = '"'; }
            else desc_safe[k++] = dests[i].description[p];
        }
        desc_safe[k]=0;
        fprintf(f,"\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n",
            dests[i].name, dests[i].category, dests[i].address, dests[i].hours, pricebuf, desc_safe);
    }
    fclose(f);
    printf("Exportado para %s\n", file);
}

/* Load all persistent */
void load_all(){ load_users(); load_ratings(); load_events(); }

/* Menu */
void menu(){
    int opt = -1;
    while (opt != 0){
        print_title();
        printf("\nMenu:\n");
        printf(CLR_BLUE "1) Cadastrar usuário\n" CLR_RESET);
        printf(CLR_YELLOW "2) Locais históricos (horário / endereço / valores)\n" CLR_RESET);
        printf(CLR_GREEN "3) Restaurantes e lanches / Bares\n" CLR_RESET);
        printf(CLR_MAGENTA "4) Avaliar e classificar um local\n" CLR_RESET);
        printf(CLR_RED "5) Informações de periculosidade do centro\n" CLR_RESET);
        printf(CLR_CYAN "6) Eventos futuros (listar / adicionar)\n" CLR_RESET);
        printf("7) Como chegar (GPS / Hotel)\n");
        printf("8) Exportar CSV para Canva\n");
        printf("0) Sair\n");
        printf("Escolha: ");
        if (scanf("%d",&opt) != 1){ clear_stdin(); opt = -1; }
        clear_stdin();
        if (opt == 1) register_user();
        else if (opt == 2) list_by_category("Historico");
        else if (opt == 3){
            printf("\n1) Restaurantes e lanches\n2) Bares\nEscolha: ");
            int c = read_int();
            if (c==1) list_by_category("Restaurante");
            else if (c==2) list_by_category("Bar");
            else printf("Opção inválida.\n");
        }
        else if (opt == 4) rate_place();
        else if (opt == 5){
            printf("\n--- Áreas com alertas de segurança ---\n");
            for (int i=0;i<n_dest;i++){
                if (dests[i].danger){
                    printf(CLR_RED "[%d] %s - %s - %s\n" CLR_RESET, dests[i].id, dests[i].name, dests[i].address, dests[i].hours);
                }
            }
        }
        else if (opt == 6){
            printf("\n1) Listar eventos\n2) Adicionar evento\nEscolha: ");
            int e = read_int();
            clear_stdin();
            if (e==1) list_events();
            else if (e==2) add_event();
            else printf("Opção inválida.\n");
        }
        else if (opt == 7) how_to_get();
        else if (opt == 8) export_canva("canva_export.csv");
        else if (opt == 0) { printf("Saindo... Até breve!\n"); }
        else printf("Opção inválida.\n");
        printf("\nPressione ENTER para continuar..."); getchar();
    }
}

int main(){
    seed_data();
    load_all();
    printf("Iniciando NavegAmazon...\n");
    menu();
    return 0;
}
