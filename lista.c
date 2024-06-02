#include "lista.h"
#include <stdlib.h>

No *Requisicoes = NULL;
No *Livros = NULL;
No *Requisitantes = NULL;


No* CriarNo(void *dados) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (!novoNo) return NULL;
    novoNo->dados = dados;
    novoNo->prox = NULL;
    return novoNo;
}

void AddNo(No **head, void *dados) {
    No *novoNo = CriarNo(dados);
    if (!novoNo) return;
    if (!*head) {
        *head = novoNo;
    } else {
        No *atual = *head;
        while (atual->prox) {
            atual = atual->prox;
        }
        atual->prox = novoNo;
    }
}

void DestruirLista(No *head, void (*LiberarDados)(void *)) {
    No *atual = head;
    while (atual) {
        No *prox = atual->prox;
        if (LiberarDados) LiberarDados(atual->dados);
        free(atual);
        atual = prox;
    }
}
