lude <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"
#define MAX_LOCAIS 50
#define MAX_COMENTARIO 100
#define MAX_TELEFONES 3
#define MAX_TIPOS 10
#define MAX_NOME 100

typedef enum {
    PATRIMONIO_HISTORICO = 1,
    CULTURAL = 2,
    IGREJA = 3,
    GASTRONOMIA = 4,
    CULINARIA_BRASILEIRA = 5,
    CULINARIA_REGIONAL = 6,
    INDIGENA = 7,
    BAR = 8,
    RESTAURANTE = 9,
    MERCADO = 10,
    MUSEU = 11,
    CINEMA = 12,
    UNIDADE_SAUDE_PUBLICA = 13,
    OUTRO = 14
} TipoDeLugar;

typedef struct {
    char rua[100];
    char cep[20];
} Endereco;

typedef struct {
    char telefones[MAX_TELEFONES][20];
    int qtdeTelefone;
    char email[100];
    char site[100];
} Contato;

typedef struct {
    char autor[50];
    char texto[500];
    float nota;
} Comentario;

typedef struct {
    char nome[100];
    char descricao[500];
    Endereco endereco;
    Contato contato;
    float ranking;
    TipoDeLugar tipos[MAX_TIPOS];
    int qtdTipos;
    float entrada;
    Comentario comentarios[MAX_COMENTARIO];
    int numComentarios;
} Local;

Local listaLugares[MAX_LOCAIS];
int numLugares = 0;

/* prototipos */
void inserirLugar();
void listarLugares();
const char* obterNomeTipoDeLugar(TipoDeLugar tipo);
TipoDeLugar obterEnumTipoDeLugar(int opcao);
void limparBuffer();
void limparTela();
void pressioneEnter();
void salvarTxt(const char *nome_arquivo);
void carregarTxt(const char *nome_arquivo);
void trim_nl(char *s);
void filtrarPorCategoria();
void cadastrarUsuario();
int login();
int loginAdmin();
void menuUsuario();
void menuAdmin();
int menuInicial();
void iconecomentarios();


void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void cabecalho() {
    printf(GREEN"\t\t                                                                    #           \n");
    printf("\t\t                                                                    ###              \n");
    printf("\t\t                                                                    #####            \n");
    printf("\t\t                                                                    #######          \n");
    printf("\t\t                                                                    #####            \n");
    printf("\t\t                                                                    ###              \n");
    printf("\t\t                                                                    #                \n");
    printf("\t\t                                                                    #                \n");
    printf("\t\t                                                                    #                \n");

    printf("\t\t                                            "RED"*"GREEN"                     "RED"*"GREEN"                  \n");
    printf("\t\t                                           "RED"*"GREEN" "RED"*"GREEN"                   "RED"*"GREEN"                   \n");
    printf("\t\t                                          "RED"*"GREEN"   "RED"*"GREEN"                 "RED"*"GREEN"                    \n");
    printf("\t\t                                         "RED"*"GREEN"     "RED"*"GREEN"               "RED"*"GREEN"                     \n");
    printf("\t\t                                        "RED"*"GREEN"       "RED"*"GREEN"             "RED"*"GREEN"                      \n");
    printf("\t\t                                       "RED"*"GREEN"         "RED"*"GREEN"           "RED"*"GREEN"                       \n");
    printf("\t\t                          #####       "RED"*"GREEN"           "RED"*"GREEN"         "RED"*"GREEN"                        \n");
    printf("\t\t                        ##     ##    "RED"*"GREEN"             "RED"*"GREEN"       "RED"*"GREEN"                         \n");
    printf("\t\t                        ##     ##   "RED"*"GREEN"               "RED"*"GREEN"     "RED"*"GREEN"                          \n");
    printf("\t\t                          #####    "RED"*"GREEN"                 "RED"*"GREEN"   "RED"*"GREEN"                           \n");
    printf("\t\t                           ###    "RED"*"GREEN"                   "RED"*"GREEN" "RED"*"GREEN"                            \n");
    printf("\t\t                            #    "RED"*"GREEN"                     "RED"*"GREEN"                             \n");
    printf("\n");
    printf(GREEN"\t\t                         "RED"N"GREEN"AVEG"RED"A"GREEN"MAZON - GUIA TURISTICO (CENTRO DE MANAUS)\n"RESET);
}

