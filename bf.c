#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <err.h>

int main(int argc, char**argv) {

    //opening and reading from a file
    
    FILE*file;

    if(argv[1]==NULL)
        errx(1,"need a file");

    if((file=fopen(argv[1], "r")) ==NULL)
        errx(1,"error");

    fseek(file, 0L, SEEK_END);
    size_t fsize=ftell(file);
    rewind(file);

    char*buf = malloc(fsize);

    fread(buf, 1, fsize, file);

    //----------------------------------

    //initialization
    int i=0, lc=0;
    unsigned int j=0;
    char arr[30000];
    memset(arr, 0, sizeof(arr));

    //commands
    for(int i=0;i<(strlen(buf)-1); ++i) {
        switch(buf[i]){
            case '>': j++; break;
            case '<': j--; break;
            case '+': arr[j]++; break;
            case '-': arr[j]--; break;
            case '.': putchar(arr[j]); break;
            case ',': arr[j]=getchar(); break;
        }
        if(buf[i]=='[') {
            if(!arr[j]) {
                ++lc;
                while(lc) {
                    i++;
                    if(buf[i]=='[') ++lc;
                    if(buf[i]==']') --lc;
                }
            }
            else continue;
        }
        else if(buf[i]==']') {
            if(!arr[j]) continue;
            else {
                if(buf[i]==']') lc++;
                while(lc) {
                    --i;
                    if(buf[i]=='[') lc--;
                    if(buf[i]==']') lc++;
                }
                --i;
            }
        }
    }
    printf("\n");
}
