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
        printf("\t\t\t\t\t\t5 - Sair\n\n");
        printf("\t\t\t\t\t\tEscolha: ");
        if (scanf("%d", &opcao) != 1) { limparBuffer(); opcao = -1; }
        limparBuffer();

        limparTela();

        switch (opcao) {
            case 1: listarLugares(); pressioneEnter(); break;
            case 2: filtrarPorCategoria(); break;
            case 3: adicionarComentario(); break;
                //case 4: listarComentarios(); break;
            case 5: return;
            default: printf(RED"Opcao invalida!\n"RESET); pressioneEnter();
        }

    } while (1);
}

void listarLugares() {
    limparTela();
    iconelistar();

    if (numLugares == 0) {
        printf("Nenhum lugar cadastrado.\n");
        return;
    }

    int porPagina = 1;  // Apenas 1 local por página
    int pagina = 0;
    int totalPaginas = (numLugares + porPagina - 1) / porPagina;

    while (1) {
        limparTela();
        iconelistar();

        printf(GREEN "\t\t\t\t\t=== LISTA DE LUGARES (%d) - Pagina %d/%d ===\n\n" RESET,
            numLugares, pagina + 1, totalPaginas);

        int i = pagina;
        Local *l = &listaLugares[i];

        printf("\t\t\t%d) %s\n", i + 1, l->nome);

        printf("\t\t\tDescricao:\n");

        int tam = strlen(l->descricao);
        int maxChars = 80;
        int maxLinhas = 6;

        for (int linha = 0; linha < maxLinhas; linha++) {
            int ini = linha * maxChars;

            if (ini >= tam)
                break;

            char buffer[85];
            strncpy(buffer, l->descricao + ini, maxChars);
            buffer[maxChars] = '\0';

            printf("\t\t\t   %s\n", buffer);
        }

        if (tam > maxLinhas * maxChars)
            printf("\t\t\t   ...\n");


        //        DADOS DO LOCAL
        printf("\t\t\tEndereco: %s | CEP: %s\n",
            l->endereco.rua, l->endereco.cep);

        printf("\t\t\tContato: ");
        if (l->contato.qtdeTelefone == 0) printf("nenhum");
        else {
            for (int t = 0; t < l->contato.qtdeTelefone; t++) {
                if (t) printf(", ");
                printf("%s", l->contato.telefones[t]);
            }
        }

        printf("\n\t\t\tCategorias: ");
        if (l->qtdTipos == 0) printf("nenhuma");
        else {
            for (int c = 0; c < l->qtdTipos; c++) {
                if (c) printf(", ");
                printf("%s", obterNomeTipoDeLugar(l->tipos[c]));
            }
        }

        printf("\n\n");

        //       MENU DE NAVEGAÇÃO
        printf("" RED "Opcoes:" RESET "\n");
        if (pagina > 0) printf("" RED "V" RESET " - Voltar pagina");
        if (pagina < totalPaginas - 1) printf("\t\t" RED "P" RESET " - Proxima pagina");
        printf("\t\t\t\t" RED "S" RESET " - Sair\n");
        printf("Escolha: ");

        char opcao;
        scanf(" %c", &opcao);
        opcao = toupper(opcao);

        if (opcao == 'P' && pagina < totalPaginas - 1) {
            pagina++;
        } else if (opcao == 'V' && pagina > 0) {
            pagina--;
        } else if (opcao == 'S') {
            return;
        } else {
            printf(RED "Opcao invalida!\n" RESET);
            pressioneEnter();
        }
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

    printf("\n\t\t\t\t\t\t=== FILTRAR POR CATEGORIA ===\n");
    printf("\t\t\t1 - Patrimonio Historico     6 - Culinaria Regional      11 - Museu\n");
    printf("\t\t\t2 - Cultural                 7 - Indigena                12 - Cinema\n");
    printf("\t\t\t3 - Igreja                   8 - Bar                     13 - Saude Publica\n");
    printf("\t\t\t4 - Gastronomia              9 - Restaurante             14 - Outro\n");
    printf("\t\t\t5 - Culinaria Brasileira     10 - Mercado\n");
    printf("\n\t\t\tEscolha uma categoria: ");

    if (scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 14) {
        limparBuffer();
        printf("\nOpcao invalida!\n");
        pressioneEnter();
        return;
    }
    limparBuffer();

    TipoDeLugar categoriaEscolhida = obterEnumTipoDeLugar(opcao);

    //    CRIA UMA LISTA TEMPORÁRIA COM RESULTADOS
    Local *resultado[100];
    int qtd = 0;

    for (int i = 0; i < numLugares; i++) {
        int temCategoria = 0;

        for (int t = 0; t < listaLugares[i].qtdTipos; t++) {
            if (listaLugares[i].tipos[t] == categoriaEscolhida) {
                temCategoria = 1;
                break;
            }
        }

        if (temCategoria) {
            resultado[qtd++] = &listaLugares[i];
        }
    }

    if (qtd == 0) {
        printf("\nNenhum lugar encontrado para essa categoria.\n");
        pressioneEnter();
        return;
    }

    //       PAGINAÇÃO (2 LOCAIS POR PÁGINA)
    int porPagina = 2;
    int pagina = 0;
    int totalPaginas = (qtd + porPagina - 1) / porPagina;

    int maxChars = 80;
    int maxLinhas = 6;

    while (1) {

        limparTela();
        printf(GREEN "\n\t\t\t=== RESULTADOS (%d) - Página %d/%d ===\n\n" RESET,
            qtd, pagina + 1, totalPaginas);

        int inicio = pagina * porPagina;
        int fim = inicio + porPagina;

        if (fim > qtd)
            fim = qtd;

        // MOSTRA SOMENTE OS 2 LOCAIS DA PÁGINA
        for (int i = inicio; i < fim; i++) {
            Local *l = resultado[i];

            printf("\t\t\t--- %s ---\n", l->nome);
            printf("\t\t\tDescricao:\n");

            int tam = strlen(l->descricao);

            for (int linha = 0; linha < maxLinhas; linha++) {
                int ini = linha * maxChars;
                if (ini >= tam)
                    break;

                char buffer[85];
                strncpy(buffer, l->descricao + ini, maxChars);
                buffer[maxChars] = '\0';

                printf("\t\t\t   %s\n", buffer);
            }

            if (tam > maxLinhas * maxChars)
                printf("\t\t\t   ...\n");

            printf("\t\t\tEndereco: %s, CEP %s\n",
                l->endereco.rua, l->endereco.cep);

            printf("\t\t\tEntrada: R$ %.2f\n", l->entrada);
            printf("\t\t\tRanking: %.1f\n\n", l->ranking);
        }


        //             MENU DE NAVEGAÇÃO
        printf(RED "Opcoes:\n" RESET);
        if (pagina > 0) printf(RED "V" RESET " - Voltar pagina\n");
        if (pagina < totalPaginas - 1) printf(RED "P" RESET " - Proxima pagina\n");
        printf(RED "S" RESET " - Sair\n");
        printf("Escolha: ");

        char op;
        scanf(" %c", &op);
        op = toupper(op);

        if (op == 'P' && pagina < totalPaginas - 1) {
            pagina++;
        } else if (op == 'V' && pagina > 0) {
            pagina--;
        } else if (op == 'S') {
            break;
        } else {
            printf(RED "Opcao invalida!\n" RESET);
            pressioneEnter();
        }
    }
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

        // Visualizar o local escolhido
        visualizarLocal(opcao - 1);        
    }    
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

void visualizarLocal(int indiceLocal) {
    if (indiceLocal < 0 || indiceLocal >= numLugares) return;

    Local *l = &listaLugares[indiceLocal];

    while (1) {
        limparTela();

        // CABEÇALHO DO LOCAL
        printf(GREEN"\n\t\t╔════════════════════════════════════════════════════════════════╗\n"RESET);
        printf(GREEN"\t\t║"RESET"  %-60s  "GREEN"║\n"RESET, l->nome);
        printf(GREEN"\t\t╚════════════════════════════════════════════════════════════════╝\n\n"RESET);

        // DESCRIÇÃO
        printf(GREEN"\t📝 DESCRIÇÃO:\n"RESET);
        printf("\t   %s\n\n", l->descricao);

        // INFORMAÇÕES DO LOCAL
        printf(GREEN"\t📍 ENDEREÇO:\n"RESET);
        printf("\t   %s - CEP: %s\n\n", l->endereco.rua, l->endereco.cep);

        printf(GREEN"\t📞 CONTATO:\n"RESET);
        if (l->contato.qtdeTelefone > 0) {
            printf("\t   Telefones: ");
            for (int t = 0; t < l->contato.qtdeTelefone; t++) {
                if (t > 0) printf(", ");
                printf("%s", l->contato.telefones[t]);
            }
            printf("\n");
        }
        if (strlen(l->contato.email) > 0) {
            printf("\t   Email: %s\n", l->contato.email);
        }
        if (strlen(l->contato.site) > 0) {
            printf("\t   Site: %s\n", l->contato.site);
        }
        printf("\n");

        // CATEGORIAS
        printf(GREEN"\t🏷️  CATEGORIAS:\n"RESET);
        printf("\t   ");
        if (l->qtdTipos == 0) {
            printf("Nenhuma categoria");
        } else {
            for (int c = 0; c < l->qtdTipos; c++) {
                if (c > 0) printf(", ");
                printf("%s", obterNomeTipoDeLugar(l->tipos[c]));
            }
        }
        printf("\n\n");

        // ENTRADA E RANKING
        printf(GREEN"\t💰 ENTRADA:\n"RESET);
        printf("\t   R$ %.2f\n\n", l->entrada);

        printf(GREEN"\t⭐ RANKING:\n"RESET);
        if (l->numComentarios > 0) {
            printf("\t   %.1f/5.0 (%d avaliações)\n\n", l->ranking, l->numComentarios);
        } else {
            printf("\t   Sem avaliações ainda\n\n");
        }

        // COMENTÁRIOS
        printf(GREEN"\t💬 COMENTÁRIOS (%d):\n"RESET, l->numComentarios);
        printf("\t   ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        if (l->numComentarios == 0) {
            printf("\t   Nenhum comentário ainda. Seja o primeiro a comentar!\n");
        } else {
            // Mostrar últimos 3 comentários
            int inicio = (l->numComentarios > 3) ? l->numComentarios - 3 : 0;

            for (int i = inicio; i < l->numComentarios; i++) {
                Comentario *c = &l->comentarios[i];
                printf("\n\t   👤 %s", c->autor);
                printf(" - ⭐ %.1f\n", c->nota);
                printf("\t   \"%s\"\n", c->texto);

                if (i < l->numComentarios - 1) {
                    printf("\t   ──────────────────────────────────────────────────────────\n");
                }
            }

            if (l->numComentarios > 3) {
                printf("\n\t   ... e mais %d comentário(s)\n", l->numComentarios - 3);
            }
        }

        printf("\t   ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

        // MENU DE OPÇÕES
        printf(RED"\t╔═══════════════════════════════════╗\n"RESET);
        printf(RED"\t║"RESET"  [C] Adicionar Comentário      "RED"║\n"RESET);
        printf(RED"\t║"RESET"  [V] Ver Todos os Comentários  "RED"║\n"RESET);
        printf(RED"\t║"RESET"  [S] Voltar                    "RED"║\n"RESET);
        printf(RED"\t╚═══════════════════════════════════╝\n"RESET);
        printf("\n\tEscolha: ");

        char opcao;
        scanf(" %c", &opcao);
        limparBuffer();
        opcao = toupper(opcao);

        if (opcao == 'C') {
            adicionarComentarioNoLocal(l);
        } else if (opcao == 'V') {
            verTodosComentarios(l);
        } else if (opcao == 'S') {
            return;
        } else {
            printf(RED"\n\tOpção inválida!\n"RESET);
            pressioneEnter();
        }
    }
}

void adicionarComentarioNoLocal(Local *l) {
    if (l->numComentarios >= MAX_COMENTARIO) {
        limparTela();
        printf(RED"\n\tEste local atingiu o limite de comentários.\n"RESET);
        pressioneEnter();
        return;
    }

    limparTela();
    printf(GREEN"\n\t╔════════════════════════════════════════════════════════════════╗\n"RESET);
    printf(GREEN"\t║"RESET"  ADICIONAR COMENTÁRIO - %-38s  "GREEN"║\n"RESET, l->nome);
    printf(GREEN"\t╚════════════════════════════════════════════════════════════════╝\n\n"RESET);

    Comentario *c = &l->comentarios[l->numComentarios];

    // Usar automaticamente o nome do usuário logado
    if (currentUser[0] != '\0') {
        strncpy(c->autor, currentUser, sizeof(c->autor) - 1);
        c->autor[sizeof(c->autor) - 1] = '\0';
        printf(GREEN"\t👤 Autor: "RESET"%s (usuário logado)\n\n", c->autor);
    } else {
        printf(GREEN"\t👤 Seu nome: "RESET);
        fgets(c->autor, sizeof(c->autor), stdin);
        trim_nl(c->autor);
        printf("\n");
    }

    printf(GREEN"\t💬 Seu comentário:\n\t   "RESET);
    fgets(c->texto, sizeof(c->texto), stdin);
    trim_nl(c->texto);

    printf(GREEN"\n\t⭐ Sua nota (0 a 5): "RESET);
    while (1) {
        if (scanf("%f", &c->nota) != 1 || c->nota < 0 || c->nota > 5) {
            limparBuffer();
            printf("\033[1A\033[2K");
            printf(RED"\t⭐ Nota inválida! Digite novamente (0 a 5): "RESET);
        } else {
            break;
        }
    }
    limparBuffer();

    l->numComentarios++;

    // Recalcular ranking médio
    float soma = 0;
    for (int i = 0; i < l->numComentarios; i++) {
        soma += l->comentarios[i].nota;
    }
    l->ranking = soma / l->numComentarios;

    printf(GREEN"\n\t✅ Comentário adicionado com sucesso!\n"RESET);
    printf("\t   Novo ranking do local: %.1f/5.0\n", l->ranking);
    pressioneEnter();
}

void verTodosComentarios(Local *l) {
    limparTela();

    printf(GREEN"\n\t╔════════════════════════════════════════════════════════════════╗\n"RESET);
    printf(GREEN"\t║"RESET"  TODOS OS COMENTÁRIOS - %-38s  "GREEN"║\n"RESET, l->nome);
    printf(GREEN"\t╚════════════════════════════════════════════════════════════════╝\n\n"RESET);

    if (l->numComentarios == 0) {
        printf("\t   Nenhum comentário ainda.\n\n");
    } else {
        printf(GREEN"\t   Total: %d comentário(s) | Ranking: %.1f/5.0\n\n"RESET,
            l->numComentarios, l->ranking);

        for (int i = 0; i < l->numComentarios; i++) {
            Comentario *c = &l->comentarios[i];

            printf("\t   ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
            printf("\t   👤 %s", c->autor);
            printf(" - ⭐ %.1f\n", c->nota);
            printf("\t   💬 \"%s\"\n", c->texto);
        }
        printf("\t   ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    }

    printf("\n");
    pressioneEnter();
}