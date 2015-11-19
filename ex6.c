#define CORBRANCO (makecol(255,255,255))
#define CORPRETO 1
#define CORCINZA (makecol(160,160,160))
#define CORAZUL (makecol(0, 0, 255))
#define CORVERDE (makecol(0, 255, 0))
#define CORAMARELO (makecol(255,255,100))
#define CORVERMELHO (makecol(255, 0, 0))
#define IMAGENAME "teste.bmp" /* nome do arquivo de imagem */

#include <stdio.h>
#include <allegro.h>
#include <math.h>
#include "mybib.h"
#define Ytela 800
#define Xtela 800
#define xc Xtela/2.0
#define yc Ytela/2.0
#define FNAME "automato1.txt"
#define KMAX 1000
void iniestado(int k, BITMAP *buff, int n);
void estados(int k,BITMAP *buff, int *final);
void transicao(int qo, int qf,BITMAP *buff,int k, char c);
void desenhaauto(automato a);

typedef struct st_fim
{
    int tf;
    struct st_fim *prox;
}fim;

typedef struct st_transicao
{
    int de,meio,para;
    struct st_transicao *prox;
}transicao;

typedef struct st_automato
{ 
    int k, alf, si;
    fim lfim;
    transicao trans;
}automato;

int main(void)
{
    int x, y, z;
    FILE *fl= fopen(FNAME,"r+");
    automato a;
    char c;
    fscanf(fl,"%d",&(a.k));
    fscanf(fl,"%d",&(a.alf));
    fscanf(fl,"%d",&(a.si));
    while(1) 
    {
        c = fgetc(fl);
        if(feof(fl) || c == '\n')
            break;
        inserirfim(&(a.lfim),(int)(c - '0'));
    }
    while(1)
    {
        if(feof(fl))
            break;
        fscanf(fl,"%d %d %d",&x, &y, &z);
        inserirtrans(&(a.trans),x,y,z);
    }
    desenhaauto(a);
    fclose(fl);
    return EXIT_SUCCESS;
}
void inserirfim(fim **cabeca,int c)
{
    fim *pl = *cabeca;
    fim *plant = NULL;
    while(pl != NULL)
    {
        plant = pl;
        pl = pl->prox;
    }
    pl = malloc(sizeof(fim));
    pl->tf = c;
    pl->prox = NULL;
    if(plant != NULL)
        plant->prox = pl;
    else
        *cabeca = pl;
    
    return;
}

void inserirtrans(transicao **cabeca,int a,int b, int c)
{
    transicao *pl = *cabeca;
    transicao *plant = NULL;
    while(pl != NULL)
    {
        plant = pl;
        pl = pl->prox;
    }
    pl = malloc(sizeof(transicao));
    pl->de = a;
    pl->meio = b;
    pl->para = c;
    pl->prox = NULL;
    if(plant != NULL)
        plant->prox = pl;
    else
        *cabeca = pl;
    
    return;
}

void desenhaauto(automato a)
{
    //k = numero de estados. No nosso exemplo, k = 5

    BITMAP *buff;
    PALETTE pal;

    if(install_allegro(SYSTEM_NONE, &errno, atexit)!=0)
        exit(EXIT_FAILURE);

    set_color_depth(16);
    get_palette(pal);

    buff = create_bitmap(Xtela,Ytela);
    if(buff == NULL)
    {
        printf("Could not create buffer!\n");
        exit(EXIT_FAILURE);
    }
    int f[KMAX] = {0},i=0;
    fim *pl = a.lfim;
    transicao *pt = a.trans;
    while(*pl != NULL)
    {
        f[i]=1;
        i++;
        pl=pl->prox;
    }
    estados(a.k,buff,f);
    iniestado(a.k,buff,a.si); //estado inicial sera tirado do scanf: linha 3
    while(*pt != NULL)
    {
        faz_transicao(pt->de,pt->para,buff,a.k,pt->meio + 'a');
        pt=pt->prox;
    }
    save_bitmap(IMAGENAME, buff, pal);
    destroy_bitmap(buff);
    allegro_exit();

    printf("Imagem %s salva com sucesso!\n", IMAGENAME);

    return;
}

