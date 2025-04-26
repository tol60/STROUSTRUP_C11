// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <cmath>

using namespace std;


int MinDivisor(int n) {
    for (int i = 2, isqrt = sqrt(n); i <= isqrt; i++) {
        if (n % i == 0) {
            return i;
        }
    }
    return n;
}





int main()
{
/*
Дано натуральное число n > 1. Выведите его наименьший делитель, отличный от 1.
Решение оформите в виде функции MinDivisor(n). Количество операций в программе должно быть пропорционально корню из n.
Указание. Если у числа n нет делителя, меньшего n , то число n — простое и ответом будет само число n.
Формат входных данных
Вводится натуральное число.
Формат выходных данных
Выведите ответ на задачу.
*/


    int n;
    cin >> n;

    cout << MinDivisor(n);

    return 0;
}
