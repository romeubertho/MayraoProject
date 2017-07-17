
// Mayra Lima 4587698

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Produto //estrutura para o produto
{
    int Codigo;
    char Nome[100];
    float Preco;
    int Estoque;
};
struct Venda //estrutura para a venda
{
    int Codigo;
    int Quantidade;
    int Dia;
    int Mes;
    int Ano;
};
struct Venda Vendas[1000];
struct Produto Produtos[1000];
int i = 0;
int j = 0;
const char *getfield(char *line, int num)
{
    const char *tok;
    for (tok = strtok(line, ";");
         tok && *tok;
         tok = strtok(NULL, ";\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}
int LoadFIle()
{

    FILE *fp;
    //----Carrega Produtos
    fp = fopen("Produtos.txt", "r");
    if (fp)
    {
        char buffer[100];
        while (fgets(buffer, 100, fp))
        {
            char *tmp1 = strdup(buffer);
            char *tmp2 = strdup(buffer);
            char *tmp3 = strdup(buffer);
            char *tmp4 = strdup(buffer);
            Produtos[i].Codigo = atoi(getfield(tmp1, 1));
            strcpy(Produtos[i].Nome, getfield(tmp2, 2));
            Produtos[i].Preco = atof(getfield(tmp3, 3));
            Produtos[i].Estoque = atoi(getfield(tmp4, 4));
            printf("%d %s %f %d\n", Produtos[i].Codigo, Produtos[i].Nome, Produtos[i].Preco, Produtos[i].Estoque);
            i++;
            free(tmp1);
            free(tmp2);
            free(tmp3);
            free(tmp4);
        }
        fclose(fp);
    }
    //----Carrega Vendas
    fp = fopen("Vendas.txt", "r");
    if (fp)
    {
        char buffer[100];
        while (fgets(buffer, 100, fp))
        {
            char *tmp1 = strdup(buffer);
            char *tmp2 = strdup(buffer);
            char *tmp3 = strdup(buffer);
            char *tmp4 = strdup(buffer);
            char *tmp5 = strdup(buffer);
            Vendas[j].Codigo = atoi(getfield(tmp1, 1));
            Vendas[j].Quantidade = atoi(getfield(tmp2, 2));
            Vendas[j].Dia = atoi(getfield(tmp3, 3));
            Vendas[j].Mes = atoi(getfield(tmp4, 4));
            Vendas[j].Ano = atoi(getfield(tmp5, 5));
            j++;
            free(tmp1);
            free(tmp2);
            free(tmp3);
            free(tmp4);
            free(tmp5);
        }
        fclose(fp);
    }
}
int WriteFile()
{
    FILE *fp;
    //----Armazena os produtos
    fp = fopen("Produtos.txt", "w");
    for (int k = 0; k < i; k++)
        if (Produtos[k].Codigo >= 0)
            fprintf(fp, "%d;%s;%f;%d\r\n", Produtos[k].Codigo, Produtos[k].Nome, Produtos[k].Preco, Produtos[k].Estoque);
    fclose(fp);
    //----Armazena as vendas
    fp = fopen("Vendas.txt", "w");
    for (int k = 0; k < j; k++)
        fprintf(fp, "%d;%d;%d;%d;%d\r\n", Vendas[k].Codigo, Vendas[k].Quantidade, Vendas[k].Dia, Vendas[k].Mes, Vendas[k].Ano);
    fclose(fp);
}
int CadastrarProduto()
{
    int codigo;
    char nome[100];
    float preco;
    printf("\nDigite o codigo do produto: ");
    scanf("%d", &Produtos[i].Codigo);
    printf("\nDigite o nome do produto: ");
    scanf("%s", &Produtos[i].Nome);
    printf("\nDigite o preco do produto: ");
    scanf("%f", &Produtos[i].Preco);
    printf("\nDigite a quantidade em estoque do produto: ");
    scanf("%d", &Produtos[i].Estoque);
    i++;
    return 0;
}
int BuscarProduto(int codigo)
{
    for (int k = 0; k < i; k++)
    {
        if (Produtos[k].Codigo == codigo)
            return k;
    }
    return -1;
}
int EditarProduto()
{
    int codigo;
    char nome[100];
    float preco;
    printf("\nDigite o codigo do produto: ");
    scanf("%d", &codigo);
    int index = BuscarProduto(codigo);
    if (index >= 0)
    {
        printf("\nDigite o nome do produto: ");
        scanf("%s", &Produtos[index].Nome);
        printf("\nDigite o preco do produto: ");
        scanf("%f", &Produtos[index].Preco);
        printf("\nDigite a quantidade em estoque do produto: ");
        scanf("%f", &Produtos[index].Estoque);
    }
    else
        printf("Produto nao encontrado");
    return 0;
}
int EliminarProduto()
{
    int codigo;
    char nome[100];
    float preco;
    printf("\nDigite o codigo do produto: ");
    scanf("%d", &codigo);
    int index = BuscarProduto(codigo);
    if (index >= 0)
    {
        Produtos[index].Codigo = -1;
    }
    else
        printf("Produto nao encontrado");
    return 0;
}
int RegistrarVenda()
{
    int codigo;
    char nome[100];
    float preco;
    printf("\nDigite o codigo do produto: ");
    scanf("%d", &codigo);
    int index = BuscarProduto(codigo);
    if (index >= 0)
    {
        printf("\nDigite a quantidade do produto: ");
        scanf("%d", &Vendas[j].Quantidade);
        printf("\nDigite o dia da venda: ");
        scanf("%d", &Vendas[j].Dia);
        printf("\nDigite o mes da venda: ");
        scanf("%d", &Vendas[j].Mes);
        printf("\nDigite o ano da venda: ");
        scanf("%d", &Vendas[j].Ano);
        Produtos[index].Estoque = Produtos[index].Estoque - Vendas[j].Quantidade;
    }
    else
        printf("Produto nao encontrado");
    j++;
    return 0;
}
int RelatorioMensalVenda()
{
    int mesVenda;
    FILE *fp;
    printf("\nDigite o mes da venda: ");
    scanf("%d", &mesVenda);
    for (int k = 0; k < j; k++)
    {
        if (Vendas[k].Mes == mesVenda)
        {
            //----Armazena as vendas
            fp = fopen("RelatorioMensalVenda.txt", "a+");
            fprintf(fp, "%d;%d;%d;%d;%d\r\n", Vendas[k].Codigo, Vendas[k].Quantidade, Vendas[k].Dia, Vendas[k].Mes, Vendas[k].Ano);
        }
    }
    fclose(fp);
    return 0;
}
int RelatorioProdutos()
{
    int codigo;
    FILE *fp;
    printf("\nDigite o codigo do produto: ");
    scanf("%d", &codigo);
    for (int k = 0; k < j; k++)
    {
        if (Vendas[k].Codigo == codigo)
        {
            //----Armazena as vendas
            fp = fopen("RelatorioProduto.txt", "a+");
            fprintf(fp, "%d;%d;%d;%d;%d\r\n", Vendas[k].Codigo, Vendas[k].Quantidade, Vendas[k].Dia, Vendas[k].Mes, Vendas[k].Ano);
        }
    }
    fclose(fp);
    return 0;
}
int RankingProdutos()
{
    struct Venda VendasAux[1000];
    FILE *fp;
    for (int k = 0; k < j; k++)
    {
        VendasAux[k].Codigo = Vendas[k].Codigo;
        VendasAux[k].Quantidade = Vendas[k].Quantidade;
    }
    for (int k = 0; k < j; k++)
    {
        int c = -1;
        int qnt = 0;
        if (VendasAux[k].Codigo >= 0)
        {
            c = VendasAux[k].Codigo;
            qnt += VendasAux[k].Quantidade;
            VendasAux[k].Codigo = -1;

            for (int h = 0; h < j; h++)
            {
                if (VendasAux[h].Codigo >= 0 && VendasAux[h].Codigo == c)
                {
                    qnt += VendasAux[h].Quantidade;
                    VendasAux[h].Codigo = -1;
                }
            }
        }
        fp = fopen("RankingProdutos.txt", "a+");
        for (int k = 0; k < j; k++)
        {
            fprintf(fp, "%d;%d\r\n", c, qnt);
        }
    }
    fclose(fp);
    return 0;
}

/*
 * 
 */
int main(int argc, char **argv)
{
    LoadFIle();
    printf("\n");
    int opcao = 0;
    while (opcao != 8)
    {
        printf("1 - Cadastrar produtos\n2 - Editar produtos\n3 - Eliminar produtos\n4 - Registrar vendas\n5 - Relatorio mensal de vendas\n6 - Relatorio de produtos\n7 - Ranking de produtos\n8 - Sair");
        printf(" \nEscolha uma opcao: ");
        scanf("%d", &opcao);
        printf("%d\n", opcao);
        int result;
        switch (opcao)
        {
        case 1:
            CadastrarProduto();
            break;

        case 2:
            EditarProduto();
            break;

        case 3:
            EliminarProduto();
            break;

        case 4:
            RegistrarVenda();
            break;

        case 5:
            RelatorioMensalVenda();
            break;

        case 6:
            RelatorioProdutos();
            break;

        case 7:
            RankingProdutos();
            break;

        default:
            opcao = 8;
            break;
        }
    }
    WriteFile();
    return (EXIT_SUCCESS);
}
