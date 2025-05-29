#include <iostream>
#include <vector>
#include <queue>
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
vector<int> NLR(NODE* pRoot) {
	vector<int> result;
	if (pRoot == nullptr) {
		return result;
	}
	result.push_back(pRoot->key);
	vector<int> left = NLR(pRoot->p_left);   
	vector<int> right = NLR(pRoot->p_right);
	result.insert(result.end(), left.begin(), left.end());
	result.insert(result.end(), right.begin(), right.end());
	return result;
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
vector<int> LRN(NODE* pRoot) {
	vector<int> result;
	if (pRoot == nullptr) {
		return result;
	}
	vector<int> left = LRN(pRoot->p_left);
	vector<int> right = LRN(pRoot->p_right);
	result.insert(result.end(), left.begin(), left.end());
	result.insert(result.end(), right.begin(), right.end());
	result.push_back(pRoot->key);
	return result;
}

vector<vector<int>> LevelOrder(NODE* pRoot) {
	vector<vector<int>> result;
	if (!pRoot) {
		return result;
	}
	queue<NODE*> q;
	q.push(pRoot);
	while (!q.empty()) {
		int levelSize = q.size();            
		vector<int> level;                  
		for (int i = 0; i < levelSize; ++i) {
			NODE* current = q.front(); 
			q.pop();
			level.push_back(current->key);  
			if (current->p_left) {
				q.push(current->p_left);
			}
			if (current->p_right) {
				q.push(current->p_right);
			}
		}
		result.push_back(level);           
	}
	return result;
}
int countNode(NODE* pRoot) {
	vector<int> Preorder = NLR(pRoot);
	return Preorder.size();
}
int sumNode(NODE* pRoot) {
	vector<int> Preorder = NLR(pRoot);
	int sum = 0;
	for (int i = 0; i < Preorder.size(); i++) {
		sum += Preorder[i];
	}
	return sum;
}
int heightNode(NODE* pRoot, int value) {
	if (!pRoot) {
		return -1;
	}
	queue<NODE*> q;
	q.push(pRoot);
	int height = 0;
	while (!q.empty()) {
		int levelSize = q.size();
		for (int i = 0; i < levelSize; ++i) {
			NODE* current = q.front();
			q.pop();
			if (current->key == value) {
				return height;
			}
			if (current->p_left) {
				q.push(current->p_left);
			}
			if (current->p_right) {
				q.push(current->p_right);
			}
		}
		height++;
	}
	return -1;
}
int Level(NODE* pRoot, NODE* p) {
	if (!pRoot || !p) {
		return -1;
	}
	queue<pair<NODE*, int>> q;
	q.push({ pRoot, 0 });
	while (!q.empty()) {
		NODE* current = q.front().first;
		int level = q.front().second;
		q.pop();
		if (current == p) {
			return level;
		}
		if (current->p_left) {
			q.push({ current->p_left, level + 1 });
		}
		if (current->p_right) {
			q.push({ current->p_right, level + 1 });
		}
	}
	return -1;
}
int countLeaf(NODE* pRoot) {
	if (!pRoot) {
		return 0;
	}
	if (!pRoot->p_left && !pRoot->p_right) {
		return 1;
	}
	return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}
void printTree(NODE* pRoot) {
	vector<int> Preorder = NLR(pRoot);
	cout << "Preorder: ";
	for (int i = 0; i < Preorder.size(); i++) {
		cout << Preorder[i] << " ";
	}
	cout << endl;
	vector<int> Inorder = LNR(pRoot);
	cout << "Inorder: ";
	for (int i = 0; i < Inorder.size(); i++) {
		cout << Inorder[i] << " ";
	}
	cout << endl;
	vector<int> Postorder = LRN(pRoot);
	cout << "Postorder: ";
	for (int i = 0; i < Postorder.size(); i++) {
		cout << Postorder[i] << " ";
	}
	cout << endl;
	vector<vector<int>> Levelorder = LevelOrder(pRoot);
	cout << "Levelorder: ";
	for (int i = 0; i < Levelorder.size(); i++) {
		for (int j = 0; j < Levelorder[i].size(); j++) {
			cout << Levelorder[i][j] << " ";
		}
	}
	cout << endl;
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
