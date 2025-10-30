#include "../includes/main.h"


void ft_free(void   *pointer)
{
    block *_block = (block *)pointer - 1;
    _block->free = true;
    //if(block)

    return ;
}