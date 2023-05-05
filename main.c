#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*-------------------------------------------------------------------------
ALUNO:  Gabriel Lourenço Reis Resende
DATA:   05/05/2023
TEMA:   Arquivos Sequencias em C
--------------------------------------------------------------------------*/

void escreverFibonacci();
void parEImpar();
void primos();
int ehPrimo(long long int);
void valor();


/*----------------------PROGRAMA PRINCIPAL(MENU)--------------------------*/
int main()
{
    char letra;
    printf("Digite qual programa deseja executar(A, B, C, D) ou digite F para sair: ");
    scanf("%c", &letra);
    while(letra!='F')
    {
        switch(letra)
        {
        case 'A':
            escreverFibonacci();
            break;
        case 'B':
            parEImpar();
            break;
        case 'C':
            primos();
            break;
        case 'D':
            valor();
            break;
        }
        printf("Digite qual programa deseja executar(A, B, C, D) ou digite F para sair: ");
        fflush(stdin);
        scanf("%c", &letra);
    }
    return 0;
}

/*-------------------------------------------------------------------------
Nome:   escreverFibonacci
Função: Gravar em um arquivo os 64 primeiros valores da série de Fibonacci.
--------------------------------------------------------------------------*/
void escreverFibonacci()
{
    FILE*arquivo;
    long long int fib1=1, fib2=1, serie=0;
    if((arquivo=fopen("arquivo.txt", "w"))==NULL)
    {
        printf("Erro de arbetura");
    }
    else
    {
        fprintf(arquivo, "%llu\n", fib1);
        fprintf(arquivo, "%lld\n", fib1);
        for(int i=3; i<=64; i++)
        {
            serie = fib1 + fib2;
            fprintf(arquivo, "%lli\n", serie);
            fib2 = fib1;
            fib1 = serie;
        }
        fclose(arquivo);
    }
}

/*-------------------------------------------------------------------------
Nome:   parEImpar
Função: Ler o arquivo da letra A e armazenar os valores pares em um arquivo
        e os impares em outro arquivo.
--------------------------------------------------------------------------*/
void parEImpar()
{
    FILE*arquivo;
    FILE*arquivoPares;
    FILE*arquivoImpares;
    long long int valor;

    if ((arquivo = fopen("arquivo.txt","r")) == NULL)
    {
        printf("Erro de abertura! \n");
    }
    else
    {
        if((arquivoPares=fopen("arquivoPares.txt", "w"))==NULL)
        {
            printf("Erro!");
        }
        if((arquivoImpares=fopen("arquivoImpares.txt", "w"))==NULL)
        {
            printf("Erro!");
        }
        while(fscanf(arquivo, "%lld", &valor) == 1)
        {
            if(valor % 2 == 0)
            {
                fprintf(arquivoPares, "%lld\n", valor);
            }
            else
            {
                fprintf(arquivoImpares, "%lld\n", valor);
            }
        }
        fclose(arquivo);
        fclose(arquivoPares);
        fclose(arquivoImpares);
    }
}

/*-------------------------------------------------------------------------
Nome:   primos
Função: Ler o arquivo letra A e armazenar apenas os primos em um arquivo.
--------------------------------------------------------------------------*/
void primos()
{
    FILE*arquivo;
    FILE*arquivoPrimos;
    long long int valor;

    if ((arquivo = fopen("arquivo.txt","r")) == NULL)
    {
        printf("Erro de abertura! \n");
    }
    else
    {
        if((arquivoPrimos=fopen("arquivoPrimos.txt", "w"))==NULL)
        {
            printf("Erro!");
        }
        while(!feof(arquivo))
        {
            fscanf(arquivo, "%lld", &valor);
            if(ehPrimo(valor))
            {
                fprintf(arquivoPrimos, "%lld\n", valor);
            }
        }
        fclose(arquivo);
        fclose(arquivoPrimos);
    }
}


/*-------------------------------------------------------------------------
Nome:   ehPrimos
Função: Verifica se o número lido do arquivo da letra A é primo.
--------------------------------------------------------------------------*/
int ehPrimo(long long int valor)
{
    if(valor <= 1||(valor%2==0 && valor !=2) || (valor%3==0 && valor!=3))
    {
        return 0;   // números menores ou iguais a 1 e pares não são primos
    }
    for(int i=5; i<=(sqrt(valor)); i++)
    {
        if(valor % i == 0)
        {
            return 0;   // se o número for divisível por algum i, não é primo
        }
    }
    return 1;  // se passou pelo laço sem encontrar divisores, é primo
}

/*-------------------------------------------------------------------------
Nome:   valor
Função: Ler um conjunto de valores (flag -1) e verificar para cada valor se
        ele se encontra ou não no arquivo gravado na letra a. Caso não exista
        será mostrado o valor anterior e o posterior a esse valor
--------------------------------------------------------------------------*/
void valor()
{
    long long int valor, valorArquivo, menor, maior;
    int cont=0, flag=1;
    FILE*arquivo;
    if ((arquivo = fopen("arquivo.txt","r")) == NULL)
    {
        printf("Erro de abertura! \n");
    }
    else
    {
        printf("Digite um valor(-1 para sair): ");
        scanf("%lld", &valor);
        while(valor!=-1)
        {
            while(!feof(arquivo))
            {
                fscanf(arquivo, "%lld", &valorArquivo);
                cont++;
                if(valor==valorArquivo)
                {
                    if(valor==1)
                    {
                        printf("O valor %lld esta no arquivo na posicao 1 e 2\n", valor);
                        flag=0;
                        break;
                    }
                    printf("O valor %lld esta no arquivo na posicao %d\n", valor, cont);
                    flag = 0;
                    break;
                }
                else if(valor<valorArquivo)
                {
                    maior = valorArquivo;
                    break;
                }
                else
                {
                    menor = valorArquivo;
                }
            }
            if(flag)
            {
                printf("O valor %lld nao esta no arquivo, valores mais proximos: %lld e %lld\n", valor, menor, maior);
            }
            printf("Digite um valor(-1 para sair): ");
            scanf("%lld", &valor);
            cont=0;
            flag=1;
            rewind(arquivo);
        }
        fclose(arquivo);
    }
}

