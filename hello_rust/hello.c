#include <stdio.h>

extern char *hello_rust(void);

int main() {
   printf("%s\n", hello_rust());
}
