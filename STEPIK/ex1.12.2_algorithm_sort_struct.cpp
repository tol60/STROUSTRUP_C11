// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct man {
    int height;
    string name;
};

bool cmp(man a, man b) {
    return a.height < b.height;
}

int main()
{
    int n; // number of words in a dictionary
    cin >> n;
    vector <man> a(n);
    for (int i = 0; i < n; i++) {
        int tmp;
        string s_tmp;
        cin >> tmp >> s_tmp;
        man struct_tmp; // temporary structure
        struct_tmp.height = tmp;
        struct_tmp.name = s_tmp;
        a[i] = struct_tmp;
    }
    sort (a.begin(),a.end(), cmp);

    for (auto now : a) {
        cout << now.name << endl;
    }

    return 0;
}
