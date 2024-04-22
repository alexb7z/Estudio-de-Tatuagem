#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cliente {
  int ficha;
  char nome[50];
  char data[6];
  float precoTatto;
};

struct no {
  Cliente dado;
  struct no *prox;
};

struct lista {
  No *inicio;
};

Lista* criaLista() {
  Lista *lista = (Lista *)malloc(sizeof(Lista));
  lista->inicio = NULL;
  return lista;
}

int InputEmailIsCorrect(char email_input[], char email[]) {
  int count = 0;
  for (int i = 0; i < 20; i++) {
    if (email_input[i] == '@') {
      count++;
    }
  }

  if (count == 1) {
    if (strlen(email_input) >= 80) {
      printf("Email inserido contem mais de 79 caracteres\n");
      return 0;
    }

    if (strcmp(email_input, email) != 0) {
      printf("Email invalido\n");
      return 0;
    }

  } else {
    printf("Email invalido, email nao contem '@' ou contem mais de um '@'\n");
    return 0;
  }

  return 1;
}

int InputPasswordIsCorrect(char password_input[], char password[]) {
  for (int i = 0; i < 9; i++) {
    if (password_input[i] != password[i]) {
      return 0;
    }
  }
  return 1;
}

void adicionaFim(Lista *lista, Cliente e) {
  No *novo = (No *)malloc(sizeof(No));
  novo->dado = e;
  novo->prox = NULL;
  if (lista->inicio == NULL) {
    lista->inicio = novo;
  } else {
    No *pi;
    for (pi = lista->inicio; pi->prox != NULL; pi = pi->prox)
      ;
    pi->prox = novo;
  }
}

void lerLista(Lista *lista) {
  FILE *file = fopen("cliente.b", "rb");
  Cliente e;

  if (file == NULL) {
    printf("Erro ao abrir o arquivo cliente.b\n");
    return;
  }

  while (fread(&e, sizeof(Cliente), 1, file)) {
    adicionaFim(lista, e);
  }
  fclose(file);
}

void salvaLista(Lista *lista) {
  FILE *file = fopen("cliente.b", "wb");
  No *pi;
  for (pi = lista->inicio; pi != NULL; pi = pi->prox) {
    fwrite(&pi->dado, sizeof(Cliente), 1, file);
  }
  fclose(file);
}

void editarFicha(Lista *lista, int ficha, float precoTatto, char data[]) {
  if (lista->inicio == NULL) {
    printf("Lista vazia\n");
  } else {
    No *pi;
    for (pi = lista->inicio; pi != NULL && pi->dado.ficha != ficha;
         pi = pi->prox)
      ;
    if (pi == NULL) {
      printf("Cliente nao encontrado\n");
    } else {
      pi->dado.precoTatto = precoTatto;
      for (int i = 0; i < 6; i++) {
        pi->dado.data[i] = data[i];
      }
    }
  }
}

void deletar(Lista *lista, int ficha) {
  if (lista->inicio == NULL) {
    printf("\n============\nLista vazia\n============\n\n");
  } else {
    No *pa = NULL;
    No *pi;
    for (pi = lista->inicio; pi->prox != NULL && pi->dado.ficha != ficha;
         pi = pi->prox) {
      pa = pi;
    }
    if (pa == NULL) {
      if (pi->dado.ficha == ficha) {
        lista->inicio = pi->prox;
        printf("\n===========================\n Ficha excluida com "
               "sucesso\n===========================\n\n");
        free(pi);
      } else {
        printf("\n====================\nFicha nao "
               "encontrada\n====================\n\n");
      }
    } else {
      if (pi->dado.ficha == ficha) {
        pa->prox = pi->prox;
        free(pi);
      } else {
        printf("\n====================\nFicha nao "
               "encontrada\n====================\n\n");
      }
    }
  }
}

