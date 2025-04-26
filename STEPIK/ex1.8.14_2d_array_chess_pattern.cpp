// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
/*
Даны числа n и m. Заполните массив размером n × m в шахматном порядке: клетки одного цвета заполнены нулями, а другого цвета - заполнены числами натурального ряда сверху вниз, слева направо. В левом верхнем углу записано число 1.
Формат входных данных

Вводятся два числа n и m, не превышающие 100.
Формат выходных данных

Выведите полученный массив, отводя на вывод каждого элемента ровно 4 символа.

Sample Input:

3 5

Sample Output:

   1   0   2   0   3
   0   4   0   5   0
   6   0   7   0   8
*/


    int n, m;
    cin >> n >> m;

    int a[100][100];

    // generation
    int cnt = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((i + j) % 2 == 0) {
                a[i][j] = cnt ++;
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
