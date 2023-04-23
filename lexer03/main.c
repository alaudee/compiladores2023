#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAX_SIZE 1000

typedef enum {
    Mais,
    Menos,
    Multiplicacao,
    Divisao,
    Potenciacao,
    Numero,
    Real,
    Indeterminado
} Token;

typedef union {
    char op;
    double num;
} TokenValue;

typedef struct {
    Token token;
    TokenValue value;
} TokenInfo;

void tokenizar(char *caracteres, int length, TokenInfo *vetorTokens, int *numTokens) {
    int i = 0;
    int j = 0;
    while (i < length) {
        if (caracteres[i] == '+' || caracteres[i] == '-' ||
            caracteres[i] == '*' || caracteres[i] == '/' ||
            (caracteres[i] == '*' && caracteres[i + 1] == '*')) {
            vetorTokens[j].token = caracteres[i] == '+' ? Mais : 
                                   caracteres[i] == '-' ? Menos :
                                   caracteres[i] == '*' && caracteres[i + 1] == '*' ? Potenciacao :
                                   caracteres[i] == '*' ? Multiplicacao :
                                   Divisao;
            vetorTokens[j].value.op = caracteres[i];
            i += (caracteres[i] == '*' && caracteres[i + 1] == '*') ? 2 : 1;
            j++;
        } else if (isdigit(caracteres[i]) || (caracteres[i] == '.' && isdigit(caracteres[i + 1]))) {
            double num = 0.0;
            double decimal = 0.0;
            double divisor = 10.0;
            int is_real = 0;
            while (isdigit(caracteres[i]) || (!is_real && caracteres[i] == '.' && isdigit(caracteres[i + 1]))) {
                if (caracteres[i] == '.') {
                    is_real = 1;
                    i++;
                    continue;
                }
                if (is_real) {
                    decimal += (caracteres[i] - '0') / divisor;
                    divisor *= 10.0;
                } else {
                    num = num * 10 + (caracteres[i] - '0');
                }
                i++;
            }
            vetorTokens[j].token = is_real ? Real : Numero;
            vetorTokens[j].value.num = num + decimal;
            j++;
        } else if (isspace(caracteres[i])) {
            i++;
        } else {
            vetorTokens[j].token = Indeterminado;
            vetorTokens[j].value.op = caracteres[i];
            i++;
            j++;
        }
    }
    *numTokens = j;
}

int main(int argc, char **argv) {
    char content[MAX_SIZE];
    FILE *fp;

    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fgets(content, MAX_SIZE, fp) != NULL);

    fclose(fp);

    TokenInfo vetorTokens[MAX_SIZE];
    int numTokens;
    tokenizar(content, strlen(content), vetorTokens, &numTokens);

    for (int k = 0; k < numTokens; k++) {
        switch (vetorTokens[k].token) {
            case Mais:
                printf("Mais: +\n");
                break;
            case Menos:
                printf("Menos: -\n");
                break;
            case Multiplicacao:
                printf("Multiplicação: *\n");
                break;
            case Potenciacao:
                printf("Potenciacao: **\n");
                break;
            case Numero:
                printf("Numero\n");
                break;
            case Real:
                printf("Real\n");
                break;
            case Indeterminado:
                printf("Indeterminado\n");
                break;
            default:
                printf("Erro ao ler o arquivo");
                break;
        }
    }
}