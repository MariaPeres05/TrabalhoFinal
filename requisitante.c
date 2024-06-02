#include "requisitante.h"
#include "lista.h"
#include "hashing.h"
#include <stdio.h>
#include <stdlib.h>
#include "texto.h"
#include <ctype.h>
#include <string.h>
#include <time.h>


void AddRequisitante(Requisitante requisitante) {
    Requisitante *novoRequisitante = (Requisitante *)malloc(sizeof(Requisitante));
    if (!novoRequisitante) return;
    *novoRequisitante = requisitante;
    AddNo(&Requisitantes, novoRequisitante);
    InserirEntrada(requisitante_hash_table, requisitante.id, novoRequisitante);
}

int CompararRequisitantes(const void *a, const void *b) {
    Requisitante *reqA = *(Requisitante **)a;
    Requisitante *reqB = *(Requisitante **)b;
    return strcmp(reqA->nome, reqB->nome);
}

void ListarRequisitantes() {
    int count = 0;
    No *atual = Requisitantes;
    while (atual) {
        count++;
        atual = atual->prox;
    }
    Requisitante **array = (Requisitante **)malloc(count * sizeof(Requisitante *));
    if (array == NULL) {
        perror("Falha na alocação de memória para array de requisitantes");
        return;
    }
    atual = Requisitantes;
    for (int i = 0; i < count; i++) {
        array[i] = (Requisitante *)atual->dados;
        atual = atual->prox;
    }
    qsort(array, count, sizeof(Requisitante *), CompararRequisitantes);
    printf("Requisitantes ordenados:\n");
    for (int i = 0; i < count; i++) {
        Requisitante *req = array[i];
        printf("ID: %s, Nome: %s, Data de Nascimento: %s, Freguesia ID: %s\n",
               req->id, req->nome, req->dataNascimento, req->id_freguesia);
    }
    free(array);
}


int ValidarIDRequisitante(const char id[]) {
   if (strlen(id) != 9) {
        return 0; // O ID deve ter exatamente 9 caracteres
    }
    int soma = 0;
    for (int i = 0; i < 9; i++) {
        if (id[i] < '0' || id[i] > '9') {
            return 0; // Todos os caracteres devem ser dígitos
        }
        soma += id[i] - '0'; // Converte o caractere para o valor inteiro correspondente
    }
    return soma % 10 == 0; // Verifica se a soma é múltiplo de 10
}


int ValidarIDFreguesia(const char id[]) {
   if (strlen(id) != 6) {
        return 0; // O ID deve ter 6 caracteres
    }
    for (int i = 0; i < 4; i++) {
        if (!isdigit((unsigned char)id[i])) {
            return 0; // Os primeiros 4 caracteres devem ser dígitos
        }
    }
    // Os últimos 2 caracteres podem ser dígitos ou letras
    for (int i = 4; i < 6; i++) {
        if (!isalnum((unsigned char)id[i])) {
            return 0; // Verifica se é um carácter alfanumérico
        }
    }
    return 1;
}

void ListarRequisitantePorNome(const char *nome){
    No *atual = Requisitantes;
    int encontrado = 0;
    while (atual) {
        Requisitante *req = (Requisitante *)atual->dados;
        if (strstr(req->nome, nome) != NULL) {  // Verifica se o nome contém o substring
            printf("Encontrar requisitante:\n Nome: %s, ID: %s, Data de Nascimento: %s, ID Freguesia: %s\n",
                   req->nome, req->id, req->dataNascimento, req->id_freguesia);
            encontrado = 1;
        }
        atual = atual->prox;
    }
    if (!encontrado) {
        printf("Requisitante nao encontrado.\n");
    }
}

// Função para calcular a idade com base na data de nascimento
int calcularIdade(const char *dataNascimento) {
    int dia, mes, ano;
    sscanf(dataNascimento, "%d-%d-%d", &dia, &mes, &ano);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int idade = tm.tm_year + 1900 - ano;
    if (tm.tm_mon + 1 < mes || (tm.tm_mon + 1 == mes && tm.tm_mday < dia)) {
        idade--;
    }
    return idade;
}

