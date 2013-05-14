/*  circular_arc.c -- simple demo for incremental circular arc drawing routine.
 *  (C) 2002, C. Bond. All rights reserved.
 *
 * Circular arc drawing algorithm based on standard incremental circle
 * algorithm (octant method with 8-way symmetry). Uses oriented lines
 * to locate arc between starting and ending points given starting and
 * ending arc angles (in radians).
 *
 * NOTE: This demo is a proof-of-concept program only. It is completely
 *      unoptimized and can be improved considerably by any interested
 *      investigator.
 */
#include <stdio.h>
#include <math.h>

int bmp[36][36];
float t1,t2;
int S0a,S1a,S2a,S3a,S4a,S5a,S6a,S7a;
int S0b,S1b,S2b,S3b,S4b,S5b,S6b,S7b;

void andplot(int x,int y)           /* arc angle is less than pi */
{
    if (S1a > 0 && S1b < 0) 
        bmp[18+y][18+x] = 1;        /* P1 */
    if (S2a > 0 && S2b < 0) 
        bmp[18+y][18-x] = 1;        /* P2 */
    if (S6a > 0 && S6b < 0) 
        bmp[18-y][18+x] = 1;        /* P6 */
    if (S5a > 0 && S5b < 0) 
        bmp[18-y][18-x] = 1;        /* P5 */
    if (S0a > 0 && S0b < 0) 
        bmp[18+x][18+y] = 1;        /* P0 */
    if (S3a > 0 && S3b < 0) 
        bmp[18+x][18-y] = 1;        /* P3 */
    if (S7a > 0 && S7b < 0) 
        bmp[18-x][18+y] = 1;        /* P7 */
    if (S4a > 0 && S4b < 0) 
        bmp[18-x][18-y] = 1;        /* P4 */
}

void orplot(int x,int y)            /* arc angle is greater than pi */
{
    if (S1a > 0 || S1b < 0) 
        bmp[18+y][18+x] = 1;        /* P1 */
    if (S2a > 0 || S2b < 0) 
        bmp[18+y][18-x] = 1;        /* P2 */
    if (S6a > 0 || S6b < 0) 
        bmp[18-y][18+x] = 1;        /* P6 */
    if (S5a > 0 || S5b < 0)
        bmp[18-y][18-x] = 1;        /* P5 */
    if (S0a > 0 || S0b < 0) 
        bmp[18+x][18+y] = 1;        /* P0 */
    if (S3a > 0 || S3b < 0) 
        bmp[18+x][18-y] = 1;        /* P3 */
    if (S7a > 0 || S7b < 0) 
        bmp[18-x][18+y] = 1;        /* P7 */
    if (S4a > 0 || S4b < 0) 
        bmp[18-x][18-y] = 1;        /* P4 */
}

void show(void)
{
    int i,j;

    printf("\n");
    for (i=0;i<36;i++) {
        for (j=0;j<36;j++) {
            printf("%d ",bmp[35-i][j]);
        }
        printf("\n");
    }
}

void clear(void)
{
    int i,j;

    for (i=0;i<36;i++) {
        for (j=0;j<36;j++) {
            bmp[i][j] = 0;
        }
    }
}

void main()
{
    int x,y,r,g,dx,dxdy;
    int Dxa,Dya,Dxb,Dyb;
    int small;

/* get start and stop angles from user */
    fprintf(stderr,"Start angle (radians) : ");
    scanf("%f",&t1);
    fprintf(stderr,"Stop angle (radians) : ");
    scanf("%f",&t2);
    if (t2 < t1) t2 += 2*M_PI;
    if ((t2 - t1) < M_PI) small = 1;
    else small = 0;

/* initialize line draw variables for arc boundary lines */
    Dxa = 1000*cos(t1);
    Dya = 1000*sin(t1);
    Dxb = 1000*cos(t2);
    Dyb = 1000*sin(t2);

/* no more floating point operations beyond this point! */    
    clear();

/* initialize circle draw variables */
    x = 0;
    r = 10;
    y = r;
    g = 3 - (r << 1);
    dxdy = 10 - (r << 2);
    dx = 6;

/* initialize line variables */
    S1a = S2a = r*Dxa;
    S5a = S6a = -S1a;
    S3a = S4a = r*Dya;
    S0a = S7a = -S3a;
    S1b = S2b = r*Dxb;
    S5b = S6b = -S1b;
    S3b = S4b = r*Dyb;
    S0b = S7b = -S3b;

/* main circle (arc) routine */
    while(x <= y) {
        if (small) andplot(x,y);
        else orplot(x,y);
        if (g >= 0) {
            g += dxdy;
            dxdy += 8;
            y--;
            S0a += Dya;
            S1a -= Dxa;
            S2a -= Dxa;
            S3a -= Dya;
            S4a -= Dya;
            S5a += Dxa;
            S6a += Dxa;
            S7a += Dya;
            S0b += Dyb;
            S1b -= Dxb;
            S2b -= Dxb;
            S3b -= Dyb;
            S4b -= Dyb;
            S5b += Dxb;
            S6b += Dxb;
            S7b += Dyb;
        }
        else {
            g += dx;
            dxdy += 4;
        }
        dx += 4;
        x++;
        S0a += Dxa;
        S1a -= Dya;
        S2a += Dya;
        S3a += Dxa;
        S4a -= Dxa;
        S5a += Dya;
        S6a -= Dya;
        S7a -= Dxa;
        S0b += Dxb;
        S1b -= Dyb;
        S2b += Dyb;
        S3b += Dxb;
        S4b -= Dxb;
        S5b += Dyb;
        S6b -= Dyb;
        S7b -= Dxb;
    }
    show();
}
