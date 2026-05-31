// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    first = nullptr;
    countOp = 0;
}
void Train::addCar(bool light) {
    Car* node = new Car;
    node->light = light;
    if (!first) {
        first = node;
        first->next = first;
        first->prev = first;
        return;
    }
    Car* tail = first->prev;
    tail->next = node;
    node->prev = tail;
    node->next = first;
    first->prev = node;
}
int Train::getLength() {
    if (!first) return 0;
    countOp = 0;
    Car* start = first;
    start->light = true;
    int result = 0;
    Car* current = start;
    while (true) {
        current = current->next;
        result++;
        countOp++;

        if (current->light) {
            current->light = false;
            int backSteps = result;
            Car* back = current;
            for (int i = 0; i < backSteps; i++) {
                back = back->prev;
                countOp++;
            }
            if (!back->light) {
                return result;
            }
            current = back;
            result = 0;
        }
    }
}
int Train::getOpCount() {
    return countOp;
}
Train::~Train() {
    if (!first) return;
    Car* cur = first->next;
    while (cur != first) {
        Car* next = cur->next;
        delete cur;
        cur = next;
    }

    delete first;
    first = nullptr;
}