void cadastrar1() {
  FILE *file = fopen("cliente.b", "ab");
  Cliente a;

  printf("Informe a ficha do cliente:\n");
  scanf("%d", &a.ficha);
  printf("Informe o nome do cliente:\n");
  scanf("%s", a.nome);
  printf("Informe a data da tatto:\n");
  scanf("%s", a.data);
  printf("Informe o preco da tatto:\n");
  scanf("%f", &a.precoTatto);
  printf("\n\n");
  fwrite(&a, sizeof(Cliente), 1, file);

  printf("===============================\nCliente cadastrado com "
         "sucesso!\n===============================\n\n");

  fclose(file);
}

/*
void listar2() {
  FILE *file = fopen("cliente.b", "rb");
  Cliente a;

  while (fread(&a, sizeof(Cliente), 1, file)) {
    printf("==================\n");
    printf("Ficha: %d\n", a.ficha);
    printf("Nome: %s\n", a.nome);
    printf("Data: %s\n", a.data);
    printf("Preco: %.2f\n", a.precoTatto);
    printf("==================\n");
    printf("\n");
  }

  printf("\n\n");
  fclose(file);
}*/

void listar2() {
  Lista lista;
  lista.inicio = NULL;
  lerLista(&lista);
  for (No *pi = lista.inicio; pi != NULL; pi = pi->prox) {
    printf("Ficha: %d\n", pi->dado.ficha);
    printf("Nome: %s\nData: %s\nPreco: %.2f\n\n", pi->dado.nome, pi->dado.data, pi->dado.precoTatto);
  }
}

int quantidade6() {
  FILE *file = fopen("cliente.b", "rb");
  Cliente a;
  int cont = 0;
  while (fread(&a, sizeof(Cliente), 1, file)) {
    cont++;
  }

  fclose(file);
  return cont;
}

/*
void editar3(int ficha) {
  int n = quantidade6();
  Cliente v[n];
  FILE *file = fopen("cliente.b", "rb");
  int i = 0;
  while (fread(&v[i], sizeof(Cliente), 1, file)) {
    i++;
  }

  fclose(file);

  file = fopen("cliente.b", "wb");

  for (i = 0; i < n; i++) {
    if (v[i].ficha == ficha) {
      printf("Informe o preco:\n");
      scanf("%f", &v[i].precoTatto);

      printf("Informe a data:\n");
      scanf("%s", v[i].data);
    }

    fwrite(&v[i], sizeof(Cliente), 1, file);
  }

  printf("\n\n");
  fclose(file);
}
*/

void editar3(int ficha) {
  Lista lista;
  lista.inicio = NULL;
  lerLista(&lista);
  float precoTatto;
  char data[6];
  printf("Informe o preco da tatuagem:\n");
  scanf("%f", &precoTatto);
  printf("Informe a data da tatuagem:\n");
  scanf("%s", data);
  editarFicha(&lista, ficha, precoTatto, data);
  salvaLista(&lista);
  printf("\n==========================\nFicha editada com "
         "sucesso!\n==========================\n\n\n");
}

/*
void excluir4(int ficha) {
  int n = quantidade6();
  Cliente v[n];
  FILE *file = fopen("cliente.b", "rb");
  int i = 0;

  while (fread(&v[i], sizeof(Cliente), 1, file)) {
    i++;
  }

  fclose(file);

  file = fopen("cliente.b", "wb");

  for (i = 0; i < n; i++) {
    if (v[i].ficha != ficha) {
      fwrite(&v[i], sizeof(Cliente), 1, file);
    }
  }

  printf("\n\n");
  fclose(file);
}
*/

void excluir4(int ficha) {
  Lista lista;
  lista.inicio = NULL;
  lerLista(&lista);
  deletar(&lista, ficha);
  salvaLista(&lista);
}

