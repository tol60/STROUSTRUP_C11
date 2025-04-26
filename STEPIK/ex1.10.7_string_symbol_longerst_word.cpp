// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <string>

using namespace std;


int main()
{
/*


Найдите в данной строке самое длинное слово и выведите его.
Входные данные
Вводится одна строка. Слова в ней отделены одним пробелом.
Выходные данные
Выведите самое длинное слово. Если таких слов несколько, то выводить нужно, которое встречается раньше.
Sample Input:
Everyone of us has all we need
Sample Output:
Everyone
*/

    string s;
    getline (cin, s);

    s += ' '; // we will add a space to simplify the code

    string max_st = "";
    int max_length = -1;
    int start = 0;
    int end_p1 = s.find(' ',start);

    while ( (end_p1 = s.find(' ',start)) != -1) { // find next space
        int len = end_p1 - start;
        if (len > max_length)  { // found longer word
            max_length = len;
            max_st = s.substr(start,len);
        }

        start = end_p1 + 1; // prepare for next search
    }

    // as we added extra space to the end of the string, do not need extra check for the last word here.

    cout << max_st;
    return 0;
}
