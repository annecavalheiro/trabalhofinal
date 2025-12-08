#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "gerente.h"
#include "turista.h"
#include "utils.h"

/*
Compilar:
gcc GUIA_TURISTICO.c gerente.c turista.c utils.c interface.c -o guia -Wall -Wextra -std=c99
*/

int main() {
    #ifdef _WIN32        
        system("chcp 65001 > nul");  /* altera code page do terminal */        
    #else
        setlocale(LC_ALL, "pt_BR.UTF-8");
    #endif
    
    carregarTxt("lugares.dat"); // tenta carregar dados no inicio (se existir)

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