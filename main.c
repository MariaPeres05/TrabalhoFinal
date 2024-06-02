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

void menuPrincipal() {
    printf("\nBem vindo à Biblioteca ESTGV!\n");
    printf("1. Carregar Dados\n");
    printf("2. Adicionar Livro\n");
    printf("3. Listar livros por area\n");
    printf("4. Buscar livro por ISBN\n");
    printf("5. Adicionar Requisitante\n");
    printf("6. Buscar Requisitante pelo nome\n");
    printf("7. Listar Requisitantes\n");
    printf("8. Requisitar livro\n");
    printf("9. Devolver Livro\n");
    printf("10. Listar atuais requisicoes\n");
    printf("11. Determinar a idade máxima de todos os requisitantes\n");
    printf("12. Determinar a média das idades de todos os requisitantes\n");
    printf("11. Determinar a idade máxima de todos os requisitantes\n");
    printf("12. Determinar a média das idades de todos os requisitantes\n");
    printf("13. Contar pessoas com idade superior a um dado valor\n");
    printf("14. Determinar a idade com mais requisitantes\n");
    printf("15. Determinar o sobrenome mais utilizado\n");
    printf("16. Listar livros mais recentes\n");
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
    SalvarLivro("livros.txt", livro.isbn);
    printf("Livro adicionado com sucesso.\n");
}

void BuscarLivroMenu() {
    char isbn[50];
    printf("Inserir ISBN: ");
    scanf("%s", isbn);
    BuscarLivroPorISBN(isbn);
}

void BuscarRequisitanteMenu (){
     char nome[50];
    printf("Inserir Nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0'; 
    ListarRequisitantePorNome(nome);
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
    SalvarRequisitantes("requisitantes.txt");
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
    char isbn[50], id_requisitante[10];
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
        getchar();
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
                BuscarRequisitanteMenu ();
                break;
            case 7:
                ListarRequisitantes();
                break;
            case 8:
                RequisitarLivroMenu();
                break;
            case 9:
                DevolverLivroMenu();
                break;
            case 10:
                 ListarAtuaisRequisicoes();
                 break;
            case 11:
                DeterminarIdadeMaxima();
                break;
            case 12:
                DeterminarMediaIdades();
                break;
            case 13: {
                int idadeMinima;
                printf("Insira a idade mínima: ");
                scanf("%d", &idadeMinima);
                ContarPessoasIdadeSuperior(idadeMinima);
                break;
            }
            case 14:
                DeterminarIdadeMaisRequisitantes();
                break;
            case 15:
                DeterminarSobrenomeMaisUsado();
                break;
            case 16:
                ListarLivrosMaisRecentes();
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
