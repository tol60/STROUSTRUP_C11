// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <iomanip>

using namespace std;


int min (int a, int b) {
    if (a <= b) {
        return a;
    } else {
        return b;
    }
}

int min4 (int a, int b, int c, int d){
    return min(min(a, b), min (c, d));
}

int main()
{
/*
Напишите функцию min(a, b), вычисляющую минимум двух чисел. Затем напишите функцию min4(a, b, c, d), вычисляющую минимум 4 чисел с помощью функции min. Считайте четыре целых числа и выведите их минимум.
Формат входных данных
Вводятся четыре целых числа.
Формат выходных данных
Выведите ответ на задачу.

Sample Input:

4
5
6
7

Sample Output:

4
*/


    int a, b, c, d;
    cin >> a >> b >> c >> d;

    cout << min4(a, b, c, d);

    return 0;
}
