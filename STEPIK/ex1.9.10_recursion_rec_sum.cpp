// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <cmath>

using namespace std;


int rec_sum() {
    int n;
    cin >> n;
    if (n == 0) {
        return 0;
    } else {
        return n + rec_sum();
    }
}

int main()
{
/*
Дана последовательность чисел, завершающаяся числом 0. Найдите сумму всех этих чисел, не используя цикл.
Формат входных данных
Вводится последовательность целых чисел, оканчивающаяся числом 0 (само число 0 в последовательность не входит, а служит как признак ее окончания).
Формат выходных данных
Выведите ответ на задачу.

Sample Input:

1
7
9
0

Sample Output:

17

*/

    cout << rec_sum();



    return 0;
}
