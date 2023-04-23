#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 1000

typedef enum Token
{
    NumeroInteiro,
    NumeroReal,
    Soma,
    Indeterminado,
} Token;

struct TokenInfo
{
    enum Token token;
    union
    {
        char op;
        double num;
    } value;
};

struct TokenNode
{
    struct TokenInfo info;
    struct TokenNode *next;
};

void tokenizar(char *caracteres, struct TokenNode **listaTokens)
{
    char *token = strtok(caracteres, " ");
    while (token != NULL)
    {
        struct TokenInfo info;
        if (strcmp(token, "+") == 0)
        {
            info.token = Soma;
            info.value.op = '+';
        }
        else if (isdigit(token[0]))
        {
            int i = 0;
            while (isdigit(token[i]))
                i++;

            if (token[i] == '.')
            {
                double decimal = atof(token + i);
                info.token = NumeroReal;
                info.value.num = atoi(token) + decimal;
            }
            else
            {
                info.token = NumeroInteiro;
                info.value.num = atoi(token);
            }
        }
        else
        {
            info.token = Indeterminado;
            info.value.op = token[0];
        }

        struct TokenNode *node = (struct TokenNode *)malloc(sizeof(struct TokenNode));
        node->info = info;
        node->next = NULL;

        if (*listaTokens == NULL)
            *listaTokens = node;
        else
        {
            struct TokenNode *lastNode = *listaTokens;
            while (lastNode->next != NULL)
                lastNode = lastNode->next;
            lastNode->next = node;
        }

        token = strtok(NULL, " ");
    }
}

int main(int argc, char **argv)
{
    char content[MAX_SIZE];
    FILE *fp;

    fp = fopen(argv[1], "r");

    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fgets(content, MAX_SIZE, fp);
    fclose(fp);

    struct TokenNode *listaTokens = NULL;
    tokenizar(content, &listaTokens);

    double resultado = 0.0;
    int sinal = 1;
    struct TokenNode *node = listaTokens;
    while (node != NULL)
    {
        if (node->info.token == Soma)
            sinal = 1;
        else if (node->info.token == NumeroInteiro || node->info.token == NumeroReal)
            resultado += sinal * node->info.value.num;
        node = node->next;
    }

    printf("O resultado é: %f\n", resultado);

    // Libera a memória alocada para a lista de tokens
    while (listaTokens != NULL)
    {
        struct TokenNode *nextNode = listaTokens->next;
        free(listaTokens);
        listaTokens = nextNode;
    }

    return 0;
}
