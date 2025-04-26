// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <set>
using namespace std;

/*
Даны два списка чисел, которые могут содержать до 100000 чисел каждый.  Выведите все числа, которые входят как в первый, так и во второй список в порядке возрастания.

Входные данные
Вводится число N - количество элементов первого списка, а затем N чисел первого списка.
Затем вводится число M - количество элементов второго списка, а затем M чисел второго списка.
Выходные данные
Выведите ответ на задачу.
Sample Input:
3
1 3 2
3
4 3 2
Sample Output:
2 3
*/
int main()
{
    int n;
    cin >> n;
    set<int> a;

    int x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        a.insert(x);
    }

    int m;
    cin >> m;
    set<int> b;

    for (int i = 0; i < m; i++) {
        cin >> x;
        b.insert(x);
    }

    // we iterate by set a.
    // and check if that element in set b
    for (auto v : a) {
        if (b.find(v) != b.end() ) {
            cout << v << ' ';
        }
    }

    return 0;
}
