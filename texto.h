#ifndef TEXTO_H
#define TEXTO_H

#include <stdio.h>
#include <stdlib.h>
#include "requisitante.h"
#include "livro.h"

typedef struct Concelho {
    int id;
    char nome[100];
    struct Concelho* prox;
} Concelho;

typedef struct Distrito {
    int id;
    char nome[100];
    Concelho* concelhos;
    struct Distrito* prox;
} Distrito;

void CarregarRequisitantes(const char *filenome);
void CarregarLivros(const char *filenome);
void SalvarLivros(const char *filename);
void SalvarLivro(const char *filename, const char *isbn);
void SalvarRequisitantes(const char *filename);
void CarregarDistritos(const char *filenome);
void CarregarConcelhos(const char *filenome);
void SalvarErro(const char *error_message, const char *linha);
void SalvarRequisicoes(const char *filename);

#endif // TEXTO_H
