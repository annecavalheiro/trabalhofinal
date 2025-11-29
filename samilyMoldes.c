/* navegamazon_eventos.c
   NavegAmazon - Eventos no Centro de Manaus
   Projeto final em C (consulta de eventos apenas)
   Funcionalidades:
    - Listagem de locais do centro de Manaus
    - Listagem de eventos reais pré-cadastrados
   Compilar: gcc -o navegamazon_eventos navegamazon_eventos.c
*/

#include <stdio.h>
#include <string.h>

#define MAX_DEST 20
#define MAX_EVENTS 50
#define MAX_NAME 120
#define MAX_DESC 512

/* ANSI colors */
#define CLR_RESET "\033[0m"
#define CLR_RED "\033[1;31m"
#define CLR_GREEN "\033[1;32m"
#define CLR_YELLOW "\033[1;33m"
#define CLR_CYAN "\033[1;36m"
#define CLR_WHITE "\033[1;37m"

/* Estruturas */
typedef struct {
    int id;
    char name[MAX_NAME];
    char category[40]; /* Historico, Restaurante, Bar, Info, Perigoso */
    char address[200];
    char hours[80];
    char description[MAX_DESC];
} Destination;

typedef struct {
    int id;
    char title[120];
    int dest_id;
    char datetime[80];
    char location[120];
} Event;

/* Dados pré-cadastrados */
Destination dests[MAX_DEST] = {
    {0, "Teatro Amazonas", "Historico", "Praça São Sebastião, Centro", "09:00-17:00", "Teatro do ciclo da borracha; visitas guiadas."},
    {1, "Palácio Rio Negro", "Historico", "Av. Sete de Setembro, Centro", "09:00-16:00", "Espaço cultural com exibições."},
    {2, "Praça Dom Pedro II", "Historico", "Centro", "08:00-20:00", "Praça central histórica de Manaus."},
    {3, "Museu do Índio", "Historico", "Rua do Comércio, Centro", "09:00-16:00", "Acervo etnográfico sobre povos indígenas."}
};
int n_dest = 4;

Event events[MAX_EVENTS] = {
    {0, "Apresentação do Amazonas Jazz Festival", 0, "2025-11-20 19:00", "Teatro Amazonas"},
    {1, "Exposição de Arte Indígena", 3, "2025-11-25 10:00", "Museu do Índio"},
    {2, "Concerto Sinfônico Manaus", 0, "2025-12-05 20:00", "Teatro Amazonas"},
    {3, "Feira de Artesanato Local", 2, "2025-12-10 09:00", "Praça Dom Pedro II"},
    {4, "Visita Guiada ao Palácio Rio Negro", 1, "2025-12-15 14:00", "Palácio Rio Negro"}
};
int n_events = 5;

/* Funções de listagem */
void list_destinations(){
    printf("\n--- %sLocais do Centro de Manaus%s ---\n", CLR_YELLOW, CLR_RESET);
    for(int i=0;i<n_dest;i++){
        printf("[%d] %s | Categoria: %s | Horário: %s | Endereço: %s\nDescrição: %s\n\n",
            dests[i].id, dests[i].name, dests[i].category, dests[i].hours, dests[i].address, dests[i].description);
    }
}

void list_events(){
    printf("\n--- %sEventos Futuros no Centro de Manaus%s ---\n", CLR_CYAN, CLR_RESET);
    if(n_events==0){ printf("Nenhum evento cadastrado.\n"); return; }
    for(int i=0;i<n_events;i++){
        printf("[%d] %s\n  Local: %s (%s)\n  Data/Hora: %s\n\n",
            events[i].id, events[i].title, dests[events[i].dest_id].name, dests[events[i].dest_id].category, events[i].datetime);
    }
}

/* Menu */
void menu(){
    int opt = -1;
    while(opt != 0){
        printf("\n--- %sNavegAmazon: Eventos Centro de Manaus%s ---\n", CLR_RED, CLR_RESET);
        printf("1) Listar locais do centro\n");
        printf("2) Listar eventos futuros\n");
        printf("0) Sair\n");
        printf("Escolha: ");
        if(scanf("%d",&opt)!=1){ opt=-1; }
        getchar(); // limpar buffer
        switch(opt){
            case 1: list_destinations(); break;
            case 2: list_events(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida.\n"); break;
        }
    }
}

/* Main */
int main(){
    printf("%sBem-vindo ao NavegAmazon - Eventos do Centro de Manaus%s\n", CLR_GREEN, CLR_RESET);
    menu();
    return 0;
}