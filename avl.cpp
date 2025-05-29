#include <iostream>
#include <vector>
using namespace std;
struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};
NODE* createNODE(int data) {
	NODE* newnode = new NODE;
	newnode->key = data;
	newnode->p_left = nullptr;
	newnode->p_right = nullptr;
    newnode->height = 1;
	return newnode;
}
int height(NODE* node) {
    if (node == nullptr)
        return 0;
    else
        return node->height;
}
int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}
int getBalance(NODE* node) {
    if (node == nullptr)
        return 0;
    return height(node->p_left) - height(node->p_right);
}
NODE* rotateRight(NODE* p) {
    NODE* x = p->p_left;
    NODE* T2 = x->p_right;
    x->p_right = p;
    p->p_left = T2;
    p->height = max(height(p->p_left), height(p->p_right)) + 1;
    x->height = max(height(x->p_left), height(x->p_right)) + 1;
    return x;
}
NODE* rotateLeft(NODE* x) {
    NODE* p = x->p_right;
    NODE* T2 = p->p_left;
    p->p_left = x;
    x->p_right = T2;
    x->height = max(height(x->p_left), height(x->p_right)) + 1;
    p->height = max(height(p->p_left), height(p->p_right)) + 1;
    return p;
}
void Insert(NODE* &pRoot, int key) {
    if (pRoot == nullptr) {
        pRoot = createNODE(key);
        return;
    }

    if (key < pRoot->key) {
        Insert(pRoot->p_left, key);
    } 
    else if (key > pRoot->key) {
        Insert(pRoot->p_right, key);
    } 
    else {
        return;
    }
    int leftheight = height(pRoot->p_left);
    int rightheight = height(pRoot->p_right);
    if (leftheight > rightheight) {
        pRoot->height = leftheight + 1;
    } else {
        pRoot->height = rightheight + 1;
    }
    int balance = getBalance(pRoot);
    if (balance > 1 && key < pRoot->p_left->key) {
        pRoot = rotateRight(pRoot);
    }
    else if (balance < -1 && key > pRoot->p_right->key) {
        pRoot = rotateLeft(pRoot);
    }
    else if (balance > 1 && key > pRoot->p_left->key) {
        pRoot->p_left = rotateLeft(pRoot->p_left);
        pRoot = rotateRight(pRoot);
    }
    else if (balance < -1 && key < pRoot->p_right->key) {
        pRoot->p_right = rotateRight(pRoot->p_right);
        pRoot = rotateLeft(pRoot);
    }
}
bool isAVL(NODE* pRoot) {
    if (pRoot == nullptr) {
    return true;
    }
    int balance = getBalance(pRoot);
    if (balance < -1 || balance > 1){
        return false;
    } 
    return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}
vector<int> LNR(NODE* pRoot) {
	vector<int> result;
	if (pRoot == nullptr) {
		return result;
	}
	vector<int> left = LNR(pRoot->p_left);
	result.insert(result.end(), left.begin(), left.end());
	result.push_back(pRoot->key);
	vector<int> right = LNR(pRoot->p_right);
	result.insert(result.end(), right.begin(), right.end());
	return result;
}
NODE* minValueNode(NODE* node) {
    NODE* current = node;
    while (current->p_left != nullptr)
        current = current->p_left;
    return current;
}
void Remove(NODE* &pRoot, int x) {
    if (pRoot == nullptr)
        return;
    if (x < pRoot->key)
        Remove(pRoot->p_left, x);
    else if (x > pRoot->key)
        Remove(pRoot->p_right, x);
    else {
        if (pRoot->p_left == nullptr || pRoot->p_right == nullptr) {
            NODE* temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
            if (temp == nullptr) { 
                temp = pRoot;
                pRoot = nullptr;
            } else { // 
                *pRoot = *temp; 
            }
            delete temp;
        } else {
            NODE* temp = minValueNode(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }

    if (pRoot == nullptr)
        return;
    pRoot->height = 1 + max(height(pRoot->p_left),
    height(pRoot->p_right));
    int balance = getBalance(pRoot);
    if (balance > 1 && getBalance(pRoot->p_left) >= 0)
        pRoot = rotateRight(pRoot);
    else if (balance > 1 && getBalance(pRoot->p_left) < 0) {
        pRoot->p_left = rotateLeft(pRoot->p_left);
        pRoot = rotateRight(pRoot);
    }
    else if (balance < -1 && getBalance(pRoot->p_right) <= 0)
        pRoot = rotateLeft(pRoot);
    else if (balance < -1 && getBalance(pRoot->p_right) > 0) {
        pRoot->p_right = rotateRight(pRoot->p_right);
        pRoot = rotateLeft(pRoot);
    }
}

int main() {
    NODE* root = nullptr;

    // Thêm các phần tử vào AVL Tree
    Insert(root, 30);
    Insert(root, 20);
    Insert(root, 40);
    Insert(root, 10);
    Insert(root, 25);
    Insert(root, 50);

    cout << "LNR Traversal: ";
    vector<int> inorder = LNR(root);
    for (int val : inorder) {
        cout << val << " ";
    }
    cout << endl;

    cout << "Is AVL? " << (isAVL(root) ? "Yes" : "No") << endl;

    Remove(root, 20);
    cout << "After removing 20:" << endl;
    cout << "LNR Traversal: ";
    inorder = LNR(root);
    for (int val : inorder) {
        cout << val << " ";
    }
    cout << endl;

    cout << "Is AVL? " << (isAVL(root) ? "Yes" : "No") << endl;

    return 0;
}