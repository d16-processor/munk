#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
struct block {
    size_t size;
    struct block * next;
    int free;
    int magic;
};
#define BLOCK_SIZE sizeof(struct block)
void* global_base;
struct block* find_free_block_asm(struct block **last, size_t size);
struct block *request_space_asm(struct block* last, size_t size);

/*
 *UNUSED STUB FUNCTIONS. 
 *implemented in lib/malloc_asm.d16
 *
 *static struct block* find_free_block(struct block **last, size_t size){
 *    struct block* current = global_base;
 *    while(current && !(current->free == 0 && current->size >= size)){
 *        *last = current;
 *        current = current->next;
 *    }
 *    return current;
 *}
 *static struct block *request_space(struct block* last, size_t size){
 *    struct block* block = sbrk(0);
 *    void* request = sbrk(size + BLOCK_SIZE);
 *
 *    if((int) request == -1){
 *        return NULL;
 *    }
 *    if(last){
 *        last->next = block;
 *    }
 *    block->size = size;
 *    block->next = NULL;
 *    block->free = 0;
 *    block->magic = 0xbeef;
 *    return block;
 *
 *}
 */
void* malloc(size_t size){
    /*puts("program_break: ");*/
    /*print_hex((int)sbrk(0));*/
    struct block* block;
    if(size<0){
        return NULL;
        
    }
    if(!global_base){
        /*puts("First time\n");*/
        block = request_space_asm(NULL,size);
        global_base = block;
        if(!block){
            return NULL;
        }
    }
    else{
        struct block* last = global_base;
        block = find_free_block_asm(&last,size);
        /*puts("found block: ");*/
        /*print_hex((int) block);*/
        if(!block){
            /*puts("requesting space\n");*/
            block = request_space_asm(last,size);
            if(!block){
                return NULL;
            }
        }
        else{
            /*print_hex(block->magic);*/
            block->free = 0;
            block->magic = 0x7777;
        }

    }
    /*print_hex(block->magic);*/
    return block+1;
}
void free(void* ptr){
    if(ptr){
        struct block *block_ptr = (struct block*)ptr - 1;
        block_ptr->free = 1;
        block_ptr->magic = 0x5555;
    }
}
//ERROR: memcpy currently broken
#ifdef REALLOC
void* realloc(void* ptr, size_t size){
    if (!ptr){
        return malloc(size);
    }
    struct block* block_ptr = (struct block*)ptr - 1;
    if(block_ptr->size >= size){
        return ptr;
    }
    void* new_ptr = malloc(size);
    if(!new_ptr){
        return NULL;
    }
    /*memcpy(new_ptr, ptr, block_ptr->size);*/
    free(ptr);
    return new_ptr;
}
#endif
