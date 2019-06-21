// list.h

#ifndef LIST_H
#define LIST_H

#include"Node.h"
#include <assert.h>

#define H -1	// 空闲区用H表示，非空闲区用0以上编号表示
#define INT_MAX 2147483647
class List
{
private:
    Node *head;
    Node *tail;
public:
    List();
    List(int size);
    ~List();
public:
    void add(Node *x);	// append
    void deleteTail();
    void deleteHead();
    void merge(Node *curr, Node* x);
    void erase(Node *x);
    void insert(Node* pos, Node* x);
    void clear();
    Node* getHead() { return head; }
};


#endif // LIST_H
