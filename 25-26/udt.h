#ifndef UDT_H
#define UDT_H

#include <stdbool.h>
#include <stddef.h>

typedef int key_type;
typedef int value_type;

typedef struct {
    key_type key;
    value_type value;
} data_type;

typedef struct Node {
    data_type data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* back;
    size_t size;
} udt;

void udt_create(udt* d);
bool udt_is_empty(const udt* d);

void udt_push_front(udt* d, data_type x);
void udt_push_back(udt* d, data_type x);

void udt_pop_front(udt* d);
void udt_pop_back(udt* d);

void udt_print(const udt* d);
size_t udt_size(const udt* d);

void udt_insert(udt* d, const data_type x);
void udt_erase(udt* d, const key_type key);

void insertion_sort(udt* d);

#endif