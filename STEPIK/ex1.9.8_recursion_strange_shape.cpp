// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <cmath>

using namespace std;


double distance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

bool IsPointInCircle(double x, double y, double xc, double yc, double r) {
    return distance (x, y, xc, yc ) <= r;
}

bool IsPointInsideCircle(double x, double y, double xc, double yc, double r) {
    return distance (x, y, xc, yc ) < r;
}

// y >= 2*x + 2
// y >= -x
bool IsPointInArea_Top (double x, double y) {
    return (y >= 2 * x + 2) && (y >= -x) && IsPointInCircle(x, y, -1, 1, 2);
}

bool IsPointInArea_Bottom (double x, double y) {
    return (y <= 2 * x + 2) && (y <= -x) && !IsPointInsideCircle(x, y, -1, 1, 2);
}

bool IsPointInArea (double x, double y) {
    return IsPointInArea_Top (x, y) || IsPointInArea_Bottom (x, y);
}

int main()
{
/*
Проверьте, принадлежит ли точка данной закрашенной области:
Если точка принадлежит области (область включает границы), выведите слово YES, иначе выведите слово NO.
Решение должно содержать функцию IsPointInArea(x, y), возвращающую True, если точка принадлежит области и False, если не принадлежит. Основная программа должна считать координаты точки, вызвать функцию IsPointInArea и в зависимости от возвращенного значения вывести на экран необходимое сообщение.
Функция IsPointInArea не должна содержать инструкцию if.
Формат входных данных
Вводятся два действительных числа.
Формат выходных данных
Выведите ответ на задачу.
*/


    double x, y;
    cin >> x >> y;

    if (IsPointInArea(x, y) ) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}
