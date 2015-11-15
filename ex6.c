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

void iniestado(int k, BITMAP *buff, int n);
void estados(int k,BITMAP *buff, int *final);
void transicao(int qo, int qf,BITMAP *buff,int k, char c);
void desenhaauto(int k);
//void desenhaauto(automato a);
//typedef struct blablabla
//{ ... int k;}automato;
int main(void)
{
    int k=5;
    desenhaauto(k);
    return EXIT_SUCCESS;
}

void desenhaauto(int k)
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
    int f[500] = {0}; //nao vai existir
    //vetor f: vetor de zeros, onde so eh um nos estados que forem finais
    //    f = {1 0 0 1 1}
    //estados  0 1 2 3 4 -> estados 0, 3 e 4 finais
    f[0] = f[3] = f[4] = 1; //isso sera lido pelo scanf e armazenado na lista automato
    //variavel k sera tirada do scanf: linha 1
    estados(k,buff,f);
    iniestado(k,buff,0); //estado inicial sera tirado do scanf: linha 3
    transicao(0,1,buff,k,'a');
    //scanf("%d %d %d",i,v,f);
    //transicao(i,f,buff,k,v);
    //0 'a' 1 -> 0 1 'a'
    //dica pra converter numero em letra: valor + 'a': 0+'a' = 'a', 1+'a' = 'b' etc...
    //transicao(estado inicial, estado final, buff, numero de estados, letra do alfabeto)
    //linha 2: numero de letras do alfabeto: a até ...
    //simbolo lido: 0 representa a, 1 representa b, 2 representa c etc...
    transicao(1,2,buff,k,'a');
    transicao(1,3,buff,k,'b');
    transicao(2,4,buff,k,'b');
    transicao(3,1,buff,k,'a');
    transicao(4,1,buff,k,'a');
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
