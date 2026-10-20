#include <stdio.h>
#include <string.h>
#include "categoria.h"
#include "util.h"

int buscarCategoriaPorCodigo(struct Categoria categorias[], int total, int codigo)
{
    int i;

    for (i = 0; i < total; i++)
    {
        if (categorias[i].codigo == codigo)
            return i;
    }

    return -1;
}

void listarCategorias(struct Categoria categorias[], int total)
{
    int i;

    printf("\n===== LISTA DE CATEGORIAS =====\n");

    if (total == 0)
    {
        printf("Nenhuma categoria cadastrada.\n");
        return;
    }

    for (i = 0; i < total; i++)
    {
        printf("\nCodigo: %d\n", categorias[i].codigo);
        printf("Nome: %s\n", categorias[i].nome);
    }
}

int cadastrarCategoria(struct Categoria categorias[], int total)
{
    struct Categoria nova;

    if (total >= MAX_CATEGORIAS)
    {
        printf("\nLimite de 20 categorias atingido.\n");
        return total;
    }

    do
    {
        printf("\nDigite o codigo da categoria: ");
        scanf("%d", &nova.codigo);

        if (!numeroPositivo(nova.codigo))
            printf("Erro: o codigo deve ser positivo.\n");
        else if (buscarCategoriaPorCodigo(categorias, total, nova.codigo) != -1)
            printf("Erro: esse codigo ja esta cadastrado.\n");

    } while (!numeroPositivo(nova.codigo) ||
             buscarCategoriaPorCodigo(categorias, total, nova.codigo) != -1);

    do
    {
        printf("Digite o nome da categoria: ");
        scanf(" %29[^\n]", nova.nome);

        if (!textoPreenchido(nova.nome))
            printf("Erro: o nome nao pode ficar vazio.\n");

    } while (!textoPreenchido(nova.nome));

    categorias[total] = nova;
    total++;

    printf("\nCategoria cadastrada com sucesso!\n");
    printf("Codigo: %d\n", nova.codigo);
    printf("Nome: %s\n", nova.nome);

    return total;
}
