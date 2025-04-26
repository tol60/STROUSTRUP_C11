// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Отсортируйте массив.
Входные данные
Первая строка входных данных содержит количество элементов в массиве N ≤ 105. Далее идет N целых чисел, не превосходящих по абсолютной величине 109.
Выходные данные
Выведите эти числа в порядке неубывания.
Sample Input:
5
5 4 3 2 1
Sample Output:
1 2 3 4 5
*/

int main()
{
    int n; // number of words in a dictionary
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    for (auto now : a) {
        cout << now << " ";
    }

    return 0;
}
