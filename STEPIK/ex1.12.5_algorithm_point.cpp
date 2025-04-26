// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility> // pair
using namespace std;

/*
Выведите все исходные точки в порядке возрастания их расстояний от начала координат.
Входные данные
Программа получает на вход набор точек на плоскости. Сначала задано количество точек n, затем идет последовательность из n строк, каждая из которых содержит два числа: координаты точки. Величина n не превосходит 100, все исходные координаты – целые числа, не превосходящие 103.
Выходные данные
Необходимо вывести все исходные точки в порядке возрастания их расстояний от начала координат.
Sample Input:
2
1 2
2 3
Sample Output:
1 2
2 3
*/

int main()
{
    int n;
    cin >> n; // number of points

    vector <pair<int, int>> a(n);
    vector <pair<int, int>> dist_ind(n); // {dist, ind} will be used for sorting,
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[i] = {x, y};

        int sq_dist = x * x + y * y;
        dist_ind[i] = {sq_dist, i};
    }

    sort(dist_ind.begin(), dist_ind.end()); // sort distance in ascending order
    // reverse(a.begin(),a.end()); // discending order

    for (auto now : dist_ind) {
        pair<int, int> & tmp = a[now.second];
        cout << tmp.first << " " << tmp.second << endl;
    }

    return 0;
}
