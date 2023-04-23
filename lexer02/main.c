#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 1000

typedef enum {
    Mais,
    Menos,
    Multiplicacao,
    Divisao,
    Potenciacao,
    Numero,
    Indeterminado,
} Token;

typedef union {
    char op;
    int num;
} Value;

typedef struct {
    Token token;
    Value value;
} TokenValue;

void tokenizar(const char *caracteres, int length, TokenValue *vetorTokens, int *numTokens) {
    int i = 0, j = 0;
    while (i < length) {
        switch (caracteres[i]) {
            case '+':
                vetorTokens[j++] = (TokenValue){.token = Mais, .value = {.op = '+'}};
                i++;
                break;
            case '-':
                vetorTokens[j++] = (TokenValue){.token = Menos, .value = {.op = '-'}};
                i++;
                break;
            case '*':
                if (caracteres[i + 1] == '*') {
                    vetorTokens[j++] = (TokenValue){.token = Potenciacao, .value = {.op = '*'}};
                    i += 2;
                } else {
                    vetorTokens[j++] = (TokenValue){.token = Multiplicacao, .value = {.op = '*'}};
                    i++;
                }
                break;
            case '/':
                vetorTokens[j++] = (TokenValue){.token = Divisao, .value = {.op = '/'}};
                i++;
                break;
            case ' ':
                i++;
                break;
            default:
                if (isdigit(caracteres[i])) {
                    int num = 0;
                    while (i < length && isdigit(caracteres[i])) {
                        num = num * 10 + (caracteres[i] - '0');
                        i++;
                    }
                    vetorTokens[j++] = (TokenValue){.token = Numero, .value = {.num = num}};
                } else {
                    vetorTokens[j++] = (TokenValue){.token = Indeterminado, .value = {.op = caracteres[i]}};
                    i++;
                }
        }
    }
    *numTokens = j;
}

int main(int argc, char **argv) {
    char content[MAX_SIZE];
    FILE *fp;
    int length = 0;

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fgets(content, MAX_SIZE, fp) != NULL) {
        length = strlen(content);
    }
    fclose(fp);

    TokenValue vetorTokens[length];
    int numTokens;
    tokenizar(content, length, vetorTokens, &numTokens);

    for (int k = 0; k < numTokens; k++) {
        TokenValue tk = vetorTokens[k];
        switch (tk.token) {
            case Mais:
                printf("Mais: +\n");
                break;
            case Menos:
                printf("Menos: -\n");
                break;
            case Multiplicacao:
                printf("Multiplicação: *\n");
                break;
            case Divisao:
                printf("Divisão: /\n");
                break;
            case Potenciacao:
                printf("Potenciação: **\n");
                break;
            case Numero:
                printf("Número: %d\n", tk.value.num);
                break;
            case Indeterminado:
                printf("Número indeterminado");
                break;
        }
    }
}