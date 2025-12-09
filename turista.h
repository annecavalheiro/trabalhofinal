#ifndef TURISTA_H
#define TURISTA_H

#include "gerente.h"

void menuUsuario();
void listarLugares();
void filtrarPorCategoria();
const char *obterNomeTipoDeLugar(TipoDeLugar tipo);
TipoDeLugar obterEnumTipoDeLugar(int opcao);
void adicionarComentario();
void listarComentarios();
void listarEventosDaSemana();

void visualizarLocal(int indiceLocal);
void adicionarComentarioNoLocal(Local *l);
void verTodosComentarios(Local *l);


#endif