void iconecadastrousuario () {
    printf("\t\t\t\t\t          "RESET"##########"GREEN"    ##        \n");
    printf("\t\t\t\t\t       "RESET"####             "GREEN"##        \n");
    printf("\t\t\t\t\t     "RESET"###    "RED"######   "GREEN"########     \n");
    printf("\t\t\t\t\t    "RESET"##     "RED"#      #     "GREEN"##        \n");
    printf("\t\t\t\t\t  "RESET"###     "RED"#        #    "GREEN"##        \n");
    printf("\t\t\t\t\t  "RESET"#      "RED"#          #             \n");
    printf("\t\t\t\t\t "RESET"##      "RED"#          #      "RESET"##     \n");
    printf("\t\t\t\t\t"RESET"##        "RED"#        #        "RESET"##    \n");
    printf("\t\t\t\t\t"RESET"#          "RED"#      #          "RESET"#    \n");
    printf("\t\t\t\t\t"RESET"#           "RED"######           "RESET"#    \n");
    printf("\t\t\t\t\t"RESET"#         "RED"#        #         "RESET"#    \n");
    printf("\t\t\t\t\t"RESET"#        "RED"#          #        "RESET"#    \n");
    printf("\t\t\t\t\t"RESET"##      "RED"#            #      "RESET"##    \n");
    printf("\t\t\t\t\t "RESET"##    "RED"#              #    "RESET"##     \n");
    printf("\t\t\t\t\t  "RESET"#   "RED"#                #   "RESET"#      \n");
    printf("\t\t\t\t\t  "RESET"## "RED"#                  #"RESET" ##      \n");
    printf("\t\t\t\t\t    "RESET"##                  "RESET"##        \n");
    printf("\t\t\t\t\t     "RESET"###              "RESET"###         \n");
    printf("\t\t\t\t\t       "RESET"####        "RESET"####           \n");
    printf("\t\t\t\t\t          "RESET"##########              \n");
    printf("\n");
}

void iconelogin(){
    printf("\t\t\t\t\t           ##########              \n");
    printf("\t\t\t\t\t        ####        ####           \n");
    printf("\t\t\t\t\t      ###    "RED"######    "RESET"###         \n");
    printf("\t\t\t\t\t     ##     "RED"#      #     "RESET"##        \n");
    printf("\t\t\t\t\t    ##     "RED"#        #     "RESET"###      \n");
    printf("\t\t\t\t\t          "RED"#          #      "RESET"#      \n");
    printf("\t\t\t\t\t     "GREEN"#    "RED"#          #      "RESET"##     \n");
    printf("\t\t\t\t\t      "GREEN"#    "RED"#        #        "RESET"##    \n");
    printf("\t\t\t\t\t      "GREEN"###   "RED"#      #          "RESET"#    \n");
    printf("\t\t\t\t\t"GREEN"###########  "RED"######           "RESET"#    \n");
    printf("\t\t\t\t\t      "GREEN"###  "RED"#       #         "RESET"#     \n");
    printf("\t\t\t\t\t      "GREEN"#   "RED"#          #        "RESET"#    \n");
    printf("\t\t\t\t\t     "GREEN"#   "RED"#            #      "RESET"##    \n");
    printf("\t\t\t\t\t        "RED"#              #    "RESET"##     \n");
    printf("\t\t\t\t\t       "RED"#                #   "RESET"#      \n");
    printf("\t\t\t\t\t   ###"RED"#                  #"RESET"###      \n");
    printf("\t\t\t\t\t     ##                  ##        \n");
    printf("\t\t\t\t\t      ###              ###         \n");
    printf("\t\t\t\t\t        ####        ####           \n");
    printf("\t\t\t\t\t           ##########              \n");
    printf("\n");
}

