#include <stdlib.h>
#include <stdio.h>

int main() {
    while(1) {
        void *p = malloc(1024 * 1024);
        if (!p) break;
        printf("Allocating memory...\n");
    }
    return 0;
}