void estados(int k,BITMAP *buff, int *final)
{
    int i;
    float rk,xi,yi,rc;
    rk=(Ytela / 4) * (M_PI/(M_PI+k));
    rc = yc - rk;
    for(i=0;i<k;i++)
    {
        yi=yc+rc*cos((2*M_PI/k)*i);
        xi=xc+rc*sin((2*M_PI/k)*i);
        circle(buff, xi, yi, rk, CORBRANCO);
        if(*final == 1)
            circle(buff, xi, yi, rk*0.8, CORBRANCO);
        textprintf_ex(buff, font, xi, yi, CORVERDE, CORPRETO, "q%d",i);
        final++;
    }
    return;
}

void transicao(int qo,int qf,BITMAP *buff,int k, char c)
{
    float delta, alfa, beta, phi, x1, y1, x2, y2, x3, y3, xo, yo, xf, yf, rk, xt1, yt1, xt2, yt2, rc;
    rk=(Ytela / 4) * (M_PI / (M_PI+k));
    rc = yc - rk;

    y1 = yc + rc*cos((2*M_PI/k)*qo);
    x1 = xc + rc*sin((2*M_PI/k)*qo);
    y3 = yc + rc*cos((2*M_PI/k)*qf);
    x3 = xc + rc*sin((2*M_PI/k)*qf);

    alfa=arctan(x1,y1,x3,y3);
    y2=(y3+y1)/2 + rk * cos(alfa);
    x2=(x3+x1)/2 - rk * sin(alfa);

    if(((alfa >= 0) && (alfa <= M_PI/2)) || ((alfa >= M_PI) && (alfa <= 3*M_PI/2)))
    {
        beta=arctan(x3,y3,x2,y2);
        phi=arctan(x1,y1,x2,y2);
        xo = x1 + rk * cos(phi);
        yo = y1 + rk * sin(phi);
        xf = x3 + rk * cos(beta);
        yf = y3 + rk * sin(beta);
    }
    else
    {
        alfa=arctan(x3,y3,x1,y1);
        y2=(y3+y1)/2 + rk * cos(alfa);
        x2=(x3+x1)/2 - rk * sin(alfa);
        beta=arctan(x1,y1,x2,y2);
        phi=arctan(x3,y3,x2,y2);
        xo = x1 - rk * cos(phi);
        yo = y1 - rk * sin(phi);
        xf = x3 - rk * cos(beta);
        yf = y3 - rk * sin(beta);
    }

    int coo[8];
    coo[0] = (int)xo;
    coo[1] = (int)yo;
    coo[2] = (int)x2;
    coo[3] = (int)y2;
    coo[4] = (int)x2;
    coo[5] = (int)y2;
    coo[6] = (int)xf;
    coo[7] = (int)yf;
    spline(buff,coo,CORBRANCO);

    delta=arctan(x2,y2,x3,y3);
    xt2 = xf - (rk / 4) * (sin(delta) + cos(delta));
    yt2 = yf + (rk / 4) * (sin(delta) - cos(delta));
    xt1 = xf + (rk / 4) * (sin(delta) - cos(delta));
    yt1 = yf - (rk / 4) * (sin(delta) + cos(delta));

    triangle(buff, xt1, yt1, xt2, yt2, xf, yf, CORBRANCO);
    textprintf_ex(buff, font, x2, y2, CORVERDE, CORPRETO, "%c", c);

    return;
}

void iniestado(int k, BITMAP *buff, int n)
{
    float ang, x1, y1, x2, y2, x3, y3, rc, rk, xt1, xt2, yt1, yt2;
    if(n>=k)
    {
        printf("Erro: estado inicial maior que o numero de estados.\n");
        exit(1);
    }
    ang = M_PI*(2.0*n)/(1.0*k);

    rk=(Ytela / 4) * (M_PI / (M_PI+k));
    rc = yc - rk;
    y3 = yc + rc*cos((2*M_PI/k)*n) - rk*sin(ang);
    x3 = xc + rc*sin((2*M_PI/k)*n) - rk*cos(ang);

    x1 = x3 - rk*cos(ang)+rand()%10;
    y1 = y3 - rk*sin(ang)+rand()%10;

    x2 = (x1+x3)/2+rand()%10;
    y2 = (y1+y3)/2+rand()%10;

    int i[8];
    i[0] = x1;
    i[1] = y1;
    i[2] = x2;
    i[3] = y2;
    i[4] = x2;
    i[5] = y2;
    i[6] = x3;
    i[7] = y3;
    spline(buff,i,CORBRANCO);

    xt2 = x2;
    yt2 = y2 + (rk/5)*cos(ang);
    xt1 = x2;
    yt1 = y2 - (rk/5)*cos(ang);

    triangle(buff, xt1, yt1, xt2, yt2, x3, y3, CORBRANCO);
    return;
}
