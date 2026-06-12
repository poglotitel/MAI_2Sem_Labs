#include <stdio.h>
#include <stdlib.h>
#include "udt.h"

void udt_create(udt* d)
{
    d->front = NULL;
    d->back = NULL;
    d->size = 0;
}

bool udt_is_empty(const udt* d)
{
    return d->size == 0;
}

void udt_push_front(udt* d, data_type x)
{
    Node* p = (Node*)malloc(sizeof(Node));

    p->data = x;
    p->prev = NULL;
    p->next = d->front;

    if (d->front)
        d->front->prev = p;
    else
        d->back = p;

    d->front = p;
    d->size++;
}

void udt_push_back(udt* d, data_type x)
{
    Node* p = (Node*)malloc(sizeof(Node));

    p->data = x;
    p->next = NULL;
    p->prev = d->back;

    if (d->back)
        d->back->next = p;
    else
        d->front = p;

    d->back = p;
    d->size++;
}

void udt_pop_front(udt* d)
{
    if (udt_is_empty(d))
        return;

    Node* tmp = d->front;

    d->front = tmp->next;

    if (d->front)
        d->front->prev = NULL;
    else
        d->back = NULL;

    free(tmp);
    d->size--;
}

void udt_pop_back(udt* d)
{
    if (udt_is_empty(d))
        return;

    Node* tmp = d->back;

    d->back = tmp->prev;

    if (d->back)
        d->back->next = NULL;
    else
        d->front = NULL;

    free(tmp);
    d->size--;
}

void udt_print(const udt* d)
{
    Node* p = d->front;

    while (p)
    {
        printf("(%d,%d) ",
            p->data.key,
            p->data.value);

        p = p->next;
    }

    printf("\n");
}

size_t udt_size(const udt* d)
{
    return d->size;
}

void udt_insert(udt* d, const data_type x)
{
    Node* cur = d->front;

    while (cur && cur->data.key < x.key)
        cur = cur->next;

    if (cur == d->front)
    {
        udt_push_front(d, x);
        return;
    }

    if (cur == NULL)
    {
        udt_push_back(d, x);
        return;
    }

    Node* p = (Node*)malloc(sizeof(Node));

    p->data = x;

    p->next = cur;
    p->prev = cur->prev;

    cur->prev->next = p;
    cur->prev = p;

    d->size++;
}

void udt_erase(udt* d, const key_type key)
{
    Node* cur = d->front;

    while (cur && cur->data.key != key)
        cur = cur->next;

    if (!cur)
        return;

    if (cur == d->front)
    {
        udt_pop_front(d);
        return;
    }

    if (cur == d->back)
    {
        udt_pop_back(d);
        return;
    }

    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;

    free(cur);
    d->size--;
}

void insertion_sort(udt* d)
{
    if (d->size < 2)
        return;

    Node* i = d->front->next;

    while (i)
    {
        data_type tmp = i->data;

        Node* j = i->prev;

        while (j && j->data.key > tmp.key)
        {
            j->next->data = j->data;
            j = j->prev;
        }

        if (j)
            j->next->data = tmp;
        else
            d->front->data = tmp;

        i = i->next;
    }
}