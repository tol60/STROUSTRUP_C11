// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

// recursive function to calculate the max number shoes
// only st_ind will be changing from 0 to lst_ind (including)
// lst_ind =  shoe_vec.size() - 1; does not change
// memorization: memory.size() should be lst_ind + 1;

int Shoe(int st_ind, const int lst_ind, const vector<int> & shoe_vec, vector<int> & memory) {
    if (st_ind == lst_ind) return 1; // the only show size remaining.

    // this is the case where st_ind < lst_ind
    if (memory[st_ind] > 0) { // this value has been computed and memorized
        return memory[st_ind];
    } else { // need to compute the value for the first time.
        // we have two branches: a - we take the st_ind, the second one + we skip it. Need to get the maximum of both
        int a = Shoe(st_ind + 1, lst_ind, shoe_vec, memory); // we skip an element at st_ind (just trying starting the next one)

        // for the case b, we will take st_ind, but we have to make sure, that we skip the 2 sizes (the shoe difference should be >= 3
        int b = 1; // we select st_ind
        int sz = shoe_vec [st_ind]; // we will take this element;
        int ind = st_ind + 1;
        while ( ind <= lst_ind && shoe_vec[ind] - sz < 3) {
            ind ++;
        }
        // check if there is at least one more shoe we can try on
        if (ind <= lst_ind) {
            b += Shoe(ind, lst_ind, shoe_vec, memory); // we already initialized b by one.
        }

        int mx = max(a, b);
        memory[st_ind] = mx;
        return mx;
    }
}

/*
В обувном магазине продается обувь разного размера. Известно, что одну пару обуви можно надеть на другую, если она хотя бы на три размера больше. В магазин пришел покупатель. Требуется определить, какое наибольшее количество пар обуви сможет предложить ему продавец так, чтобы он смог надеть их все одновременно.
Входные данные
Сначала вводится размер ноги покупателя (обувь меньшего размера он надеть не сможет), затем количество пар обуви в магазине и размер каждой пары. Размер — натуральное число, не превосходящее 100, количество пар обуви в магазине не превосходит 1000.
Выходные данные
Выведите единственное число — максимальное количество пар обуви.
Sample Input:
26
5
30 35 40 41 42
Sample Output:
3
*/

int main()
{
/*
    int leg_sz;
    cin >> leg_sz; // leg size

    int n;
    cin >> n; // number of shoes

    set <int> s; // we will keep track of the available sizes.

    for (int i = 0; i < n; i++) {
        int sz;
        cin >> sz;
        s.insert(sz);
    }

    vector <int> v(s.size()); // the available sizes, but in a vector (sorted)

    for (auto now: s) {
        v.push_back(now);
    }

    // make sure there is at least one pair that the foot can feet into
    int idx = 0;
    for (; idx < (int)v.size(); idx ++) {
        if (v[idx] >= leg_sz) {
            break;
        }
    }
    if (idx <  (int) v.size() ) { // at least one pair exist, do the search.
        vector <int> mem(v.size()); // memorization vector
        int ans = Shoe(idx,v.size()-1, v, mem);
        cout << ans;
    } else {
        cout << "0";
    }
    */

    // https://stepik.org/lesson/13030/step/4?discussion=1123911&reply=4756862&thread=solutions&unit=4382
    int test_size, n;
    std::cin >> test_size >> n;
    std::set<int> shoes;
    for (int i=0, shoe_size=0; i<n; ++i) {
        std::cin >> shoe_size;
        shoes.insert(shoe_size);
    }

    int max_cnt = 0;
    for (auto shoe_size:shoes) {
        if (shoe_size >= test_size) {
            test_size = shoe_size + 3;
            max_cnt++;
        }
    }
  std::cout << max_cnt;

    return 0;
}
