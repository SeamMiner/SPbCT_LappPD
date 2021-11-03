#include <process.h>
#include <stdarg.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "ru");
    FILE* f; 
    errno_t err;
    f = fopen(argv[1], "r");
    if (!f) {
        cout << "Файл не был открыт";
        return 0;
    }
    char* pEnd;
    char c, ch[50];
    int counter = -1, max = strtoll(argv[1], &pEnd, 10);
    if (f != 0) {
        while (true)
        {
            counter++;
            ch[counter] = fgetc(f);
            if (ch[counter] == EOF)
                break;
            cout << ch[counter] << " ";
        }

        fclose(f);
    }
}
