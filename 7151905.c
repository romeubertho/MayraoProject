//Romeu Bertho Junior Nusp: 7151905

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>

struct Pessoa //estrutura para o registro
{
    char LastName[100];
    char FirstName[100];
    char Address[200];
    char City[100];
    char Age[100];
};
int main()
{
    struct Pessoa registro;
    int c;
    char saida[100];
    char saida2[100];
    strcpy(saida,"s");
    //----Abre/cria o arquivo
    FILE * fp;
    fp = fopen ("file.txt", "a+");
    do // loop do registro
    {
        //----Usu�rio entra com o registro das pessoas
    printf("Entre com o sobrenome: \n");
    gets(registro.LastName);
    system("cls");
    printf("Entre com o primeiro nome: \n");
    gets(registro.FirstName);
    system("cls");
    printf("Entre com o Endereco: \n");
    gets(registro.Address);
    system("cls");
    printf("Entre com a cidade: \n");
    gets(registro.City);
    system("cls");
    printf("Entre com a idade: \n");
    gets(registro.Age);
    system("cls");
    //----- Vai para o fim do arquivo e faz a escrita nele
    fseek(fp, 0, SEEK_END);
    fprintf(fp,"%s ; %s ; %s ; %s ; %s\r\n",registro.LastName,registro.FirstName,registro.Address,registro.City,registro.Age);
    //---Op��o para continuar com a entrada de novos registros
    printf("Continuar S/N: \n");
    gets(saida2);
    system("cls");
    } while(strcmp(saida,saida2)==0); // Se "s" usu�rio entra com um novo registro, caso contr�rio, � impresso os registros no terminal
    fseek(fp,0,SEEK_SET); // volta para o come�o do arquivo
    while ((c = getc(fp)) != EOF) // enquanto n�o for o fim do arquivo, imprime caractere por caractere
        putchar(c);
    fclose(fp); // fecha o arquivo
    return 0;
}

