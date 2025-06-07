// compile: gcc -fno-stack-protector -z execstack -no-pie overflow1.c -o overflow1
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char buf[256];
    strcpy(buf,argv[1]);
    return 0;
}
