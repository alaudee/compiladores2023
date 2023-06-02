#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TAM_MEMORIA 256
#define ARGUMENTO_ARQUIVO_OBRIGATORIO "Argumento do arquivo é obrigatório!"

typedef enum {
    NOP = 0x00,
    STA = 0x10,
    LDA = 0x20,
    ADD = 0x30,
    OR = 0x40,
    AND = 0x50,
    NOT = 0x60,
    JMP = 0x80,
    JN = 0x90,
    JZ = 0xA0,
    HLT = 0xF0
} Instrucao;

void carregar_arquivo(const char *arquivo, uint8_t *acumulador, uint8_t *contador_programa, uint8_t *memoria)
{
    FILE *ponteiro_arquivo = fopen(arquivo, "rb");
    if (ponteiro_arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    fread(memoria, sizeof(uint8_t), TAM_MEMORIA, ponteiro_arquivo);
    fclose(ponteiro_arquivo);

    *acumulador = memoria[1];
    *contador_programa = memoria[2];
}

void executeNOP()
{
    // Não faz nada
}

void executeSTA(uint8_t *memoria, uint8_t endereco, uint8_t acumulador)
{
    memoria[endereco] = acumulador;
}

void executeLDA(uint8_t *memoria, uint8_t endereco, uint8_t *acumulador)
{
    *acumulador = memoria[endereco];
}

void executeADD(uint8_t *memoria, uint8_t endereco, uint8_t *acumulador)
{
    *acumulador += memoria[endereco];
}

void executeOR(uint8_t *memoria, uint8_t endereco, uint8_t *acumulador)
{
    *acumulador |= memoria[endereco];
}

void executeAND(uint8_t *memoria, uint8_t endereco, uint8_t *acumulador)
{
    *acumulador &= memoria[endereco];
}

void executeNOT(uint8_t *acumulador)
{
    *acumulador = ~(*acumulador);
}

void executeJMP(uint8_t endereco, uint8_t *contador_programa)
{
    *contador_programa = endereco - 1;
}

void executeJN(uint8_t *memoria, uint8_t endereco, uint8_t *contador_programa, int *flag_n)
{
    if (*flag_n)
    {
        *contador_programa = endereco - 1;
    }
}

void executeJZ(uint8_t *memoria, uint8_t endereco, uint8_t *contador_programa, int *flag_z)
{
    if (*flag_z)
    {
        *contador_programa = endereco - 1;
    }
}

void executeHLT(uint8_t acumulador, uint8_t contador_programa, int flag_n, int flag_z)
{
    printf("Acumulador: %d\n", acumulador);
    printf("Contador de Programa: %d\n", contador_programa);
    printf("Flags: N = %d, Z = %d\n", flag_n, flag_z);
    exit(0);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf(ARGUMENTO_ARQUIVO_OBRIGATORIO);
        return 1;
    }

    uint8_t acumulador = 0;
    uint8_t contador_programa = 0;
    uint8_t memoria[TAM_MEMORIA] = {0};
    int flag_n = 0;
    int flag_z = 0;

    carregar_arquivo(argv[1], &acumulador, &contador_programa, memoria);

    while (contador_programa < TAM_MEMORIA)
    {
        uint8_t instrucao = memoria[contador_programa];

        switch (instrucao)
        {
            case NOP:
                executeNOP();
                break;
            case STA:
                executeSTA(memoria, memoria[++contador_programa], acumulador);
                break;
            case LDA:
                executeLDA(memoria, memoria[++contador_programa], &acumulador);
                break;
            case ADD:
                executeADD(memoria, memoria[++contador_programa], &acumulador);
                break;
            case OR:
                executeOR(memoria, memoria[++contador_programa], &acumulador);
                break;
            case AND:
                executeAND(memoria, memoria[++contador_programa], &acumulador);
                break;
            case NOT:
                executeNOT(&acumulador);
                break;
            case JMP:
                executeJMP(memoria[++contador_programa], &contador_programa);
                break;
            case JN:
                executeJN(memoria, memoria[++contador_programa], &contador_programa, &flag_n);
                break;
            case JZ:
                executeJZ(memoria, memoria[++contador_programa], &contador_programa, &flag_z);
                break;
            case HLT:
                executeHLT(acumulador, contador_programa, flag_n, flag_z);
                break;
            default:
                break;
        }

        // Atualiza as flags
        flag_z = (acumulador == 0) ? 1 : 0;
        flag_n = (acumulador & 0x80) ? 1 : 0;

        contador_programa++;
    }

    return 0;
}
