// node.h

#ifndef NODE_H
#define NODE_H

typedef int key;
struct Node {
    int begin;
    int end;
    key ID;
    Node *prev;
    Node *next;
    Node(key id,int b,int e)
        :begin(b),end(e),ID(id),prev(0),next(0){}
};

#endif // NODE_H
