#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "turista.h"
#include "interface.h"
#include "gerente.h"
#include "utils.h"

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

        switch (opcao) {
            case 1: listarLugares(); pressioneEnter(); break;
            case 2: filtrarPorCategoria(); break;
            case 3: adicionarComentario(); break;
            case 4: listarComentarios(); break;
            case 5: return;
            default: printf(RED"Opcao invalida!\n"RESET); pressioneEnter();
        }

    } while (1);
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
        printf("%d) %s\n", i + 1, l->nome);
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
        printf("\t\t\t\tCategorias: ");
        int c;
        for (c = 0; c < l->qtdTipos; c++) {
            if (c) printf(", ");
            printf("%s", obterNomeTipoDeLugar(l->tipos[c]));
        }
        if (l->qtdTipos == 0) printf("nenhuma");
        printf("\n\n");
    }
}

void filtrarPorCategoria() {
    iconefiltrar();
    if (numLugares == 0) {
        printf("\nNenhum lugar cadastrado.\n");
        pressioneEnter();
        return;
    }

    int opcao;

    printf("\n\t\t\t\t=== FILTRAR POR CATEGORIA ===\n");
    printf("\t1 - Patrimonio Historico     6 - Culinaria Regional      11 - Museu\n");
    printf("\t2 - Cultural                 7 - Indigena                12 - Cinema\n");
    printf("\t3 - Igreja                   8 - Bar                     13 - Saude Publica\n");
    printf("\t4 - Gastronomia              9 - Restaurante             14 - Outro\n");
    printf("\t5 - Culinaria Brasileira     10 - Mercado\n");
    printf("\tEscolha uma categoria: ");

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
    printf("\n\t\t\t\t=== RESULTADOS DA BUSCA ===\n");
    int i;
    for (i = 0; i < numLugares; i++) {
        // Verifica apenas categorias EXATAS (aqui escolhi tratar quando qtdTipos == 1 e igual)
        if (listaLugares[i].qtdTipos == 1 && listaLugares[i].tipos[0] == categoriaEscolhida) {
            printf("\n\t\t\t\t--- %s ---\n", listaLugares[i].nome);
            printf("\t\t\t\tDescricao: %s\n", listaLugares[i].descricao);
            printf("\t\t\t\tEndereco: %s, CEP %s\n",
                listaLugares[i].endereco.rua,
                listaLugares[i].endereco.cep);
            printf("\t\t\t\tEntrada: R$ %.2f\n", listaLugares[i].entrada);
            printf("\t\t\t\tRanking: %.1f\n", listaLugares[i].ranking);

            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("\nNenhum lugar encontrado para essa categoria exata.\n");
    }

    printf("\n");
    pressioneEnter();
}

const char *obterNomeTipoDeLugar(TipoDeLugar tipo) {
    switch (tipo) {
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

void adicionarComentario() {
    iconecomentarios();
    if (numLugares == 0) {
        printf(RED"\nNenhum lugar cadastrado para comentar.\n"RESET);
        pressioneEnter();
        return;
    }

    int paginaAtual = 0;
    int itensPorPagina = 6;
    int totalPaginas = (numLugares + itensPorPagina - 1) / itensPorPagina;
    int opcao = -1;
    char comando[10];

    while (1) {
        limparTela();
        iconecomentarios();

        printf(GREEN"\n\t\t\t=== ESCOLHA UM LUGAR PARA COMENTAR ===\n"RESET);
        printf(GREEN"\t\t\t   (Página %d de %d)\n\n"RESET, paginaAtual + 1, totalPaginas);

        // Exibir locais da página atual
        int inicio = paginaAtual * itensPorPagina;
        int fim = inicio + itensPorPagina;
        if (fim > numLugares) fim = numLugares;

        printf("\t\t\t+----+--------------------------------------+\n");
        printf("\t\t\t| N  | NOME DO LOCAL                        |\n");
        printf("\t\t\t+----+--------------------------------------+\n");

        for (int i = inicio; i < fim; i++) {
            printf("\t\t\t| %-2d | %-36.36s |\n", i + 1, listaLugares[i].nome);
        }

        printf("\t\t\t+----+--------------------------------------+\n\n");

        // Opções de Navegação
        printf("\t\t\t[N] Próxima página  ");
        printf("[A] Página anterior  ");
        printf("[S] Sair\n");
        printf("\t\t\tOu Digite o número do local: ");

        if (scanf("%9s", comando) != 1) {
            limparBuffer();
            continue;
        }
        limparBuffer();

        // Verificar se é comando de navegação
        if (tolower(comando[0]) == 'n' && strlen(comando) == 1) {
            if (paginaAtual < totalPaginas - 1) {
                paginaAtual++;
            } else {
                printf(RED"\n\t\t\tJa esta na ultima pagina!\n"RESET);
                pressioneEnter();
            }
            continue;
        }

        if (tolower(comando[0]) == 'a' && strlen(comando) == 1) {
            if (paginaAtual > 0) {
                paginaAtual--;
            } else {
                printf(RED"\n\t\t\tJa esta na primeira pagina!\n"RESET);
                pressioneEnter();
            }
            continue;
        }

        if (tolower(comando[0]) == 's' && strlen(comando) == 1) {
            return;
        }

        // Tentar converter para número
        opcao = atoi(comando);

        if (opcao < 1 || opcao > numLugares) {
            printf(RED"\n\t\t\tOpcao invalida!\n"RESET);
            pressioneEnter();
            continue;
        }

        // Número válido escolhido, sair do loop
        break;
    }

    // processar comentário
    Local *l = &listaLugares[opcao - 1];

    if (l->numComentarios >= MAX_COMENTARIO) {
        printf(RED"Este local atingiu o limite de comentarios.\n"RESET);
        pressioneEnter();
        return;
    }

    limparTela();
    iconecomentarios();
    printf(GREEN"\n\t\t\t=== COMENTAR: %s ===\n\n"RESET, l->nome);

    Comentario *c = &l->comentarios[l->numComentarios];

    if (currentUser[0] != '\0') {
        strncpy(c->autor, currentUser, sizeof(c->autor) - 1);
        c->autor[sizeof(c->autor) - 1] = '\0';
        printf(GREEN"\n\t\t\tAutor:\n\t\t\t\t" RESET "%s"  "\n\n", c->autor);
    } else {
        printf("\n\t\t\tAutor:\n\t");
        fgets(c->autor, sizeof(c->autor), stdin);
        trim_nl(c->autor);
    }

    printf(GREEN"\t\t\tDeixe seu comentário: \n\t\t\t\t"RESET);
    fgets(c->texto, sizeof(c->texto), stdin);
    trim_nl(c->texto);

    printf(GREEN"\n\t\t\tNota (0 a 5): "RESET);
    do {
        if (scanf("%f", &c->nota) != 1 || c->nota < 0 || c->nota > 5) {
            limparBuffer();

            // Volta o cursor uma linha acima e limpa
            printf("\033[1A");   // move o cursor uma linha para cima
            printf("\033[2K");   // limpa a linha inteira            

            printf(RED"\t\t\tNota inválida! Digite novamente (0 a 5): "RESET);
        } else break;
    } while (1);

    limparBuffer();

    l->numComentarios++;

    // recalcular ranking médio
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
    printf("\nEscolha o numero do lugar: ");
    int escolha;

    if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > numLugares) {
        limparBuffer();
        printf(RED"Opção inválida!\n"RESET);
        return;
    }
    limparBuffer();

    Local *l = &listaLugares[escolha - 1];

    printf(GREEN"\n=== Comentarios de %s ===\n\n"RESET, l->nome);

    if (l->numComentarios == 0) {
        printf("Nenhum comentario ainda.\n");
        return;
    }

    for (int i = 0; i < l->numComentarios; i++) {
        Comentario *c = &l->comentarios[i];
        printf("Autor: %s\n", c->autor);
        printf("Comentario: %s\n", c->texto);
        printf("Nota: %.1f\n", c->nota);
        printf("--------------------------\n");
    }
}