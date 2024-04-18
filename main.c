#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

void menu() {
  printf("Escolha uma opcao:\n");
  printf("1 - Cadastar cliente\n");
  printf("2 - Listar clientes\n");
  printf("3 - Editar ficha\n");
  printf("4 - Excluir ficha\n");
  printf("5 - Buscar cliente\n");
  printf("6 - Quantidade de clientes\n");
  printf("7 - Solicitar orçamento\n");
  printf("8 - Visualizar agenda do dia\n");
  printf("9 - Preco medio das tatuagens\n");
  printf("10 - Ordenar clientes\n");
  printf("0 - sair\n");
}

int main(void) {
  char email [20] = "alexbruno@gmail.com";
  char password [10] = "123456789";
  char email_input [20];
  char password_input [10];

  /*
  do {
    printf("Digite o seu email: ");
    scanf("%s", email_input);
  } while (!InputEmailIsCorrect(email_input, email));
  printf("Email correto!\n");
  
  do {
    printf("Digite a sua senha: ");
    scanf("%9s", password_input);
  } while (InputPasswordIsCorrect(password_input, password) == 0);
  printf("Senha correta!\n\n");
  */
  
  printf("~<=================================>~\n");
  printf("  Bem-vindo ao estudio Tatto Artist!\n");
  printf("~<=================================>~\n\n");
  
  int op;
  menu();
  scanf("%d", &op);

  printf("\n");
  while(op != 0){
    if (op == 1){
       cadastrar1();
      
    } else if (op == 2){
        listar2();
      
    } else if (op == 3){
      int ficha;
      printf("Infomrme a ficha do cliente que você pretende editar:\n");
      scanf("%d", &ficha);
      
      editar3(ficha);
      
    } else if (op == 4){
      int ficha;
      printf("Informe a ficha para exclusao:\n");
      scanf("%d", &ficha);
      
      excluir4(ficha);
      
    } else if (op == 5){
      int ficha;
      printf("Informe a ficha do cliente que pretende buscar:\n");
      scanf("%d", &ficha);
      
      buscar5(ficha);
      
    } else if (op == 6){
      int n = quantidade6();
      printf("\n===========================\n");
      printf("Quantidade de clientes: %d\n", n);
      printf("===========================\n");
      printf("\n\n");
      
    } else if (op == 7){
      int altura;
      int largura;
      int cor;
      printf("Informe a altura da tatuagem:\n");
      scanf("%d", &altura);
      printf("Informe a largura da tatuagem:\n");
      scanf("%d", &largura);
      do {
        printf("Se a tatuagem for colorida digite 1, caso contrario digite 2:\n");
        scanf("%d", &cor);
      } while (cor != 1 && cor != 2);
      
      printf("\n");
      orcanento7(altura, largura, cor);
      
    } else if (op == 8){
      char data[6];
      printf("Qual a data que desejar vizualizar na agenda?\n");
      scanf("%s", data);
      visualizar8(data);
      
    } else if (op == 9){
      int n;
      precomedio9(n);
      
    } else if (op == 10){
      int n = quantidade6();
      ordenar10(n);
    }
    
    menu();
    scanf("%d", &op);
    printf("\n\n");
  }
  
  return 0;
}