#include <iostream>
using namespace std;

struct Node {
    int x;
};

void deallocate(Node *node) {
    delete node;
    node = nullptr;
}

Node* init() {
    return new Node{5};
}

int pow(int x, int power)
{
    int result = 1;
    for (; power > 0; power--, result *= x);
    return result;
}

int main() {

    Node *node1 = init();
    delete node1;
    // Node *node2 = init();
    // cout << node1 << endl;
    // cout << node2 << endl;
    // deallocate(node1);
    int x = 0%5;
    cout << pow(2, 5) << endl;

    return 0;
}