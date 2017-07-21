
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
    int QtdVendida;
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
int i = 0; // num de produtos armazenados
int j = 0; // num de vendas armazenadas
int LoadFIle()
{

    FILE *fp;
    //----Carrega Produtos
    fp = fopen("Produtos.txt", "r");
    if (fp)
    {
        char buffer[100], buffer1[100], buffer2[100], buffer3[100];
        while (fgets(buffer, 100, fp) && fgets(buffer1, 100, fp) && fgets(buffer2, 100, fp) && fgets(buffer3, 100, fp))
        {
            strcpy(Produtos[i].Nome, buffer);
            strtok(Produtos[i].Nome, "\n");
            Produtos[i].Codigo = atoi(buffer1);
            Produtos[i].Preco = atof(buffer2);
            Produtos[i].Estoque = atoi(buffer3);
            Produtos[i].QtdVendida = 0;
            printf("%d %s %f %d\n", Produtos[i].Codigo, Produtos[i].Nome, Produtos[i].Preco, Produtos[i].Estoque);
            i++;
        }
        fclose(fp);
    }
    //----Carrega Vendas
    fp = fopen("Vendas.txt", "r");
    if (fp)
    {
        char buffer[100], buffer1[100], buffer2[100], buffer3[100], buffer4[100];
        while (fgets(buffer, 100, fp) && fgets(buffer1, 100, fp) && fgets(buffer2, 100, fp) && fgets(buffer3, 100, fp) && fgets(buffer4, 100, fp))
        {
            Vendas[j].Codigo = atoi(buffer);
            Vendas[j].Quantidade = atoi(buffer1);
            Vendas[j].Dia = atoi(buffer2);
            Vendas[j].Mes = atoi(buffer3);
            Vendas[j].Ano = atoi(buffer4);
            j++;
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
        {
            fprintf(fp, "%s\n", Produtos[k].Nome);
            fprintf(fp, "%d\n", Produtos[k].Codigo);
            fprintf(fp, "%f\n", Produtos[k].Preco);
            fprintf(fp, "%d\n", Produtos[k].Estoque);
        }
    fclose(fp);
    //----Armazena as vendas
    fp = fopen("Vendas.txt", "w");
    for (int k = 0; k < j; k++)
    {
        fprintf(fp, "%d\n", Vendas[k].Codigo);
        fprintf(fp, "%d\n", Vendas[k].Quantidade);
        fprintf(fp, "%d\n", Vendas[k].Dia);
        fprintf(fp, "%d\n", Vendas[k].Mes);
        fprintf(fp, "%d\n", Vendas[k].Ano);
    }
    fclose(fp);
}
int CadastrarProduto()
{
    char buffer[100];
    printf("\nDigite o codigo do produto: ");
    fgets(buffer, sizeof buffer, stdin);
    Produtos[i].Codigo = atoi(buffer);

    printf("\nDigite o nome do produto: ");
    fgets(buffer, 100, stdin);
    strcpy(Produtos[i].Nome, buffer);
    strtok(Produtos[i].Nome, "\n");

    printf("\nDigite o preco do produto: ");
    fgets(buffer, sizeof buffer, stdin);
    Produtos[i].Preco = atof(buffer);

    printf("\nDigite a quantidade em estoque do produto: ");
    fgets(buffer, sizeof buffer, stdin);
    Produtos[i].Estoque = atoi(buffer);
    Produtos[i].QtdVendida = 0;
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
    char buffer[100];
    printf("\nDigite o codigo do produto: ");
    fgets(buffer, sizeof buffer, stdin);
    codigo = atoi(buffer);
    int index = BuscarProduto(codigo);
    if (index >= 0)
    {
        printf("\nDigite o nome do produto: ");
        fgets(buffer, 100, stdin);
        strcpy(Produtos[index].Nome, buffer);
        strtok(Produtos[index].Nome, "\n");

        printf("\nDigite o preco do produto: ");
        fgets(buffer, sizeof buffer, stdin);
        Produtos[index].Preco = atof(buffer);

        printf("\nDigite a quantidade em estoque do produto: ");
        fgets(buffer, sizeof buffer, stdin);
        Produtos[index].Estoque = atoi(buffer);
        Produtos[index].QtdVendida = 0;
    }
    else
        printf("Produto nao encontrado");
    return 0;
}
int EliminarProduto()
{
    int codigo;
    char buffer[100];
    printf("\nDigite o codigo do produto: ");
    fgets(buffer, sizeof buffer, stdin);
    codigo = atoi(buffer);
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
    char buffer[100];
    printf("\nDigite o codigo do produto: ");
    fgets(buffer, sizeof buffer, stdin);
    codigo = atoi(buffer);
    int index = BuscarProduto(codigo);
    if (index >= 0)
    {
        printf("\nDigite a quantidade do produto: ");
        fgets(buffer, sizeof buffer, stdin);
        if (atoi(buffer) > Produtos[index].Estoque)
        {
            printf("Quantidade solicitada indisponivel. Disponivel: %d.\n\n", Produtos[index].Estoque);
            return 0;
        }
        Vendas[j].Codigo = codigo;
        Vendas[j].Quantidade = atoi(buffer);

        printf("\nDigite o dia da venda: ");
        fgets(buffer, sizeof buffer, stdin);
        Vendas[j].Dia = atoi(buffer);

        printf("\nDigite o mes da venda: ");
        fgets(buffer, sizeof buffer, stdin);
        Vendas[j].Mes = atoi(buffer);

        printf("\nDigite o ano da venda: ");
        fgets(buffer, sizeof buffer, stdin);
        Vendas[j].Ano = atoi(buffer);

        Produtos[index].Estoque = Produtos[index].Estoque - Vendas[j].Quantidade;
        j++;
    }
    else
        printf("Produto nao encontrado.\n\n");
    return 0;
}
int RelatorioMensalVenda()
{
    int mesVenda;
    char buffer[100];
    FILE *fp;
    printf("\nDigite o mes da venda: ");
    fgets(buffer, sizeof buffer, stdin);
    mesVenda = atoi(buffer);
    fp = fopen("RelatorioMensalVenda.txt", "w");
    for (int k = 0; k < j; k++)
    {
        if (Vendas[k].Mes == mesVenda)
        {
            //----Armazena as vendas
            fprintf(fp, "%d\n", Vendas[k].Codigo);
            fprintf(fp, "%d\n", Vendas[k].Quantidade);
            fprintf(fp, "%d\n", Vendas[k].Dia);
            fprintf(fp, "%d\n", Vendas[k].Mes);
            fprintf(fp, "%d\n", Vendas[k].Ano);
        }
    }
    fclose(fp);
    return 0;
}
int RelatorioProdutos()
{
    int codigo;
    char buffer[100];
    FILE *fp;
    printf("\nDigite o codigo do produto: ");
    fgets(buffer, sizeof buffer, stdin);
    codigo = atoi(buffer);
    fp = fopen("RelatorioProduto.txt", "w");
    for (int k = 0; k < j; k++)
    {
        if (Vendas[k].Codigo == codigo)
        {
            //----Armazena as vendas
            fprintf(fp, "%d\n", Vendas[k].Codigo);
            fprintf(fp, "%d\n", Vendas[k].Quantidade);
            fprintf(fp, "%d\n", Vendas[k].Dia);
            fprintf(fp, "%d\n", Vendas[k].Mes);
            fprintf(fp, "%d\n", Vendas[k].Ano);
        }
    }
    fclose(fp);
    return 0;
}
int RankingProdutos()
{
    struct Venda VendasAux[1000];
    FILE *fp;
    fp = fopen("RankingProdutos.txt", "w");
    for (int k = 0; k < j; k++)
    {
        int index = BuscarProduto(Vendas[k].Codigo);
        Produtos[index].QtdVendida += Vendas[k].Quantidade;
    }
    for (int k = 0; k < i; k++)
    {
        fprintf(fp, "%s, %d venda(s) \n", Produtos[k].Nome, Produtos[k].QtdVendida);
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
        char buffer[100];
        fgets(buffer, sizeof buffer, stdin);
        opcao = atoi(buffer);
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
