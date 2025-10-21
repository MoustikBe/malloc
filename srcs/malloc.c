#include "../includes/malloc.h"

static block *g_head = NULL;

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

bool init_memory()
{
    void *zone = mmap(NULL, sysconf(_SC_PAGESIZE) * 10, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if(zone == MAP_FAILED) 
        return(false);
    // -- Le nombre de block qui va être utiliser -- (le calcul prend en compte la memoire total necessaire a un block, avec la partie block et la partie de donnees) //
    size_t number_block = sysconf(_SC_PAGESIZE) * 10 / (sizeof(block) + BLOCK_SIZE);
    // -- la zone actuel de memoire est egal a block mnt, donc la tête contient toutes la memoire -- //
    g_head = (block *) zone;
    block *current = g_head; 
    for(size_t i = 0; i < number_block ; i++)
    {
        // -- Ici on va definir la "limite d'octet" qui peuvent être utiliser -- //
        current->bytes = BLOCK_SIZE;
        current->free = true;
        // -- Ici on va definir la data, sur l'addresse actuel de current + la taille du block car cette memoire apartient a block pour son fonctionnement -- //
        current->data = (char *)current + sizeof(block);
        // -- Ici on regarde si c'est le dernier block de la liste -- //
        if(i < number_block - 1)
            // -- Si sa l'est pas on va definir l'addresse du block suivant, en claire on calcul ou s'arrete le "taille" du block, on fait l'addresse actuel + la taille d'un block + le nombre d'octet d'un block -- //
            current->next = (block *)((char *)current + sizeof(block) + BLOCK_SIZE);
        else 
            current->next = NULL; 
        current = current->next;
    }
    return(true);
}

void *ft_malloc(size_t size)
{
    if(!size)
        return(NULL);
    // -- Je penses qu'il va falloir creer une fonction check_if_enought_memory(), qui va verifier qu'il n'est pas necessaire de rajouter de la memoire a la liste -- //
    if(!g_head)
    {
        if(!init_memory())
            return(NULL);
    }

    // Apres on regarde le nombre de memoire que malloc demande. On calcule le nombre de block dont on va avoir besoin avec get_units_number
    // On creer une variable qui va stocker la memoire de actual_block->memoire_save
    // On boucle jusqu'a avoir le nombre de block exacte, quand on est sur le dernier block, on regarde combien de memoire on transfert a la variable
    // On bouge la memoire necessaire et laisse le reste 
    // On retourne la variable avec la memoire demander
    return (NULL);
}

/*
size_t block_size = 4096;
size_t num_blocks = sysconf(_SC_PAGESIZE) * 10 / block_size; // combien de blocs dans la zone

block *current = (block *)zone;
for (size_t i = 0; i < num_blocks; i++) {
    current->bytes = block_size;
    current->free = true;
    current->data = (char *)current + sizeof(block);
    current->next = (i < num_blocks - 1) ? (block *)((char *)current + sizeof(block) + block_size) : NULL;
    current = current->next;
}
*/