#include "requisitante.h"
#include "lista.h"
#include "hashing.h"
#include <stdio.h>
#include <stdlib.h>
#include "texto.h"
#include <ctype.h>
#include <string.h>
#include "requisicao.h"
#include "livro.h"

void RequisitarLivro(Requisicao requisicao) {
    Requisicao *novaRequisicao = (Requisicao *)malloc(sizeof(Requisicao));
    if (!novaRequisicao) return;
    *novaRequisicao = requisicao;
    AddNo(&Requisicoes, novaRequisicao);
    SalvarRequisicoes("requisicoes.txt");  // Salva no arquivo após adicionar
}

void ListarAtuaisRequisicoes() {
    No *atual = Requisicoes;
    while (atual) {
        Requisicao *req = (Requisicao *)atual->dados;
        printf("Requisitante ID: %s, ISBN: %s, data: %s\n",
               req->id_requisitante, req->isbn, req->data);
        atual = atual->prox;
    }
}

void ListarRequisicoesPorArea() {
    if (Requisicoes == NULL) {
        printf("Nenhuma requisição cadastrada.\n");
        return;
    }
    No *atual = Requisicoes;
    Requisicao **arrayRequisicoes = NULL;
    int count = 0;
    while (atual) {
        arrayRequisicoes = realloc(arrayRequisicoes, (count + 1) * sizeof(Requisicao *));
        if (!arrayRequisicoes) {
            perror("Erro ao alocar memória para as requisições");
            return;
        }
        arrayRequisicoes[count++] = (Requisicao *)atual->dados;
        atual = atual->prox;
    }
    qsort(arrayRequisicoes, count, sizeof(Requisicao *), CompararRequisicoesPorArea);
    printf("Requisições ordenadas por área:\n");
    for (int i = 0; i < count; i++) {
        Requisicao *req = arrayRequisicoes[i];
        Livro *livro = BuscarLivroPorISBN(req->isbn);
        if (livro) {
            printf("Área: %s, ISBN: %s, Título: %s, Requisitante ID: %s, Data: %s\n",
                   livro->area, livro->isbn, livro->titulo, req->id_requisitante, req->data);
        }
    }
    free(arrayRequisicoes);
}

int CompararRequisicoesPorArea(const void *a, const void *b) {
    Requisicao *reqA = *(Requisicao **)a;
    Requisicao *reqB = *(Requisicao **)b;
    Livro *livroA = BuscarLivroPorISBN(reqA->isbn);
    Livro *livroB = BuscarLivroPorISBN(reqB->isbn);
    if (livroA && livroB) {
        return strcmp(livroA->area, livroB->area);
    }
    return 0;
}