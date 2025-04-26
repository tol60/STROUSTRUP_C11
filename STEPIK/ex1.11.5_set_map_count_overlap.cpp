// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <set>
using namespace std;

/*
Даны два списка чисел, которые могут содержать до 100000 чисел каждый. Посчитайте, сколько чисел содержится одновременно как в первом списке, так и во втором.

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
2
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

    int cnt = 0;
    // we iterate by set a.
    // and check if that element in set b
    for (auto v : a) {
        if (b.find(v) != b.end() ) {
            cnt ++;
        }
    }

    cout << cnt;

    return 0;
}
