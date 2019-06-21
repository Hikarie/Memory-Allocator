// allocator.cpp

#include "allocator.h"

#include <QDebug>

#include "List.h"
#include "Node.h"

using namespace std;

Allocator::Allocator() {
    memory = List();
}

Allocator::Allocator(int size) {
    MEMO_SIZE = size;
    memory = List(size);
}

int Allocator::getSize(){
    return MEMO_SIZE;
}

List Allocator::getMemory(){
    return memory;
}

bool Allocator::BestFit(key id, int size) {
    Node* curr = memory.getHead();
    Node* temp = NULL;
    int min = INT_MAX;
    while (curr != NULL) {
        if (curr->ID == H && curr->end - curr->begin >= size) {
            if (curr->end - curr->begin - size <= min) {
                min = curr->end - curr->begin - size;
                temp = curr;
            }
        }
        curr = curr->next;
    }
    if (temp != NULL) {
        allocate(id, size, temp);
        return true;
    }
    else return false;
}

bool Allocator::FirstFit(key id, int size) {
    Node *curr = memory.getHead();
    bool found = false;
    while (curr != NULL) {
        if (curr->ID == H && curr->end - curr->begin >= size) {
            allocate(id, size, curr);
            return true;
        }
        else curr = curr->next;
    }
    if (found == false) return false;
}

bool Allocator::NextFit(key id, int size) {
    Node *curr = memory.getHead();
    Node *temp = NULL;
    while (curr != NULL) {
        if (curr->ID == H && curr->end - curr->begin >= size) {
            if (temp == NULL) temp = curr;
            else {
                allocate(id, size, curr);
                return true;
            }
        }
        curr = curr->next;
    }
    if (temp == NULL)return false;
    else {
        allocate(id, size, temp);
        return true;
    }
}

bool Allocator::WorstFit(key id, int size) {
    Node* curr = memory.getHead();
    Node* temp = NULL;
    int max = INT_MIN;
    while (curr != NULL) {
        if (curr->ID == H && curr->end - curr->begin >= size) {
            if (curr->end - curr->begin - size >= max) {
                max = curr->end - curr->begin - size;
                temp = curr;
            }
        }
        curr = curr->next;
    }
    if (temp != NULL) {
        allocate(id, size, temp);
        return true;
    }
    else return false;
}

void Allocator::allocate(key id, int size, Node *curr) {
    Node *x = new Node(id, curr->begin, curr->begin + size);
    memory.insert(curr, x);
    curr->begin += size;
    if (curr->begin == curr->end)memory.erase(curr);
    qDebug() << x->begin << " to " << x->end << " has been allocated\n";
}
bool Allocator::release(key id) {
    Node *curr = memory.getHead();
    int begin, end;
    while (curr != NULL) {
        if (curr->ID == id) {
            begin = curr->begin;
            end = curr->end;
            if (curr->prev != NULL && curr->next != NULL) {
                if (curr->prev->ID == H && curr->next->ID == H) {
                    // 前后都是空闲区
                    Node* temp = curr->prev;
                    memory.merge(curr, curr->prev);
                    memory.merge(temp, temp->next);

                }
                else if (curr->prev->ID == H && curr->next->ID != H) {
                    // 前一个是空闲区
                    memory.merge(curr, curr->prev);
                }
                else if (curr->prev->ID != H && curr->next->ID == H) {
                    // 后一个是空闲区
                    memory.merge(curr, curr->next);
                }
                else {
                    // 前后都不空闲
                    curr->ID = H;
                }
            }
            else {	// 触碰到边界的情况
                if (curr->prev == NULL && curr->next == NULL|| curr->prev->ID != H && curr->next == NULL || curr->prev == NULL && curr->next->ID != H) {
                    curr->ID = H;
                }
                else {
                    if (curr->prev->ID == H)
                        memory.merge(curr, curr->prev);
                    else
                        memory.merge(curr, curr->next);
                }
            }
            qDebug() << begin << " to " << end << " has been released\n";
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void Allocator::shrink(){
    Node *curr = memory.getHead();
    bool change = false;
    while(curr != NULL){
        if(curr->ID==H&&curr->next!=NULL){
            curr->end = curr->begin + curr->next->end - curr->end;
            curr->ID = curr->next->ID;
            memory.erase(curr->next);
            change = true;
        }
        if(change == true){
            int temp = curr->begin;
            curr->begin = curr->prev->end;
            curr->end = curr->end-temp+curr->begin;
        }
        if(curr->next == NULL){
            Node *x = new Node(H,curr->end,MEMO_SIZE);
            memory.add(x);
        }
        curr = curr->next;
    }

}
