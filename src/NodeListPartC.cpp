//Hayden Trent
//EECE2140
//Lab 11

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <limits>

using namespace std;

struct ListNode {
    int id;
    string name;
    ListNode* next;
};

class NodeList {
private:
    ListNode* head;
    int count;

    void clear() {
        ListNode* curr = head;
        while (curr) {
            ListNode* next = curr->next;
            delete curr;
            curr = next;
        }
        head = nullptr;
        count = 0;
    }

public:
    NodeList() : head(nullptr), count(0) {}

    void addNode(int id, string name) {
        ListNode* n = new ListNode{id, name, head};
        head = n;
        count++;
    }

    void removeNode(int id) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr && curr->id != id) {
            prev = curr;
            curr = curr->next;
        }
        if (!curr) return;
        if (prev) prev->next = curr->next;
        else head = curr->next;
        delete curr;
        cout << curr->id << endl;
        count--;
    }

    void display() const {
        ListNode* curr = head;
        while (curr) {
            cout << "[" << curr->id << ": "
                << curr->name << "] -> ";
            curr = curr->next;
        }
        cout << "null" << endl;
    }


    NodeList(const NodeList& other) : head(nullptr), count(0) {
        ListNode* curr = other.head;
        ListNode* prev = nullptr;
        while (curr) {
            ListNode* n = new ListNode{curr->id, curr->name, nullptr};
            if (prev) prev->next = n;
            else head = n;
            prev = n;
            curr = curr->next;
            count++;
        }
    }

    NodeList& operator=(const NodeList& other) {
        if (this == &other) return *this;
        clear();
        ListNode* curr = other.head;
        ListNode* prev = nullptr;
        while (curr) {
            ListNode* n = new ListNode{curr->id, curr->name, nullptr};
            if (prev) prev->next = n;
            else head = n;
            prev = n;
            curr = curr->next;
            count++;
        }
        return *this;
    }

    ~NodeList() {
        clear();
    }
};

int main() {
    NodeList list;

    list.addNode(1, "John");
    list.addNode(2, "David");
    list.addNode(3, "Washington");

    cout << "Original list: ";
    list.display();

    list.removeNode(2);
    cout << "After removing node 2: ";
    list.display();

    NodeList copyList(list);
    cout << "Copied list: ";
    copyList.display();

    NodeList assignedList;
    assignedList = list;
    cout << "Assigned list: ";
    assignedList.display();

    return 0;
}
