#ifndef REQUISITANTE_H
#define REQUISITANTE_H
#include "lista.h"
#include "hashing.h"

typedef struct {
    char id[10];
    char nome[50];
    char dataNascimento[11];
    char id_freguesia[7];
} Requisitante;



void AddRequisitante(Requisitante requisitante);
void ListarRequisitantes();
void ListarRequisitantePorNome(const char *nome);
int ValidarIDRequisitante(const char id[]);
int ValidarData(const char *data);
int ValidarIDFreguesia(const char id[]);
void DeterminarIdadeMaisRequisitantes();
void ContarPessoasIdadeSuperior(int idadeMinima);
void DeterminarMediaIdades();
void DeterminarIdadeMaxima();
int calcularIdade(const char *dataNascimento);
void DeterminarSobrenomeMaisUsado();

#endif // REQUISITANTE_H