void iconeadministrador(){
    printf("\t\t\t\t\t             ##########              \n");
    printf("\t\t\t\t\t          ####        ####           \n");
    printf("\t\t\t\t\t        ###    "RED"######    "RESET"###         \n");
    printf("\t\t\t\t\t       ##     "RED"#      #     "RESET"##        \n");
    printf("\t\t\t\t\t     ###     "RED"#        #     "RESET"###      \n");
    printf("\t\t\t\t\t     #      "RED"#          #      "RESET"#      \n");
    printf("\t\t\t\t\t    ##      "RED"#          #      "RESET"##     \n");
    printf("\t\t\t\t\t   ##        "RED"#        #        "RESET"##    \n");
    printf("\t\t\t\t\t   #          "RED"#      #          "RESET"#    \n");
    printf("\t\t\t\t\t   #           "RED"######           "RESET"#    \n");
    printf("\t\t\t\t\t             "RED"#        #         "RESET"#    \n");
    printf("\t\t\t\t\t      "GREEN"###   "RED"#          #        "RESET"#    \n");
    printf("\t\t\t\t\t     "GREEN"#   #              "RED"#      "RESET"##    \n");
    printf("\t\t\t\t\t    "GREEN"#     ###########     "RED"#    "RESET"##    \n");
    printf("\t\t\t\t\t     "GREEN"#   #      # #        "RED"#   "RESET"#     \n");
    printf("\t\t\t\t\t      "GREEN"###       # #         "RED"#"RESET"##      \n");
    printf("\t\t\t\t\t                           ##        \n");
    printf("\t\t\t\t\t        ###              ###         \n");
    printf("\t\t\t\t\t          ####        ####           \n");
    printf("\t\t\t\t\t             ##########              \n");
    printf("\n");
}

void iconelistar(){
    printf("\t\t\t\t\t         "GREEN"########################            \n");
    printf("\t\t\t\t\t         "GREEN"#                      #            \n");
    printf("\t\t\t\t\t         "GREEN"#  "RED"##                  "GREEN"#\n");
    printf("\t\t\t\t\t         "GREEN"#  "RED"## ______________   "GREEN"#\n");
    printf("\t\t\t\t\t         "GREEN"#                      #            \n");
    printf("\t\t\t\t\t         "GREEN"#  "RED"##                  "GREEN"#\n");
    printf("\t\t\t\t\t         "GREEN"#  "RED"## ______________   "GREEN"#\n");
    printf("\t\t\t\t\t         "GREEN"#                      #            \n");
    printf("\t\t\t\t\t         "GREEN"#  "RED"##                  "GREEN"#\n");
    printf("\t\t\t\t\t         "GREEN"#  "RED"## ______________   "GREEN"#\n");
    printf("\t\t\t\t\t         "GREEN"#                      #            \n");
    printf("\t\t\t\t\t         "GREEN"#  "RED"##                  "GREEN"#\n");
    printf("\t\t\t\t\t         "GREEN"#  "RED"## ______________   "GREEN"#\n");
    printf("\t\t\t\t\t         "GREEN"#                      #            \n");
    printf("\t\t\t\t\t         "GREEN"#                      #            \n");
    printf("\t\t\t\t\t         "GREEN"#                      #            \n");
    printf("\t\t\t\t\t         "GREEN"########################            \n");
    printf("\n");
}

void iconefiltrar(){
	printf("\t\t\t\t\t                    "GREEN"##########    \n");
    printf("\t\t\t\t\t                    "GREEN"# "RED"______ "GREEN"#    \n");
    printf("\t\t\t\t\t                    "GREEN"# "RED"______ "GREEN"#    \n");
    printf("\t\t\t\t\t                    "GREEN"# "RED"______ "GREEN"#    \n");
    printf("\t\t\t\t\t                    "GREEN"#        "GREEN"#"RESET"    \n");
    printf("\t\t\t\t\t                  ##############  \n");
    printf("\t\t\t\t\t                   #          #   \n");
    printf("\t\t\t\t\t                    #        #    \n");
    printf("\t\t\t\t\t                     #      #     \n");
    printf("\t\t\t\t\t                      #    #      \n");
    printf("\t\t\t\t\t                       #  #       \n");
    printf("\t\t\t\t\t                       #  #       \n");
    printf("\t\t\t\t\t                       # /        \n");
    printf("\t\t\t\t\t                       #          \n");
    printf("\n");
}

