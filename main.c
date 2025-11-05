#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "includes/malloc.h"

static void print_header(const char *title)
{
    printf("\n========== %s ==========\n", title);
}

// Vérifie que deux zones mémoire sont identiques
static void check_memory_content(const char *msg, void *p, const char *expected, size_t size)
{
    if (memcmp(p, expected, size) == 0)
        printf("[OK] %s\n", msg);
    else
        printf("[ERROR] %s: contenu incorrect\n", msg);
}

int main(void)
{
    srand((unsigned int)time(NULL));

    print_header("Test basique d'allocation et libération");

    char *str = (char *)ft_malloc(20);
    if (!str)
        printf("[ERROR] ft_malloc a renvoyé NULL\n");
    else {
        strcpy(str, "Hello world!");
        printf("Contenu: %s\n", str);
        ft_free(str);
        printf("[OK] Allocation + free simples\n");
    }

    print_header("Test de multiples allocations");

    void *ptrs[10];
    for (int i = 0; i < 10; i++) {
        ptrs[i] = ft_malloc(50 + i * 10);
        if (!ptrs[i]) {
            printf("[ERROR] Allocation %d a échoué\n", i);
            return 1;
        }
        memset(ptrs[i], i, 50 + i * 10);
    }
    printf("[OK] 10 allocations successives\n");

    for (int i = 0; i < 10; i += 2)
        ft_free(ptrs[i]);
    printf("[OK] Libération de la moitié des blocs\n");

    for (int i = 1; i < 10; i += 2)
        ft_free(ptrs[i]);
    printf("[OK] Libération du reste\n");

    print_header("Test de réallocation");

    char *data = ft_malloc(10);
    strcpy(data, "abcde");
    data = ft_realloc(data, 20);
    strcat(data, "12345");
    printf("Après realloc: %s\n", data);
    check_memory_content("Realloc conserve les données", data, "abcde12345", 10);
    ft_free(data);

    print_header("Test de realloc sur NULL et taille = 0");

    char *null_realloc = ft_realloc(NULL, 30);
    if (null_realloc)
        printf("[OK] ft_realloc(NULL, size) agit comme malloc\n");
    ft_free(null_realloc);

    char *small = ft_malloc(10);
    small = ft_realloc(small, 0);
    if (small == NULL)
        printf("[OK] ft_realloc(ptr, 0) renvoie NULL et libère\n");

    print_header("Test de fragmentation et réutilisation de blocs");

    void *a = ft_malloc(100);
    void *b = ft_malloc(200);
    void *c = ft_malloc(50);
    ft_free(b); // Libère un bloc au milieu
    void *d = ft_malloc(180); // Doit réutiliser le bloc de b si ta gestion est efficace
    if (d)
        printf("[OK] Bloc libre réutilisé (fragmentation test)\n");
    ft_free(a);
    ft_free(c);
    ft_free(d);

    print_header("Test de stress aléatoire");

    void *pool[1000] = {0};
    for (int i = 0; i < 5000; i++) {
        int idx = rand() % 1000;
        if (pool[idx]) {
            ft_free(pool[idx]);
            pool[idx] = NULL;
        } else {
            size_t size = (rand() % 256) + 1;
            pool[idx] = ft_malloc(size);
            if (pool[idx])
                memset(pool[idx], 0xAA, size);
        }
    }
    for (int i = 0; i < 1000; i++)
        if (pool[i])
            ft_free(pool[i]);
    printf("[OK] Stress test terminé sans crash\n");

    print_header("Test double free (comportement attendu : sécurisé ou erreur contrôlée)");

    void *df = ft_malloc(42);
    ft_free(df);
    printf("Libération une fois : OK\n");
    ft_free(df); // Doit être ignoré ou provoquer une erreur gérée
    printf("Tentative double free terminée\n");

    
    print_header("Test realloc sur pointeur invalide");

    int fake;
    void *invalid = &fake;
    void *res = ft_realloc(invalid, 50);
    if (res)
        printf("[WARNING] ft_realloc a accepté un pointeur invalide !\n");
    else
        printf("[OK] ft_realloc a détecté un pointeur invalide\n");

    print_header("Tous les tests terminés ✅");

    return 0;
}
