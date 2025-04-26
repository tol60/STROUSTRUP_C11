// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <cmath>

using namespace std;


double distance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

int main()
{
/*
Даны четыре действительных числа: x1, y1, x2, y2. Напишите функцию distance(x1, y1, x2, y2), вычисляющую расстояние между точкой (x1. y1) и (x2, y2). Считайте четыре действительных числа и выведите результат работы этой функции.
Формат входных данных
Вводятся четыре действительных числа.
Формат выходных данных
Выведите ответ на задачу.

Sample Input:

0
0
1
1

Sample Output:

1.41421
*/


    double x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    cout << distance(x1, y1, x2, y2);

    return 0;
}
