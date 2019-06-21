// allocator.h

#ifndef ALLOCATOR_H
#define ALLOCATOR_H


#include <iostream>

#include "List.h"
#include "Node.h"

using namespace std;

class Allocator {

private:

    List memory;
    int MEMO_SIZE;

public:

    Allocator();

    Allocator(int size);

public:

    int getSize();

    List getMemory();

    bool BestFit(key id, int size);

    bool FirstFit(key id, int size);

    bool NextFit(key id, int size);

    bool WorstFit(key id, int size);

    void allocate(key id, int size, Node *curr);

    bool release(key id);

    void shrink();
};

#endif // ALLOCATOR_H