void DeterminarIdadeMaxima() {
    if (Requisitantes == NULL) {
        printf("Nenhum requisitante cadastrado.\n");
        return;
    }

    No *atual = Requisitantes;
    int idadeMaxima = 0;
    while (atual) {
        Requisitante *req = (Requisitante *)atual->dados;
        int idade = calcularIdade(req->dataNascimento);
        if (idade > idadeMaxima) {
            idadeMaxima = idade;
        }
        atual = atual->prox;
    }

    printf("A idade máxima dos requisitantes é: %d anos\n", idadeMaxima);
}

void DeterminarMediaIdades() {
    if (Requisitantes == NULL) {
        printf("Nenhum requisitante cadastrado.\n");
        return;
    }
    No *atual = Requisitantes;
    int somaIdades = 0;
    int contador = 0;

    while (atual) {
        Requisitante *req = (Requisitante *)atual->dados;
        somaIdades += calcularIdade(req->dataNascimento);
        contador++;
        atual = atual->prox;
    }
    double mediaIdades = (double)somaIdades / contador;
    printf("A média das idades dos requisitantes é: %.2f anos\n", mediaIdades);
}

void ContarPessoasIdadeSuperior(int idadeMinima) {
    if (Requisitantes == NULL) {
        printf("Nenhum requisitante cadastrado.\n");
        return;
    }
    No *atual = Requisitantes;
    int contador = 0;
    while (atual) {
        Requisitante *req = (Requisitante *)atual->dados;
        int idade = calcularIdade(req->dataNascimento);
        if (idade > idadeMinima) {
            contador++;
        }
        atual = atual->prox;
    }
    printf("Número de requisitantes com idade superior a %d anos: %d\n", idadeMinima, contador);
}

void DeterminarIdadeMaisRequisitantes() {
    if (Requisitantes == NULL) {
        printf("Nenhum requisitante cadastrado.\n");
        return;
    }
    No *atual = Requisitantes;
    int idades[150] = {0}; // Supondo que ninguém tem mais de 150 anos
    while (atual) {
        Requisitante *req = (Requisitante *)atual->dados;
        int idade = calcularIdade(req->dataNascimento);
        if (idade >= 0 && idade < 150) {
            idades[idade]++;
        }
        atual = atual->prox;
    }
    int maxRequisitantes = 0;
    int idadeMaisRequisitantes = 0;
    for (int i = 0; i < 150; i++) {
        if (idades[i] > maxRequisitantes) {
            maxRequisitantes = idades[i];
            idadeMaisRequisitantes = i;
        }
    }
    printf("A idade com mais requisitantes é: %d anos, com %d requisitantes\n", idadeMaisRequisitantes, maxRequisitantes);
}

void DeterminarSobrenomeMaisUsado() {
    if (!Requisitantes) {
        printf("Nenhum requisitante cadastrado.\n");
        return;
    }
    typedef struct {
        char sobrenome[50];
        int count;
    } SobrenomeCount;

    SobrenomeCount *sobrenomes = NULL;
    int sobrenomeCount = 0;
    No *atual = Requisitantes;
    while (atual) {
        Requisitante *req = (Requisitante *)atual->dados;
        char *token = strtok(req->nome, " ");
        char *ultimoToken = token;
        while (token) {
            ultimoToken = token;
            token = strtok(NULL, " ");
        }
        int encontrado = 0;
        for (int i = 0; i < sobrenomeCount; i++) {
            if (strcmp(sobrenomes[i].sobrenome, ultimoToken) == 0) {
                sobrenomes[i].count++;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
      sobrenomes = realloc(sobrenomes, (sobrenomeCount + 1) * sizeof(SobrenomeCount));
            if (!sobrenomes) {
                perror("Erro ao alocar memória para sobrenomes");
                return;
            }
            strcpy(sobrenomes[sobrenomeCount].sobrenome, ultimoToken);
            sobrenomes[sobrenomeCount].count = 1;
            sobrenomeCount++;
        }
        atual = atual->prox;
    }
    int maxCount = 0;
    char sobrenomeMaisUsado[50];
    for (int i = 0; i < sobrenomeCount; i++) {
        if (sobrenomes[i].count > maxCount) {
            maxCount = sobrenomes[i].count;
            strcpy(sobrenomeMaisUsado, sobrenomes[i].sobrenome);
        }
    }
    printf("Sobrenome mais usado: %s, usado %d vezes.\n", sobrenomeMaisUsado, maxCount);
    free(sobrenomes);
}
