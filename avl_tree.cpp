#include <iostream>

// 5
// 1 100
// 1 200
// 1 50
// 2 1
// 1 150

bool compare(int a, int b)
{
    if (a > b) {
        return true;
    } 
    return false;
}


struct Node {
    int Data;
    int height;
    int children;
    Node* Left;
    Node* Right;
    Node(int d) : Data (d), height(1), children(1), Left(nullptr), Right(nullptr) {}
};

class AVLTree {
private:
    bool (*p_comp_f)(int, int) = NULL;


    int GetHeight(Node*& root) {
        if (root == nullptr) {
            return 0;
        }
        else {
            return root->height;
        }
    }

    int GetChildren(Node*& root) {
        if (root == nullptr) {
            return 0;
        }
        else {
            return root->children;
        }
    }

    void RotateRight(Node*& root) {
        Node* tmp = root;
        root = root->Left;
        tmp->Left = root->Right;
        root->Right = tmp;
        root->Right->height = std::max(GetHeight(root->Right->Left), GetHeight(root->Right->Right)) + 1;
        root->height = std::max(GetHeight(root->Left), GetHeight(root->Right)) + 1;
        root->Right->children = GetChildren(root->Right->Left) + GetChildren(root->Right->Right) + 1;
        root->children = GetChildren(root->Right) + GetChildren(root->Left) + 1;
    }

    void RotateLeft(Node*& root) {
        Node* tmp = root;
        root = root->Right;
        tmp->Right = root->Left;
        root->Left = tmp;
        root->Left->height = std::max(GetHeight(root->Left->Left), GetHeight(root->Left->Right)) + 1;
        root->height = std::max(GetHeight(root->Left), GetHeight(root->Right)) + 1;
        root->Left->children = GetChildren(root->Left->Left) + GetChildren(root->Left->Right) + 1;
        root->children = GetChildren(root->Right) + GetChildren(root->Left) + 1;
    }

    void BigRotateLeft (Node*& root) {
        RotateLeft(root);
        RotateLeft(root->Left);
        RotateRight(root);
    }

    void BigRotateRight (Node*& root) {
        RotateRight(root);
        RotateRight(root->Right);
        RotateLeft(root);
    }

    void Balancer(Node*& root) {
        if (root != nullptr) {
            root->height = std::max(GetHeight(root->Right), GetHeight(root->Left)) + 1;
            if (GetHeight(root->Left) - GetHeight(root->Right) == -2) {
                if (GetHeight(root->Right->Left) <= GetHeight(root->Right->Right)) {
                    RotateLeft(root);
                }
                else {
                    BigRotateLeft(root);
                }
            }
            else if (GetHeight(root->Left) - GetHeight(root->Right) == 2) {
                if (GetHeight(root->Left->Right) <= GetHeight(root->Left->Left)) {
                    RotateRight(root);
                }
                else {
                    BigRotateRight(root);
                }
            }
        }
    }
public:
    AVLTree() {
        p_comp_f = &compare;
    }
    void Insert(Node*& root, int value, int& result) {
        if (root == nullptr) {
            root = new Node(value);
        }
        else {
            ++(root->children);
            if (root->Data <= value) {
                Insert(root->Right, value, result);
            }
            else {
                result += GetChildren(root->Right) + 1;
                Insert(root->Left, value, result);
            }
            Balancer(root);
        }
    }

    void Remove(Node*& root, int pos) {
        if (root != nullptr) {
            int r_elem = GetChildren(root->Right);  // check height
            if (r_elem < pos) {
                --root->children;
                pos -= (r_elem + 1);
                Remove(root->Left, pos);
            }
            else if (r_elem > pos) {
                --root->children;
                Remove(root->Right, pos);
            }
            else {
                if (root->Left == nullptr) {
                    if (root->Right == nullptr) {
                        root = nullptr;
                    }
                    else {
                        root = root->Right;
                    }
                }
                else if (root->Right == nullptr) {
                    root = root->Left;
                }
                else {
                    // int value = root->Data;
                    Node* node_right = root->Right;
                    while (node_right->Left != nullptr) {
                        node_right = node_right->Left;
                    }
                    Node* node_left = root->Left;
                    while (node_left->Right != nullptr) {
                        node_left = node_left->Right;
                    }
                    if (root->Data - node_left->Data < node_right->Data - root->Data) {
                        Remove(root, pos + 1);
                        node_left->Left = root->Left;
                        node_left->Right = root->Right;
                        node_left->children = root->children;
                        root = node_left;
                    }
                    else {
                        Remove(root, pos - 1);
                        node_right->Left = root->Left;
                        node_right->Right = root->Right;
                        node_right->children = root->children;
                        root = node_right;
                    }
                }
                Balancer(root);
            }
        }
    }
};

int main() {
    int n = 0;
    int num = 0;
    std::cin >> n;
    int value = 0;
    Node *node = nullptr;
    int result = 0;
    AVLTree tree;

    for (int i = 0; i < n; ++i) {
        std::cin >> num;
        std::cin >> value;
        if (num == 1) {
            result = 0;
            tree.Insert(node, value, result);
            std::cout << result << std::endl;
        }
        if (num == 2) {
            tree.Remove(node, value);
        }
    }
    return 0;
}