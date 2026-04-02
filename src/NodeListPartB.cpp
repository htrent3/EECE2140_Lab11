//Hayden Trent
//EECE2140
//Lab 11

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <limits>
#include <memory>

using namespace std;

struct SmartListNode {
    int id;
    string name;
    unique_ptr<SmartListNode> next;

    SmartListNode(int i, string n, unique_ptr<SmartListNode> nx)
        : id(i), name(n), next(move(nx)) {}
};

class SmartNodeList {
private:
    unique_ptr<SmartListNode> head;
    int count;

public:
    SmartNodeList() : head(nullptr), count(0) {}

    void addNode(int id, string name) {
        head = make_unique<SmartListNode>(id, name, move(head));
        count++;
    }

    void display() const {
        SmartListNode* curr = head.get();
        while (curr) {
            cout << "[" << curr->id << ": "
                << curr->name << "] -> ";
            curr = curr->next.get();
        }
        cout << "null" << endl;
    }

    void removeNode(int id) {
        SmartListNode* prev = nullptr;
        SmartListNode* curr = head.get();
        while (curr && curr->id != id) {
            prev = curr;
            curr = curr->next.get();
        }
        if (!curr) return;
        if (prev) prev->next = move(curr->next);
        else head = move(curr->next);
        count--;
    }

};