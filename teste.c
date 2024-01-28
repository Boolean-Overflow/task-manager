#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Hello,,5,World! This is a sample string.";
    const char delim[] = " ,.!"; // Delimitadores: espaço, vírgula e ponto de exclamação

    // Primeira chamada
    char *token = strtok(str, delim);

    // Subsequentes chamadas
    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, delim);
    }

    return 0;
}
