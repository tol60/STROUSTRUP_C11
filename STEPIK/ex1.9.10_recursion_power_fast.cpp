// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <cmath>

using namespace std;


double power(double a, int n) {
    if (n < 0) {
       return 1 / power(a, -n);
    } else if (n == 0) {
        return 1;
    } else if (n% 2 == 0){
        return power(a*a, n/2);
    } else {
         return a * power(a, n - 1);
    }
}

int main()
{
/*
Возводить в степень можно гораздо быстрее, чем за n умножений! Для этого нужно воспользоваться следующими рекуррентными соотношениями:

an = (a2)n/2  при четном n,

an = a × an−1 при нечетном n.

Реализуйте алгоритм быстрого возведения в степень с помощью рекурсивной функции.
Формат входных данных
Вводятся действительное число a и целое неотрицательное число n.
Формат выходных данных
Выведите ответ на задачу.
*/


    double a;
    int n;
    cin >> a >> n;

    cout << power(a, n);



    return 0;
}
