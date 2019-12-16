#include <iostream>
#include <stack>

using std::cin;
using std::cout;
using std::stack;

struct Node {
    int Data;
    Node* Left; 
    Node* Right; 
};

void Insert(Node*& node, int value) 
{
    if (node == NULL) {
        node = new Node();
        node->Data = value;
        return;
    }
    if (node->Data > value)
        Insert(node->Left, value);
    else
        Insert(node->Right, value);
};

// Обратный обход в глубину. non-recursive post-order
void TraverseDFS(Node* root)
{
    if (root == NULL) 
        return; 
    stack<Node *> s, s2; 

    s.push(root); 
    Node *node = new Node(); 

    while (!s.empty()) { 

        node = s.top(); 
        s.pop(); 
        s2.push(node); 

        if (node->Left) 
            s.push(node->Left); 
        if (node->Right) 
            s.push(node->Right); 
    } 

    // print elements of second stack 
    while (!s2.empty()) { 
        node = s2.top(); 
        s2.pop(); 
        cout << node->Data << " "; 
        delete node;
    } 

};


int main() {
    int n;
    cin >> n;
    int root_data;
    cin >> root_data;
    Node *node = new Node();
    node->Data = root_data;
    --n;
    for (int i = 0; i < n; i++){
        int val;
        cin >> val;
        Insert(node, val);
    }
    TraverseDFS(node);
    return 0;
}