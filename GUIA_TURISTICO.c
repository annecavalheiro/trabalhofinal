#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "gerente.h"
#include "turista.h"
#include "utils.h"
#ifdef _WIN32
#include <windows.h>
#endif


/*
    Compilar:
    gcc GUIA_TURISTICO.c gerente.c turista.c utils.c interface.c -o guia -Wall -Wextra -std=c99
*/

int main() {
    #ifdef _WIN32
        /* Ajusta code page do console para Windows-1252 e locale */
        system("chcp 1252 > nul");  /* altera code page do terminal */
        SetConsoleOutputCP(1252);
        SetConsoleCP(1252);
        setlocale(LC_ALL, "Portuguese_Brazil.1252");
    #else
        setlocale(LC_ALL, "pt_BR.UTF-8");
    #endif
    
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