void iconecomentarios(){
    printf("\t\t\t\t\t             "GREEN"###########    \n");
    printf("\t\t\t\t\t           "GREEN"#  "RED"________  "GREEN"#   \n");
    printf("\t\t\t\t\t          "GREEN"#   "RED"________   "GREEN"#  \n");
    printf("\t\t\t\t\t         "GREEN"#    "RED"________    "GREEN"# \n");
    printf("\t\t\t\t\t         "GREEN"#    "RED"________    "GREEN"# \n");
    printf("\t\t\t\t\t          "GREEN"#   "RED"________   "GREEN"#  \n");
    printf("\t\t\t\t\t           "GREEN"#            #   \n");
    printf("\t\t\t\t\t            "GREEN"#   ########    \n");
    printf("\t\t\t\t\t             "GREEN"#  #           \n");
    printf("\t\t\t\t\t              "GREEN"##            \n");
    printf("\t\t\t\t\t               "GREEN"#            \n");
    printf("\n");
}

void adicionarComentario() {
    iconecomentarios();
    if (numLugares == 0) {
        printf(RED"\nNenhum lugar cadastrado para comentar.\n"RESET);
        pressioneEnter();
        return;
    }

    listarLugares();
    printf("\n\t\t\t\tDigite o numero do lugar que deseja comentar: ");
    int opcao;

    if (scanf("%d", &opcao) != 1 || opcao < 1 || opcao > numLugares) {
        limparBuffer();
        printf(RED"Opcao invalida!\n"RESET);
        pressioneEnter();
        return;
    }
    limparBuffer();

    Local *l = &listaLugares[opcao - 1];

    if (l->numComentarios >= MAX_COMENTARIO) {
        printf(RED"Este local atingiu o limite de comentarios.\n"RESET);
        pressioneEnter();
        return;
    }

    Comentario *c = &l->comentarios[l->numComentarios];

    printf("\n\t\t\t\tAutor do comentario: ");
    fgets(c->autor, sizeof(c->autor), stdin);
    trim_nl(c->autor);

    printf("\t\t\t\tDigite seu comentario: ");
    fgets(c->texto, sizeof(c->texto), stdin);
    trim_nl(c->texto);

    printf("\t\t\t\tNota (0 a 5): ");
    if (scanf("%f", &c->nota) != 1 || c->nota < 0 || c->nota > 5) {
        limparBuffer();
        printf(RED"Nota invalida!\n"RESET);
        pressioneEnter();
        return;
    }
    limparBuffer();

    l->numComentarios++;

    // recalcular ranking 
    float soma = 0;
    for (int i = 0; i < l->numComentarios; i++) {
        soma += l->comentarios[i].nota;
    }
    l->ranking = soma / l->numComentarios;

    printf(GREEN"\nComentario adicionado com sucesso!\n"RESET);
    pressioneEnter();
}

void listarComentarios() {
    listarLugares();
    printf("\n\t\t\t\tEscolha o numero do lugar: ");
    int escolha;

    if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > numLugares) {
        limparBuffer();
        printf(RED"Opcao invalida!\n"RESET);
        return;
    }
    limparBuffer();
    limparTela();
    
    Local *l = &listaLugares[escolha - 1];

    printf(GREEN"\n\t\t\t\t\t=== Comentarios de %s ===\n\n"RESET, l->nome);

    if (l->numComentarios == 0) {
        printf("\t\t\t\t\tNenhum comentario ainda.\n");
        pressioneEnter();
        return;
    }

    for (int i = 0; i < l->numComentarios; i++) {
        Comentario *c = &l->comentarios[i];
        printf("\t\t\t\t\tAutor: %s\n", c->autor);
        printf("\t\t\t\t\tComentario: %s\n", c->texto);
        printf("\t\t\t\t\tNota: %.1f\n", c->nota);
        printf("\t\t\t\t\t--------------------------\n");
        pressioneEnter();
    }
    
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void trim_nl(char *s) {
    size_t len = strlen(s);
    if (len == 0) return;
    if (s[len-1] == '\n') s[len-1] = '\0';
}

