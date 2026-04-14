#include <stdio.h>
#include <stdlib.h>
#include "../include/include.h"

int main(int argc, char const *argv[])
{
    int tmp, esq,dir;
    Aluno **alunos;
    FILE *fp = fopen(argv[1], "r+");
    FILE *arquivo = fopen("../../relatorio.txt", "w");
    FILE *arqCsv = fopen("../../dados.csv", "a+");
    if (fp == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    tmp=alocAluno(fp);
    exemplo_leitura_linha(fp,arquivo,tmp,&alunos);
    Ordenacao(arquivo,&alunos,tmp);
    QuickSort(&alunos,)
    
    for (int i = 0; i < tmp; i++)
    {
        free(alunos[i]->notas);
        free(alunos[i]);
    }
    free(alunos);
    fclose(fp);
    fclose(arquivo);
    fclose(arqCsv);
    return 0;
}
