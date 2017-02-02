#include <stdio.h>
int heap_free(void);
int main(int argc,char** argv){
    puts("Munk v0.0.1, (c) Michael Nolan\nbytes free: ");
    print_hex(heap_free());
    return 1;
}