const char* obterNomeTipoDeLugar(TipoDeLugar tipo) {
    switch(tipo) {
        case PATRIMONIO_HISTORICO: return "Patrimonio Historico";
        case CULTURAL: return "Cultural";
        case IGREJA: return "Igreja";
        case GASTRONOMIA: return "Gastronomia";
        case CULINARIA_BRASILEIRA: return "Culinaria Brasileira";
        case CULINARIA_REGIONAL: return "Culinaria Regional";
        case INDIGENA: return "Indigena";
        case BAR: return "Bar";
        case RESTAURANTE: return "Restaurante";
        case MERCADO: return "Mercado";
        case MUSEU: return "Museu";
        case CINEMA: return "Cinema";
        case UNIDADE_SAUDE_PUBLICA: return "Unidade Saude Publica";
        default: return "Outro";
    }
}

TipoDeLugar obterEnumTipoDeLugar(int opcao) {
    if (opcao >= 1 && opcao <= 14)
        return (TipoDeLugar)opcao;
    return OUTRO;
}

void filtrarPorCategoria() {
    iconefiltrar();
    if (numLugares == 0) {
        printf("\nNenhum lugar cadastrado.\n");
        pressioneEnter();
        return;
    }

    int opcao;

    printf("\n\t\t\t\t\t\t=== FILTRAR POR CATEGORIA ===\n");
    printf("\t\t\t   1 - Patrimonio Historico     6 - Culinaria Regional      11 - Museu\n");
    printf("\t\t\t   2 - Cultural                 7 - Indigena                12 - Cinema\n");
    printf("\t\t\t   3 - Igreja                   8 - Bar                     13 - Saude Publica\n");
    printf("\t\t\t   4 - Gastronomia              9 - Restaurante             14 - Outro\n");
    printf("\t\t\t   5 - Culinaria Brasileira     10 - Mercado\n");
    printf("\t\t\t   Escolha uma categoria: ");

    if (scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 14) {
        limparBuffer();
        printf("\nOpcao invalida!\n");
        pressioneEnter();
        return;
    }
    limparBuffer();

    TipoDeLugar categoriaEscolhida = obterEnumTipoDeLugar(opcao);
    int encontrados = 0;

    limparTela();
    printf("\n\t\t\t\t\t\t=== RESULTADOS DA BUSCA ===\n");

    for (int i = 0; i < numLugares; i++) {

        int temCategoria = 0;
        for (int t = 0; t < listaLugares[i].qtdTipos; t++) {
            if (listaLugares[i].tipos[t] == categoriaEscolhida) {
                temCategoria = 1;
                break;
            }
        }

        if (temCategoria) {
            printf("\n\t\t\t\t\t--- %s ---\n", listaLugares[i].nome);
            printf("\t\t\t\t\tDescricao: %s\n", listaLugares[i].descricao);
            printf("\t\t\t\t\tEndereco: %s, CEP %s\n",
                listaLugares[i].endereco.rua,
                listaLugares[i].endereco.cep);
            printf("\t\t\t\t\tEntrada: R$ %.2f\n", listaLugares[i].entrada);
            printf("\t\t\t\t\tRanking: %.1f\n", listaLugares[i].ranking);

            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("\nNenhum lugar encontrado para essa categoria.\n");
    }

    printf("\n");
    pressioneEnter();
}

void cadastrarUsuario() {
    limparTela();
    iconecadastrousuario();
    char usuario[50], senha[50];
    FILE *arq = fopen("usuarios.txt", "a");

    if (!arq) {
        printf(RED"Erro ao abrir o arquivo!\n"RESET);
        pressioneEnter();
        return;
    }

    printf(GREEN"\t\t\t\t\t  === CADASTRAR USUARIO ===\n\n"RESET);

    printf("\t\t\t\t\tUsuario: ");
    if (scanf("%49s", usuario) != 1) { limparBuffer(); fclose(arq); return; }

    printf("\t\t\t\t\tSenha: ");
    if (scanf("%49s", senha) != 1) { limparBuffer(); fclose(arq); return; }

    fprintf(arq, "%s %s\n", usuario, senha);
    fclose(arq);

    printf(GREEN"\nUsuario cadastrado com sucesso!\n"RESET);
    printf("Pressione ENTER para continuar...");
    limparBuffer();
    getchar();
}

void inserirLugar() {
    int retorno = 1;
    if (numLugares >= MAX_LOCAIS) {
        printf("\nLista cheia!\n");
        return;
    }
    
    Local novoLugar;
    int opcao, i;
    memset(&novoLugar, 0, sizeof(Local));

    printf("\n\t\t\t\t=== CADASTRO DE NOVO LUGAR ===\n");
    limparBuffer(); // garantir buffer limpo antes do fgets

    printf("\t\t\t\tNome do lugar: ");
    fgets(novoLugar.nome, sizeof(novoLugar.nome), stdin);
    trim_nl(novoLugar.nome);

    printf("\t\t\t\tDescricao: ");
    fgets(novoLugar.descricao, sizeof(novoLugar.descricao), stdin);
    trim_nl(novoLugar.descricao);

    printf("\n\t\t\t\t--- Endereco ---\n\t\t\t\tRua: ");
    fgets(novoLugar.endereco.rua, sizeof(novoLugar.endereco.rua), stdin);
    trim_nl(novoLugar.endereco.rua);

    printf("\t\t\t\tCEP: ");
    fgets(novoLugar.endereco.cep, sizeof(novoLugar.endereco.cep), stdin);
    trim_nl(novoLugar.endereco.cep);

    printf("\n\t\t\t\t--- Contato ---\n\t\t\t\tQuantos telefones? (max 3): ");
    if (scanf("%d", &novoLugar.contato.qtdeTelefone) != 1) novoLugar.contato.qtdeTelefone = 0;
    if (novoLugar.contato.qtdeTelefone > MAX_TELEFONES) novoLugar.contato.qtdeTelefone = MAX_TELEFONES;
    limparBuffer();

    for (i = 0; i < novoLugar.contato.qtdeTelefone; i++) {
        printf("\t\t\t\tTelefone %d: ", i + 1);
        fgets(novoLugar.contato.telefones[i], sizeof(novoLugar.contato.telefones[i]), stdin);
        trim_nl(novoLugar.contato.telefones[i]);
    }

    printf("\t\t\t\tE-mail: ");
    fgets(novoLugar.contato.email, sizeof(novoLugar.contato.email), stdin);
    trim_nl(novoLugar.contato.email);

    printf("\t\t\t\tSite: ");
    fgets(novoLugar.contato.site, sizeof(novoLugar.contato.site), stdin);
    trim_nl(novoLugar.contato.site);
	limparTela();
	printf("\n\t\t\t\t=== CADASTRO DE NOVO LUGAR ===\n");
	
    /* categorias multiplas */
    novoLugar.qtdTipos = 0;
    printf("\n\t\t\t\t--- Categorias do lugar --- \n");
    printf("\t\t\t\t1-Patrimonio Historico\n");
    printf("\t\t\t\t2-Cultural\n");
    printf("\t\t\t\t3-Igreja\n");
    printf("\t\t\t\t4-Gastronomia\n");
    printf("\t\t\t\t5-Culinaria Brasileira\n");
    printf("\t\t\t\t6-Culinaria Regional\n");
    printf("\t\t\t\t7-Indigena\n");
    printf("\t\t\t\t8-Bar\n");
    printf("\t\t\t\t9-Restaurante\n");
    printf("\t\t\t\t10-Mercado\n");
    printf("\t\t\t\t11-Museu\n");
    printf("\t\t\t\t12-Cinema\n");
    printf("\t\t\t\t13-Saude\n");
    printf("\t\t\t\t14-Outro\n\n");

	printf("\t\t\t\tEscolha a(s) categoria(s) - "RED"(informe uma ou \n\t\t\t\tmais categorias que se encaixam ao local. Para encerrar a \n\t\t\t\tinclusao de categorias, digite 0):\n"RESET"");
    while (1) {
    	printf("\t\t\t\tEscolha: ");
        if (scanf("%d", &opcao) != 1) { limparBuffer(); continue; }
        limparBuffer();

        if (opcao == 0) break;
        if (opcao < 0 || opcao > 14) {
            printf("Opcao invalida.\n");
            continue;
        }
        if (novoLugar.qtdTipos < MAX_TIPOS) {
            novoLugar.tipos[novoLugar.qtdTipos++] = obterEnumTipoDeLugar(opcao);
        } else {
            printf("Limite de categorias atingido!\n");
            break;
        }
    }

    novoLugar.ranking = 0.0f;
    novoLugar.numComentarios = 0;
    novoLugar.entrada = 0.0f;

    listaLugares[numLugares++] = novoLugar;
    printf(GREEN"\nLugar cadastrado com sucesso!\n"RESET);
}

int login() {
    
    limparTela();
    iconelogin();

    char usuario[50], senha[50], fileUser[50], filePass[50];
    FILE *arq = fopen("usuarios.txt", "r");

    printf(GREEN"\t\t\t\t\t\t === LOGIN ===\n\n"RESET);

    printf("\t\t\t\t\tUsuario: ");
    if (scanf("%49s", usuario) != 1) {
        limparBuffer();
        return 0;
    }

    printf("\t\t\t\t\tSenha: ");
    if (scanf("%49s", senha) != 1) {
        limparBuffer();
        return 0;
    }

    limparBuffer();

    //login admin
    if (strcmp(usuario, "admin") == 0) {
        if (strcmp(senha, "admin123") == 0) {
            return 2; // ADMIN
        } else {
            printf(RED"\nSenha do administrador incorreta!\n"RESET);
            pressioneEnter();
            return 0;
        }
    }

    // login usuario txt
    if (!arq) {
        printf(RED"\nArquivo de usuarios nao encontrado!\n"RESET);
        pressioneEnter();
        return 0;
    }

    while (fscanf(arq, "%49s %49s", fileUser, filePass) != EOF) {
        if (strcmp(usuario, fileUser) == 0 && strcmp(senha, filePass) == 0) {
            fclose(arq);
            return 1; // USUARIO NORMAL
        }
    }

    fclose(arq);

    printf(RED"\nLogin invalido!\n"RESET);
    pressioneEnter();
    return 0;
}

void listarLugares() {
    limparTela();
    iconelistar();
    printf(GREEN"\t\t\t\t\t\t=== LISTA DE LUGARES (%d) ===\n\n"RESET, numLugares);
    if (numLugares == 0) {
        printf("Nenhum lugar cadastrado.\n");
        return;
    }
    int i;
    for (i = 0; i < numLugares; i++) {
        Local *l = &listaLugares[i];
        printf("\t\t\t\t\t%d) %s\n", i+1, l->nome);
        printf("\t\t\t\t\tDescricao: %.80s%s\n", l->descricao, (strlen(l->descricao) > 80 ? "..." : ""));
        printf("\t\t\t\t\tEndereco: %s CEP: %s\n", l->endereco.rua, l->endereco.cep);
        printf("\t\t\t\t\tContato: ");
        int t;
        for (t = 0; t < l->contato.qtdeTelefone; t++) {
            if (t) printf(", ");
            printf("%s", l->contato.telefones[t]);
        }
        if (l->contato.qtdeTelefone == 0) printf("nenhum");
        printf("\n");
        printf("\t\t\t\t\tCategorias: ");
        int c;
        for (c = 0; c < l->qtdTipos; c++) {
            if (c) printf(", ");
            printf("%s", obterNomeTipoDeLugar(l->tipos[c]));
        }
        if (l->qtdTipos == 0) printf("nenhuma");
        printf("\n\n");
    }
}

void pressioneEnter() {
    printf("Pressione ENTER para continuar...");
    limparBuffer();
    getchar();
}

void salvarTxt(const char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "wb");
    if (!f) {
        printf(RED"Erro ao abrir arquivo para salvar!\n"RESET);
        return;
    }
    if (fwrite(&numLugares, sizeof(numLugares), 1, f) != 1) {
        printf(RED"Erro ao salvar numero de lugares\n"RESET);
        fclose(f);
        return;
    }
    if (numLugares > 0) {
        if (fwrite(listaLugares, sizeof(Local), numLugares, f) != (size_t)numLugares) {
            printf(RED"Erro ao salvar lugares\n"RESET);
        }
    }
    fclose(f);
    printf(GREEN"Dados salvos em %s\n"RESET, nome_arquivo);
}

