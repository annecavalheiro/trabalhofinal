/* Navegantes - Guia Turístico (Console em C)
   Autor: Gerado por assistente
   Usuário padrão: Manauara
   Funcionalidades:
    - Guiar Manauaras sobre o centro de Manaus
    - Interação simulada com GPS (entrada de coordenadas)
    - Cadastro de usuários (users.csv)
    - Locais: históricos (com tabela de valores), restaurantes, bares
    - Avaliação/nota por usuário (ratings.csv)
    - Eventos futuros (events.csv)
    - Como chegar (rota aproximada a partir de hotéis)
   Compilar: gcc -o navegantes Navegantes_main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_DEST 80
#define MAX_NAME 120
#define MAX_DESC 512
#define MAX_CAT 50
#define INF 1000000000
#define MAX_USERS 300
#define MAX_RATINGS 1000
#define MAX_EVENTS 200
#define MAX_LINE 1024

typedef struct {
    int id;
    char name[MAX_NAME];
    char category[MAX_CAT]; /* "Historico", "Restaurante", "Bar" */
    char description[MAX_DESC];
    char hours[100];
    double lat, lon;
    double price; /* entrada / valor tabelado (apenas para historicos; 0 se não aplicável) */
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
    char datetime[100]; /* data e hora */
    char location[120];
} Event;

/* Dados em memória */
Destination dests[MAX_DEST]; int n_dest = 0;
int adj[MAX_DEST][MAX_DEST];
User users[MAX_USERS]; int n_users = 0;
Rating ratings[MAX_RATINGS]; int n_ratings = 0;
Event events[MAX_EVENTS]; int n_events = 0;

/* Hotéis (origens aproximadas) */
typedef struct { int id; char name[120]; double lat, lon; } Hotel;
Hotel hotels[10]; int n_hotels = 0;

/* ---------- utilitários ---------- */

