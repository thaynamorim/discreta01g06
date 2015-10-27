#define CORBRANCO (makecol(255,255,255))
#define CORPRETO 1
#define CORCINZA (makecol(160,160,160))
#define CORAZUL (makecol(0, 0, 255))
#define CORVERDE (makecol(0, 255, 0))
#define CORAMARELO (makecol(255,255,100))
#define CORVERMELHO (makecol(255, 0, 0))
#define PI 3.141592653589793238462643383279502884
#define IMAGENAME "teste.bmp" /* nome do arquivo de imagem */

#include <stdio.h>
#include <allegro.h>
#include <math.h>
#include "mybib.h"
#define Ytela 800
#define Xtela 800
#define xc Xtela/2.0
#define yc Ytela/2.0

void estados(int k,BITMAP *buff);
void transicao(int qo, int qf,BITMAP *buff,int k);
void desenhaauto(int k);
int main(void)
{
    int k=2;
    desenhaauto(k);
    return EXIT_SUCCESS;
}
void desenhaauto(int k)
{

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
    estados(k,buff);
    transicao(1,2,buff,k);
    transicao(2,1,buff,k);
    save_bitmap(IMAGENAME, buff, pal);
    destroy_bitmap(buff);
    allegro_exit();

    printf("Imagem %s salva com sucesso!\n", IMAGENAME);

    return;
}

void estados(int k,BITMAP *buff)
{
    int i;
    float rk,xi,yi;
    rk=(Ytela / 2) * (M_PI / (M_PI+k));
    for(i=0;i<k;i++)
    {
        yi=yc+cos((2*M_PI/k)*i);
        xi=xc+sin((2*M_PI/k)*i);
        circle(buff, xi, yi, rk, CORBRANCO);
    }
    return;
}

void transicao(int qo,int qf,BITMAP *buff,int k)
{
    float delta, alfa, beta, phi, x1, y1, x2, y2, x3, y3, xo, yo, xf, yf, rk, xt1, yt1, xt2, yt2;
    int  d=1;
    y1=yc + cos(2 * PI / k) * qo;
    x1=xc + sin(2 * PI / k) * qo;
    y3=xc + sin(2 * PI / k) * qf;
    x3=xc + sin(2 * PI / k) * qf;
    rk=(Ytela / 2) * (PI / (PI+k));

    alfa=arctan(x1,y1,x3,y3);
    y2=(y3+y1)/2 + rk * cos(alfa);
    x2=(x3+x1)/2 + rk * sin(alfa);

    beta=arctan(x3,y3,x2,y2);
    phi=arctan(x1,y1,x2,y2);
    xo = x1 + rk * cos(phi);
    yo = y1 + rk * sin(phi);
    xf = x3 + rk * cos(beta);
    yf = y3 + rk * sin(beta);

    line(buff, x1, y1, xo, yo, CORBRANCO);
    line(buff, xo, yo, x3, y3, CORBRANCO);

    delta=arctan(x2,y2,xf,yf);
    xt2 = xf - d*(sin(delta) + cos(delta));
    yt2 = yf + d*(sin(delta) - cos(delta));
    xt1 = xf + (rk / 4) * (sin(delta) - cos(delta));
    yt1 = yf - (rk / 4) * (sin(delta) + cos(delta));

    triangle(buff, xt1, yt1, xt2, yt2, x3, y3, CORBRANCO);

    return;
}
