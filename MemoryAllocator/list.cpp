// list.cpp

#include "list.h"

List::List() :head(NULL), tail(NULL) {}

List::List(int size) : head(NULL), tail(NULL)
{
    Node *x = new Node(H, 0, size);
    add(x);
}

List::~List()
{
}

void List::add(Node * x)
{
    if (head == NULL) {
        head = x;
        tail = head;
    }
    else {
        Node* temp = head;
        head = x;
        head->next = temp;
        temp->prev = head;
    }
}

void List::deleteHead()
{
    if (head == NULL);
    else {
        Node * temp = head;
        head = head->next;
        head->prev = NULL;
    }
}

void List::merge(Node * curr, Node * x)
{
    x->begin = curr->begin < x->begin ? curr->begin : x->begin;
    x->end = curr->end > x->end ? curr->end : x->end;
    erase(curr);
}

void List::deleteTail()
{
    if (head == NULL);
    else if (head == tail) {
        delete head;
        head = NULL;
        tail = NULL;
    }
    else {
        Node *curr = head;
        while (curr->next != tail) {
            curr = curr->next;
        }
        delete tail;
        tail = curr;
        tail->prev = curr->prev;
        tail->next = NULL;
    }
}

void List::erase(Node * x)
{
    assert(x);
    if (x == tail) {
        deleteTail();
    }
    else if (x == head) {
        deleteHead();
    }
    else {
        x->prev->next = x->next;
        x->next->prev = x->prev;
        delete x;
    }
}

void List::insert(Node * pos, Node * x)
{
    assert(x);
    if (pos == head)add(x);
    else {
        x->prev = pos->prev;
        pos->prev = x;
        x->prev->next = x;
        x->next = pos;
    }
}

void List::clear()
{
    Node* temp = head;
    while (temp != tail) {
        head = head->next;
        delete temp;
        temp = head;
    }
    head = NULL;
    tail = NULL;
}

