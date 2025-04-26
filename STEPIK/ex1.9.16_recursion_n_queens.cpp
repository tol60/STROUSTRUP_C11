// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <vector>

using namespace std;

// Recursive function, is trying to put the queen into the other column
// n_queens - number of queens
// n - how many queens had been placed
int queens(int n_queens, int n, vector <int> & row, vector <int> & taken_rows) {
    if (n == n_queens) {
        return 1;
    }

    int sum = 0;
    for (int i = 0; i < n_queens; i++) {
        // trying to place another queen (index n) into row i
        if (taken_rows[i] > 0) { // we already placed another queen in this row
            continue;
        }

        // check if we hit the diagonal
        bool hit = false;
        for (int j = 0; j < n; j++) {
            if ( abs(j - n) == abs(row[j] - i) ) {
                hit = true;
                continue;
            }
        }
        if (hit) {
            continue;
        }

        // we can put the n-th queen into i-th row
        taken_rows[i] = 1;
        row[n] = i;

        sum += queens(n_queens, n + 1, row, taken_rows); // recursion

        taken_rows[i] = 0;
        row[n] = 0;
    }
    return sum;
}


int main()
{
/*
Дано число N. Определите, сколькими способами можно расставить на доске N×N N ферзей, не бьющих друг друга.
Формат входных данных

Задано единственное число N. (N ≤ 10)
Формат выходных данных
Выведите ответ на задачу.
Подсказка
Напишите рекурсивную функцию, которая пытается поставить ферзя в очередной столбец. Если на эту клетку ставить ферзя нельзя (он бьет предыдущих), то такой вариант даже не стоит рассматривать. Когда вы успешно поставили ферзя в последний столбец - увеличивайте счетчик.

Sample Input:

8

Sample Output:

92
*/

    // int [10][10] field;
    int n;
    cin >> n;

    vector <int> row(n); // row[i] will give the row of the i-th queen
    vector <int> taken_rows(n); // keep track of taken rows

    cout << queens(n, 0, row, taken_rows);

    return 0;
}
