#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "funcoesLeitura.h"


/* Funcoes para leitura de dados */

void lerString(char vetor[80], int max){
    int tamanhoString;

    do
    {
        fgets(vetor, max, stdin);
        tamanhoString = strlen(vetor);
    }
    while (tamanhoString == 1);	   /* Repete leitura se introduzida string apenas com o \n */

    if (vetor[tamanhoString-1] != '\n')
    {
        limpaBufferStdin(); 	/* limpa dados do buffer stdin */
    }
    else
    {
        vetor[tamanhoString-1] ='\0'; 	/* substitui por \0 o caracter \n da string armazenada */
    }

}

int lerInteiro(int min, int max){
    int numero, controlo;

    do 	// Repete leitura enquanto valor introduzido n�o for num�rico e n�o estiver no intervalo desejado (min -> max)
    {
        controlo = scanf("%d", &numero); // scanf devolve quantidade de valores v�lidos obtidos
        limpaBufferStdin();   /* limpa dados do buffer stdin */
    }
    while (numero<min || numero>max || controlo==0);

    return numero;
}

void limpaBufferStdin(void) 	/* Chamar apos leituras de dados atraves do teclado */{
    char lixo;

    do
    {
        lixo=getchar();
    }
    while (lixo!='\n' && lixo!=EOF);
}

tipoData lerData(void){
    tipoData data;
    int maxDiaMes;

    printf("\n Ano (%d a %d): ",2018,2030);
    data.ano = lerInteiro(2018,2030);

    printf("Mes (%d a %d): ",1,12);
    data.mes = lerInteiro(1,12);

    switch (data.mes)
    {
    case 2:
        if((data.ano%400==0) || (data.ano%4==0 && data.ano%100!=0))
        {
            maxDiaMes = 29;    /* Ano bissexto */
        }
        else
        {
            maxDiaMes = 28;

        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        maxDiaMes = 30;
        break;
    default:
        maxDiaMes = 31;
    }
    printf("Dia (%d a %d): ", 1, maxDiaMes);
    data.dia = lerInteiro(1, maxDiaMes);

    return data;
}

tipoHora lerHora(void){
    tipoHora horatype;

    printf("\n Horas (%d a %d): ",0,23);
    horatype.hora = lerInteiro(0,23);

    printf("\n Minutos (%d a %d): ",0,59);
    horatype.min = lerInteiro(0,59);   
return horatype;
}
