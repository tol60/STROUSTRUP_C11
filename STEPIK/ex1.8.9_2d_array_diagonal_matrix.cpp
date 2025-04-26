// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
/*
По данным числам n и m заполните двумерный массив размером n×m числами от 1 до n×m “диагоналями”, как показано в примере.
Формат входных данных

Вводятся два числа n и m, не превышающие 100.
Формат выходных данных

Выведите полученный массив, отводя на вывод каждого элемента ровно 4 символа.

Sample Input:

3 5

Sample Output:

   1   2   4   7  10
   3   5   8  11  13
   6   9  12  14  15
*/


    int n, m;
    cin >> n >> m;

    int a[100][100];

    // generation
    int x = 0;
    int y = 0;
    int xy_sum = 0;
    for (int i = 1; i <= n * m; i++) {
        a[y][x] = i;
        x --;
        y ++;
        if (y == n || x < 0) { // we finish the diagonal
            xy_sum ++;
            if (xy_sum >= m) {
                x = m - 1;
                y = xy_sum - x;
            } else {
                x = xy_sum;
                y = 0;
            }
        }
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
