// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <cmath>

using namespace std;


double power(double a, int n) {
    if (n > 0) {
        return a * power(a, n - 1);
    } else if (n == 0) {
        return 1;
    } else { // if n < 0
        return 1 / power(a, -n);
    }
}





int main()
{
/*
Дано действительное положительное число a и целоe число n.

Вычислите a^n. Решение оформите в виде рекурсивной функции power(a, n).
Формат входных данных
Вводится действительное положительное число a и целоe число n.
Формат выходных данных
Выведите ответ на задачу.
*/


    double a;
    int n;
    cin >> a >> n;

    cout << power(a, n);

    return 0;
}
