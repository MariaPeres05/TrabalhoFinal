#ifndef Livro_H
#define Livro_H

typedef struct {
    char isbn[50];
    char titulo[100];
    char autor[50];
    char area[30];
    int ano;
} Livro;


// Function prototypes
void AddLivro(Livro Livro);
void ListarLivrosPorArea();
Livro* BuscarLivroPorISBN(const char *isbn);
void DevolverLivro(const char *isbn, const char *id_requisitante);
void ListarLivrosMaisRecentes();

#endif // Livro_H
