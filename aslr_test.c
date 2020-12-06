#include <stdio.h>
#include <string.h>

char *str = "HELLO ASLR";

int main() {
    printf("ptr %p\n", str);

    return 0;
}
