#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gerente.h"
#include "turista.h"


/*
    Compilar:
    gcc GUIA_TURISTICO.c gerente.c turista.c utils.c interface.c -o guia -Wall -Wextra -std=c99
*/

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