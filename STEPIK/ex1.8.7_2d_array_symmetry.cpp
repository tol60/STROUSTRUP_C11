// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>

using namespace std;

int main()
{
/*
Дано число n, не превосходящее 10, и массив размером n × n. Проверьте, является ли этот массив симметричным относительно главной диагонали. Выведите слово “YES”, если массив симметричный, и слово “NO” в противном случае.

Sample Input:

3
0 1 2
1 2 3
2 3 4

Sample Output:

YES
*/
    int n;
    cin >> n;

    int a [10][10];
    // input
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            cin >> a[i][j];
        }
    }


    // processing
    for (int i = 0; i < n-1; i++) { // row
        for (int j = 1+i; j < n; j++) {
            if (a[i][j] != a[j][i]) {
                cout << "NO";
                return 0;
            }
        }
    }

    cout << "YES";
    return 0;
}
