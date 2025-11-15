#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Códigos ANSI para cores
#define RESET "\033[0m"
#define GREEN "\033[1;32m"
#define RED   "\033[1;31m"
#define YELLOW "\033[1;33m"

typedef struct {
    char nome[50];
    char tipo[20];  // "Turismo" ou "Bar"
    char localizacao[100];
    char onibus[100];
    char dica[200];
    int perigoso; // 1 = sim, 0 = não
} Ponto;

int main() {
    Ponto locais[] = {
        {"Teatro Amazonas", "Turismo", "Largo de Sao Sebastiao", "120, 300, 350, 450, 640",
         "Evite circular sozinho a noite em ruas pouco movimentadas.", 0},

        {"Mercado Municipal Adolpho Lisboa", "Turismo", "Rua dos Bares, Centro", "005, 011, 120, 214, 215, 640",
         "Cuidado com pertences em locais cheios; prefira visitar de dia.", 0},

        {"Porto de Manaus", "Turismo", "Roadway, Centro", "005, 010, 120, 214, 215",
         "Evite horarios de pouco fluxo e mantenha atencao a pertences.", 0},

        {"Praca Sao Sebastiao", "Turismo", "Largo de Sao Sebastiao", "120, 300, 350, 450, 640",
         "Local tranquilo, mas evite permanecer sozinho tarde da noite.", 0},

        {"Praca dos Remedios", "Turismo", "Centro, proximo ao Porto", "005, 011, 120, 214",
         "Ha relatos de furtos e uso de drogas em horarios de menor movimento.", 1},

        {"Igreja da Matriz", "Turismo", "Praca da Matriz, proxima ao Porto", "005, 010, 120, 214, 215",
         "Ha registros de crimes nas proximidades; evite horarios vazios.", 1},

        {"Bar Caldeira", "Bar", "Rua Jose Clemente, proximo ao Teatro Amazonas", "120, 300, 350, 450",
         "Movimento intenso a noite; evite deixar objetos desacompanhados.", 0},

        {"Bar do Armando", "Bar", "Largo de Sao Sebastiao", "120, 300, 350, 450, 640",
         "Movimentado e seguro, mas evite ruas desertas apos o fechamento.", 0},

        {"Gringos Bar", "Bar", "Rua 10 de Julho, proximo ao Teatro Amazonas", "120, 300, 350, 450",
         "Evite estacionar em ruas isoladas nas redondezas.", 0}
    };

    int opcao;
    int i;
    int tamanho = sizeof(locais) / sizeof(locais[0]);

    do {
        system("cls || clear");
        printf(GREEN "=============================================\n");
        printf("                 NavegAmazon\n");
        printf("=============================================\n");
        printf("  Explore o Centro de Manaus com seguranca!\n");
        printf("=============================================\n" RESET);
        printf("1 - Listar TODOS os locais\n");
        printf("2 - Filtrar apenas PONTOS TURISTICOS\n");
        printf("3 - Filtrar apenas BARES\n");
        printf("4 - Filtrar locais com RISCO DE PERIGO\n");
        printf("5 - Sair\n");
        printf("=============================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        system("cls || clear");

        switch (opcao) {
            case 1:
                printf(GREEN "=== Todos os Locais ===\n\n" RESET);
                for (i = 0; i < tamanho; i++) {
                    printf(GREEN "%s (%s)\n" RESET, locais[i].nome, locais[i].tipo);
                    printf(YELLOW "Localizacao: %s\n", locais[i].localizacao);
                    printf("Onibus: %s\n" RESET, locais[i].onibus);
                    if (locais[i].perigoso)
                        printf(RED "? Risco: %s\n" RESET, locais[i].dica);
                    else
                        printf("Dica: %s\n", locais[i].dica);
                    printf("---------------------------------------------\n");
                }
                break;

            case 2:
                printf(GREEN "=== Pontos Turisticos ===\n\n" RESET);
                for (i = 0; i < tamanho; i++) {
                    if (strcmp(locais[i].tipo, "Turismo") == 0) {
                        printf(GREEN "%s\n" RESET, locais[i].nome);
                        printf(YELLOW "Localizacao: %s\n", locais[i].localizacao);
                        printf("Onibus: %s\n" RESET, locais[i].onibus);
                        if (locais[i].perigoso)
                            printf(RED "? Risco: %s\n" RESET, locais[i].dica);
                        else
                            printf("Dica: %s\n", locais[i].dica);
                        printf("---------------------------------------------\n");
                    }
                }
                break;

            case 3:
                printf(GREEN "=== Bares ===\n\n" RESET);
                for (i = 0; i < tamanho; i++) {
                    if (strcmp(locais[i].tipo, "Bar") == 0) {
                        printf(GREEN "%s\n" RESET, locais[i].nome);
                        printf(YELLOW "Localizacao: %s\n", locais[i].localizacao);
                        printf("Onibus: %s\n" RESET, locais[i].onibus);
                        printf("Dica: %s\n", locais[i].dica);
                        printf("---------------------------------------------\n");
                    }
                }
                break;

            case 4:
                printf(RED "=== Locais com RISCO DE PERIGO ===\n\n" RESET);
                for (i = 0; i < tamanho; i++) {
                    if (locais[i].perigoso == 1) {
                        printf(GREEN "%s (%s)\n" RESET, locais[i].nome, locais[i].tipo);
                        printf(YELLOW "Localizacao: %s\n", locais[i].localizacao);
                        printf("Onibus: %s\n" RESET, locais[i].onibus);
                        printf(RED "? Alerta: %s\n" RESET, locais[i].dica);
                        printf("---------------------------------------------\n");
                    }
                }
                break;

            case 5:
                printf(GREEN "Encerrando o programa... Obrigado por usar o NavegAmazon!\n" RESET);
                break;

            default:
                printf(RED "Opcao invalida! Tente novamente.\n" RESET);
        }

        if (opcao != 5) {
            printf("\nPressione ENTER para voltar ao menu...");
            getchar(); // limpa o buffer
            getchar(); // espera ENTER
        }

    } while (opcao != 5);

    return 0;
}
