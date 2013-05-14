#include <conio.h>
#include <stdlib.h>

void putpixel(unsigned int X,unsigned int Y,unsigned char Color)
{
  asm {
        mov     ax, [Y]
        mov     dx, 320
        imul    dx
        add     ax, [X]
        mov     di, ax
        push    es
        mov     ax, 0xA000
        mov     es, ax
        mov     al,[Color]
        stosb
        pop     es
      }
}

void ellipse(int x, int y, int a, int b, int color)
{
 int col, i, row, bnew;
 long a_square, b_square, two_a_square, two_b_square, four_a_square, four_b_square,d;

  b_square = b * b;
  a_square = a * a;
  row = b;
  col = 0;
  two_a_square = a_square << 1;
  four_a_square = a_square << 2;
  four_b_square = b_square << 2;
  two_b_square = b_square << 1;
  d = two_a_square * ((row - 1) * (row)) + a_square + two_b_square * (1 - a_square);
  while (a_square * (row) > b_square * (col)) {
   putpixel(col + x, row + y, color);
   putpixel(col + x, y - row, color);
   putpixel(x - col, row + y, color);
   putpixel(x - col,y - row, color);
   if (d >= 0) {
    row--;
    d -= four_a_square * (row);
   }
   d += two_b_square * (3 + (col << 1));
   col++;
  }
  d = two_b_square * (col + 1) * col + two_a_square * (row * (row - 2) + 1) + (1 - two_a_square) * b_square;
  while ((row) + 1) {
   putpixel(col + x, row + y, color);
   putpixel(col + x, y - row, color);
   putpixel(x - col, row + y, color);
   putpixel(x - col, y - row, color);
   if (d <= 0) {
    col++;
    d += four_b_square * col;
   }
   row--;
   d += two_a_square * (3 - (row << 1));
  }
}

void main(void)
{
 int X,Y;

 asm mov    ax,0x0013
 asm int    0x10
 while (!kbhit()) putpixel(random(320),random(200),random(255));
 getch();
 while (!kbhit()) {
    X = 50 + random(220);
    Y = 50 + random(100);
    ellipse(X, Y, 1 + random(48), 1 + random(48), random(255));
  }
 getch();
}
