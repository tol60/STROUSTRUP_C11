// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <set>
using namespace std;

/*
Во входной строке записана последовательность чисел через пробел. Для каждого числа выведите слово YES (в отдельной строке), если это число ранее встречалось в последовательности или NO, если не встречалось.

Входные данные
Вводится число N - количество элементов списка, а затем N чисел.
Выходные данные
Выведите ответ на задачу.
Sample Input:
6
1 2 3 2 3 4
Sample Output:
NO
NO
NO
YES
YES
NO
*/
int main()
{
    int n;
    cin >> n;

    set<int> s;
    int x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        if (s.find(x) == s.end()) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
        s.insert(x);
    }

    return 0;
}
