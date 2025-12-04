#ifndef GERENTE_H
#define GERENTE_H

#define MAX_LOCAIS 50
#define MAX_COMENTARIO 100
#define MAX_TELEFONES 3
#define MAX_TIPOS 10
#define MAX_NOME 100

typedef enum {
    PATRIMONIO_HISTORICO = 1,
    CULTURAL = 2,
    IGREJA = 3,
    GASTRONOMIA = 4,
    CULINARIA_BRASILEIRA = 5,
    CULINARIA_REGIONAL = 6,
    INDIGENA = 7,
    BAR = 8,
    RESTAURANTE = 9,
    MERCADO = 10,
    MUSEU = 11,
    CINEMA = 12,
    UNIDADE_SAUDE_PUBLICA = 13,
    OUTRO = 14
} TipoDeLugar;

typedef struct {
    char rua[100];
    char cep[20];
} Endereco;

typedef struct {
    char telefones[MAX_TELEFONES][20];
    int qtdeTelefone;
    char email[100];
    char site[100];
} Contato;

typedef struct {
    char autor[50];
    char texto[500];
    float nota;
} Comentario;

typedef struct {
    char nome[100];
    char descricao[500];
    Endereco endereco;
    Contato contato;
    float ranking;
    TipoDeLugar tipos[MAX_TIPOS];
    int qtdTipos;
    float entrada;
    Comentario comentarios[MAX_COMENTARIO];
    int numComentarios;
} Local;

int loginAdmin();
void menuAdmin();
void inserirLugar();
int login();
void cadastrarUsuario();
int menuInicial();
void salvarTxt(const char *nome_arquivo);
void carregarTxt(const char *nome_arquivo);



extern Local listaLugares[MAX_LOCAIS];
extern int numLugares;

#endif