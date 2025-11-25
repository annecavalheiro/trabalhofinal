void menuFiltragem() {
    int opc;

    printf("\n===== FILTRAGEM =====\n");
    printf("1 - FILTRAR APENAS PONTOS TURISTICOS\n");
    printf("2 - FILTRAR APENAS BARES\n");
    printf("3 - FILTRAR POR RESTAURANTES\n");
    printf("4 - FILTRAR POR HOSPITAIS\n");
    printf("5 - FILTRAR POR CINEMAS\n");
    printf("6 - FILTRAR POR LOCAIS GRATUITOS\n");
    printf("7 - VOLTAR AO MENU\n");
    printf("Escolha: ");
    scanf("%d", &opc);
    getchar();

    switch (opc) {
        case 1:
            filtrarPorTipo("Ponto Turistico");
            break;
        case 2:
            filtrarPorTipo("Bar");
            break;
        case 3:
            filtrarPorTipo("Restaurante");
            break;
        case 4:
            filtrarPorTipo("Hospital");
            break;
        case 5:
            filtrarPorTipo("Cinema");
            break;
        case 6:
            filtrarPorTipo("Gratuito");
            break;
        case 7:
            // apenas volta ao menu principal
            return;
        default:
            printf("Opcao invalida!\n");
            break;
    }
}
