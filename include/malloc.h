#define size_t int
void* malloc(size_t);
void free(void*);
void* calloc(size_t elems, size_t elemsize);
void* realloc(void* ptr, size_t newsize);
