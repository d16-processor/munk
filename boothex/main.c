#include <stdio.h>
#include <stdint.h>
void put_byte(uint8_t byte, FILE* dest){
    fputc(((byte>>4)&0xf)+'A',dest);
    fputc((byte&0xf)+'A',dest);
}
int main(int argc, char** argv){
    FILE* input = NULL;
    FILE* output = NULL;
    if(argc < 2) {fprintf(stderr,"No input specified\n");return 1;}
    if(argc == 2){
        input = fopen(argv[1],"rb");
        output = stdout;
    }
    if(argc == 3){
        input = fopen(argv[1],"rb");
        output = fopen(argv[2],"w");
    }
    if(input == NULL) {fprintf(stderr,"Error opening input file: %s\n",argv[1]); return 1;}
    if(output == NULL) {fprintf(stderr,"Error opening output file: %s\n",argv[2]); return 1;}
    char buf[128];
    size_t bytes = 0;
    while((bytes = fread(buf,1,sizeof(buf),input)) > 0){
        for(int i=0;i<bytes;i+=2){
            put_byte(buf[i],output);  
            put_byte(buf[i+1],output);  
        }
    }
    fputc('\0', output);
    fflush(stdout);
    return 0;
    
}
