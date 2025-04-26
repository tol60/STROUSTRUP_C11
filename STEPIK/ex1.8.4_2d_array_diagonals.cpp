// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>

using namespace std;

int main()
{
/*


Дано число n, не превышающее 100. Создайте массив размером n×n и заполните его по следующему правилу. На главной диагонали должны быть записаны числа 0. На двух диагоналях, прилегающих к главной, числа 1. На следующих двух диагоналях числа 2, и т.д. Выведите полученный массив на экран, разделяя элементы массива пробелами.

Sample Input:

5

Sample Output:

0 1 2 3 4
1 0 1 2 3
2 1 0 1 2
3 2 1 0 1
4 3 2 1 0


*/
    int n;
    cin >> n;


    // fill up the  matrix
    int a[100][100];
    for (int i = 0; i < n; i++) { // select the fill
        for (int j = 0; j < n - i; j++) {
            a[j][j+i] = i;
            a[j+i][j] = i;
        }
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
