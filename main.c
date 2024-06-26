#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"
#include "requisitante.h"
#include "requisicao.h"
#include "texto.h"
#include "lista.h"
#include "hashing.h"
//#include "utils.h"

No *Livros = NULL;
Entrada *Livro_hash_table[HASH_TABLE_SIZE] = {0};

void menuPrincipal() {
    printf("\nBem vindo à Biblioteca ESTGV!\n");
    printf("1. CarregarDados\n");
    printf("2. Adicionar Livro\n");
    printf("3. Listar livros por area\n");
    printf("4. Buscar livro por ISBN\n");
    printf("5. Adicionar Requisitante\n");
    printf("6. Listar Requisitantes\n");
    printf("7. Requisitar livro\n");
    printf("8. Devolver Livro\n");
    printf("9. Listar atuais requisicoes\n");
    printf("0. Sair\n");
    printf("Insira a sua escolha: ");
}

void CarregarDados() {
    CarregarRequisitantes("requisitantes.txt");
    CarregarDistritos("distritos.txt");
    CarregarConcelhos("concelhos.txt");
    CarregarLivros("livros.txt");
    // load_freguesias("freguesias.txt");
    // Add other data loading functions as needed
    printf("Dados carregados com sucesso.\n");
}

void AddLivroMenu() {
    Livro livro;
    printf("Inserir ISBN: ");
    scanf("%s", livro.isbn);
    printf("Inserir titulo: ");
    scanf(" %[^\n]%*c", livro.titulo);
    printf("Inserir autor: ");
    scanf(" %[^\n]%*c", livro.autor);
    printf("Inserir Area: ");
    scanf("%s", livro.area);
    printf("Inserir ano: ");
    scanf("%d", &livro.ano);
    AddLivro(livro);
    SalvarLivros("livros.txt");
    printf("Livro adicionado com sucesso.\n");
}

void BuscarLivroMenu() {
    char isbn[14];
    printf("Inserir ISBN: ");
    scanf("%s", isbn);
    BuscarLivroPorISBN(isbn);
}

void AddRequisitanteMenu() {
    Requisitante requisitante;
    printf("Inserir ID: ");
    scanf("%s", requisitante.id);
    printf("Inserir nome: ");
    scanf(" %[^\n]%*c", requisitante.nome);
    printf("Inserir Birth data (dd-mm-yyyy): ");
    scanf("%s", requisitante.dataNascimento);
    printf("Inserir Freguesia ID: ");
    scanf("%s", requisitante.id_freguesia);
    if (!ValidarIDRequisitante(requisitante.id)) {
        printf("ID do requisitante invalido.\n");
        return; // Retorna imediatamente se o ID do requisitante for inválido
    } 
    if (!ValidarIDFreguesia(requisitante.id_freguesia)) {
        printf("ID da freguesia invalido.\n");
        return; // Retorna imediatamente se o ID da freguesia for inválido
    } 
    AddRequisitante(requisitante);
    FILE *file = fopen("requisitantes.txt", "a"); // Salva apenas o novo requisitante no modo append
    if (!file) {
        perror("Não foi possível abrir o ficheiro de requisitantes para escrita");
        return;
    }
    fprintf(file, "%s\t%s\t%s\t%s\n",
            requisitante.id, requisitante.nome, requisitante.dataNascimento, requisitante.id_freguesia);
    fclose(file);
    
    printf("Requisitante adicionado com sucesso.\n");

}

void RequisitarLivroMenu() {
    Requisicao requisicao;
    printf("Inserir Requisitante ID: ");
    scanf("%s", requisicao.id_requisitante);
    printf("Inserir Livro ISBN: ");
    scanf("%s", requisicao.isbn);
    printf("Inserir data (dd-mm-yyyy): ");
    scanf("%s", requisicao.data);
    RequisitarLivro(requisicao);
    printf("Livro requisitado com sucesso.\n");
}

void DevolverLivroMenu() {
    char isbn[14], id_requisitante[10];
    printf("Inserir Livro ISBN: ");
    scanf("%s", isbn);
    printf("Inserir Requisitante ID: ");
    scanf("%s", id_requisitante);
    DevolverLivro(isbn, id_requisitante);
    printf("Livro devolvido com sucesso.\n");
}

int main() {

    int op;
    while (1) {
        menuPrincipal();
        scanf("%d", &op);
        switch (op) {
            case 1:
                CarregarDados();
                break;
            case 2:
                AddLivroMenu();
                break;
            case 3:
                ListarLivrosPorArea();
                break;
            case 4:
                BuscarLivroMenu();
                break;
            case 5:
                AddRequisitanteMenu();
                break;
            case 6:
                ListarRequisitantes();
                break;
            case 7:
                RequisitarLivroMenu();
                break;
            case 8:
                DevolverLivroMenu();
                break;
            case 9:
                ListarAtuaisRequisicoes();
                break;
            case 0:
                printf("A sair...\n");
                exit(0);
            default:
                printf("Escolha inválida.Tente outra vez.\n");
        }
    }
    return 0;
}
