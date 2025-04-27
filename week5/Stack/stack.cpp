#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;
struct NODE {
    int key;
    NODE* p_next;
};
struct Stack {
    NODE* top;
};
Stack* initializeStack(){
    Stack* newstack= new Stack;
    newstack->top=nullptr;
    return newstack;
}
void push (Stack &s, int key){
    NODE* newNode = new NODE;
    newNode->key = key;
    newNode->p_next = s.top;
    s.top = newNode;
}
int pop (Stack &s){
    if (s.top==nullptr){
        return -1;
    }
    NODE*temp=s.top;
    int value=temp->key;
    s.top=s.top->p_next;
    delete temp;
    return value;
}
int size (Stack s){
    int count=0;
    NODE* cur= s.top;
    while (cur!=nullptr){
        count++;
        cur=cur->p_next;
    }
    return count;
}
bool isEmpty(Stack s) {
    return (s.top == NULL);
}
int main() {
    const char* filename = "input.txt";
    const char* op = "output.txt";
    ifstream infile(filename);
    ofstream outFile(op);
    
    if (!infile.is_open() || !outFile.is_open()) {
        cerr << "Loi mo file!";
        return 1;
    }
    
    Stack* s = initializeStack();
    char ip[100]; 
    
    while (infile.getline(ip, 100)) { 
        char* token = strtok(ip, " ");
        while (token != nullptr) {
            if (strcmp(token, "init") == 0) {
                s = initializeStack();
                outFile << "EMPTY\n";
            }
            else if (strcmp(token, "push") == 0) {
                token = strtok(nullptr, " ");
                int data = atoi(token);
                push(*s, data);
                
                if (isEmpty(*s)) {
                    outFile << "EMPTY\n";
                } else {
                    int stacksize = size(*s);
                    int* arr = new int[stacksize];
                    NODE* current = s->top;
                    for (int i = stacksize - 1; i >= 0; i--) {
                        arr[i] = current->key;
                        current = current->p_next;
                    }
                    for (int i = 0; i < stacksize; i++) {
                        if (i > 0) outFile << " ";
                        outFile << arr[i];
                    }
                    outFile << "\n";
                    delete[] arr;
                }
            }
            else if (strcmp(token, "pop") == 0) {
                if (isEmpty(*s)) {
                    outFile << "EMPTY\n";
                } else {
                    pop(*s);
                    if (isEmpty(*s)) {
                        outFile << "EMPTY\n";
                    } else {
                        int stackSize = size(*s);
                        int* tempArr = new int[stackSize];
                        NODE* current = s->top;
                        for (int i = stackSize - 1; i >= 0; i--) {
                            tempArr[i] = current->key;
                            current = current->p_next;
                        }
                        for (int i = 0; i < stackSize; i++) {
                            if (i > 0) outFile << " ";
                            outFile << tempArr[i];
                        }
                        outFile << "\n";
                        delete[] tempArr;
                    }
                }
            }
            token = strtok(nullptr, " ");
        }
    }
    cout << "Doc va ghi file thanh cong"<<endl;
    infile.close();
    outFile.close();
    cout << "Chuong trinh chay thanh cong";
    return 0;
}