#include "../includes/malloc.h"

/*
Malloc:
    in case of error -> return NULL
    try to allocate [size] in a pointer that the function create 
    and return the ptr create with [size] of memory created

    use mmap() -> mmap is a function that create the memory
    mmap(NULL, sizeof(char) * 100, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
*/

//bool init_memory()
//{
//    void *zone = mmap(NULL, sysconf(_SC_PAGESIZE) * 10, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
//    if(zone == MAP_FAILED) 
//        return(false);
//    // -- Le nombre de block qui va être utiliser -- (le calcul prend en compte la memoire total necessaire a un block, avec la partie block et la partie de donnees) //
//    size_t number_block = sysconf(_SC_PAGESIZE) * 10 / (sizeof(block) + BLOCK_SIZE);
//    // -- la zone actuel de memoire est egal a block mnt, donc la tête contient toutes la memoire -- //
//    g_head = (block *) zone;
//    block *current = g_head; 
//    for(size_t i = 0; i < number_block ; i++)
//    {
//        // -- Ici on va definir la "limite d'octet" qui peuvent être utiliser -- //
//        current->bytes = BLOCK_SIZE;
//        current->free = true;
//        // -- Ici on va definir la data, sur l'addresse actuel de current + la taille du block car cette memoire apartient a block pour son fonctionnement -- //
//        current->data = (char *)current + sizeof(block);
//        // -- Ici on regarde si c'est le dernier block de la liste -- //
//        if(i < number_block - 1)
//            // -- Si sa l'est pas on va definir l'addresse du block suivant, en claire on calcul ou s'arrete le "taille" du block, on fait l'addresse actuel + la taille d'un block + le nombre d'octet d'un block -- //
//            current->next = (block *)((char *)current + sizeof(block) + BLOCK_SIZE);
//        else 
//            current->next = NULL; 
//        current = current->next;
//    }
//    return(true);
//}
//
//bool extend_memory()
//{
//    void *zone = mmap(NULL, sysconf(_SC_PAGESIZE) * 10, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
//    if(zone == MAP_FAILED) 
//        return(false);
//    size_t number_block = sysconf(_SC_PAGESIZE) * 10 / (sizeof(block) + BLOCK_SIZE);
//    
//    block *current = g_head;
//    while (current->next)
//        current = current->next;
//
//    block *new = (block *) zone;
//    current->next = new;
//    for(size_t i = 0; i < number_block ; i++)
//    {
//        new->bytes = BLOCK_SIZE;
//        new->free = true;
//        new->data = (char *)new + sizeof(block);
//        if(i < number_block - 1)
//            new->next = (block *)((char *)new + sizeof(block) + BLOCK_SIZE);
//        else 
//            new->next = NULL; 
//        new = new->next;
//    }
//    return(true);
//}
//
//
//void *request_memory(size_t size)
//{
//    // -- L'addresse memoire qui sera renvoyer pour malloc -- // 
//    void *addr_malloc;
//    size_t size_needed = size;
//    block *current = g_head;
//    
//    // -- Tant que c'est pas un bloc libre on cherche un bloc libre -- //
//    while(current && current->free == false)
//        current = current->next;
//    // -- Si on n'a plus de block on renvois NULL -- //
//    if(!current)
//    {
//        if(!extend_memory())
//            return(NULL);
//        current = g_head;
//        while(current && current->free == false)
//            current = current->next;
//        if(!current)
//            return(printf("Deux fois pas assez de memoire\n"), NULL);
//    }
//    // -- Si on a trouver un block libre on lui donne l'addresse ici -- //
//    addr_malloc = current->data;
//    
//    // -- Tant que la taille recherche existe et que y'a des block -- //
//    while (size_needed > 0 && current)
//    {
//        // -- Si la taille rechercher est plus petite ou egal a la taille du block actuel -- //
//        if(current->bytes >= size_needed)
//        {
//            // -- On retire les bytes qu'on a besoin -- //
//            current->bytes -= size_needed;
//            // -- Si y'a plus d'espace, on dit que il n'y a plus d'esapce -- //
//            if(current->bytes == 0) 
//                current->free = false;
//            size_needed = 0;
//        }
//        else
//        {
//            // -- Sinon on retire les bytes qu'il y'avait de disponible dans le block -- //
//            size_needed -= current->bytes;
//            // -- On le mets a jour en signalant que y'a bien plus de bytes et on le mets a FALSE pour le signaler vide -- //
//            current->bytes = 0;
//            current->free = false;
//            // -- On passe au block suivant -- //
//            current = current->next;
//        }
//    }
//        
//    // -- Verif au cas ou y'a toujours de la size_needed mais plus de block -- //
//    if(!current)
//    {
//        // -- Peut cause des segfault en cas de récursion non securiser avec de gros call mmap -- //
//        /*
//        if(!extend_memory())
//            return(NULL);
//        return(request_memory(size));
//        */
//    }
//    //printf("ALLOCATION OF MEMORY FINISH WITH SUCCESS\n");
//    return (addr_malloc);
//}

static block *tiny_head = NULL;
static block *small_head = NULL;

void    *request_mem(size_t size)
{
    if(size <= TINY_SIZE)
    {
        printf("Allocate memory for TINY SIZE");
    }
    else if(size > TINY_SIZE && size <= SMALL_SIZE)
    {
        printf("Allocate memory for SMALL SIZE");
    }
    else
    {
        void *zone = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if(zone == MAP_FAILED)
            return (NULL);
        return(zone);
    }
}

void *ft_malloc(size_t size)
{
    if(!size)
        return(NULL);
    void *ptr_malloc = request_mem(size);
    if(!ptr_malloc)
        return(NULL);
    return(ptr_malloc);
}
