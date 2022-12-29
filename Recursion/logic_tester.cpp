#include <iostream>
#include <cstring>

using namespace std;

void fun(int &a) {
    cout << a;
}

void fixArr(char c[], int index, int distance) {

    if (index >= 20) {
        return;
    }
    
    if (index < distance) {
        c[index] = c[index+1];
    } else {
        c[index] = '\0';
    }

    fixArr(c, index+1, distance);
}

int main() {
    char c[20] = "123456789abcd0";

    fixArr(c, 0, 4);

    //c[0]='A';

    int size = strlen(c);

    for (int i = 0; i < 20; i++) {
        if (c[i] == '\0') {
            cout << 1;

        }
        else {cout << 0;}
    }
    cout << c << endl;

    cout << char(1) << "1"<< endl;

    int x = 5;
    //fun(x);

    // if (c[3] == '\0') {

    //     cout << "123";
    // }

    cout << endl << (19*55)%141 << endl;


    return 0;
}