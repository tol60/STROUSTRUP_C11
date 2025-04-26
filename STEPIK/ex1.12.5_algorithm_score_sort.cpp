// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility> // pair
using namespace std;


/*
Во время проведения олимпиады каждый из участников получил свой идентификационный номер – натуральное число.
Необходимо отсортировать список участников олимпиады по количеству набранных ими баллов.
Входные данные
На первой строке дано число N (1 ≤ N ≤ 1000) – количество участников.
На каждой следующей строке даны идентификационный номер и набранное число баллов соответствующего участника. Все числа во входном файле не превышают 105.
Выходные данные
В выходной файл выведите исходный список в порядке убывания баллов. Если у некоторых участников одинаковые баллы, то их между собой нужно упорядочить в порядке возрастания идентификационного номера.

Sample Input 1:
3
101 80
305 90
200 14
Sample Output 1:
305 90
101 80
200 14

Sample Input 2:
3
20 80
30 90
25 90
Sample Output 2:
25 90
30 90
20 80
*/

// {id, pnt}
bool cmp(const pair<int, int>& a, const pair<int,int>& b) {
    if (a.second == b.second) { // pnt
        // return a.first >= b.first; // id
        return a.first > b.first; // id
    } else {
        return a.second < b.second; // pnt
    }
}

int main()
{
    int n;
    cin >> n; // number of shoes

    vector <pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int id, pnt;
        cin >> id >> pnt;
        a[i] = {id, pnt};
    }

    sort(a.begin(), a.end(), cmp);
    reverse(a.begin(),a.end()); // discending order

    for (auto now : a) {
        cout << now.first << " " << now.second << endl;
    }

    return 0;
}
