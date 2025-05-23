// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>

using namespace std;

int main()
{
/*

Дан двумерный массив и два числа: i и j. Поменяйте в массиве столбцы с номерами i и j
Формат входных данных
Программа получает на вход размеры массива n и m, не превосходящие 100, затем элементы массива, затем числа i и j.
Формат выходных данных

Выведите результат.

Sample Input:

3 4
11 12 13 14
21 22 23 24
31 32 33 34
0 1

Sample Output:

12 11 13 14
22 21 23 24
32 31 33 34
*/
    int n, m;
    cin >> n >> m;

    int a [100][100];
    // input
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }

    int i, j;
    cin >> i >> j;

    for (int k = 0; k < n; k++) {
        int tmp = a[k][i];
        a[k][i] = a[k][j];
        a[k][j] = tmp;
    }

    // output
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
