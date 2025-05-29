#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;

struct NODE {
    int key;
    NODE* p_next;
};

struct Queue {
    NODE* head;
    NODE* tail;
};

Queue* initializeQueue() {
    Queue* NewQueue = new Queue;
    NewQueue->head = nullptr;
    NewQueue->tail = nullptr;
    return NewQueue;
}

void enqueue(Queue& q, int key) {
    NODE* NodeQueue = new NODE;
    NodeQueue->key = key;
    NodeQueue->p_next = nullptr;
    if (q.head == nullptr) {
        q.head = NodeQueue;
        q.tail = NodeQueue;
    } else {
        q.tail->p_next = NodeQueue;
        q.tail = NodeQueue;
    }
}

int dequeue(Queue& q) {
    if (q.head == nullptr) {
        return -1;
    }
    if (q.head == q.tail) {
        NODE* temp = q.head;
        int key = q.head->key;
        q.head = q.tail = nullptr;
        delete temp;
        return key;
    }
    else {
        NODE* temp = q.head;
        int key = q.head->key;
        q.head = q.head->p_next;
        delete temp;
        return key;
    }
}

int size(Queue q) {
    NODE* cur = q.head;
    int count = 0;
    while (cur != nullptr) {
        count++;
        cur = cur->p_next;
    }
    return count;
}

bool isEmpty(Queue q) {
    return (q.head == nullptr);
}

void printQueue(Queue q, ofstream& outFile) {
    if (isEmpty(q)) {
        outFile << "EMPTY\n";
        return;
    }
    NODE* cur = q.head;
    while (cur != nullptr) {
        outFile << cur->key;
        if (cur->p_next != nullptr) {
            outFile << " ";
        }
        cur = cur->p_next;
    }
    outFile << "\n";
}

int main() {
    const char* filename = "input.txt";
    const char* op = "output.txt";
    ifstream infile(filename);
    ofstream outFile(op);

    if (!infile.is_open() || !outFile.is_open()) {
        cerr << "Loi mo file!" << endl;
        return 1;
    }

    Queue* q = initializeQueue();
    char ip[100];
    while (infile.getline(ip, 100)) {
        char* token = strtok(ip, " ");
        while (token != nullptr) {
            if (strcmp(token, "init") == 0) {
                q = initializeQueue();
                outFile << "EMPTY\n";
            }
            else if (strcmp(token, "enqueue") == 0) {
                token = strtok(nullptr, " ");
                int data = atoi(token);
                enqueue(*q, data);
                printQueue(*q, outFile);
            }
            else if (strcmp(token, "dequeue") == 0) {
                if (isEmpty(*q)) {
                    outFile << "EMPTY\n";
                }
                else {
                    dequeue(*q);
                    printQueue(*q, outFile);
                }
            }
            token = strtok(nullptr, " ");
        }
    }

    cout << "Doc va ghi file thanh cong" << endl;
    infile.close();
    outFile.close();
    cout << "Chuong trinh chay thanh cong" << endl;
    return 0;
}
