
#include <iostream>
#include <vector>
using namespace std;
struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};
NODE* createNODE(int data) {
	NODE* newnode = new NODE;
	newnode->key = data;
	newnode->p_left = nullptr;
	newnode->p_right = nullptr;
	return newnode;
}
NODE* Search(NODE* pRoot, int x) {
    if (pRoot == nullptr || pRoot->key == x)
        return pRoot;

    if (x < pRoot->key)
        return Search(pRoot->p_left, x);
    else
        return Search(pRoot->p_right, x);
}
void Insert(NODE* &pRoot, int x) {
    if (pRoot == nullptr) {
        pRoot = createNODE(x);
        return;
    }
    if (x < pRoot->key) {
        Insert(pRoot->p_left, x);
    } 
    else if (x > pRoot->key) {
        Insert(pRoot->p_right, x);
    }
}
void Remove(NODE* &pRoot, int x) {
    if (pRoot == nullptr) {
        return;  
    }
    if (x < pRoot->key) {
        Remove(pRoot->p_left, x); 
    } 
    else if (x > pRoot->key) {
        Remove(pRoot->p_right, x); 
    } 
    else {
        if (pRoot->p_left == nullptr && pRoot->p_right == nullptr) {
            delete pRoot;
            pRoot = nullptr;
        }
        else if (pRoot->p_left == nullptr) {
            NODE* temp = pRoot;
            pRoot = pRoot->p_right;
            delete temp;
        } 
        else if (pRoot->p_right == nullptr) {
            NODE* temp = pRoot;
            pRoot = pRoot->p_left;
            delete temp;
        }
        else {
            NODE* temp = pRoot->p_right;
            while (temp->p_left != nullptr)
                temp = temp->p_left;
            pRoot->key = temp->key; 
            Remove(pRoot->p_right, temp->key);  
        }
    }
}
NODE* createTree(int a[], int n){
    NODE* pRoot= createNODE(a[0]);
    for (int i=1 ;i <n;i++){
        Insert(pRoot, a[i]);
    }
    return pRoot;
}
void removeTree(NODE* &pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    removeTree(pRoot->p_left);   
    removeTree(pRoot->p_right);  
    delete pRoot;                
    pRoot = nullptr;             
}
int Height(NODE* pRoot) {
    if (pRoot == nullptr) return 0;
    int left = Height(pRoot->p_left);
    int right = Height(pRoot->p_right);
    return max(left, right) + 1;
}
int countLess(NODE* pRoot, int x) {
    if (pRoot == nullptr) {
        return 0;
    }
    if (pRoot->key < x) {
        return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
    }
    else {
        return countLess(pRoot->p_left, x);
    }
}
int countGreater(NODE* pRoot, int x){
    if (pRoot == nullptr) {
        return 0;
    }
    if (pRoot->key > x) {
        return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
    }
    else {
        return countGreater(pRoot->p_right, x);
    }
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
bool isBST(NODE* pRoot) {
    vector<int> Inorder = LNR(pRoot);
	for (int i = 1; i < Inorder.size(); ++i) {
        if (Inorder[i] <= Inorder[i - 1]) {
            return false;
        }
    }
    return true;
}
bool isFullTree(NODE* pRoot) {
    if (pRoot == nullptr) return true;
    if ((pRoot->p_left == nullptr) != (pRoot->p_right == nullptr)) return false;
    return isFullTree(pRoot->p_left) && isFullTree(pRoot->p_right);
}
bool isFullBST(NODE* pRoot) {
    return isBST(pRoot) && isFullTree(pRoot);
}
void print(NODE* pRoot){
    vector<int> Inorder = LNR(pRoot);
    for (int i = 0; i < Inorder.size(); i++) {
		cout << Inorder[i] << " ";
	}
	cout << endl;
}

int main() {
    int n;
    cout << "Nhap so luong phan tu: ";
    cin >> n;
    int* a = new int[n];
    cout << "Nhap mang (" << n << " so): ";
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // 4. Khoi tao cay tu mang
    NODE* root = createTree(a, n);

    // In truoc khi thao tac
    cout << "\nCay BST sau khi khoi tao (in-order): ";
    print(root);

    // 1. Tim kiem
    int x;
    cout << "\nNhap gia tri can tim: ";
    cin >> x;
    NODE* found = Search(root, x);
    if (found)
        cout << "Tim thay node co key = " << found->key << endl;
    else
        cout << "Khong tim thay node co key = " << x << endl;

    // 2. Chen node
    cout << "\nNhap gia tri can chen: ";
    cin >> x;
    Insert(root, x);
    cout << "Cay sau khi chen " << x << " (in-order): ";
    print(root);

    // 3. Xoa node
    cout << "\nNhap gia tri can xoa: ";
    cin >> x;
    Remove(root, x);
    cout << "Cay sau khi xoa " << x << " (in-order): ";
    print(root);

    // 6. Tinh chieu cao cay
    cout << "\nChieu cao cua cay: " << Height(root) << endl;

    // 7. Dem so node < y
    int y;
    cout << "\nNhap nguyen so y de dem node < y: ";
    cin >> y;
    cout << "So node co key < " << y << " la: " << countLess(root, y) << endl;

    // 8. Dem so node > z
    int z;
    cout << "\nNhap nguyen so z de dem node > z: ";
    cin >> z;
    cout << "So node co key > " << z << " la: " << countGreater(root, z) << endl;

    // 9. Kiem tra BST hop le
    cout << "\nCay hien tai " << (isBST(root) ? "la BST." : "khong phai BST!") << endl;

    // 10. Kiem tra full BST
    cout << "Cay hien tai " << (isFullBST(root) ? "la Full BST." : "khong phai Full BST!") << endl;

    // 5. Xoa toan bo cay
    removeTree(root);
    cout << "\nDa xoa toan bo cay. root = " << root << endl;

    delete[] a;
    return 0;
}
