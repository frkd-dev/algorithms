/***********************************************************************
This code is generated by the AlgoPascal translator

This code is distributed under the ALGLIB license
    (see http://www.alglib.net/copyrules.php for details)
***********************************************************************/

#include "ap.h"

/*-----------------------------------------------
This routines must be defined by the programmer:

void setpixel(int x, int y, double alpha);
-----------------------------------------------*/

void drawwuellipse(double x1, double y1, double x2, double y2);

/*************************************************************************
<<<<<<< HEAD
Рисование эллипса с использованием метода Ву для
антиалиасинга.
=======
��������� ������� � �������������� ������ �� ���
�������������.
>>>>>>> 58e3d87... Added Wu's antialiasing algorithms for circle, ellipsis, line
*************************************************************************/
void drawwuellipse(double x1, double y1, double x2, double y2)
{
    double t;
    double a;
    double b;
    double cx;
    double cy;
    double x;
    double y;
    double f;
    int ix;
    int iy;
    int i1;
    int i2;
    bool exch;

    if( x2<x1 )
    {
        t = x1;
        x1 = x2;
        x2 = t;
    }
    if( y2<y1 )
    {
        t = y1;
        y1 = y2;
        y2 = t;
    }
    if( x2-x1<y2-y1 )
    {
        exch = false;
    }
    else
    {
        exch = true;
        t = x1;
        x1 = y1;
        y1 = t;
        t = x2;
        x2 = y2;
        y2 = t;
    }
    a = (x2-x1)/2;
    b = (y2-y1)/2;
    cx = (x1+x2)/2;
    cy = (y1+y2)/2;
    t = a*a/sqrt(a*a+b*b);
    i1 = ap::ifloor(cx-t);
    i2 = ap::iceil(cx+t);
    for(ix = i1; ix <= i2; ix++)
    {
        if( 1-ap::sqr((ix-cx)/a)<0 )
        {
            continue;
        }
        y = b*sqrt(1-ap::sqr((ix-cx)/a));
        iy = ap::iceil(cy+y);
        f = iy-cy-y;
        if( !exch )
        {
            setpixel(ix, iy, 1-f);
            setpixel(ix, iy-1, f);
        }
        else
        {
            setpixel(iy, ix, 1-f);
            setpixel(iy-1, ix, f);
        }
        iy = ap::ifloor(cy-y);
        f = cy-y-iy;
        if( !exch )
        {
            setpixel(ix, iy+1, f);
            setpixel(ix, iy, 1-f);
        }
        else
        {
            setpixel(iy+1, ix, f);
            setpixel(iy, ix, 1-f);
        }
    }
    t = b*b/sqrt(a*a+b*b);
    i1 = ap::iceil(cy-t);
    i2 = ap::ifloor(cy+t);
    for(iy = i1; iy <= i2; iy++)
    {
        if( 1-ap::sqr((iy-cy)/b)<0 )
        {
            continue;
        }
        x = a*sqrt(1-ap::sqr((iy-cy)/b));
        ix = ap::ifloor(cx-x);
        f = cx-x-ix;
        if( !exch )
        {
            setpixel(ix, iy, 1-f);
            setpixel(ix+1, iy, f);
        }
        else
        {
            setpixel(iy, ix, 1-f);
            setpixel(iy, ix+1, f);
        }
        ix = ap::iceil(cx+x);
        f = ix-cx-x;
        if( !exch )
        {
            setpixel(ix, iy, 1-f);
            setpixel(ix-1, iy, f);
        }
        else
        {
            setpixel(iy, ix, 1-f);
            setpixel(iy, ix-1, f);
        }
    }
}