void init_graph() {
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

char *strcasestr_local(const char *hay, const char *needle){
    if (!*needle) return (char*)hay;
    for (; *hay; hay++){
        const char *h=hay, *n=needle;
        while (*h && *n && (tolower((unsigned char)*h) == tolower((unsigned char)*n))){
            h++; n++;
        }
        if (!*n) return (char*)hay;
    }
    return NULL;
}

/* ---------- persistência ---------- */

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

/* ---------- seed data (Manaus - Centro) ---------- */

void add_destination(const char *name,const char *cat,const char *desc,const char *hours,double lat,double lon,double price){
    if (n_dest >= MAX_DEST) return;
    dests[n_dest].id = n_dest;
    strncpy(dests[n_dest].name, name, MAX_NAME-1);
    strncpy(dests[n_dest].category, cat, MAX_CAT-1);
    strncpy(dests[n_dest].description, desc, MAX_DESC-1);
    strncpy(dests[n_dest].hours, hours, 99);
    dests[n_dest].lat = lat; dests[n_dest].lon = lon;
    dests[n_dest].price = price;
    n_dest++;
}

void seed_data(){
    init_graph();
    n_dest=0; n_hotels=0; n_users=0; n_ratings=0; n_events=0;
    add_destination("Teatro Amazonas", "Historico", "Teatro histórico do ciclo da borracha, visitas guiadas.", "09:00-17:00", -3.1019, -60.0250, 10.0);
    add_destination("Palácio Rio Negro", "Historico", "Antiga residência do governo, agora espaço cultural.", "09:00-17:00", -3.1045, -60.0190, 0.0);
    add_destination("Museu do Indio", "Historico", "Acervo etnográfico sobre povos indígenas.", "09:00-16:00", -3.0970, -60.0240, 5.0);
    add_destination("Restaurante Regional - Centro", "Restaurante", "Pratos regionais: tacacá, tambaqui, cupuaçu.", "11:00-23:00", -3.1185, -60.0230, 0.0);
    add_destination("Lanches Rápidos - Praça", "Restaurante", "Lanchonetes e pratos rápidos.", "08:00-22:00", -3.1188, -60.0215, 0.0);
    add_destination("Bar do Porto", "Bar", "Bar tradicional com música local.", "17:00-02:00", -3.1175, -60.0220, 0.0);
    add_destination("Beco Perigoso - Atenção", "Bar", "Área com alerta noturno: evite andar sozinho à noite.", "24h (evitar à noite)", -3.1160, -60.0240, 0.0);
    add_destination("Ponto de Informações - Praça Central", "Info", "Posto de informações turísticas.", "08:00-18:00", -3.1180, -60.0210, 0.0);

    for (int i=0;i<n_dest;i++){
        for (int j=0;j<n_dest;j++){
            if (i==j) adj[i][j]=0;
            else {
                double d = haversine(dests[i].lat, dests[i].lon, dests[j].lat, dests[j].lon);
                int cost = (int) (d * 10) + 5;
                adj[i][j] = cost;
            }
        }
    }

    hotels[n_hotels].id = n_hotels; strncpy(hotels[n_hotels].name, "Hotel Centro Plaza", 119); hotels[n_hotels].lat = -3.1170; hotels[n_hotels].lon = -60.0220; n_hotels++;
    hotels[n_hotels].id = n_hotels; strncpy(hotels[n_hotels].name, "Hotel Amazonas Inn", 119); hotels[n_hotels].lat = -3.1050; hotels[n_hotels].lon = -60.0260; n_hotels++;
}

/* ---------- Dijkstra para rotas ---------- */

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
/* ---------- listagens / detalhes / busca / usuários / avaliações ---------- */

void list_all(){
    printf("\n--- Todos os locais ---\n");
    for (int i=0;i<n_dest;i++){
        if (dests[i].price > 0.0)
            printf("[%d] %s | %s | Horário: %s | Valor: R$ %.2f\n", dests[i].id, dests[i].name, dests[i].category, dests[i].hours, dests[i].price);
        else
            printf("[%d] %s | %s | Horário: %s | Valor: Gratuito/Não aplicável\n", dests[i].id, dests[i].name, dests[i].category, dests[i].hours);
    }
}

void list_by_category(const char *cat){
    printf("\n--- Locais na categoria: %s ---\n", cat);
    int found=0;
    for (int i=0;i<n_dest;i++){
        if (strcasecmp(dests[i].category, cat)==0){
            if (dests[i].price > 0.0)
                printf("[%d] %s | Horário: %s | Valor: R$ %.2f\n", dests[i].id, dests[i].name, dests[i].hours, dests[i].price);
            else
                printf("[%d] %s | Horário: %s | Valor: Gratuito/Não aplicável\n", dests[i].id, dests[i].name, dests[i].hours);
            found++;
        }
    }
    if (!found) printf("Nenhum local encontrado nesta categoria.\n");
}

void show_details(int id){
    if (id<0 || id>=n_dest){ printf("ID inválido.\n"); return; }
    Destination *d = &dests[id];
    printf("\n=== %s ===\n", d->name);
    printf("Categoria: %s\n", d->category);
    printf("Descrição: %s\n", d->description);
    printf("Horário: %s\n", d->hours);
    if (d->price>0) printf("Valor de entrada: R$ %.2f\n", d->price);
    else printf("Entrada: Gratuita / Não aplicável\n");
    /* avaliações resumidas */
    int count=0; double sum=0;
    for (int i=0;i<n_ratings;i++){
        if (ratings[i].dest_id == id){
            printf("- Usuário %d: nota %d. %s\n", ratings[i].user_id, ratings[i].rating, ratings[i].comment);
            sum += ratings[i].rating; count++;
        }
    }
    if (count>0) printf("Média: %.2f (%d avaliações)\n", sum/count, count);
    else printf("Nenhuma avaliação ainda.\n");
}

/* ---------- usuários / registro / busca ---------- */

int find_user_by_username(const char *uname){
    for (int i=0;i<n_users;i++) if (strcmp(users[i].username, uname)==0) return users[i].id;
    return -1;
}

void register_user(){
    if (n_users >= MAX_USERS){ printf("Limite de usuários atingido.\n"); return; }
    char uname[50], fname[120];
    printf("Escolha um nome de usuário (sem espaços): ");
    if (scanf("%49s", uname) != 1){ while(getchar()!='\n'); printf("Entrada inválida.\n"); return; }
    while(getchar()!='\n');
    if (find_user_by_username(uname) != -1){ printf("Usuário já existe.\n"); return; }
    printf("Nome completo: ");
    fgets(fname, sizeof(fname), stdin); fname[strcspn(fname, "\n")] = 0;
    users[n_users].id = n_users;
    strncpy(users[n_users].username, uname, sizeof(users[n_users].username)-1);
    strncpy(users[n_users].fullname, fname, sizeof(users[n_users].fullname)-1);
    n_users++;
    save_users();
    printf("Usuário cadastrado com id %d.\n", n_users-1);
}

/* ---------- avaliações ---------- */

void rate_place(){
    if (n_users==0){ printf("Cadastre-se primeiro.\n"); return; }
    char uname[50];
    printf("Informe seu nome de usuário: "); if (scanf("%49s", uname) != 1){ while(getchar()!='\n'); printf("Entrada inválida.\n"); return; }
    while(getchar()!='\n');
    int uid = find_user_by_username(uname);
    if (uid == -1){ printf("Usuário não encontrado.\n"); return; }
    list_all();
    int did; printf("Escolha ID do local a avaliar: "); if (scanf("%d",&did) != 1){ while(getchar()!='\n'); printf("Entrada inválida.\n"); return; }
    while(getchar()!='\n');
    if (did<0 || did>=n_dest){ printf("Destino inválido.\n"); return; }
    int rt; printf("Nota (1-5): "); if (scanf("%d",&rt) != 1){ while(getchar()!='\n'); printf("Entrada inválida.\n"); return; }
    while(getchar()!='\n');
    if (rt<1 || rt>5){ printf("Nota inválida.\n"); return; }
    char comment[256]; printf("Comentário (opcional): "); fgets(comment, sizeof(comment), stdin); comment[strcspn(comment, "\n")] = 0;
    ratings[n_ratings].user_id = uid; ratings[n_ratings].dest_id = did; ratings[n_ratings].rating = rt; strncpy(ratings[n_ratings].comment, comment, 255); n_ratings++;
    save_ratings();
    printf("Avaliação registrada. Obrigado!\n");
}

/* ---------- eventos ---------- */

void add_event(){
    if (n_events >= MAX_EVENTS){ printf("Limite de eventos atingido.\n"); return; }
    char title[120]; int did; char dt[100]; char loc[120];
    printf("Título do evento: "); fgets(title, sizeof(title), stdin); title[strcspn(title,"\n")] = 0;
    printf("ID do local (veja lista):\n"); list_all(); printf("ID: "); if (scanf("%d",&did) != 1){ while(getchar()!='\n'); printf("Entrada inválida.\n"); return; }
    while(getchar()!='\n');
    if (did<0 || did>=n_dest){ printf("ID de local inválido.\n"); return; }
    printf("Data e hora (ex: 2025-11-20 19:00): "); fgets(dt, sizeof(dt), stdin); dt[strcspn(dt,"\n")] = 0;
    printf("Local (texto): "); fgets(loc, sizeof(loc), stdin); loc[strcspn(loc,"\n")] = 0;
    events[n_events].id = n_events; strncpy(events[n_events].title, title, 119); events[n_events].dest_id = did;
    strncpy(events[n_events].datetime, dt, 99); strncpy(events[n_events].location, loc, 119); n_events++;
    save_events();
    printf("Evento adicionado.\n");
}

void list_events(){
    printf("\n--- Eventos futuros ---\n");
    if (n_events==0){ printf("Nenhum evento cadastrado.\n"); return; }
    for (int i=0;i<n_events;i++){
        printf("[%d] %s | Local: %s | Data/Hora: %s | No local: %s\n", events[i].id, events[i].title, events[i].location, events[i].datetime, dests[events[i].dest_id].name);
    }
}

/* ---------- como chegar (GPS / hotéis) ---------- */

void how_to_get(){
    printf("\nDeseja usar:\n1) GPS (inserir suas coordenadas)\n2) Escolher hotel como origem\nEscolha: ");
    int opt; if (scanf("%d",&opt) != 1){ while(getchar()!='\n'); printf("Entrada inválida.\n"); return; }
    while(getchar()!='\n');
    double lat, lon;
    int start = 0;
    if (opt==1){
        printf("Insira sua latitude (ex: -3.1170): "); if (scanf("%lf",&lat) != 1){ while(getchar()!='\n'); printf("Inválido.\n"); return; }
        printf("Insira sua longitude (ex: -60.0220): "); if (scanf("%lf",&lon) != 1){ while(getchar()!='\n'); printf("Inválido.\n"); return; }
        while(getchar()!='\n');
        double bestd = 1e18; for (int i=0;i<n_dest;i++){ double d = haversine(lat,lon,dests[i].lat,dests[i].lon); if (d < bestd){ bestd = d; start = i; } }
    } else {
        printf("Hotéis:\n"); for (int i=0;i<n_hotels;i++) printf("[%d] %s\n", hotels[i].id, hotels[i].name);
        int hid; printf("Escolha ID do hotel: "); if (scanf("%d",&hid) != 1){ while(getchar()!='\n'); printf("Inválido.\n"); return; }
        if (hid<0 || hid>=n_hotels){ printf("Hotel inválido.\n"); return; }
        while(getchar()!='\n');
        double bestd = 1e18; for (int i=0;i<n_dest;i++){ double d = haversine(hotels[hid].lat,hotels[hid].lon,dests[i].lat,dests[i].lon); if (d < bestd){ bestd = d; start = i; } }
    }
    list_all();
    int did; printf("Escolha ID do destino: "); if (scanf("%d",&did) != 1){ while(getchar()!='\n'); printf("Inválido.\n"); return; }
    if (did<0 || did>=n_dest){ printf("Destino inválido.\n"); return; }
    int dist[MAX_DEST], prev[MAX_DEST]; dijkstra(start, dist, prev);
    if (dist[did] >= INF){ printf("Rota não encontrada.\n"); return; }
    printf("Rota sugerida (ponto de acesso inicial: %s):\n", dests[start].name);
    print_path(prev, did);
    printf("Distância aproximada entre pontos: %.2f km\n", haversine(dests[start].lat,dests[start].lon,dests[did].lat,dests[did].lon));
}

/* ---------- export para Canva (CSV) ---------- */

void export_canva(const char *file){
    FILE *f = fopen(file,"w");
    if (!f){ printf("Erro ao criar arquivo %s\n", file); return; }
    fprintf(f,"name,category,description,hours,price\n");
    for (int i=0;i<n_dest;i++){
        char pricebuf[32];
        if (dests[i].price > 0.0) snprintf(pricebuf, sizeof(pricebuf), "R$ %.2f", dests[i].price);
        else strncpy(pricebuf, "Gratuito", sizeof(pricebuf));
        /* escape simples: trocar aspas internas por aspas duplas */
        char desc_safe[MAX_DESC*2]; int k=0;
        for (int p=0; p < (int)strlen(dests[i].description) && k < (int)sizeof(desc_safe)-2; p++){
            if (dests[i].description[p] == '"'){ desc_safe[k++] = '"'; desc_safe[k++] = '"'; }
            else desc_safe[k++] = dests[i].description[p];
        }
        desc_safe[k] = '\0';
        fprintf(f,"\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n", dests[i].name, dests[i].category, desc_safe, dests[i].hours, pricebuf);
    }
    fclose(f);
    printf("Exportado para %s\n", file);
}

/* ---------- menu e main ---------- */

void load_all(){ load_users(); load_ratings(); load_events(); }

void menu(){
    int opt = -1;
    while (opt != 0){
        printf("\n--- Navegantes - Guia do Centro (Manauara) ---\n");
        printf("1) Listar todos locais\n");
        printf("2) Listar por categoria\n");
        printf("3) Mostrar detalhes de um local\n");
        printf("4) Como chegar (GPS )\n");
        printf("5) Cadastrar usuário\n");
        printf("6) Avaliar e classificar um local\n");
        printf("7) Eventos futuros (listar/adicionar)\n");
        printf("8) Exportar para Canva (canva_export.csv)\n");
        printf("9) Listar avaliações de um local\n");
        printf("0) Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opt) != 1){ while(getchar()!='\n'); opt=-1; }
        while(getchar()!='\n');
        if (opt==1) list_all();
        else if (opt==2){
            int catOpt=0;
            printf("\n--- Escolha uma categoria ---\n");
            printf("1) Locais históricos\n");
            printf("2) Restaurantes e lanches\n");
            printf("3) Bares\n");
            printf("4) Pontos de informação\n");
            printf("Opção: "); if (scanf("%d", &catOpt) != 1){ while(getchar()!='\n'); printf("Entrada inválida.\n"); continue; }
            while(getchar()!='\n');
            switch(catOpt){
                case 1: list_by_category("Historico"); break;
                case 2: list_by_category("Restaurante"); break;
                case 3: list_by_category("Bar"); break;
                case 4: list_by_category("Info"); break;
                default: printf("Categoria inválida.\n"); break;
            }
        }
        else if (opt==3){
            int id; printf("ID do local: "); if (scanf("%d", &id)!=1){ while(getchar()!='\n'); printf("Entrada inválida.\n"); continue; } show_details(id);
        }
        else if (opt==4) how_to_get();
        else if (opt==5) register_user();
        else if (opt==6) rate_place();
        else if (opt==7){
            int eopt=0;
            printf("1) Listar eventos\n2) Adicionar evento\nEscolha: "); if (scanf("%d", &eopt) != 1){ while(getchar()!='\n'); printf("Entrada inválida.\n"); continue; }
            while(getchar()!='\n');
            if (eopt==1) list_events(); else if (eopt==2) add_event(); else printf("Opção inválida.\n");
        }
        else if (opt==8) export_canva("canva_export.csv");
        else if (opt==9){ int id; printf("ID do local: "); if (scanf("%d", &id)!=1){ while(getchar()!='\n'); printf("Entrada inválida.\n"); continue; } show_details(id); }
        else if (opt==0) printf("Saindo...\n");
        else printf("Opção inválida.\n");
    }
}

int main(){
    seed_data();
    load_all();
    printf("\033[1;34m=== NAVEGANTES - GUIA DO CENTRO ===\033[0m\n");
    printf("%d locais carregados.\n", n_dest);
    menu();
    return 0;
}