void buscar5(int ficha) {
  FILE *file = fopen("cliente.b", "rb");
  Cliente a;
  int entrou = 0;
  while (fread(&a, sizeof(Cliente), 1, file)) {
    if (a.ficha == ficha) {
      printf("\n==================\n");
      printf("Ficha: %d\n", a.ficha);
      printf("Nome: %s\n", a.nome);
      printf("Data: %s\n", a.data);
      printf("Preco: %.2f\n", a.precoTatto);
      printf("==================\n");
      entrou = 1;
    }
  }

  if (entrou == 0) {
    printf("\n====================\n");
    printf("Cliente nao encontrado\n");
    printf("====================\n");
  }

  printf("\n\n");
  fclose(file);
}

void orcanento7(int tamanho, int largura, int cor) {
  FILE *file = fopen("cliente.b", "rb");
  Cliente a;
  float preco = tamanho * 10 + largura * 10 + 100;
  if (cor == 1) {
    preco = preco * 1.4;
  }
  printf("==================================\n");
  printf("O preco da tatuagem e: R$ %.2f\n", preco);
  printf("==================================\n");

  printf("\n\n");
  fclose(file);
}

void visualizar8(char *data) {
  FILE *file = fopen("cliente.b", "rb");
  Cliente a;
  int entrou = 0;
  while (fread(&a, sizeof(Cliente), 1, file)) {
    if (strcmp(a.data, data) == 0) {
      printf("\n==================\n");
      printf("Ficha: %d\n", a.ficha);
      printf("Nome: %s\n", a.nome);
      printf("Data: %s\n", a.data);
      printf("Preco: %.2f\n", a.precoTatto);
      printf("==================\n");
      entrou = 1;
    }
  }
  if (entrou == 0) {
    printf("\n======================================\n");
    printf("Nao tem horario marcado para esse dia\n");
    printf("======================================\n");
  }

  printf("\n\n");
  fclose(file);
}

/*
void precomedio9 (){
  int n = quantidade6();
  Cliente v[n];
  FILE *file = fopen("cliente.b", "rb");
  int i = 0;
  float soma = 0;

  while (fread(&v[i], sizeof(Cliente), 1, file)){
    soma += v[i].precoTatto;
    i++;
  }

  float media = soma/n;

  printf("O preco medio das tatuagens e: %.2f\n\n", media);
  fclose(file);
}
*/

void precomedio9() {
  Lista lista;
  lista.inicio = NULL;
  lerLista(&lista);
  int n = quantidade6();
  float soma = 0;
  float media;
  for (No *pi = lista.inicio; pi != NULL; pi = pi->prox) {
    soma += pi->dado.precoTatto;
  }
  media = soma / n;
  printf("O preco medio das tatuagens e: %.2f\n\n", media);
}

/*
void ordenar10(int n){
  Cliente v[n];
  FILE *file = fopen("cliente.b", "rb");
  int i = 0;
  while (fread(&v[i], sizeof(Cliente), 1, file)){
    i++;
  }
  fclose(file);
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(v[i].ficha < v[j].ficha){
        Cliente aux = v[i];
        v[i] = v[j];
        v[j] = aux;
      }
    }
  }
  file = fopen("cliente.b", "wb");
  for(int i = 0; i < n; i++){
    fwrite(&v[i], sizeof(Cliente), 1, file);
  }
  fclose(file);
}
*/

void ordenar10(Lista *lista) {
  FILE *file = fopen("cliente.b", "rb");
  if (file == NULL) {
    printf("\n============\nLista vazia\n============\n\n");
    return;
  }

  if (lista->inicio == NULL) {
    printf("\n============\nLista vazia\n============\n\n");
    fclose(file);
    return;
  }
  fclose(file);

  int trocado;
  No *pi, *pj = NULL;
  do {
    trocado = 0;
    pi = lista->inicio;
    while (pi->prox != pj) {
      if (pi->dado.ficha > pi->prox->dado.ficha) {
        Cliente aux = pi->dado;
        pi->dado = pi->prox->dado;
        pi->prox->dado = aux;
        trocado = 1;
      }
      pi = pi->prox;
    }
    pj = pi;
  } while (trocado);

  salvaLista(lista);
}
