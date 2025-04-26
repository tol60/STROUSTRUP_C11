// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <cmath>

using namespace std;


bool IsPointInSquare(double x, double y) {
    return abs(x) <=1 && abs(y) <= 1;
}

int main()
{
/*
Даны два действительных числа x и y. Проверьте, принадлежит ли точка с координатами (x, y) заштрихованному квадрату (включая его границу). Если точка принадлежит квадрату, выведите слово YES, иначе выведите слово NO. На рисунке сетка проведена с шагом 1.
Решение должно содержать функцию IsPointInSquare(x, y), возвращающую true, если точка принадлежит квадрату и false, если не принадлежит. Основная программа должна считать координаты точки, вызвать функцию IsPointInSquare и в зависимости от возвращенного значения вывести на экран необходимое сообщение.

Функция IsPointInSquare не должна содержать инструкцию if.
Формат входных данных
Вводятся два действительных числа.
Формат выходных данных
Выведите ответ на задачу.

Sample Input 1:

0
0

Sample Output 1:

YES

Sample Input 2:

3
-7

Sample Output 2:

NO
*/


    double x, y;
    cin >> x >> y;

    if (IsPointInSquare(x, y) ) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}
