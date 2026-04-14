#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct
{
    char nome[50];
    float *notas;
    float mediaAlunos;
    int num_notas;
} Aluno;

int alocAluno(FILE *fp)
{
    char buffer[256];
    int tmp = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        if (buffer[strlen(buffer) - 1] == '\n' || feof(fp))
            tmp++;
    }
    return tmp;
}

void exemplo_leitura_linha(FILE *fp, FILE *arquivo, int tmp, Aluno ***alunos)
{
    char linha[256], linha2[256];
    rewind(fp);
    *alunos = (Aluno **)malloc(tmp * sizeof(Aluno *));
    for (int i = 0; i < tmp; i++)
        (*alunos)[i] = (Aluno *)malloc(sizeof(Aluno));
    int i = 0;
    // Tenta ler uma linha do arquivo. Se for bem-sucedido...
    while (fgets(linha, sizeof(linha), fp) != NULL)
    {
        strcpy(linha2, linha);
        char *token;
        // Primeiro, tokeniza a linha usando a vírgula como delimitador
        token = strtok(linha, ",");
        if (token != NULL)
            strcpy((*alunos)[i]->nome, token); // Copia o 1 token, no caso o nome para o campo nome da struct do aluno

        int notas = 0;
        float res = 0.0;
        char *temp = strtok(NULL, ","); // Pega a primeira nota, 2 token
        while (temp != NULL)            // Caso houver uma nota, != NULL
        {
            notas++;                  // computa a nota
            temp = strtok(NULL, ","); // Pega o proximo token, nota
        }
        (*alunos)[i]->notas = (float *)malloc(notas * sizeof(float));
        (*alunos)[i]->num_notas = notas;
        // Pega o proximo token
        strtok(linha2, ",");
        for (int j = 0; j < notas; j++)
        {
            token = strtok(NULL, ",");
            (*alunos)[i]->notas[j] = atof(token);
            res += (*alunos)[i]->notas[j];
        }
        fprintf(arquivo, "Nome do aluno: %s , ", (*alunos)[i]->nome);
        for (int k = 0; k < notas; k++)
            fprintf(arquivo, "nota %d : %.2f ", k + 1, (*alunos)[i]->notas[k]);
        fprintf(arquivo, " e media do aluno: %.2f \n", res / (*alunos)[i]->num_notas);
        (*alunos)[i]->mediaAlunos = res / (*alunos)[i]->num_notas;
        i++;
    }
}
void Ordenacao(FILE *arquivo, Aluno ***alunos, int quantAlunos)
{
    int indice[quantAlunos];
    float vetAux[quantAlunos], aux;
    for (int i = 0; i < quantAlunos; i++)
        vetAux[i] = (*alunos)[i]->mediaAlunos;
    for (int i = 1; i < quantAlunos; i++)
    {
        for (int j = 0; j < quantAlunos - i; j++)
        {
            if ((*alunos)[j]->mediaAlunos < (*alunos)[j + 1]->mediaAlunos)
            {
                aux = (*alunos)[j]->mediaAlunos;
                (*alunos)[j]->mediaAlunos = (*alunos)[j + 1]->mediaAlunos;
                (*alunos)[j + 1]->mediaAlunos = aux;
            }
        }
    }
    for (int i = 0; i < quantAlunos; i++)
    {
        for (int j = 0; j < quantAlunos; j++)
        {
            if ((*alunos)[i]->mediaAlunos == vetAux[j])
                indice[i] = j;
        }
    }
    fprintf(arquivo, "\n\n");
    fprintf(arquivo, "Medias ordenadas: \n\n");
    for (int i = 0; i < quantAlunos; i++)
    {
        fprintf(arquivo, "Nome do aluno: %s , ", (*alunos)[indice[i]]->nome);
        for (int k = 0; k < (*alunos)[i]->num_notas; k++)
            fprintf(arquivo, "nota %d : %.2f ", k + 1, (*alunos)[indice[i]]->notas[k]);
        fprintf(arquivo, " e media do aluno: %.2f \n", (*alunos)[i]->mediaAlunos);
    }
    for (int i = 0; i < quantAlunos; i++)
        (*alunos)[i]->mediaAlunos = vetAux[i];
}
void QuickSort(Aluno ***alunos, int esq, int dir)
{
    if (esq < dir)
    {
        int q = Divisao(&alunos, esq, dir);
        QuickSort(&alunos, esq, q - 1);
        QuickSprt(&alunos, q + 1, dir);
    }
    clock_t inicio = clock();

    algoritmo(dados_para_ordenar, 0, n - 1);

    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
}
int Divisao(Aluno ***alunos, int esq, int dir)
{
    int pivo = (*alunos)[dir];
    int i = esq - 1;

    for (int j = 0; j < dir; j++)
    {
        if ((*alunos)[j] < pivo)
        {
            i++;
            Troca(&(*alunos)[i], &alunos[j]);
        }
    }
    Troca(&(*alunos)[i + 1], &(*alunos)[dir]);
    return i + 1;
}
void Troca(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}