void carregarTxt(const char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "rb");
    if (!f) {
        // arquivo pode nao existir ainda; nao tratar como erro critico
        return;
    }
    int q = 0;
    if (fread(&q, sizeof(q), 1, f) != 1) {
        fclose(f);
        return;
    }
    if (q < 0 || q > MAX_LOCAIS) q = 0;
    if (q > 0) {
        if (fread(listaLugares, sizeof(Local), q, f) != (size_t)q) {
            fclose(f);
            return;
        }
    }
    numLugares = q;
    fclose(f);
}

void menuUsuario() {
    int opcao;

    do {
        limparTela();
        cabecalho();

        printf(GREEN"\t\t\t\t\t\t   === MENU DO USUARIO ===\n\n"RESET);
        printf("\t\t\t\t\t\t1 - Listar locais\n");
        printf("\t\t\t\t\t\t2 - Filtrar por Categoria\n");
        printf("\t\t\t\t\t\t3 - Comentar um lugar\n");
        printf("\t\t\t\t\t\t4 - Ver comentarios de um lugar\n");
        printf("\t\t\t\t\t\t5 - Sair\n\n");
        printf("\t\t\t\t\t\tEscolha: ");
        if (scanf("%d", &opcao) != 1) { limparBuffer(); opcao = -1; }
        limparBuffer();

        limparTela();

        switch(opcao) {
            case 1: listarLugares(); pressioneEnter(); break;
            case 2: filtrarPorCategoria(); break;
            case 3: adicionarComentario(); break;
            case 4: listarComentarios();break;
            case 5: return;
            default: printf(RED"Opcao invalida!\n"RESET); pressioneEnter();
        }

    } while (1);
}

