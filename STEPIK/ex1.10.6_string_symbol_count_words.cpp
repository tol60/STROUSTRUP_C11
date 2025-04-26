// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <string>

using namespace std;


int main()
{
/*
Дана строка, содержащая пробелы. Найдите, сколько в ней слов (слово – это последовательность непробельных символов, слова разделены одним пробелом,
первый и последний символ строки – не пробел).
Входные данные
На вход подается несколько строк.
Выходные данные
Необходимо вывести количество слов в первой из введенных строк.
Примечание
﻿В этой задаче может быть полезен метод find с двумя параметрами. Первый из них - искомая подстрока, второй - позиция, начиная с которой нужно искать первое вхождение.
Sample Input:
In the town where I was born
Sample Output:
7
*/


    string s;
    getline(cin, s);  // read string s

    int cnt = 1;
    int start = 0;
    while ( (start = s.find(' ', start + 1)) != -1){ // find next space
        cnt ++;
    }

    cout << cnt;

    return 0;
}
