// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
/*
По данным числам n и m заполните двумерный массив размером n×m числами от 1 до n×m по спирали, выходящей из левого верхнего угла и закрученной по часовой стрелке, как показано в примере.
Формат входных данных

Вводятся два числа n и m, не превышающие 100.
Формат выходных данных

Выведите полученный массив, отводя на вывод каждого элемента ровно 4 символа.

Sample Input:

4 5

Sample Output:

   1   2   3   4   5
  14  15  16  17   6
  13  20  19  18   7
  12  11  10   9   8
*/


    int n, m;
    cin >> n >> m;

    int a[100][100];

    // generation
    int x = 0;
    int y = 0;
    int dx = 1;
    int dy = 0;
    int x_min = 0;
    int y_min = 1;
    int y_max = n - 1;
    int x_max = m - 1;
    for (int cnt = 1; cnt <= n * m; cnt++) {
        a[y][x] = cnt;
        if (dx > 0) {
            if (x == x_max) {
                dx = 0;
                dy = 1;
                x_max --;  // next time we would have to turn one step to the left
            }
        } else if (dx < 0) {
            if ( x == x_min) {
                dx = 0;
                dy = -1;
                x_min ++;
            }
        } else if (dy > 0) {
            if (y == y_max) {
                dy = 0;
                dx = -1;
                y_max --;
            }
        } else if (dy < 0) {
            if (y == y_min) {
                dy = 0;
                dx = 1;
                y_min ++;
            }
        }
        x += dx;
        y += dy;
    }

    // output
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << setw(4) << a[i][j];
        }
        cout << endl;
    }

    return 0;
}
