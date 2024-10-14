// gcc -o overflow1 -fno-stack-protector -m32 -z execstack overflow1.c
// -fno-stack-protector
// Remove the canary value at the end of the buffer: -fno-stack-protector
// Set the program to compile into a 32 bit program: -m32
// Make the stack executable: -z execstack

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    char buf[256]'
    strcpy(buf, argv[1]);
    printf("%s\n", buf);
    return 0;
}
