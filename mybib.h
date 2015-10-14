float arctan(float x1, float y1, float x2, float y2);
lista *buscar(lista *cabeca, int x);
void inserir(lista **cabeca, int x);
void remover(lista **cabeca, lista *r);
lista *anterior(lista *cabeca, lista *r);

typedef struct st_lista
{
    int c;
    struct st_lista *prox;
}lista;
