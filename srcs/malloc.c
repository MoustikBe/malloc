#include "../includes/malloc.h"


/*
Malloc:
    in case of error -> return NULL
    try to allocate [size] in a pointer that the function create 
    and return the ptr create with [size] of memory created

    use mmap() -> mmap is a function that create the memory
    mmap(NULL, sizeof(char) * 100, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
*/

size_t get_units_number(size_t size)
{    
    size_t units = 0;
    size_t blockSize = 4096;

    if(!size)
        return(0);
    if(size){
        units = (((blockSize + size - 1) / blockSize));
    }
    printf("nb of block -> %zu\n", units);
    return(units);
}

void create_memory(block *head, size_t size)
{
    /* WORK IN PROGRESS */
    size_t units = get_units_number(size);
    if(units){
        // Initialiser/Creer tout les block de memoires
        // Decouper les blocs en trop 
        for(size_t i = 0; i < units; i++){
            block *new;
            new->data = mmap(NULL, sysconf(_SC_PAGESIZE) * 10, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
            new->bytes = 4096;
            new->free = false; 
            //new->next = 
        }
    }
    return ;
    /* WORK IN PROGRESS */
}


void *ft_malloc(size_t size)
{
    if(!size)
        return(NULL);
    block *head = mmap(NULL, sysconf(_SC_PAGESIZE) * 10, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    head->next = head;
    head->free = true;
    create_memory(head, size);
    return (NULL);
}