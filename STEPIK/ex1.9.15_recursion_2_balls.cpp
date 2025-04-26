// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <vector>

using namespace std;

// When we introduce an extra throw, the first throw would go to floor n, and that would allow us to test extra C(n) floors
// C(1) = 1
// C(n) = C(n-1) + 1;
// The case of C[0] = 1 is to cover the case of just 1 floor. We know by definition that the ball will break, so 0 throws are required.
// The more interesting cases start at the second floor (where we need a single throw at floor 1)
// memo vector should be initialized it memo[0] = 1, and memo[1] = 1
//     std::vector<int> memo = {1, 1}; // C[1] = 1. (C[0] = 1 will not be used in actual conputation
int C(int n, std::vector<int> & memo) {
    if (n == 1) return 1;
    if (memo.size() < n + 1) {
        int ans = C(n - 1, memo) + 1; // recursion
        memo.push_back(ans); // record in the memory array
    }
    return memo[n];  // return the record
}

// k - is the floor we enquire
int floor(int k, std::vector<int> & memo) {
    if (k == 1) return 0;
    int n = 1; // how many throws we will try.
    int fl = 2; // when we are on the second floor we only need 1 throw.
    while (fl < k) {
        n++; // add another throw
        fl += C(n, memo); // this will cover extra floors
    }
    return n;
}

int main()
{
/*
В небоскребе n этажей. Известно, что если уронить стеклянный шарик с этажа номер p, и шарик разобьется, то если уронить шарик с этажа номер p+1, то он тоже разобьется. Также известно, что при броске с последнего этажа шарик всегда разбивается.Вы хотите определить минимальный номер этажа, при падении с которого шарик разбивается. Для проведения экспериментов у вас есть два шарика. Вы можете разбить их все, но в результате вы должны абсолютно точно определить этот номер.
Определите, какого числа бросков достаточно, чтобы заведомо решить эту задачу.
Формат входных данных
Программа получает на вход количество этажей в небоскребе.
Формат выходных данных
Требуется вывести наименьшее число бросков, при котором можно всегда решить задачу.
Примечание
Комментарий к первому примеру. Нужно бросить шарик со 2-го этажа. Если он разобьется, то бросим второй шарик с 1-го этажа, а если не разобьется - то бросим шарик с 3-го этажа.
Подсказки
1. Как следует действовать, если шарик был бы только один?
2. Пусть шариков два и мы бросили один шарик с этажа номер k. Как мы будем действовать в зависимости от того, разобьется ли шарик или нет?
3. Пусть f(n) - это минимальное число бросков, за которое можно определить искомый этаж, если бы в небоскребе было n этажей. Выразите f(n) через значения f(a) для меньших значений a.

Sample Input 1:

4

Sample Output 1:

2

Sample Input 2:

5
*/

    std::vector<int> memo = {1, 1}; // C[1] = 1. (C[0] = 1 will not be used in actual conputation
    int n;
    cin >> n;

    int answer = floor(n, memo);
    cout << answer;

    int form = answer * (answer + 1) / 2 + 1; // Exact formula
    cout << endl << "This would cover " << form << endl;



    return 0;
}