void menuAdmin() {
    int opcao;

    do {
        limparTela();
        cabecalho();

        printf(GREEN"\t\t\t\t\t\t=== MENU DO ADMINISTRADOR ===\n\n"RESET);
        printf("\t\t\t\t\t\t1 - Cadastrar local\n");
        printf("\t\t\t\t\t\t2 - Editar local (nao implementado)\n");
        printf("\t\t\t\t\t\t3 - Excluir local (nao implementado)\n");
        printf("\t\t\t\t\t\t4 - Salvar dados\n");
        printf("\t\t\t\t\t\t5 - Carregar dados\n");
        printf("\t\t\t\t\t\t6 - Sair\n\n");
        printf("\t\t\t\t\t\tEscolha: ");
        if (scanf("%d", &opcao) != 1) { limparBuffer(); opcao = -1; }
        limparBuffer();

        limparTela();

        switch(opcao) {
            case 1: inserirLugar(); pressioneEnter(); break;
            case 2: printf("Editar local - funcao pendente.\n"); pressioneEnter(); break;
            case 3: printf("Excluir local - funcao pendente.\n"); pressioneEnter(); break;
            case 4: salvarTxt("lugares.dat"); pressioneEnter(); break;
            case 5: carregarTxt("lugares.dat"); printf("Dados carregados.\n"); pressioneEnter(); break;
            case 6: return;
            default: printf(RED"Opcao invalida!\n"RESET); pressioneEnter();
        }

    } while (1);
}

int menuInicial() {
    int opcao;

    do {
        limparTela();
        cabecalho();

        printf("\t\t\t\t\t\t1 - Login\n");
        printf("\t\t\t\t\t\t2 - Cadastrar usuario\n");
        printf("\t\t\t\t\t\t3 - Sair\n");	     

        printf("\t\t\t\t\t\tEscolha: ");
        if (scanf("%d", &opcao) != 1) { limparBuffer(); opcao = -1; }
        limparBuffer();

        switch(opcao) {
            case 1:
                return login();
            case 2:
                cadastrarUsuario();
                break;      
            case 3:
                exit(0);
            default:
                printf(RED"\nOpcao invalida!\n"RESET);
                pressionEnter: ;
                printf("Pressione ENTER para continuar...");
                limparBuffer();
                getchar();
        }

    } while (1);
}

int main() {
    // tenta carregar dados no inicio (se existir)
    carregarTxt("lugares.dat");

    while (1) {
        int tipo = menuInicial();

        if (tipo == 1)
            menuUsuario();
        else if (tipo == 2)
            menuAdmin();
        // tipo == 0 -> volta para menu inicial
    }

    return 0;
}
