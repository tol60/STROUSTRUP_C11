// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

/*
Выведите фамилии и имена учащихся в порядке убывания их среднего балла.
Входные данные
Заданы сначала количество учащихся n, затем n строк, каждая из которых содержит фамилию, имя и три числа
(оценки по трем предметам: математике, физике, информатике). Данные в строке разделены одним пробелом. Оценки принимают значение от 1 до 5.
Выходные данные
Необходимо вывести пары фамилия-имя по одной на строке, разделяя фамилию и имя одним пробелом.
Выводить оценки не нужно. Если несколько учащихся имеют одинаковые средние баллы, то их нужно выводить в порядке, заданном во входных данных.
Sample Input:
3
Markov Valeriy 5 5 5
Sergey Petrov 1 1 1
Petrov Petr 3 3 3

Sample Output:
Markov Valeriy
Petrov Petr
Sergey Petrov
*/

struct Pupil {
    string last_name;
    string first_name;
    int gr_a;
    int gr_b;
    int gr_c;
    int sum;
    Pupil () { // constructor
        std::cin >> last_name >> first_name >> gr_a >> gr_b >> gr_c;
        sum = gr_a + gr_b + gr_c;
    }

    // Overload compare operator for sorting
    bool operator < (const Pupil & p ) const {
        return sum > p.sum;
    }

    // Overload print operator
    friend std::ostream & operator << (std::ostream & out, const Pupil& p) {
        out << p.last_name << " " << p.first_name;
        return out;
    }
};

int main()
{
    int n;
    cin >> n; // number of points

    vector <Pupil> a(n);
    // sort(a.begin(), a.end());
    stable_sort(a.begin(), a.end());
    // reverse(a.begin(),a.end()); // reverse order

    for (auto now : a) {
        cout << now << endl;
    }

    return 0;
}
