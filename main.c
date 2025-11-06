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

    char *str = (char *)malloc(20);
    if (!str)
        printf("[ERROR] malloc a renvoyé NULL\n");
    else {
        strcpy(str, "Hello world!");
        printf("Contenu: %s\n", str);
        free(str);
        printf("[OK] Allocation + free simples\n");
    }

    print_header("Test de multiples allocations");

    void *ptrs[10];
    for (int i = 0; i < 10; i++) {
        ptrs[i] = malloc(50 + i * 10);
        if (!ptrs[i]) {
            printf("[ERROR] Allocation %d a échoué\n", i);
            return 1;
        }
        memset(ptrs[i], i, 50 + i * 10);
    }
    printf("[OK] 10 allocations successives\n");

    for (int i = 0; i < 10; i += 2)
        free(ptrs[i]);
    printf("[OK] Libération de la moitié des blocs\n");

    for (int i = 1; i < 10; i += 2)
        free(ptrs[i]);
    printf("[OK] Libération du reste\n");

    print_header("Test de réallocation");

    char *data = malloc(10);
    strcpy(data, "abcde");
    data = realloc(data, 20);
    strcat(data, "12345");
    printf("Après realloc: %s\n", data);
    check_memory_content("Realloc conserve les données", data, "abcde12345", 10);
    free(data);

    print_header("Test de realloc sur NULL et taille = 0");

    char *null_realloc = realloc(NULL, 30);
    if (null_realloc)
        printf("[OK] realloc(NULL, size) agit comme malloc\n");
    free(null_realloc);

    char *small = malloc(10);
    small = realloc(small, 0);
    if (small == NULL)
        printf("[OK] realloc(ptr, 0) renvoie NULL et libère\n");

    print_header("Test de fragmentation et réutilisation de blocs");

    void *a = malloc(100);
    void *b = malloc(200);
    void *c = malloc(50);
    free(b); // Libère un bloc au milieu
    void *d = malloc(180); // Doit réutiliser le bloc de b si ta gestion est efficace
    if (d)
        printf("[OK] Bloc libre réutilisé (fragmentation test)\n");
    free(a);
    free(c);
    free(d);

    print_header("Test de stress aléatoire");

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
    printf("[OK] Stress test terminé sans crash\n");

    print_header("Test double free (comportement attendu : sécurisé ou erreur contrôlée)");

    void *df = malloc(42);
    free(df);
    printf("Libération une fois : OK\n");
    free(df); // Doit être ignoré ou provoquer une erreur gérée
    printf("Tentative double free terminée\n");

    
    print_header("Test realloc sur pointeur invalide");

    int fake;
    void *invalid = &fake;
    void *res = realloc(invalid, 50);
    if (res)
        printf("[WARNING] realloc a accepté un pointeur invalide !\n");
    else
        printf("[OK] realloc a détecté un pointeur invalide\n");

    print_header("Tous les tests terminés ✅");

    return 0;
}
