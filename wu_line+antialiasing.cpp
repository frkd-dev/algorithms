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

void drawwuline(double x1, double y1, double x2, double y2);
double myfrac(double x);

/*************************************************************************
<<<<<<< HEAD
Рисование линии с использованием метода Ву для
антиалиасинга.

Кординаты начала и конца могут быть дробными.
=======
��������� ����� � �������������� ������ �� ���
�������������.

��������� ������ � ����� ����� ���� ��������.
>>>>>>> 58e3d87... Added Wu's antialiasing algorithms for circle, ellipsis, line
*************************************************************************/
void drawwuline(double x1, double y1, double x2, double y2)
{
    double grad;
    double xd;
    double yd;
    double length;
    double xm;
    double ym;
    double xgap;
    double ygap;
    double xend;
    double yend;
    double xf;
    double yf;
    double brightness1;
    double brightness2;
    int x;
    int y;
    int ix1;
    int ix2;
    int iy1;
    int iy2;
    bool wasexchange;
    int tmpint;
    double tmpreal;

    xd = x2-x1;
    yd = y2-y1;
    if( xd==0&&yd==0 )
    {
        return;
    }
    if( fabs(xd)>fabs(yd) )
    {
        wasexchange = false;
    }
    else
    {
        wasexchange = true;
        tmpreal = x1;
        x1 = y1;
        y1 = tmpreal;
        tmpreal = x2;
        x2 = y2;
        y2 = tmpreal;
        tmpreal = xd;
        xd = yd;
        yd = tmpreal;
    }
    if( x1>x2 )
    {
        tmpreal = x1;
        x1 = x2;
        x2 = tmpreal;
        tmpreal = y1;
        y1 = y2;
        y2 = tmpreal;
        xd = x2-x1;
        yd = y2-y1;
    }
    grad = yd/xd;
    xend = ap::ifloor(x1+0.5);
    yend = y1+grad*(xend-x1);
    xgap = 1-myfrac(x1+0.5);
    ix1 = ap::ifloor(x1+0.5);
    iy1 = ap::ifloor(yend);
    brightness1 = (1-myfrac(yend))*xgap;
    brightness2 = myfrac(yend)*xgap;
    if( wasexchange )
    {
        setpixel(iy1, ix1, brightness1);
        setpixel(iy1+1, ix1, brightness2);
    }
    else
    {
        setpixel(ix1, iy1, brightness1);
        setpixel(ix1, iy1+1, brightness2);
    }
    yf = yend+grad;
    xend = ap::ifloor(x2+0.5);
    yend = y2+grad*(xend-x2);
    xgap = 1-myfrac(x2-0.5);
    ix2 = ap::ifloor(x2+0.5);
    iy2 = ap::ifloor(yend);
    brightness1 = (1-myfrac(yend))*xgap;
    brightness2 = myfrac(yend)*xgap;
    if( wasexchange )
    {
        setpixel(iy2, ix2, brightness1);
        setpixel(iy2+1, ix2, brightness2);
    }
    else
    {
        setpixel(ix2, iy2, brightness1);
        setpixel(ix2, iy2+1, brightness2);
    }
    for(x = ix1+1; x <= ix2-1; x++)
    {
        brightness1 = 1-myfrac(yf);
        brightness2 = myfrac(yf);
        if( wasexchange )
        {
            setpixel(ap::ifloor(yf), x, brightness1);
            setpixel(ap::ifloor(yf)+1, x, brightness2);
        }
        else
        {
            setpixel(x, ap::ifloor(yf), brightness1);
            setpixel(x, ap::ifloor(yf)+1, brightness2);
        }
        yf = yf+grad;
    }
}


double myfrac(double x)
{
    double result;

    result = x-ap::ifloor(x);
    return result;
}


