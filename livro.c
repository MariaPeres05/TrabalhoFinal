#include "livro.h"
#include "lista.h"
#include "hashing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "texto.h"
#include "requisicao.h"


typedef struct NoArea {
    char area[50];
    No *livros;
    struct NoArea *prox;
} NoArea;


void AddLivro(Livro livro) {
    Livro *novoLivro = (Livro *)malloc(sizeof(Livro));
    if (!novoLivro) return;
    *novoLivro = livro;
    AddNo(&Livros, novoLivro);
    //printf("Livro isbn: [%s]", livro.isbn);
    InserirEntrada(Livro_hash_table, livro.isbn, novoLivro);
}

void ListarLivrosPorArea() {
    NoArea *areas = NULL;
    // Agrupar livros por área
    No *atual = Livros;
    while (atual) {
        Livro *livro = (Livro *)atual->dados;
        NoArea *noArea = areas;
        NoArea *antNoArea = NULL;
        // Procurar se a área já existe na lista de áreas
        while (noArea && strcmp(noArea->area, livro->area) != 0) {
            antNoArea = noArea;
            noArea = noArea->prox;
        }
        // Se a área não existir, criar uma nova
        if (!noArea) {
            noArea = (NoArea *)malloc(sizeof(NoArea));
            if (!noArea) return;
            strcpy(noArea->area, livro->area);
            noArea->livros = NULL;
            noArea->prox = NULL;

            // Adicionando nova área à lista
            if (!antNoArea) {
                areas = noArea;
            } else {
                antNoArea->prox = noArea;
            }
        }
        // Adicionar o livro à lista de livros da área correspondente
        Livro *livroCopia = (Livro *)malloc(sizeof(Livro));
        if (!livroCopia) return;
        memcpy(livroCopia, livro, sizeof(Livro));
        AddNo(&(noArea->livros), livroCopia);

        atual = atual->prox;
    }
    // Exibir os livros agrupados por área
    NoArea *noArea = areas;
    while (noArea) {
        printf("Area: %s\n", noArea->area);
        No *livroNo = noArea->livros;
        while (livroNo) {
            Livro *livro = (Livro *)livroNo->dados;
            printf("  ISBN: %s, Titulo: %s, Autor: %s, Ano: %d\n",
                   livro->isbn, livro->titulo, livro->autor, livro->ano);
            livroNo = livroNo->prox;
        }
        noArea = noArea->prox;
        printf("\n");
    }

    // Liberar a memória alocada para os nós de área
    while (areas) {
        NoArea *tmp = areas;
        areas = areas->prox;
        // Liberar memória alocada para os livros na área
        while (tmp->livros) {
            No *livroNo = tmp->livros;
            tmp->livros = livroNo->prox;
            free(livroNo->dados);
            free(livroNo);
        }
        free(tmp);
    }
}

Livro* BuscarLivroPorISBN(const char *isbn) {
    Livro *livro = (Livro *)ObterValor(Livro_hash_table, isbn);
    if (livro) {
        printf("Encontrar Livro:\n ISBN: %s, titulo: %s, autor: %s, Area: %s, ano: %d\n",
               livro->isbn, livro->titulo, livro->autor, livro->area, livro->ano);
    } else {
        printf("Livro nao encontrado.\n");
    }
}

void DevolverLivro(const char *isbn, const char *id_requisitante) {
    No **atual = &Requisicoes;
    while (*atual) {
        Requisicao *req = (Requisicao *)(*atual)->dados;
        if (strcmp(req->isbn, isbn) == 0 && strcmp(req->id_requisitante, id_requisitante) == 0) {
            No *temp = *atual;
            *atual = (*atual)->prox;
            free(temp->dados);
            free(temp);
            return;
        }
        atual = &(*atual)->prox;
    }
}

void ListarLivrosMaisRecentes() {
    if (!Livros) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }
    int anoMaisRecente = 0;
    No *atual = Livros;
    // Encontrar o ano mais recente
    while (atual) {
        Livro *livro = (Livro *)atual->dados;
        if (livro->ano > anoMaisRecente) {
            anoMaisRecente = livro->ano;
        }
        atual = atual->prox;
    }
    // Listar todos os livros que foram publicados no ano mais recente
    printf("Livros mais recentes (ano %d):\n", anoMaisRecente);
    atual = Livros;
    while (atual) {
        Livro *livro = (Livro *)atual->dados;
        if (livro->ano == anoMaisRecente) {
            printf("ISBN: %s, Título: %s, Autor: %s, Área: %s, Ano: %d\n",
                   livro->isbn, livro->titulo, livro->autor, livro->area, livro->ano);
        }
        atual = atual->prox;
    }
}

