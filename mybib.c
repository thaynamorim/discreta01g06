typedef struct st_lista
{
    int c;
    struct st_lista *prox;
}lista;

float arctan(float x1, float y1, float x2, float y2)
{
    if(x2 == x1)
    {
        if(y2 == y1)
            return 9;
        else
            if(y2>y1)
                return M_PI/2.0;
            return 3.0*M_PI/2.0;
    }
    if((y2 == y1) && (x2 < x1))
        return M_PI;
    float a = atan(fabs(y2-y1)/fabs(x2-x1));
    if((x2 < x1) && (y2 > y1)) // QUAD = 2
        return a + M_PI/2.0;
    if((x2 < x1) && (y2 < y1)) // QUAD = 3
        return a + M_PI;
    if((x2 > x1) && (y2 < y1)) // QUAD = 4
        return a + 3.0*M_PI/2.0;
    return a; // QUAD = 1

}

lista *buscar(lista *cabeca, int x)
{
    lista *pl = cabeca;
    while(pl != NULL)
    {
        if(pl->c == x)
            return pl;
        pl = pl->prox;
    }
    return NULL;
}

void inserir(lista **cabeca, int x)
{
    lista *pl = *cabeca;
    lista *plant = NULL;
    while(pl != NULL)
    {
        plant = pl;
        pl = pl->prox;
    }
    pl = malloc(sizeof(lista));
    pl->c = x;
    pl->prox = NULL;
    if(plant != NULL)
        plant->prox = pl;
    else
        *cabeca = pl;
}

void remover(lista **cabeca, lista *r)
{
    lista *pl=*cabeca;
    lista *plant=NULL;
    if(r==NULL)
        return;
    while(pl!=NULL && pl!=r) //ate achar r ou fim
    {
        plant=pl;
        pl=pl->prox;
    }
    if(pl==NULL) //nao achou ou lista vazia
        return;
    if(plant!=NULL) //tem anterior
        plant->prox=pl->prox;
    else //eliminando cabeca
        *cabeca=pl->prox;
    free(pl);
    return;
}

lista *anterior(lista *cabeca, lista *r)
{
    lista *pl=cabeca, *plant=NULL;
    if(r==NULL)
        return NULL;
    while(pl!=NULL && pl!=r)
    {
        plant=pl;
        pl=pl->prox;
    }
    return plant;
}

void imprimir(lista *cabeca)
{
    lista *pl=cabeca;
    while(pl!=NULL)
    {
        printf("%d->",pl->c);
        pl=pl->prox;
    }
    printf("NULL\n");
    return;
}
