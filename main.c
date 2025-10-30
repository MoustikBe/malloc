#include "includes/main.h"

int main(void)
{
    int *nb = ft_malloc(sizeof(int) * 5);
    for(int i = 0; i < 5; i++){
        nb[i] = i;
        printf("nb -> %d\n", nb[i]);
    }
}

/*
    printf("Test ft_malloc\n");

    // --- Test tiny allocation ---
    char *tiny1 = (char *)ft_malloc(16);
    char *tiny2 = (char *)ft_malloc(32);

    if (tiny1 && tiny2)
    {
        strcpy(tiny1, "Hello Tiny1!");
        strcpy(tiny2, "Hello Tiny2!");
        printf("tiny1: %s\n", tiny1);
        printf("tiny2: %s\n", tiny2);
    }
    else
        printf("Tiny allocation failed!\n");

    // --- Test small allocation ---
    char *small1 = (char *)ft_malloc(128);
    char *small2 = (char *)ft_malloc(256);

    if (small1 && small2)
    {
        strcpy(small1, "Hello Small1!");
        strcpy(small2, "Hello Small2!");
        printf("small1: %s\n", small1);
        printf("small2: %s\n", small2);
    }
    else
        printf("Small allocation failed!\n");

    // --- Test large allocation ---
    char *large1 = (char *)ft_malloc(1024);
    if (large1)
    {
        strcpy(large1, "Hello Large!");
        printf("large1: %s\n", large1);
    }
    else
        printf("Large allocation failed!\n");

    // --- Test multiple allocations to fill tiny zone ---
    for (int i = 0; i < 10; i++)
    {
        char *p = (char *)ft_malloc(16);
        if (p)
        {
            sprintf(p, "Tiny %d", i);
            printf("%s\n", p);
        }
        else
            printf("Allocation %d failed!\n", i);
    }

    return 0;
*/