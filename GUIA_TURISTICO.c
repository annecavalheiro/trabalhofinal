#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"


// LIMPAR TELA (REFRESH)

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


// CABEÇALHO NAVEGAMAZON

void cabecalho() {
  
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
}

//icone cadastro de usuario 
void iconecadastrousuario (){
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
// icone login
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
// CADASTRAR USUARIO

void cadastrarUsuario() {
    limparTela();
    
	iconecadastrousuario();
    char usuario[50], senha[50];
    FILE *arq = fopen("usuarios.txt", "a");

    if (!arq) {
        printf(RED"Erro ao abrir o arquivo!\n"RESET);
        return;
    }

    printf(GREEN"=== CADASTRAR USUARIO ===\n\n"RESET);

	
    printf("Usuario: ");
    scanf("%s", usuario);

    printf("Senha: ");
    scanf("%s", senha);

    fprintf(arq, "%s %s\n", usuario, senha);
    fclose(arq);

    printf(GREEN"\nUsuario cadastrado com sucesso!\n"RESET);
    printf("Pressione ENTER para continuar...");
    getchar(); getchar();
}


// LOGIN NORMAL (USUARIOS DO TXT)

int login() {
    limparTela();
    iconelogin();

    char usuario[50], senha[50], fileUser[50], filePass[50];
    FILE *arq = fopen("usuarios.txt", "r");

    printf(GREEN"=== LOGIN ===\n\n"RESET);

    printf("Usuario: ");
    scanf("%s", usuario);

    printf("Senha: ");
    scanf("%s", senha);

    if (!arq) {
        printf(RED"\nArquivo de usuarios nao encontrado!\n"RESET);
        getchar(); getchar();
        return 0;
    }

    while (fscanf(arq, "%s %s", fileUser, filePass) != EOF) {
        if (strcmp(usuario, fileUser) == 0 && strcmp(senha, filePass) == 0) {
            fclose(arq);

            if (strcmp(usuario, "admin") == 0)
                return 2;  // ADMIN

            return 1;      // USUARIO
        }
    }

    fclose(arq);

    printf(RED"\nLogin invalido!\n"RESET);
    printf("Pressione ENTER para continuar...");
    getchar(); getchar();

    return 0;
}


// LOGIN DO ADMINISTRADOR (com senha de acesso)

int loginAdmin() {
    limparTela();
    cabecalho();

    char senha[50];

    printf(GREEN"=== LOGIN DO ADMINISTRADOR ===\n\n"RESET);

    printf("Digite a senha do administrador: ");
    scanf("%s", senha);

    // DEFINA A SENHA DO ADMIN AQUI:
    if (strcmp(senha, "admin123") == 0) {
        return 2;  // acesso ao menuAdmin()
    }

    printf(RED"\nSenha incorreta!\n"RESET);
    printf("Pressione ENTER para continuar...");
    getchar(); getchar();

    return 0;
}


// MENU DO USUÁRIO

void menuUsuario() {
    int opcao;

    do {
        limparTela();
        cabecalho();

        printf(GREEN"=== MENU DO USUARIO ===\n\n"RESET);
        printf("1 - Listar locais\n");
        printf("2 - Filtrar\n");
        printf("3 - Comentários\n");
        printf("4 - Sair\n\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        limparTela();

        switch(opcao) {
            case 1: printf("Listagem...\n"); break;
            case 2: printf("Filtros...\n"); break;
            case 3: printf("Comentarios...\n"); break;
            case 4: return;
            default: printf(RED"Opcao invalida!\n"RESET);
        }

        printf("\nPressione ENTER para voltar...");
        getchar(); getchar();

    } while (1);
}


// MENU DO ADMINISTRADOR

void menuAdmin() {
    int opcao;

    do {
        limparTela();
        cabecalho();

        printf(GREEN"=== MENU DO ADMINISTRADOR ===\n\n"RESET);
        printf("1 - Cadastrar local\n");
        printf("2 - Editar local\n");
        printf("3 - Excluir local\n");
        printf("4 - Sair\n\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        limparTela();

        switch(opcao) {
            case 1: printf("Cadastrar local...\n"); break;
            case 2: printf("Editar local...\n"); break;
            case 3: printf("Excluir local...\n"); break;
            case 4: return;
            default: printf(RED"Opcao invalida!\n"RESET);
        }

        printf("\nPressione ENTER para voltar...");
        getchar(); getchar();

    } while (1);
}


// MENU INICIAL COM LOGIN DO ADMIN

int menuInicial() {
    int opcao;

    do {
        limparTela();
        cabecalho();

        printf("1 - Login\n");
        printf("2 - Cadastrar usuario\n");
        printf("3 - Login como Administrador\n");
        printf("4 - Sair\n\n");

        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                return login();
            case 2:
                cadastrarUsuario();
                break;
            case 3:
                return loginAdmin();
            case 4:
                exit(0);
            default:
                printf(RED"\nOpcao invalida!\n"RESET);
                getchar(); getchar();
        }

    } while (1);
}


// MAIN

int main() {
    while (1) {
        int tipo = menuInicial();

        if (tipo == 1)
            menuUsuario();
        else if (tipo == 2)
            menuAdmin();
    }

    return 0;
}






