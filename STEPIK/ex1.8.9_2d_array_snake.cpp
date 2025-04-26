// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
/*
По данным числам n и m заполните двумерный массив размером n×m числами от 1 до n×m “змейкой”, как показано в примере.
Формат входных данных
Вводятся два числа n и m, каждое из которых не превышает 30.
Формат выходных данных

Выведите полученный массив, отводя на вывод каждого элемента ровно 4 символа.

Sample Input:

3 5

Sample Output:

   1   2   3   4   5
  10   9   8   7   6
  11  12  13  14  15
*/


    int n, m;
    cin >> n >> m;

    int a[30][30];

    int cnt = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++){
            if (i % 2 == 0) {
                a[i][j] = cnt++;
            } else {
                a[i][m - j -1] = cnt++;
            }
        }
    }

    // process
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << setw(4) << a[i][j];
        }
        cout << endl;
    }

    return 0;
}
