#include <stdio.h>
#include "arquivo.h"

void salvarCategorias(struct Categoria categorias[], int totalCategorias)
{
    FILE *arquivo;
    int i;

    arquivo = fopen("categorias.txt", "w");

    if (arquivo == NULL)
    {
        printf("\nErro ao salvar categorias.\n");
        return;
    }

    for (i = 0; i < totalCategorias; i++)
    {
        fprintf(arquivo, "%d;%s\n",
                categorias[i].codigo,
                categorias[i].nome);
    }

    fclose(arquivo);
}

int carregarCategorias(struct Categoria categorias[])
{
    FILE *arquivo;
    int total = 0;

    arquivo = fopen("categorias.txt", "r");

    if (arquivo == NULL)
        return 0;

    while (total < MAX_CATEGORIAS &&
           fscanf(arquivo, "%d;%29[^\n]\n",
                  &categorias[total].codigo,
                  categorias[total].nome) == 2)
    {
        total++;
    }

    fclose(arquivo);
    return total;
}

void salvarProdutos(struct Produto produtos[], int totalProdutos)
{
    FILE *arquivo;
    int i;

    arquivo = fopen("produtos.txt", "w");

    if (arquivo == NULL)
    {
        printf("\nErro ao salvar produtos.\n");
        return;
    }

    for (i = 0; i < totalProdutos; i++)
    {
        fprintf(arquivo, "%d;%s;%c;%.2f;%d;%d;%d\n",
                produtos[i].codigo,
                produtos[i].nome,
                produtos[i].prateleira,
                produtos[i].preco,
                produtos[i].quantidade,
                produtos[i].disponivel,
                produtos[i].codigoCategoria);
    }

    fclose(arquivo);
}

int carregarProdutos(struct Produto produtos[])
{
    FILE *arquivo;
    int total = 0;

    arquivo = fopen("produtos.txt", "r");

    if (arquivo == NULL)
        return 0;

    while (total < MAX_PRODUTOS &&
           fscanf(arquivo, "%d;%49[^;];%c;%f;%d;%d;%d\n",
                  &produtos[total].codigo,
                  produtos[total].nome,
                  &produtos[total].prateleira,
                  &produtos[total].preco,
                  &produtos[total].quantidade,
                  &produtos[total].disponivel,
                  &produtos[total].codigoCategoria) == 7)
    {
        total++;
    }

    fclose(arquivo);
    return total;
}
