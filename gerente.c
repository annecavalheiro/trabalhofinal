#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include "gerente.h"
#include "turista.h"
#include "interface.h"
#include "utils.h"


Local listaLugares[MAX_LOCAIS];
int numLugares = 0;
char currentUser[50] = "";

void inserirLugar() {
    //int retorno = 1;
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
        while (1) {
        printf("\t\t\t\tValor da entrada (R$): ");  
        
        if (scanf("%f", &novoLugar.entrada) != 1) {
            limparBuffer();
            printf(RED"\t\t\t\tValor invalido! Tente novamente.\n"RESET);
            continue;
        }
        limparBuffer();

        if (novoLugar.entrada < 0) {
            printf(RED"\t\t\t\tO valor nao pode ser negativo.\n"RESET);
            continue;
        }

        break;
    }


    novoLugar.ranking = 0.0f;
    novoLugar.numComentarios = 0;
    novoLugar.entrada = 0.0f;

    listaLugares[numLugares++] = novoLugar;
    printf("\n");
    printf(GREEN"\nLugar cadastrado com sucesso!\n"RESET);
}

void editarLocal() {
    if (numLugares == 0) {
        printf(RED"\nNenhum lugar cadastrado.\n"RESET);
        return;
    }

    limparTela();
    printf("\n\t\t\t=== EDITAR LOCAL ===\n");

    // Mostrar todos os lugares com ï¿½ndice
    for (int i = 0; i < numLugares; i++) {
        printf("\t%d - %s\n", i + 1, listaLugares[i].nome);
    }

    printf("\n\tEscolha o número do local que deseja editar: ");
    int escolha;
    if (scanf("%d", &escolha) != 1) {
        limparBuffer();
        return;
    }
    limparBuffer();

    if (escolha < 1 || escolha > numLugares) {
        printf(RED"\nOpção inválida!\n"RESET);
        pressioneEnter();
        return;
    }

    Local *L = &listaLugares[escolha - 1];

    int opcao;

    while (1) {
        limparTela();
        printf("\n\t\t=== Editando: %s ===\n", L->nome);

        printf("\n\t1 - Editar Nome");
        printf("\n\t2 - Editar Descricao");
        printf("\n\t3 - Editar Endereco");
        printf("\n\t4 - Editar Contato");
        printf("\n\t5 - Editar Categorias");
        printf("\n\t6 - Editar Valor da Entrada");
        printf("\n\t0 - Voltar");

        printf("\n\n\tEscolha: ");
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            continue;
        }
        limparBuffer();

        if (opcao == 0) break;

        switch (opcao) {

            case 1: {
                printf("\nNovo nome: ");
                fgets(L->nome, MAX_NOME, stdin);
                trim_nl(L->nome);
                break;
            }

            case 2: {
                printf("\nNova descricao: ");
                fgets(L->descricao, sizeof(L->descricao), stdin);
                trim_nl(L->descricao);
                break;
            }

            case 3: {
                printf("\nNova rua: ");
                fgets(L->endereco.rua, sizeof(L->endereco.rua), stdin);
                trim_nl(L->endereco.rua);

                printf("\nNovo CEP: ");
                fgets(L->endereco.cep, sizeof(L->endereco.cep), stdin);
                trim_nl(L->endereco.cep);
                break;
            }

            case 4: {
                printf("\nQuantos telefones (max 3): ");
                scanf("%d", &L->contato.qtdeTelefone);
                limparBuffer();

                if (L->contato.qtdeTelefone > MAX_TELEFONES)
                    L->contato.qtdeTelefone = MAX_TELEFONES;

                for (int i = 0; i < L->contato.qtdeTelefone; i++) {
                    printf("Telefone %d: ", i + 1);
                    fgets(L->contato.telefones[i], 30, stdin);
                    trim_nl(L->contato.telefones[i]);
                }

                printf("E-mail: ");
                fgets(L->contato.email, 50, stdin);
                trim_nl(L->contato.email);

                printf("Site: ");
                fgets(L->contato.site, 50, stdin);
                trim_nl(L->contato.site);

                break;
            }

            case 5: {
                L->qtdTipos = 0;
                int c;

                printf("\n--- NOVAS CATEGORIAS ---\n");
                printf("Digite 0 para terminar.\n");

                while (1) {
                    printf("Categoria (1-14): ");
                    if (scanf("%d", &c) != 1) {
                        limparBuffer();
                        continue;
                    }
                    limparBuffer();

                    if (c == 0) break;

                    if (c < 1 || c > 14) {
                        printf(RED"Categoria invalida!\n"RESET);
                        continue;
                    }

                    L->tipos[L->qtdTipos++] = obterEnumTipoDeLugar(c);

                    if (L->qtdTipos >= MAX_TIPOS) break;
                }
                break;
            }

            case 6: {
                while (1) {
                    printf("\nNovo valor de entrada (R$): ");
                    if (scanf("%f", &L->entrada) != 1) {
                        limparBuffer();
                        printf(RED"Valor invï¿½lido!\n"RESET);
                        continue;
                    }
                    limparBuffer();

                    if (L->entrada < 0) {
                        printf(RED"O valor nao pode ser negativo!\n"RESET);
                        continue;
                    }
                    break;
                }
                break;
            }

            default:
                printf(RED"\nOpcao invalida!\n"RESET);
        }

        printf(GREEN"\nAlteração salva!\n"RESET);
        pressioneEnter();
    }
}

