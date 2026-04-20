#include <stdio.h>
#include <unistd.h>

int main() {
    while(1) {
        printf("I/O pulse...\n");
        sleep(1);
    }
    return 0;
}
