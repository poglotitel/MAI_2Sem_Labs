#include <stdio.h>
#include "udt.h"

int main(void)
{
    udt d;
    udt_create(&d);

    data_type a[] =
    {
        {10, 100},
        {30, 300},
        {50, 500},
        {70, 700}
    };

    for (int i = 0; i < 4; i++)
        udt_push_back(&d, a[i]);

    printf("Original dec:\n");
    udt_print(&d);

    data_type x = { 40, 400 };

    udt_insert(&d, x);

    printf("After insertion:\n");
    udt_print(&d);

    return 0;
}