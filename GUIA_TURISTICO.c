#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LOCAIS 50
#define MAX_COMENTARIO 100
#define MAX_TELEFONES 3
#define MAX_TIPOS 10

#define RED   "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

typedef enum {
    PATRIMONIO_HISTORICO = 1,
    CULTURAL,
    IGREJA,
    GASTRONOMIA,
    CULINARIA_BRASILEIRA,
    CULINARIA_REGIONAL,
    INDIGENA,
    BAR,
    RESTAURANTE,
    MERCADO,
    MUSEU,
    CINEMA,
    UNIDADE_SAUDE_PUBLICA,
    OUTRO
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

/* protótipos */
void inserirLugar();
void listarLugares();
const char* obterNomeTipoDeLugar(TipoDeLugar tipo);
TipoDeLugar obterEnumTipoDeLugar(int opcao);
void limparBuffer();
void limparTela();
void pressioneEnter();
void menuDeBusca();
void salvarTxt(const char *nome_arquivo);
void carregarTxt(const char *nome_arquivo);
char* strcasestr_simples(const char* haystack, const char* needle);
void trim_nl(char *s);
void filtrarPorCategoria();
void deletarLugar();

int main() {
    carregarTxt("locais.txt");

    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif

    {
        int opcao;
        do {
            limparTela();
            printf(GREEN"                                                                    #           \n");
            printf("                                                                    ###              \n");
            printf("                                                                    #####            \n");
            printf("                                                                    #######          \n");
            printf("                                                                    #####            \n");
            printf("                                                                    ###              \n");
            printf("                                                                    #                \n");
            printf("                                                                    #                \n");
            printf("                                                                    #                \n");

            printf("                                            "RED"*"GREEN"                     "RED"*"GREEN"                  \n");
            printf("                                           "RED"*"GREEN" "RED"*"GREEN"                   "RED"*"GREEN"                   \n");
            printf("                                          "RED"*"GREEN"   "RED"*"GREEN"                 "RED"*"GREEN"                    \n");
            printf("                                         "RED"*"GREEN"     "RED"*"GREEN"               "RED"*"GREEN"                     \n");
            printf("                                        "RED"*"GREEN"       "RED"*"GREEN"             "RED"*"GREEN"                      \n");
            printf("                                       "RED"*"GREEN"         "RED"*"GREEN"           "RED"*"GREEN"                       \n");
            printf("                          #####       "RED"*"GREEN"           "RED"*"GREEN"         "RED"*"GREEN"                        \n");
            printf("                        ##     ##    "RED"*"GREEN"             "RED"*"GREEN"       "RED"*"GREEN"                         \n");
            printf("                        ##     ##   "RED"*"GREEN"               "RED"*"GREEN"     "RED"*"GREEN"                          \n");
            printf("                          #####    "RED"*"GREEN"                 "RED"*"GREEN"   "RED"*"GREEN"                           \n");
            printf("                           ###    "RED"*"GREEN"                   "RED"*"GREEN" "RED"*"GREEN"                            \n");
            printf("                            #    "RED"*"GREEN"                     "RED"*"GREEN"                             \n");

            printf("\n");
            printf(GREEN"                         "RED"N"GREEN"AVEG"RED"A"GREEN"MAZON - GUIA TURISTICO (CENTRO DE MANAUS)\n"RESET);
            printf("1 - Inserir novo lugar\n");
            printf("2 - Listar lugares\n");
            printf("3 - Filtrar por categorias\n");
            printf("4 - Salvar em TXT (locais.txt)\n");
            printf("5 - Deletar por nome do local\n");
            printf("0 - Sair\n");
            printf("Escolha uma opcao: ");
            if (scanf("%d", &opcao) != 1) { limparBuffer(); opcao = -1; }
            limparBuffer();

            switch(opcao) {
                case 1:
                    limparTela();
                    inserirLugar();
                    break;
                case 2:
                    limparTela();
                    listarLugares();
                    pressioneEnter();
                    break;
                case 3:
                    limparTela();
                    filtrarPorCategoria();
                    break;
                case 4:
                    limparTela();
                    salvarTxt("locais.txt");
                    printf("Arquivo salvo em locais.txt\n");
                    pressioneEnter();
                    break;
                case 5:
                    limparTela();
                    deletarLugar();
                    pressioneEnter();
                    break;
                case 0:
                    printf("\nEncerrando programa...\n");
                    break;
                default:
                    printf("\nOpcão inválida!\n");
                    pressioneEnter();
            }
        } while(opcao != 0);
    }

    return 0;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparTela(){
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void pressioneEnter() {
    printf("Pressione ENTER para continuar...");
    while(getchar() != '\n');
}

/* retira newline final */
void trim_nl(char *s) {
    size_t len;
    if (!s) return;
    len = strlen(s);
    if (len == 0) return;
    if (s[len-1] == '\n') s[len-1] = '\0';
}

/* busca case-insensitive simples */
char* strcasestr_simples(const char* haystack, const char* needle) {
    if (!haystack || !needle || *needle == '\0') return NULL;
    {
        int len_h = strlen(haystack);
        int len_n = strlen(needle);
        int i,j;
        for (i = 0; i <= len_h - len_n; i++) {
            int found = 1;
            for (j = 0; j < len_n; j++) {
                char a = haystack[i+j];
                char b = needle[j];
                if (tolower((unsigned char)a) != tolower((unsigned char)b)) { found = 0; break; }
            }
            if (found) return (char*)haystack + i;
        }
    }
    return NULL;
}

void inserirLugar() {
    if (numLugares >= MAX_LOCAIS) {
        printf("\nLista cheia!\n");
        return;
    }

    {
        Local novoLugar;
        int opcao, i;
        memset(&novoLugar, 0, sizeof(Local));

        printf("\n=== CADASTRO DE NOVO LUGAR ===\n");

        printf("Nome do lugar: ");
        fgets(novoLugar.nome, sizeof(novoLugar.nome), stdin);
        trim_nl(novoLugar.nome);

        printf("Descricao: ");
        fgets(novoLugar.descricao, sizeof(novoLugar.descricao), stdin);
        trim_nl(novoLugar.descricao);

        printf("\n--- Endereco ---\nRua: ");
        fgets(novoLugar.endereco.rua, sizeof(novoLugar.endereco.rua), stdin);
        trim_nl(novoLugar.endereco.rua);

        printf("CEP: ");
        fgets(novoLugar.endereco.cep, sizeof(novoLugar.endereco.cep), stdin);
        trim_nl(novoLugar.endereco.cep);

        printf("\n--- Contato ---\nQuantos telefones? (max 3): ");
        if (scanf("%d", &novoLugar.contato.qtdeTelefone) != 1) novoLugar.contato.qtdeTelefone = 0;
        if (novoLugar.contato.qtdeTelefone > MAX_TELEFONES) novoLugar.contato.qtdeTelefone = MAX_TELEFONES;
        limparBuffer();

        for (i = 0; i < novoLugar.contato.qtdeTelefone; i++) {
            printf("Telefone %d: ", i + 1);
            fgets(novoLugar.contato.telefones[i], sizeof(novoLugar.contato.telefones[i]), stdin);
            trim_nl(novoLugar.contato.telefones[i]);
        }

        printf("E-mail: ");
        fgets(novoLugar.contato.email, sizeof(novoLugar.contato.email), stdin);
        trim_nl(novoLugar.contato.email);

        printf("Site: ");
        fgets(novoLugar.contato.site, sizeof(novoLugar.contato.site), stdin);
        trim_nl(novoLugar.contato.site);

        /* categorias múltiplas */
        novoLugar.qtdTipos = 0;
        printf("\n--- Categorias do lugar (digite 0 para parar) ---\n");
        printf("1-Patrimonio Historico\n2-Cultural\n3-Igreja\n4-Gastronomia\n5-Culinaria Brasileira\n");
        printf("6-Culinaria Regional\n7-Indigena\n8-Bar\n9-Restaurante\n");
        printf("10-Mercado\n11-Museu\n12-Cinema\n13-Saude Publica\n14-Outro\n");

        while (1) {
            printf("Escolha uma categoria (0 para finalizar): ");
            if (scanf("%d", &opcao) != 1) { limparBuffer(); continue; }
            limparBuffer();

            if (opcao == 0) break;
            if (opcao < 0 || opcao > 14) {
                printf("Opcão inválida.\n");
                continue;
            }
            if (novoLugar.qtdTipos < MAX_TIPOS) {
                novoLugar.tipos[novoLugar.qtdTipos++] = obterEnumTipoDeLugar(opcao);
            } else {
                printf("Limite de categorias atingido!\n");
                break;
            }
        }

        printf("Valor da entrada (0 = gratuito): ");
        if (scanf("%f", &novoLugar.entrada) != 1) novoLugar.entrada = 0;
        limparBuffer();

        novoLugar.ranking = 5.0f;
        novoLugar.numComentarios = 0;

        listaLugares[numLugares++] = novoLugar;

        printf("\nLugar cadastrado!\n");
        pressioneEnter();
    }
}

void listarLugares() {
    if (numLugares == 0) {
        printf("\nNenhum lugar cadastrado.\n");
        return;
    }

    int i, j;
    printf("\n=== LUGARES ===\n");
    for (i = 0; i < numLugares; i++) {
        printf("\n--- %s ---\n", listaLugares[i].nome);
        printf("Descricao: %s\n", listaLugares[i].descricao);
        printf("Endereco: %s, CEP %s\n", listaLugares[i].endereco.rua, listaLugares[i].endereco.cep);

        printf("Contato: ");
        if (listaLugares[i].contato.qtdeTelefone > 0) {
            printf("Telefones: ");
            for (j = 0; j < listaLugares[i].contato.qtdeTelefone; j++) {
                printf("%s", listaLugares[i].contato.telefones[j]);
                if (j < listaLugares[i].contato.qtdeTelefone - 1) printf(", ");
            }
            printf("; ");
        }
        if (strlen(listaLugares[i].contato.email) > 0) printf("Email: %s; ", listaLugares[i].contato.email);
        if (strlen(listaLugares[i].contato.site) > 0) printf("Site: %s", listaLugares[i].contato.site);
        printf("\n");

        printf("Categorias: ");
        if (listaLugares[i].qtdTipos == 0) {
            printf("Nenhuma");
        } else {
            for (j = 0; j < listaLugares[i].qtdTipos; j++) {
                printf("%s", obterNomeTipoDeLugar(listaLugares[i].tipos[j]));
                if (j < listaLugares[i].qtdTipos - 1) printf(", ");
            }
        }
        printf("\n");

        printf("Ranking: %.1f\n", listaLugares[i].ranking);
        printf("Entrada: R$ %.2f\n", listaLugares[i].entrada);

        if (listaLugares[i].numComentarios > 0) {
            printf("Comentarios (%d):\n", listaLugares[i].numComentarios);
            for (j = 0; j < listaLugares[i].numComentarios; j++) {
                printf("  - %s (%.1f): %s\n", listaLugares[i].comentarios[j].autor,
                       listaLugares[i].comentarios[j].nota,
                       listaLugares[i].comentarios[j].texto);
            }
        }
    }
}

void filtrarPorCategoria() {
    if (numLugares == 0) {
        printf("\nNenhum lugar cadastrado.\n");
        pressioneEnter();
        return;
    }

    int opcao;

    printf("\n=== FILTRAR POR CATEGORIA ===\n");
    printf("1 - Patrimonio Historico\n");
    printf("2 - Cultural\n");
    printf("3 - Igreja\n");
    printf("4 - Gastronomia\n");
    printf("5 - Culinaria Brasileira\n");
    printf("6 - Culinaria Regional\n");
    printf("7 - Indigena\n");
    printf("8 - Bar\n");
    printf("9 - Restaurante\n");
    printf("10 - Mercado\n");
    printf("11 - Museu\n");
    printf("12 - Cinema\n");
    printf("13 - Saude Publica\n");
    printf("14 - Outro\n");
    printf("Escolha uma categoria: ");

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
    printf("\n=== RESULTADOS DA BUSCA ===\n");

    for (int i = 0; i < numLugares; i++) {
        for (int j = 0; j < MAX_TIPOS; j++) {
            if (listaLugares[i].tipos[j] == categoriaEscolhida) {
                printf("\n--- %s ---\n", listaLugares[i].nome);
                printf("Descricao: %s\n", listaLugares[i].descricao);
                printf("Endereco: %s, CEP %s\n",
                    listaLugares[i].endereco.rua,
                    listaLugares[i].endereco.cep);
                printf("Entrada: R$ %.2f\n", listaLugares[i].entrada);
                printf("Ranking: %.1f\n", listaLugares[i].ranking);
                encontrados = 1;
            }
        }
    }

    if (encontrados == 0) {
        printf("\nNenhum lugar encontrado para essa categoria exata.\n");
    }

    printf("\n");
    pressioneEnter();
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
        case UNIDADE_SAUDE_PUBLICA: return "Saude Publica";
        default: return "Outro";
    }
}

TipoDeLugar obterEnumTipoDeLugar(int opcao) {
    switch(opcao) {
        case 1: return PATRIMONIO_HISTORICO;
        case 2: return CULTURAL;
        case 3: return IGREJA;
        case 4: return GASTRONOMIA;
        case 5: return CULINARIA_BRASILEIRA;
        case 6: return CULINARIA_REGIONAL;
        case 7: return INDIGENA;
        case 8: return BAR;
        case 9: return RESTAURANTE;
        case 10: return MERCADO;
        case 11: return MUSEU;
        case 12: return CINEMA;
        case 13: return UNIDADE_SAUDE_PUBLICA;
        default: return OUTRO;
    }
}

void menuDeBusca() {
    filtrarPorCategoria();
}

/* salva no formato "simples" conforme pedido */
void salvarTxt(const char *nome_arquivo) {
    int i, j;
    FILE *file = fopen(nome_arquivo, "w");
    if (!file) {
        printf("Erro ao abrir arquivo para escrita.\n");
        return;
    }

    fprintf(file, "%d\n", numLugares);
    for (i = 0; i < numLugares; i++) {
        fprintf(file, "LUGAR\n");
        fprintf(file, "Nome: %s\n", listaLugares[i].nome);
        fprintf(file, "Descricao: %s\n", listaLugares[i].descricao);
        fprintf(file, "Rua: %s\n", listaLugares[i].endereco.rua);
        fprintf(file, "CEP: %s\n", listaLugares[i].endereco.cep);

        fprintf(file, "Telefones: %d\n", listaLugares[i].contato.qtdeTelefone);
        for (j = 0; j < listaLugares[i].contato.qtdeTelefone; j++) {
            fprintf(file, "Telefone: %s\n", listaLugares[i].contato.telefones[j]);
        }
        fprintf(file, "Email: %s\n", listaLugares[i].contato.email);
        fprintf(file, "Site: %s\n", listaLugares[i].contato.site);

        fprintf(file, "Categorias: %d\n", listaLugares[i].qtdTipos);
        for (j = 0; j < listaLugares[i].qtdTipos; j++) {
            /* gravamos o número da categoria conforme as opções (1..14) */
            fprintf(file, "Categoria: %d\n", (int)listaLugares[i].tipos[j]);
        }

        fprintf(file, "Entrada: %.2f\n", listaLugares[i].entrada);
        fprintf(file, "Ranking: %.2f\n", listaLugares[i].ranking);

        fprintf(file, "Comentarios: %d\n", listaLugares[i].numComentarios);
        for (j = 0; j < listaLugares[i].numComentarios; j++) {
            fprintf(file, "Autor: %s\n", listaLugares[i].comentarios[j].autor);
            fprintf(file, "Nota: %.1f\n", listaLugares[i].comentarios[j].nota);
            fprintf(file, "Texto: %s\n", listaLugares[i].comentarios[j].texto);
        }

        fprintf(file, "FIM\n");
    }

    fclose(file);
}

/* carrega do formato "simples" */
void carregarTxt(const char *nome_arquivo) {
    FILE *file;
    char linha[1024];
    int total = 0;
    int i;

    file = fopen(nome_arquivo, "r");
    if (!file) {
        /* arquivo não existe — ok */
        return;
    }

    /* inicializa */
    numLugares = 0;

    /* primeiro, tenta ler a primeira linha — número de lugares (opcional) */
    if (fgets(linha, sizeof(linha), file) == NULL) {
        fclose(file);
        return;
    }
    trim_nl(linha);
    /* se for número, podemos usar, senão voltamos arquivo ao início */
    if (sscanf(linha, "%d", &total) != 1) {
        /* não era número: reinicia leitura desde começo */
        rewind(file);
    }

    while (fgets(linha, sizeof(linha), file) != NULL) {
        trim_nl(linha);
        if (strcmp(linha, "LUGAR") == 0) {
            Local novoLugar;
            memset(&novoLugar, 0, sizeof(Local));
            novoLugar.qtdTipos = 0;
            novoLugar.numComentarios = 0;
            novoLugar.contato.qtdeTelefone = 0;
            novoLugar.ranking = 5.0f;
            novoLugar.entrada = 0.0f;

            /* lê até encontrar "FIM" ou EOF */
            while (fgets(linha, sizeof(linha), file) != NULL) {
                trim_nl(linha);
                if (strncmp(linha, "Nome:", 5) == 0) {
                    char *p = linha + 5;
                    while (*p == ' ') p++;
                    strncpy(novoLugar.nome, p, sizeof(novoLugar.nome)-1);
                } else if (strncmp(linha, "Descricao:", 10) == 0) {
                    char *p = linha + 10;
                    while (*p == ' ') p++;
                    strncpy(novoLugar.descricao, p, sizeof(novoLugar.descricao)-1);
                } else if (strncmp(linha, "Rua:", 4) == 0) {
                    char *p = linha + 4;
                    while (*p == ' ') p++;
                    strncpy(novoLugar.endereco.rua, p, sizeof(novoLugar.endereco.rua)-1);
                } else if (strncmp(linha, "CEP:", 4) == 0) {
                    char *p = linha + 4;
                    while (*p == ' ') p++;
                    strncpy(novoLugar.endereco.cep, p, sizeof(novoLugar.endereco.cep)-1);
                } else if (strncmp(linha, "Telefones:", 10) == 0) {
                    int qtd = 0;
                    sscanf(linha + 10, "%d", &qtd);
                    if (qtd < 0) qtd = 0;
                    if (qtd > MAX_TELEFONES) qtd = MAX_TELEFONES;
                    novoLugar.contato.qtdeTelefone = qtd;
                    /* ler os telefones nas próximas linhas */
                    {
                        int t;
                        for (t = 0; t < qtd; t++) {
                            if (fgets(linha, sizeof(linha), file) == NULL) break;
                            trim_nl(linha);
                            if (strncmp(linha, "Telefone:", 9) == 0) {
                                char *p = linha + 9;
                                while (*p == ' ') p++;
                                strncpy(novoLugar.contato.telefones[t], p, sizeof(novoLugar.contato.telefones[t])-1);
                            } else {
                                /* formato inesperado: volta ponteiro de arquivo uma linha para reprocessar */
                                /* não é trivial voltar uma linha em fgets; como fallback copia a linha para telefone */
                                strncpy(novoLugar.contato.telefones[t], linha, sizeof(novoLugar.contato.telefones[t])-1);
                            }
                        }
                    }
                } else if (strncmp(linha, "Email:", 6) == 0) {
                    char *p = linha + 6;
                    while (*p == ' ') p++;
                    strncpy(novoLugar.contato.email, p, sizeof(novoLugar.contato.email)-1);
                } else if (strncmp(linha, "Site:", 5) == 0) {
                    char *p = linha + 5;
                    while (*p == ' ') p++;
                    strncpy(novoLugar.contato.site, p, sizeof(novoLugar.contato.site)-1);
                } else if (strncmp(linha, "Categorias:", 11) == 0) {
                    int qtd = 0;
                    sscanf(linha + 11, "%d", &qtd);
                    if (qtd < 0) qtd = 0;
                    if (qtd > MAX_TIPOS) qtd = MAX_TIPOS;
                    novoLugar.qtdTipos = 0;
                    /* ler categorias nas próximas linhas */
                    {
                        int t;
                        for (t = 0; t < qtd; t++) {
                            if (fgets(linha, sizeof(linha), file) == NULL) break;
                            trim_nl(linha);
                            if (strncmp(linha, "Categoria:", 10) == 0) {
                                int cat = 0;
                                sscanf(linha + 10, "%d", &cat);
                                if (cat < 1 || cat > 14) cat = 14;
                                novoLugar.tipos[novoLugar.qtdTipos++] = obterEnumTipoDeLugar(cat);
                            } else {
                                /* linha inesperada: ignorar */
                            }
                        }
                    }
                } else if (strncmp(linha, "Entrada:", 8) == 0) {
                    float e = 0.0f;
                    sscanf(linha + 8, "%f", &e);
                    novoLugar.entrada = e;
                } else if (strncmp(linha, "Ranking:", 8) == 0) {
                    float r = 0.0f;
                    sscanf(linha + 8, "%f", &r);
                    novoLugar.ranking = r;
                } else if (strncmp(linha, "Comentarios:", 11) == 0) {
                    int qtd = 0;
                    sscanf(linha + 11, "%d", &qtd);
                    if (qtd < 0) qtd = 0;
                    if (qtd > MAX_COMENTARIO) qtd = MAX_COMENTARIO;
                    novoLugar.numComentarios = 0;
                    {
                        int c;
                        for (c = 0; c < qtd; c++) {
                            Comentario com;
                            memset(&com, 0, sizeof(Comentario));
                            /* Autor */
                            if (fgets(linha, sizeof(linha), file) == NULL) break;
                            trim_nl(linha);
                            if (strncmp(linha, "Autor:", 6) == 0) {
                                char *p = linha + 6;
                                while (*p == ' ') p++;
                                strncpy(com.autor, p, sizeof(com.autor)-1);
                            }
                            /* Nota */
                            if (fgets(linha, sizeof(linha), file) == NULL) break;
                            trim_nl(linha);
                            if (strncmp(linha, "Nota:", 5) == 0) {
                                float n = 0.0f;
                                sscanf(linha + 5, "%f", &n);
                                com.nota = n;
                            }
                            /* Texto */
                            if (fgets(linha, sizeof(linha), file) == NULL) break;
                            trim_nl(linha);
                            if (strncmp(linha, "Texto:", 6) == 0) {
                                char *p = linha + 6;
                                while (*p == ' ') p++;
                                strncpy(com.texto, p, sizeof(com.texto)-1);
                            }
                            novoLugar.comentarios[novoLugar.numComentarios++] = com;
                        }
                    }
                } else if (strcmp(linha, "FIM") == 0) {
                    break;
                } else {
                    /* linha inesperada: ignorar */
                }
            }

            if (numLugares < MAX_LOCAIS) {
                listaLugares[numLugares++] = novoLugar;
            } else {
                /* excedeu capacidade */
                break;
            }
        } else {
            /* linha que não é 'LUGAR' - ignorar */
        }
    }

    fclose(file);
}

void deletarLugar() {
    char nome[50];
    printf("Digite o nome do local:");
    fgets(nome, sizeof(nome), stdin);
    trim_nl(nome);

    int indice = 0;
    int encontrou = 1;

    for (int i = 0; i < numLugares; i++) {
        encontrou = strcmp(listaLugares[i].nome, nome);
        if (encontrou == 0) {
            printf("Encontrou");
            indice = i;
            break;
        }
    }

    if (encontrou == 0) {
        for (int i = indice; i < numLugares; i++) {
            listaLugares[i] = listaLugares[i + 1];
        }
        numLugares--;
        salvarTxt("locais.txt");
        printf("Arquivo atualizado com sucesso!\n");
    }else {
        printf("Não foi encontrado o local \"%s\"\n", nome);
    }
}





