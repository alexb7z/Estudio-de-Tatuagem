#ifndef H_CLIENTE
#define H_CLIENTE

typedef struct cliente Cliente;

typedef struct lista Lista;

typedef struct no No;

int InputEmailIsCorrect(char email_input[], char email[]);

int InputPasswordIsCorrect (char password_input[], char password[]);

void cadastrar1();

void listar2();

int quantidade6();

void editar3(int ficha);

void excluir4(int ficha);

void buscar5 (int ficha);

void orcanento7(int tamanho, int largura, int cor);

void visualizar8(char *data);

void precomedio9 (int n);

void ordenar10(int n);

void lerLista(Lista *lista);

void adicionaFim(Lista *lista, Cliente e);

void editarCliente(Lista* lista, int ficha, float precoTatto, char data[]);

#endif