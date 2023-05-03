#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void escreverFibonacci();
void parEImpar();
void primos();
int ehPrimo(long long int valor);
void valor();

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
        fprintf(arquivo, "%d\n", fib1);
        fprintf(arquivo, "%d\n", fib1);
        for(int i=3; i<=64; i++)
        {
            serie = fib1 + fib2;
            fprintf(arquivo, "%lld\n", serie);
            fib2 = fib1;
            fib1 = serie;
        }
        fclose(arquivo);
    }
}


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
        while(!feof(arquivo))
        {
            fscanf(arquivo, "%lld", &valor);
            if(valor%2==0)
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

int ehPrimo(long long int valor)
{
    if(valor <= 1||(valor%2==0 && valor !=2) || (valor%3==0 && valor!=3))
    {
        return 0;   // n�meros menores ou iguais a 1 e pares n�o s�o primos
    }
    for(int i=5; i<=(sqrt(valor)); i++)
    {
        if(valor % i == 0)
        {
            return 0;   // se o n�mero for divis�vel por algum i, n�o � primo
        }
    }
    return 1;  // se passou pelo la�o sem encontrar divisores, � primo
}

void valor()
{
    long long int valor, valorArquivo, menor, maior;
    int flag=1;
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
                if(valor==valorArquivo)
                {
                    long long int serie=0, fib1=1, fib2=1;
                    int i;
                    for(i = 1; serie<=valor; i++)
                    {
                        serie = fib1 + fib2;
                        fib2 = fib1;
                        fib1 = serie;
                    }
                    if(valor!=1)
                    {
                        printf("O valor %lld esta no arquivo na posicao %d\n", valor, i);
                    }
                    flag = 0;
                    if(valor==1)
                    {
                        printf("O valor 1 esta no arquivo na posicao 1 e 2\n");
                        break;
                    }
                }
            }
            if(flag)
            {
                long long int fib1 =1, fib2=1, serie=0, menor=valor, maior=valor;
                for(int i=3; serie<=valor; i++)
                {
                    serie = fib1 + fib2;
                    if(serie>valor)
                    {
                        maior = serie;
                    }
                    if(serie<valor)
                    {
                        menor = serie;
                    }
                    fib2 = fib1;
                    fib1 = serie;
                }
                printf("Maior: %lld\n", maior);
                printf("Menor: %lld\n", menor);
            }
            printf("Digite um valor(-1 para sair): ");
            scanf("%lld", &valor);
            flag = 1;
            rewind(arquivo);
        }
        fclose(arquivo);
    }
}