void excluirLocal() {
    if (numLugares == 0) {
        printf(RED"\nNenhum lugar cadastrado.\n"RESET);
        return;
    }

    limparTela();
    printf("\n\t\t\t=== EXCLUIR LOCAL ===\n");

    for (int i = 0; i < numLugares; i++) {
        printf("\t%d - %s\n", i + 1, listaLugares[i].nome);
    }

    printf("\n\tEscolha o número do local que deseja excluir: ");
    int escolha;
    if (scanf("%d", &escolha) != 1) {
        return;
    }
    limparBuffer();

    if (escolha < 1 || escolha > numLugares) {
        printf(RED"\nOpção inválida!\n"RESET);
        return;
    }

    int idx = escolha - 1;

    printf(RED"\nTem certeza que deseja excluir '%s'? (s/n): "RESET, listaLugares[idx].nome);
    char c = getchar();
    limparBuffer();

    if (tolower(c) != 's') {
        printf("\nOperação cancelada.\n");
        return;
    }

    // Remover deslocando o vetor
    for (int i = idx; i < numLugares - 1; i++) {
        listaLugares[i] = listaLugares[i + 1];
    }

    numLugares--;

    printf(GREEN"\nLocal excluido com sucesso!\n"RESET);
    pressioneEnter();
}

int loginAdmin() {
    limparTela();
    iconeadministrador();

    char senha[50];

    printf(GREEN"\t\t\t\t\t=== LOGIN DO ADMINISTRADOR ===\n\n"RESET);

    printf("\t\t\t\t\tDigite a senha do administrador: ");
    if (scanf("%49s", senha) != 1) { limparBuffer(); return 0; }

    // DEFINA A SENHA DO ADMIN AQUI:
    if (strcmp(senha, "admin123") == 0) {
        return 2;  // acesso ao menuAdmin()
    }

    printf(RED"\nSenha incorreta!\n"RESET);
    printf("Pressione ENTER para continuar...");
    limparBuffer();
    getchar();

    return 0;
}

void menuAdmin() {
    int opcao;

    do {
        limparTela();
        cabecalho();

        printf(GREEN"=== MENU DO ADMINISTRADOR ===\n\n"RESET);
        printf("1 - Cadastrar local\n");
        printf("2 - Editar local\n");
        printf("3 - Excluir local\n");
        printf("4 - Salvar dados\n");
        printf("5 - Carregar dados\n");
        printf("6 - Sair\n\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) { limparBuffer(); opcao = -1; }
        limparBuffer();

        limparTela();

        switch (opcao) {
            case 1: inserirLugar(); pressioneEnter(); break;
            case 2: editarLocal(); break;
            case 3: excluirLocal(); break;
            case 4: salvarTxt("lugares.dat"); pressioneEnter(); break;
            case 5: carregarTxt("lugares.dat"); printf("Dados carregados.\n"); pressioneEnter(); break;
            case 6: return;
            default: printf(RED"Opcao invalida!\n"RESET); pressioneEnter();
        }

    } while (1);
}

int login() {
    limparTela();
    iconelogin();

    char usuario[50], senha[50], fileUser[50], filePass[50];
    FILE *arq = fopen("usuarios.txt", "r");

    printf(GREEN"\t\t\t\t\t\t === LOGIN ===\n\n"RESET);

    printf("\t\t\t\t\tUsuário: ");
    if (scanf("%49s", usuario) != 1) { limparBuffer(); return 0; }

    printf("\t\t\t\t\tSenha: ");
    if (scanf("%49s", senha) != 1) { limparBuffer(); return 0; }

    if (!arq) {
        printf(RED"\nArquivo de usuarios nao encontrado!\n"RESET);
        printf("Pressione ENTER para continuar...");
        limparBuffer();
        getchar();
        return 0;
    }

    while (fscanf(arq, "%49s %49s", fileUser, filePass) != EOF) {
        if (strcmp(usuario, fileUser) == 0 && strcmp(senha, filePass) == 0) {
            fclose(arq);

            /* armazenar nome do usuÃ¡rio logado */
            strncpy(currentUser, usuario, sizeof(currentUser)-1);
            currentUser[sizeof(currentUser)-1] = '\0';

            if (strcmp(usuario, "admin") == 0)
                return 2;  // ADMIN

            return 1;      // USUARIO
        }
    }

    fclose(arq);

    printf(RED"\nLogin invalido!\n"RESET);
    printf("Pressione ENTER para continuar...");
    limparBuffer();
    getchar();

    return 0;
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

int menuInicial() {
    int opcao;

    do {
        limparTela();
        cabecalho();

        printf("\t\t\t\t\t\t1 - Login\n");
        printf("\t\t\t\t\t\t2 - Cadastrar usuário\n");
        printf("\t\t\t\t\t\t3 - Login como Administrador\n");
        printf("\t\t\t\t\t\t4 - Sair\n");

        printf("\t\t\t\t\t\tEscolha: ");
        if (scanf("%d", &opcao) != 1) { limparBuffer(); opcao = -1; }
        limparBuffer();

        switch (opcao) {
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
                pressioneEnter();
                printf("Pressione ENTER para continuar...");
                limparBuffer();
                getchar();
        }

    } while (1);
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
