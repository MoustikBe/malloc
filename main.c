#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
/* lib */
#include "libft/libft.h"
/* lib */
#include "includes/malloc.h"

/* LD_PRELOAD=./libft_malloc.so [program] */

static void print_header(const char *title)
{
    ft_printf("\n========== %s ==========\n", title);
}

static void check_memory_content(const char *msg, void *p, const char *expected, size_t size)
{
    if (memcmp(p, expected, size) == 0)
        ft_printf("[OK] %s\n", msg);
    else
        ft_printf("[ERROR] %s: Bad content\n", msg);
}

int main(void)
{
    /* Allocation test */
    srand((unsigned int)time(NULL));

    print_header("Basic test allocation and free");

    char *str = (char *)malloc(20);
    if (!str)
        ft_printf("[ERROR] malloc has return NULL\n");
    else {
        strcpy(str, "Hello world!");
        ft_printf("Content: %s\n", str);
        free(str);
        ft_printf("[OK] Allocation + free basic\n");
    }

    print_header("Multiple test");

    void *ptrs[10];
    for (int i = 0; i < 10; i++) {
        ptrs[i] = malloc(50 + i * 10);
        if (!ptrs[i]) {
            ft_printf("[ERROR] Allocation %d failed\n", i);
            return 1;
        }
        memset(ptrs[i], i, 50 + i * 10);
    }
    ft_printf("[OK] 10 allocations successive\n");

    for (int i = 0; i < 10; i += 2)
        free(ptrs[i]);
    ft_printf("[OK] Half of the block free\n");

    for (int i = 1; i < 10; i += 2)
        free(ptrs[i]);
    ft_printf("[OK] The other half free\n");

    print_header("Test of realloc");

    char *data = malloc(10);
    strcpy(data, "abcde");
    data = realloc(data, 20);
    strcat(data, "12345");
    ft_printf("After realloc: %s\n", data);
    check_memory_content("Realloc keep data", data, "abcde12345", 10);
    free(data);

    print_header("Test of realloc on NULL and size = 0");

    char *null_realloc = realloc(NULL, 30);
    if (null_realloc)
        ft_printf("[OK] realloc(NULL, size) is working as malloc\n");
    free(null_realloc);

    char *small = malloc(10);
    small = realloc(small, 0);
    if (small == NULL)
        ft_printf("[OK] realloc(ptr, 0) return NULL and free the block\n");

    print_header("Test of fragmentation and re used of blocks");

    void *a = malloc(100);
    void *b = malloc(200);
    void *c = malloc(50);
    free(b);
    void *d = malloc(180);
    if (d)
        ft_printf("[OK] Bloc free re used (fragmentation test)\n");
    free(a);
    free(c);
    free(d);

    print_header("Random stress test");

    void *pool[1000] = {0};
    for (int i = 0; i < 5000; i++) {
        int idx = rand() % 1000;
        if (pool[idx]) {
            free(pool[idx]);
            pool[idx] = NULL;
        } else {
            size_t size = (rand() % 256) + 1;
            pool[idx] = malloc(size);
            if (pool[idx])
                memset(pool[idx], 0xAA, size);
        }
    }
    for (int i = 0; i < 1000; i++)
        if (pool[i])
            free(pool[i]);
    ft_printf("[OK] Stress test finished without crash\n");

    print_header("Test double free (expected behavior : securised or managed error)");

    void *df = malloc(42);
    free(df);
    ft_printf("Free once : OK\n");
    free(df);
    ft_printf("Attempt of double free\n");
    
    print_header("Realloc test on invalid pointer");

    int fake;
    void *invalid = &fake;
    void *res = realloc(invalid, 50);
    if (res)
        ft_printf("[WARNING] realloc has accepted a invalid pointer !\n");
    else
        ft_printf("[OK] realloc has detected an invalid pointer\n");

    print_header("All test finished gg wp! ✅");

    return 0;
}
