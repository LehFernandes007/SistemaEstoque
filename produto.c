
#include <stdio.h>
#include <string.h>
#include "produto.h"
#include "util.h"
#include "categoria.h"

int cadastrarProduto(struct Produto produtos[], int totalProdutos,
                     struct Categoria categorias[], int totalCategorias)
{
    struct Produto novoProduto;
    int codigoExiste;

    if (totalCategorias == 0)
    {
        printf("\nCadastre uma categoria antes de cadastrar produtos.\n");
        return totalProdutos;
    }

    if (totalProdutos >= MAX_PRODUTOS)
    {
        printf("\nErro: a lista de produtos esta cheia.\n");
        return totalProdutos;
    }

    do
    {
        printf("\nDigite o codigo do produto: ");
        scanf("%d", &novoProduto.codigo);

        if (!numeroPositivo(novoProduto.codigo))
        {
            printf("Erro: o codigo deve ser positivo.\n");
            codigoExiste = 0;
        }
        else
        {
            codigoExiste = buscarPorCodigo(produtos, totalProdutos,
                                          novoProduto.codigo) != -1;

            if (codigoExiste)
                printf("Erro: esse codigo ja esta cadastrado.\n");
        }

    } while (!numeroPositivo(novoProduto.codigo) || codigoExiste);

    do
    {
        printf("Digite o nome do produto: ");
        scanf(" %49[^\n]", novoProduto.nome);

        if (!textoPreenchido(novoProduto.nome))
            printf("Erro: o nome nao pode ficar em branco.\n");

    } while (!textoPreenchido(novoProduto.nome));

    do
    {
        printf("Digite a prateleira (A, B, C ou D): ");
        scanf(" %c", &novoProduto.prateleira);

        if (!prateleiraValida(novoProduto.prateleira))
            printf("Erro: prateleira invalida.\n");

    } while (!prateleiraValida(novoProduto.prateleira));

    do
    {
        printf("Digite o preco unitario: ");
        scanf("%f", &novoProduto.preco);

        if (!precoValido(novoProduto.preco))
            printf("Erro: o preco deve ser maior que zero.\n");

    } while (!precoValido(novoProduto.preco));

    do
    {
        printf("Digite a quantidade em estoque: ");
        scanf("%d", &novoProduto.quantidade);

        if (!quantidadeValida(novoProduto.quantidade))
            printf("Erro: a quantidade nao pode ser negativa.\n");

    } while (!quantidadeValida(novoProduto.quantidade));

    printf("\n===== ESCOLHA A CATEGORIA =====\n");
    listarCategorias(categorias, totalCategorias);

    do
    {
        printf("\nDigite o codigo da categoria: ");
        scanf("%d", &novoProduto.codigoCategoria);

        if (buscarCategoriaPorCodigo(categorias, totalCategorias,
                                    novoProduto.codigoCategoria) == -1)
        {
            printf("Erro: categoria nao encontrada.\n");
        }

    } while (buscarCategoriaPorCodigo(categorias, totalCategorias,
                                      novoProduto.codigoCategoria) == -1);

    novoProduto.disponivel = novoProduto.quantidade > 0 ? 1 : 0;

    produtos[totalProdutos] = novoProduto;
    totalProdutos++;

    printf("\n===== PRODUTO CADASTRADO =====\n");
    exibirProduto(novoProduto, categorias, totalCategorias);

    return totalProdutos;
}

void listarProdutos(struct Produto produtos[], int totalProdutos,
                    struct Categoria categorias[], int totalCategorias)
{
    int i;

    if (totalProdutos == 0)
    {
        printf("\nNenhum produto foi cadastrado.\n");
        return;
    }

    printf("\n===== LISTA DE PRODUTOS =====\n");

    for (i = 0; i < totalProdutos; i++)
    {
        printf("\n--- Produto %d ---\n", i + 1);
        exibirProduto(produtos[i], categorias, totalCategorias);
    }
}

void exibirProduto(struct Produto produto,
                   struct Categoria categorias[], int totalCategorias)
{
    int posicaoCategoria;

    printf("Codigo: %d\n", produto.codigo);
    printf("Nome: %s\n", produto.nome);
    printf("Prateleira: %c\n", produto.prateleira);
    printf("Preco unitario: %.2f\n", produto.preco);
    printf("Quantidade: %d\n", produto.quantidade);
    printf("Disponivel para venda: %d\n", produto.disponivel);

    posicaoCategoria = buscarCategoriaPorCodigo(
        categorias, totalCategorias, produto.codigoCategoria);

    if (posicaoCategoria != -1)
        printf("Categoria: %s\n", categorias[posicaoCategoria].nome);
    else
        printf("Categoria: nao encontrada\n");
}

int buscarPorCodigo(struct Produto produtos[], int totalProdutos, int codigo)
{
    int i;

    for (i = 0; i < totalProdutos; i++)
    {
        if (produtos[i].codigo == codigo)
            return i;
    }

    return -1;
}

int buscarPorNome(struct Produto produtos[], int totalProdutos, char nome[])
{
    int i;

    for (i = 0; i < totalProdutos; i++)
    {
        if (strcmp(produtos[i].nome, nome) == 0)
            return i;
    }

    return -1;
}

void pesquisarProduto(struct Produto produtos[], int totalProdutos,
                      struct Categoria categorias[], int totalCategorias)
{
    int tipoPesquisa, codigo, posicao;
    char nomePesquisa[50];

    printf("\n===== PESQUISAR PRODUTO =====\n");
    printf("1 - Por codigo\n");
    printf("2 - Por nome\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &tipoPesquisa);

    if (tipoPesquisa == 1)
    {
        printf("\nDigite o codigo do produto: ");
        scanf("%d", &codigo);

        posicao = buscarPorCodigo(produtos, totalProdutos, codigo);
    }
    else if (tipoPesquisa == 2)
    {
        printf("\nDigite o nome do produto: ");
        scanf(" %49[^\n]", nomePesquisa);

        posicao = buscarPorNome(produtos, totalProdutos, nomePesquisa);
    }
    else
    {
        printf("\nOpcao de pesquisa invalida!\n");
        return;
    }

    if (posicao != -1)
        exibirProduto(produtos[posicao], categorias, totalCategorias);
    else
        printf("\nNenhum produto foi encontrado.\n");
}

