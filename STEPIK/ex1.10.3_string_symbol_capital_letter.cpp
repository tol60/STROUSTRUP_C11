// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <string>

using namespace std;


int main()
{
/*
Переведите символ в верхний регистр.
Входные данные
Вводится единственый символ.
Выходные данные
Если введеный символ является строчной буквой латинского алфавита, то выведите такую же заглавную букву. В противном случае выведите тот же символ, который был введен.
Sample Input:
b
Sample Output:
B
*/


    char c;
    cin >> c;

    if (c >= 'a' && c <= 'z' ) {
        c = (c - 'a') + 'A';
    }

    cout << c;

    return 0;
}
