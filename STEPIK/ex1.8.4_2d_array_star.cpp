// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>

using namespace std;

int main()
{
/*




Дано нечетное число n, не превосходящее 15. Создайте двумерный массив из n×n элементов, заполнив его символами "." (каждый элемент массива является строкой из одного символа). Затем заполните символами "*" среднюю строку массива, средний столбец массива, главную диагональ и побочную диагональ. В результате "*" в массиве должны образовывать изображение звездочки. Выведите полученный массив на экран, разделяя элементы массива пробелами.

Sample Input:

5

Sample Output:

* . * . *
. * * * .
* * * * *
. * * * .
* . * . *




*/
    int n;
    cin >> n;

    // set all to '.'
    char a[15][15];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = '.';
        }
    }

    int m = n - 1;
    for (int i = 0; i < n; i++) {
        a[i][i] = '*'; // one diagonal
        a[i][m - i] = '*'; // another diagonal
        a[i][m / 2] = '*';  // half horizontal
        a[m / 2] [i] = '*'; // half vertical
    }

    // output
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
