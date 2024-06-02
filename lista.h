#ifndef LISTA_H
#define LISTA_H


typedef struct No {
    void *dados;
    struct No *prox;
} No;


No* CriarNo(void *dados);
void AddNo(No **head, void *dados);
void DestruirLista(No *head, void (*LiberarDados)(void *));

extern No *Requisitantes;
extern No *Livros;
extern No *Requisicoes;

#endif // LISTA_H
