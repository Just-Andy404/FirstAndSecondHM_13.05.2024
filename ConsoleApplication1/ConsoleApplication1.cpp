/*
������� n1
�������� � ����� ����������� ������ �������� ��������� ����������. �� ��� ����� ����������� ���������� � ������
������. ��������, �������� ������, ������� ��������
�� ������� ������ � �.�.
*/
/*
������� n2
�������� �������� ���������������� �������-����������. � ��� ������ ���� ������ ��� ��������� ��������. 
� �������� ���������� ������� ����������� ���� ������������ 
� �������� �������. ��������, ������ �������������� 
������ ��� ��������� ��������� �������������� ������, 
�������� ������, �������� ��� ������ � ������� � �.�.*/

#include <iostream>
#include <fstream>
using namespace std;

// ������� ����� ��� ���������������� ����������
class ListException : public exception {
private:
    const char* message;

public:
    explicit ListException(const char* msg) : message(msg) {}

    const char* what() const noexcept override {
        return message;
    }
};

// ����� ��� ��������� ������ ������
class MemoryException : public ListException {
public:
    explicit MemoryException(const char* msg) : ListException(msg) {}
};

// ����� ��� ��������� �������������� ������
class MathException : public ListException {
public:
    explicit MathException(const char* msg) : ListException(msg) {}
};

// ����� ��� ��������� ������ ��� ������ � �������
class FileException : public ListException {
public:
    explicit FileException(const char* msg) : ListException(msg) {}
};

// ����� ���� ������
class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

// ����� ����������� ������
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addToFront(int value) {
        Node* newNode = new (nothrow) Node(value);
        if (!newNode) {
            throw MemoryException("Memory allocation failed");
        }

        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void addToBack(int value) {
        Node* newNode = new (nothrow) Node(value);
        if (!newNode) {
            throw MemoryException("Memory allocation failed");
        }

        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void removeFromFront() {
        if (head == nullptr) {
            throw ListException("Attempt to remove from an empty list");
        }

        Node* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete temp;
    }

    void removeFromBack() {
        if (tail == nullptr) {
            throw ListException("Attempt to remove from an empty list");
        }

        Node* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
        delete temp;
    }

    void printList() const {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // ����� ��� ������ ������ �� ����� � ���������� � ������
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            throw FileException("Failed to open file");
        }

        int value;
        while (file >> value) {
            addToBack(value);
        }

        if (file.bad()) {
            throw FileException("Error reading from file");
        }

        file.close();
    }
};

int main() {
    try {
        DoublyLinkedList list;
        list.addToFront(10);
        list.addToBack(20);
        list.printList();

        list.removeFromFront();
        list.printList();

        list.removeFromBack();
        list.printList();

        // ������� �������� �� ������� ������
        list.removeFromFront();
    }
    catch (const ListException& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    try {
        DoublyLinkedList fileList;
        fileList.loadFromFile("data.txt");
        fileList.printList();
    }
    catch (const FileException& e) {
        cerr << "FileException: " << e.what() << endl;
    }
    catch (const ListException& e) {
        cerr << "ListException: " << e.what() << endl;
    }

    return 0;
}
