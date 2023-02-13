#include <stdio.h>

unsigned int fnv1a(char *string) {
    static unsigned int prime = 16777619;
    unsigned int hash = 2166136261;

    while (*string) {
        hash ^= *string;
        hash *= prime;
        string++;
    }

    return hash;
}

int main() {
    unsigned int a = fnv1a("Hello there");
    unsigned int b = fnv1a("Hey");
    unsigned int c = fnv1a("Jake");

    printf("%u\n", a);
    printf("%u\n", b);
    printf("%u\n", c);
    return 0;
}
