#ifndef Requisicao_H
#define Requisicao_H

typedef struct {
    char id_requisitante[10];
    char isbn[50];
    char data[11];
} Requisicao;

// Function prototypes
void RequisitarLivro(Requisicao requisicao);
void ListarAtuaisRequisicoes();
void ListarRequisicoesPorArea();
int CompararRequisicoesPorArea(const void *a, const void *b);

#endif // Requisicao_H
