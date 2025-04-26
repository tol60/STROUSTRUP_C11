// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

const int N_dig = 7; // number of different numbers
bool dom[N_dig][N_dig]; // this will allow us to keep track of the domino's and their orientantion


/*
Domino
Given n doninos try to find the longest chain possible
Idea:
In the longest chain there is always going to be one tile on the edge.
So we can can iterate over all available dominos (two orientations) as the starting tile, and then expand the following dominoes on one end only
*/

struct Domino {
    int x;
    int y;

    Domino() { // констуктор, вызывается при создании объекта класса
        std::cin >> x >> y;
    }

    // перегрузка оператора вывода
    friend std::ostream& operator << (std::ostream &out, const Domino& p)
    {
        out << p.x << " " << p.y;
        return out;
    }

};

/*
ostream& operator << (ostream &out, Point& p)
{
    return out << p.x << " " << p.y;
}
*/

// parms:
// p - the integer (on the right end) we are trying to attach next domino to
// len - the current length of the chain
// taken_domino - to keep track of which domino's are still available
// chain - to keep track of the chain we are creating
// Return:
// by how much can we extand the chain
int rec_trace (int p, int len, vector <bool> & taken_domino, vector <int> & chain, vector <int> & max_chain) {
    int n = chain.size(); // the number of longers possible chain
    if (len == n) {
        return 0;  // we can not extand the chain any more
    }

    int mx = 0;
    for (int i = 0; i < chain.size(); i++) {
        int depth = 0;
        if (taken_domino[i] == false) { // if we did not already taken this domino, check it
            int a = a[i].x;
            int b = a[i].y;

            int next_numb = -1;
            if (p == a) {
                next_numb = b;
            } else if (p == b) {
                next_numb = a;
            } else {
                continue;
            }

            //
            taken_domino[i] = true;
            chain[len] = i;
            depth = 1 + rec_trace (next_num, len + 1, taken_domino, chain, max_chain);
            taken_domino[i] = false;
        }
        if (depth > mx) {
            mx = depth;
            for (int i = len; i < len + depth; i++) {
                max_chain[i] = chain[i];
            }
        }
    }
    return mx;
}

int main() {
    for (int i = 0; i < N_dig; i++) {
        for (int j = 0; j < N_dig; j++) {
            dom[i][j] = false;
        }
    }
    int n;
    cin >> n; // number of domino's available.

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        dom[x][y] = true;
        dom[y][x] = true;
    }

 /*
    vector <Domino> a(n);
    cout << "Dominos:\n";
    for (auto now : a) {
        cout << now << endl;
    }
*/
    int len = 0;
    int max_len = 0;
    vector <int> chain(n); // current chain, indexs into a(n)
    vector <int> max_chain(n); // indexes into a(n), will keep track of the longest chain
    vector <bool> taken_domino(n); // if zero: available, if 1 - taken.

    // Idea:
    // In the longest chain there is always going to be one tile on the edge.
    // So we can can iterate over all available dominos (two orientations) as the starting tile, and then expand the following dominoes on one end only
    int mx = 0;
    for (int i = 0; i < n; i++) { // iterate over the starting domino
        Domino & d = a[i];

        int len = rec_trace (d.x, 0, taken_domino, chain, max_chain);
        if (mx < len) {
            mx = len;
        }

        len = 1;
        chain[0] = i;

    }

    return 0;
}
