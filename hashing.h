#ifndef HASHING_H
#define HASHING_H

#define HASH_TABLE_SIZE 100

// Hash table Entrada 
typedef struct Entrada {
    char *key;
    void *valor;
    struct Entrada *prox;
} Entrada;


unsigned int hash(const char *key);
Entrada* CriarEntrada(const char *key, void *valor);
void InserirEntrada(Entrada **hash_table, const char *key, void *valor);
void* ObterValor(Entrada **hash_table, const char *key);
void DestruirHashing(Entrada **hash_table);

// Declare the hash tables as extern
extern Entrada *Livro_hash_table[HASH_TABLE_SIZE];
extern Entrada *requisitante_hash_table[HASH_TABLE_SIZE];

#endif // HASHING_H
