#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funcoesLeitura.h"
#include "funcoesMembros.h"
#include "funcoesTestes.h" 
#include "funcoesFicheiros.h"


//!!!!!!!!!!!!         TESTES       !!!!!!!!!!!!!!!!

int contaTestesPCR(tipoTeste vetorTestes[],int totTestes, int totMembros, int dataDia, int dataMes, int dataAno){

   // tipoData datacheck1;
    int totPCR, i, k;
    totPCR = 1;
    for(i=0; i < totTestes; i++){
        if (dataDia == vetorTestes[i].dataRealizacao.dia && dataMes == vetorTestes[i].dataRealizacao.mes && dataAno == vetorTestes[i].dataRealizacao.ano) {
                     //if(vetorTestes[i].tipoTeste == 1){
                        totPCR++;
                    // }
        }
    }

    return totPCR;
}

tipoTeste *agendarTeste(tipoTeste *vetorTestes, tipoMembro vetorMembros[],int *totTestes, int *totTestesAgendados, int totMembros){

    tipoTeste dadosTeste;
    tipoMembro dadosMembro;
    tipoTeste *paux; /* ponteiro para restaurar valor de vFunc  */
    int dataDia, dataMes, dataAno;
    int posicao, totalPCR, numUtente;

    paux = vetorTestes;

    printf("Numero de Utente: ");
    numUtente = lerInteiro(1,9999999);
    posicao = procuraMembro(vetorMembros, totMembros, numUtente);

    if (posicao == -1){

           printf("Esse numero de utente nao existe.\n");

        }else{ 
                 printf("%d TESTES ANTES DO REALLOC NO agendarTeste \t", *totTestes); //TESTE//TESTE//TESTE//TESTE//TESTE

                vetorTestes = realloc(vetorTestes,(*totTestes+1)*sizeof(tipoTeste));

            if (vetorTestes == NULL)
            {
                printf ("Erro - Impossivel aumentar o vetor");
                vetorTestes = paux; 	/* restaura valor de vFunc caso nao acrescente 1 espaco no vetor  */
            }
            else
            {
                printf("Data da Realizacao do Teste: ");
                tipoData dataRealizacao = lerData(); 
                printf("\nInsira o tipo de Teste\n");
                printf("(1)PCR ou (2)Antigeneo: ");
                dadosTeste.tipoTeste = lerInteiro(1,2);
                dadosTeste.numUtente = numUtente;
                dadosTeste.dataRealizacao.dia = dataRealizacao.dia;
                dadosTeste.dataRealizacao.mes = dataRealizacao.mes;
                dadosTeste.dataRealizacao.ano = dataRealizacao.ano;

                printf("%d dia \t", dadosTeste.dataRealizacao.dia); //TESTE//TESTE//TESTE//TESTE//TESTE
                printf("%d mes \t", dadosTeste.dataRealizacao.mes);//TESTE//TESTE//TESTE//TESTE//TESTE
                printf("%d ano \t",dadosTeste.dataRealizacao.ano);//TESTE//TESTE//TESTE//TESTE//TESTE

                    if(dadosTeste.tipoTeste == 1){
                        dataDia = dadosTeste.dataRealizacao.dia;
                        dataMes = dadosTeste.dataRealizacao.mes;
                        dataAno = dadosTeste.dataRealizacao.ano;
                        int totT = *totTestes;
                        totalPCR = contaTestesPCR(vetorTestes, totT, totMembros, dataDia, dataMes, dataAno); // conta testes pcr do msm dia
                        printf("%d PCR's na Data Inserida", totalPCR); // TESTE TESTE TESTE TESTE TESTE TESTE TESTE TESTE TESTE 
                    }else if(totalPCR >= 15){

                        printf ("Nao e possivel fazer mais testes neste dia");
                    // dadosTeste.dataRealizacao = -1;
                        dadosTeste.numUtente = -1;
                        dadosTeste.tipoTeste = -1;
                        dadosTeste.dataRealizacao.dia = -1;
                        dadosTeste.dataRealizacao.mes = -1;
                        dadosTeste.dataRealizacao.ano = -1;
                         }
                }
                            //printf("%d numero de utente <- TESTE\n", dadosTeste.numUtente);  // TESTE TESTE TESTE TESTE TESTE TESTE TESTE TESTE TESTE 
                            vetorTestes[*totTestes].tipoTeste = dadosTeste.tipoTeste; // para os dados irem para o ultimo espaco do vetor
                            vetorTestes[*totTestes].numUtente = dadosTeste.numUtente; 
                            vetorTestes[*totTestes].dataRealizacao.dia = dadosTeste.dataRealizacao.dia;
                            vetorTestes[*totTestes].dataRealizacao.mes = dadosTeste.dataRealizacao.mes; 
                            vetorTestes[*totTestes].dataRealizacao.ano = dadosTeste.dataRealizacao.ano; 
                            vetorTestes[*totTestes].resultado = '\0'; 
                            vetorTestes[*totTestes].horaColheita.hora = -1; 
                            vetorTestes[*totTestes].horaColheita.min = -1; 
                            vetorTestes[*totTestes].tempDuracao = -1;
                            //printf("%d numero de utente <- TESTE\n", dadosTeste.numUtente);  // TESTE TESTE TESTE TESTE TESTE TESTE TESTE TESTE TESTE 
                            (*totTestesAgendados)++;
                            (*totTestes)++;
                            LogTestesInfo(vetorMembros[posicao], dadosTeste);
                            printf("\nAgendado com sucesso");
                        
                    }
    return vetorTestes;
}

tipoTeste *inserirTesteRealizado(tipoTeste *vetorTestes, int *totTestes, int *totTestesRealizados, int *totTestesAgendados, tipoMembro vetorMembros[], int totMembros){

    tipoTeste dadosTeste;
    tipoTeste *paux; /* ponteiro para restaurar valor de vFunc  */
    tipoMembro dadosMembro;

    int total = *totTestes;
    int dataDia, dataMes, dataAno;
    int posicao, totalPCR, numUtente, pos;
    char opResultado;

    paux = vetorTestes;

    printf(" \n %d totTestes", *totTestes);

    printf("\n Numero de Utente: ");
    numUtente = lerInteiro(1,9999999);
    posicao = procuraMembro(vetorMembros, totMembros, numUtente);

    printf("\n Data da Realizacao do Teste: ");
    tipoData dataRealizacao = lerData(); 


        if (posicao == -1){

                printf("Esse numero de utente nao existe.\n");

                }else{
                    
                        if(*totTestes == 0){ //CASO vetorTestes Ainda esteja na pos 0

                                vetorTestes = realloc(vetorTestes,(*totTestes+1)*sizeof(tipoTeste));

                                if (vetorTestes == NULL)
                                {
                                    printf ("Erro - Impossivel aumentar o vetor");
                                    vetorTestes = paux; 	/* restaura valor de vFunc  */
                                }
                                else{
                                        printf("Insira o tipo de Teste\n");
                                        printf("(1)PCR ou (2)Antigeneo: ");
                                        dadosTeste.tipoTeste = lerInteiro(1,2);
                                        dadosTeste.numUtente = numUtente;
                                        dadosTeste.dataRealizacao.dia = dataRealizacao.dia;
                                        dadosTeste.dataRealizacao.mes = dataRealizacao.mes;
                                        dadosTeste.dataRealizacao.ano = dataRealizacao.ano;


                                        do{
                                                printf("Resultado{(p)ositivo, (n)egativo ou (i)nconclusivo} : ");
                                                scanf("%c", &opResultado);    
                                                opResultado = toupper(opResultado);
                                                limpaBufferStdin();        
                                            }while(opResultado != 'P' && opResultado != 'N' && opResultado != 'I');
                                                dadosTeste.resultado = opResultado;

                                            printf("\nHora da Colheita: ");
                                            dadosTeste.horaColheita = lerHora();

                                            printf("\nTempo de Duracao(0min a 59min): ");
                                            dadosTeste.tempDuracao = lerInteiro(0,59);

                                            (*totTestesRealizados)++;

                                                vetorTestes[*totTestes].tipoTeste = dadosTeste.tipoTeste; // para os dados irem para o ultimo espaco do vetor
                                                vetorTestes[*totTestes].numUtente = dadosTeste.numUtente; 
                                                vetorTestes[*totTestes].dataRealizacao.dia = dadosTeste.dataRealizacao.dia;
                                                vetorTestes[*totTestes].dataRealizacao.mes = dadosTeste.dataRealizacao.mes; 
                                                vetorTestes[*totTestes].dataRealizacao.ano = dadosTeste.dataRealizacao.ano; 
                                                vetorTestes[*totTestes].resultado = dadosTeste.resultado; 
                                                vetorTestes[*totTestes].horaColheita = dadosTeste.horaColheita; 
                                                vetorTestes[*totTestes].tempDuracao = dadosTeste.tempDuracao; 

                                                vetorMembros[posicao].totRealizadosIndiv++;

                                                // printf(" \n %d numUtente do ultimo membro inserido",vetorTestes[*totTestes].numUtente); // #TESTE# // #TESTE# // #TESTE# // #TESTE# // #TESTE#
                                                // printf(" \n %d numUtente do ultimo membro inserido",vetorTestes[*totTestes].numUtente);  // #TESTE# // #TESTE# // #TESTE# // #TESTE# // #TESTE#

                                                (*totTestes)++;
                                                LogTestesInfo(vetorMembros[posicao], dadosTeste);
                                                printf(" \n %d totTestes", *totTestes);
                                                printf("\nTeste Realizado com sucesso");
                                }
                        }else if(*totTestes != 0){
                        //printf("Data da Realizacao do Teste: ");
                        //tipoData dataRealizacao = lerData(); 
                         //printf("NAO CHEGOU AO FOR");
                         // printf(" \n %d totTestes", *totTestes);
                            
                                for(pos=0;pos < total; pos++){ 
                                            printf("\n %d Dia da posicao Encontrada", vetorTestes[pos].dataRealizacao.dia);
                                            printf(" \n %d Dia registado \n", dataRealizacao.dia);
                                    if(vetorTestes[pos].resultado == '\0' && vetorTestes[pos].numUtente == numUtente && vetorTestes[pos].dataRealizacao.dia == dataRealizacao.dia && vetorTestes[pos].dataRealizacao.mes == dataRealizacao.mes && vetorTestes[pos].dataRealizacao.ano == dataRealizacao.ano){ //CASO numUtente && data ja existam em um espaco no vetor
                     //        verificar se utente ja realizou teste nesse msm dia
                                        total = pos; // parar loop(for)
                                                do{
                                                    printf("Resultado{(p)ositivo, (n)egativo ou (i)nconclusivo} : ");
                                                    scanf("%c", &opResultado);    
                                                    opResultado = toupper(opResultado);
                                                    limpaBufferStdin();        
                                                }while(opResultado != 'P' && opResultado != 'N' && opResultado != 'I');
                                                    vetorTestes[pos].resultado = opResultado;

                                                printf("\nHora da Colheita: ");
                                                vetorTestes[pos].horaColheita = lerHora();

                                                printf("\nTempo de Duracao(0min a 59min): ");
                                                vetorTestes[pos].tempDuracao = lerInteiro(0,59);

                                                (*totTestesAgendados)--;
                                                (*totTestesRealizados)++;

                                                dadosTeste.tipoTeste = vetorTestes[pos].tipoTeste; // para os dados irem para o ultimo espaco do vetor
                                                dadosTeste.numUtente = vetorTestes[pos].numUtente; 
                                                dadosTeste.dataRealizacao.dia = vetorTestes[pos].dataRealizacao.dia;
                                                dadosTeste.dataRealizacao.mes = vetorTestes[pos].dataRealizacao.mes; 
                                                dadosTeste.dataRealizacao.ano = vetorTestes[pos].dataRealizacao.ano; 
                                                dadosTeste.resultado = vetorTestes[pos].resultado; 
                                                dadosTeste.horaColheita = vetorTestes[pos].horaColheita; 
                                                dadosTeste.tempDuracao = vetorTestes[pos].tempDuracao;

                                                // if Condicao, break the loop
                                               /* if (vetorTestes[pos].numUtente == numUtente) {
                                                    (*totTestes)--;
                                                    break;
                                                }*/
                                        }
                                    else if(dadosTeste.tipoTeste == -1 && vetorTestes[pos].numUtente == numUtente){                     //caso nao exista adiciona +1 espaco no vetor
                                    // printf(" CHEGOU AO ELSE");
                                        total = pos; // parar loop(for)
                                        vetorTestes = realloc(vetorTestes,(*totTestes+1)*sizeof(tipoTeste));

                                    if (vetorTestes == NULL)
                                    {
                                        printf ("Erro - Impossivel aumentar o vetor");
                                        vetorTestes = paux; 	/* restaura valor de vFunc  */
                                    }
                                        else{                   // Pede todos os dados tipoTeste
                                            printf("Insira o tipo de Teste\n");
                                            printf("(1)PCR ou (2)Antigeneo: ");
                                            dadosTeste.tipoTeste = lerInteiro(1,2);
                                            dadosTeste.numUtente = numUtente;
                                            dadosTeste.dataRealizacao.dia = dataRealizacao.dia;
                                            dadosTeste.dataRealizacao.mes = dataRealizacao.mes;
                                            dadosTeste.dataRealizacao.ano = dataRealizacao.ano;

                                            do{
                                            printf("Resultado{(p)ositivo, (n)egativo ou (i)nconclusivo} : ");
                                            scanf("%c", &opResultado);    
                                            opResultado = toupper(opResultado);
                                            limpaBufferStdin();        
                                            }while(opResultado != 'P' && opResultado != 'N' && opResultado != 'I');
                                                dadosTeste.resultado = opResultado;
                                            printf("\nHora da Colheita: ");
                                            dadosTeste.horaColheita = lerHora();

                                            printf("\nTempo de Duracao(0min a 59min): ");
                                            dadosTeste.tempDuracao = lerInteiro(0,59);

                                            (*totTestesRealizados)++;


                                                if(dadosTeste.tipoTeste == 1){
                                                        dataDia = dadosTeste.dataRealizacao.dia;
                                                        dataMes = dadosTeste.dataRealizacao.mes;
                                                        dataAno = dadosTeste.dataRealizacao.ano;
                                                        int totT = *totTestes;
                                                        totalPCR = contaTestesPCR(vetorTestes, totT, totMembros, dataDia, dataMes, dataAno); // conta testes pcr do msm dia
                                                        printf("%d PCR's na Data Inserida", totalPCR);
                                                    }else if(totalPCR >= 15){

                                                        printf ("Nao e possivel fazer mais testes neste dia");
                                                        dadosTeste.numUtente = -1;
                                                        dadosTeste.tipoTeste = -1;
                                                        dadosTeste.dataRealizacao.dia = -1;
                                                        dadosTeste.dataRealizacao.mes = -1;
                                                        dadosTeste.dataRealizacao.ano = -1;

                                                        dadosTeste.resultado = '\0';
                                                        dadosTeste.horaColheita.hora = -1; 
                                                        dadosTeste.horaColheita.min = -1; 
                                                        dadosTeste.tempDuracao = -1;
                                                    }

                                                    vetorTestes[*totTestes].tipoTeste = dadosTeste.tipoTeste; // para os dados irem para o ultimo espaco do vetor
                                                    vetorTestes[*totTestes].numUtente = dadosTeste.numUtente; 
                                                    vetorTestes[*totTestes].dataRealizacao.dia = dadosTeste.dataRealizacao.dia;
                                                    vetorTestes[*totTestes].dataRealizacao.mes = dadosTeste.dataRealizacao.mes; 
                                                    vetorTestes[*totTestes].dataRealizacao.ano = dadosTeste.dataRealizacao.ano; 
                                                    vetorTestes[*totTestes].resultado = dadosTeste.resultado; 
                                                    vetorTestes[*totTestes].horaColheita = dadosTeste.horaColheita; 
                                                    vetorTestes[*totTestes].tempDuracao = dadosTeste.tempDuracao; 
                                                    
                                                }
                                        }    
                                       /* if (vetorTestes[pos].numUtente == numUtente) {
                                                    break;
                                                    }   */
                                    }

                                        vetorMembros[posicao].totRealizadosIndiv++;

                                       // printf(" \n %d numUtente do ultimo membro inserido",vetorTestes[*totTestes].numUtente); // #TESTE# // #TESTE# // #TESTE# // #TESTE# // #TESTE#
                                       // printf(" \n %d numUtente do ultimo membro inserido",vetorTestes[*totTestes].numUtente);  // #TESTE# // #TESTE# // #TESTE# // #TESTE# // #TESTE#



                                        (*totTestes)++;
                                        LogTestesInfo(vetorMembros[posicao], dadosTeste);
                                        printf(" \n %d totTestes", *totTestes);
                                        printf("\nTeste Realizado com sucesso");


                                     /*  int k, posT;
                                    for(posT=0;posT < *totTestes; posT++){
                                        if(vetorTestes[posT].horaColheita.hora > 23 || vetorTestes[posT].horaColheita.min >59){           //vetorTestes[posT].tipoTeste != 0 && vetorTestes[posT].tipoTeste != 1 && vetorTestes[posT].tipoTeste != 0 && 
                                               // total = posT; // parar loop(for)
                                             vetorTestes = realloc(vetorTestes,(*totTestes-1)*sizeof(tipoTeste));
                                        }
                                    }*/

                               
                                }
                    
                }
    return vetorTestes;
}

void mostrarDadosTestes(tipoTeste *vetorTestes,int *totTestes, tipoMembro vetorMembros[], int totMembros)
{
    int i, k;

    if (totMembros == 0)
    {
        printf("\n Nao existem membros inscritos!");
    }else if(*totTestes == 0){
        printf("\n Nao existem testes agendados ou realizados!");
    }
    else
    {
        printf("\n-----------Registos Testes-----------\n");
        printf("\nNumero Utente \t Nome \t Tipo de Membro \t Tipo Teste Realizado \t Data de Realizacao \t Resultado \t Hora da Colheita \t Duracao");
        for (i=0; i< *totTestes; i++)
        {
                if(vetorTestes[i].tipoTeste == 1 || vetorTestes[i].tipoTeste == 2){ //        verificar se 'e teste agendado analisando se o resultado se encontra vazio
                        //printf("**Teste Agendado**");
                        //printf("\nNumero Utente \t Nome \t Tipo de Membro \t Tipo Teste Agendado \t Data de Agendamento ");

                        printf("\n %d \t", vetorTestes[i].numUtente);

                        for (k=0; k< totMembros; k++){     
                                if (vetorTestes[i].numUtente == vetorMembros[k].numUtente)  // para interligar os vetores
                                {
                                    printf("\t %s", vetorMembros[k].nome);

                                    if (vetorMembros[k].estadoMembro == 'E')
                                        {
                                            printf("\t Estudante");
                                        }
                                        else if (vetorMembros[k].estadoMembro == 'D')
                                        {
                                        printf("\t Docente");
                                        }
                                        else if (vetorMembros[k].estadoMembro == 'T')
                                        {
                                        printf("\t Tecnico");
                                        }
                                }
                                
                        }

                            if (vetorTestes[i].tipoTeste == 1)
                                {
                                    printf("\t\t PCR");
                                }
                            else if (vetorTestes[i].tipoTeste == 2)
                                {
                                    printf("\t\t Antigenio");
                                }

                            printf("\t\t\t %02d/%02d/%4d", vetorTestes[i].dataRealizacao.dia, vetorTestes[i].dataRealizacao.mes, vetorTestes[i].dataRealizacao.ano );

                            if(vetorTestes[i].resultado == 'P')
                                            {
                                                printf("\t\t Positivo");
                                            }else if (vetorTestes[i].resultado == 'N')
                                            {
                                                printf("\t\t Negativo");
                                            }else if (vetorTestes[i].resultado == 'I')
                                            {
                                                printf("\t\t Inconclusivo");
                                            }else{
                                                printf("\t\t [Sem Registo]");
                                            }

                                            printf("\t [Sem Registo] \t");
                                            printf("\t [Sem Registo]\n");
                }
                
                else if(vetorTestes[i].resultado == 'p' || vetorTestes[i].resultado == 'n' || vetorTestes[i].resultado == 'i'){ //verificar se e realizado

                            //printf("**Teste Realizado**");
                            //printf("\nNumero Utente \t Nome \t Tipo de Membro \t Tipo Teste Realizado \t Data de Realizacao \t Resultado \t Hora da Colheita \t Duracao");

                            printf("\n %d \t",vetorTestes[i].numUtente);

                            for (k=0; k< totMembros; k++){     
                                    if (vetorTestes[i].numUtente == vetorMembros[k].numUtente)  // para interligar os vetores
                                    {
                                        printf("\t %s", vetorMembros[k].nome);

                                        if (vetorMembros[k].estadoMembro == 'E')
                                            {
                                                printf("\t\t Estudante");
                                            }
                                            else if (vetorMembros[k].estadoMembro == 'D')
                                            {
                                            printf("\t\t Docente");
                                            }
                                            else if (vetorMembros[k].estadoMembro == 'T')
                                            {
                                            printf("\t\t Tecnico");
                                            }
                                    }
                                    
                            }

                                if (vetorTestes[i].tipoTeste == 1)
                                    {
                                        printf("\t\t PCR");
                                    }
                                else if (vetorTestes[i].tipoTeste == 2)
                                    {
                                        printf("\t\t Antigenio");
                                    }

                                printf("\t\t\t %02d/%02d/%4d", vetorTestes[i].dataRealizacao.dia, vetorTestes[i].dataRealizacao.mes, vetorTestes[i].dataRealizacao.ano);

                                
                                if(vetorTestes[i].resultado == 'P')
                                {
                                    printf("\t\t Positivo");
                                }else if (vetorTestes[i].resultado == 'N')
                                {
                                    printf("\t\t Negativo");
                                }else if (vetorTestes[i].resultado == 'I')
                                {
                                    printf("\t\t Inconclusivo");
                                }

                                printf("\t %02d:%02d \t",  vetorTestes[i].horaColheita.hora, vetorTestes[i].horaColheita.min );
                                printf("\t %02d minutos\n",  vetorTestes[i].tempDuracao);
                    }
            }
        }
}

void mostrarTestesUtilizador(tipoTeste *vetorTestes,int *totTestes, tipoMembro vetorMembros[], int totMembros)
{
    int i, k, j, numUtente, posicao, quantPositivos;
    int total;
    total = *totTestes;

    printf("\n Numero de Utente: ");
    numUtente = lerInteiro(1,9999999);
    posicao = procuraMembro(vetorMembros, totMembros, numUtente);
    
    if (posicao == -1){
        printf("Esse numero de utente nao existe.\n");
    }else if (totMembros == 0)
    {
        printf("\n Nao existem membros inscritos!");
    }else if(*totTestes == 0){
        printf("\n Nao existem testes agendados ou realizados!");
    }
    else
    {
        printf("\n-----------Registos dos Testes do Membro Inserido-----------\n");
        printf("\nNumero Utente \t Nome \t Tipo de Membro \t Tipo Teste Realizado \t Data de Realizacao \t Resultado \t Hora da Colheita \t Duracao");
                    for (i=0; i< *totTestes; i++)
                    {
                            if(vetorTestes[i].resultado == '\0' && vetorTestes[i].numUtente == numUtente){ //        verificar se 'e teste agendado analisando se o resultado se encontra vazio && se o numUtente inserido existe no vetorTestes
                                    //printf("\n**Teste Agendado**");

                                    printf("\n %d \t",vetorMembros[i].numUtente);

                                    for (k=0; k< *totTestes; k++){     
                                            if (vetorTestes[i].numUtente == vetorMembros[k].numUtente)  // para interligar os vetores
                                            {
                                                printf("\t %s", vetorMembros[k].nome);

                                                if (vetorMembros[k].estadoMembro == 'E')
                                                    {
                                                        printf("\t Estudante");
                                                    }
                                                    else if (vetorMembros[k].estadoMembro == 'D')
                                                    {
                                                    printf("\t Docente");
                                                    }
                                                    else if (vetorMembros[k].estadoMembro == 'T')
                                                    {
                                                    printf("\t Tecnico");
                                                    }
                                            }
                                            
                                    }

                                        if (vetorTestes[i].tipoTeste == 1)
                                            {
                                                printf("\t\t PCR");
                                            }
                                        else if (vetorTestes[i].tipoTeste == 2)
                                            {
                                                printf("\t\t Antigenio");
                                            }

                                        printf("\t\t\t %02d/%02d/%4d", vetorTestes[i].dataRealizacao.dia, vetorTestes[i].dataRealizacao.mes, vetorTestes[i].dataRealizacao.ano );

                                        if(vetorTestes[i].resultado == 'P')
                                            {
                                                printf("\t\t Positivo");
                                            }else if (vetorTestes[i].resultado == 'N')
                                            {
                                                printf("\t\t Negativo");
                                            }else if (vetorTestes[i].resultado == 'I')
                                            {
                                                printf("\t\t Inconclusivo");
                                            }else{
                                                printf("\t\t [Sem Registo]");
                                            }

                                            printf("\t [Sem Registo] \t");
                                            printf("\t [Sem Registo]\n");
                            }
                            
                            else if(vetorTestes[i].resultado != '\0' && vetorTestes[i].numUtente == numUtente){ //        verificar se 'e teste realizado analisando se o resultado 'e diferente de vazio && se o numUtente inserido existe no vetorTestes

                                       // printf("\n**Teste Realizado**");

                                        printf("\n %d \t",vetorTestes[i].numUtente);

                                        for (k=0; k< *totTestes; k++){     
                                                if (vetorTestes[i].numUtente == vetorMembros[k].numUtente)  // para interligar os vetores
                                                {
                                                    printf("\t %s", vetorMembros[k].nome);

                                                    if (vetorMembros[k].estadoMembro == 'E')
                                                        {
                                                            printf("\t\t Estudante");
                                                        }
                                                        else if (vetorMembros[k].estadoMembro == 'D')
                                                        {
                                                        printf("\t\t Docente");
                                                        }
                                                        else if (vetorMembros[k].estadoMembro == 'T')
                                                        {
                                                        printf("\t\t Tecnico");
                                                        }
                                                }
                                                
                                        }

                                            if (vetorTestes[i].tipoTeste == 1)
                                                {
                                                    printf("\t\t PCR");
                                                }
                                            else if (vetorTestes[i].tipoTeste == 2)
                                                {
                                                    printf("\t\t Antigenio");
                                                }

                                            printf("\t\t\t %02d/%02d/%4d", vetorTestes[i].dataRealizacao.dia, vetorTestes[i].dataRealizacao.mes, vetorTestes[i].dataRealizacao.ano );

                                            
                                            if(vetorTestes[i].resultado == 'P')
                                            {
                                                printf("\t\t Positivo");
                                            }else if (vetorTestes[i].resultado == 'N')
                                            {
                                                printf("\t\t Negativo");
                                            }else if (vetorTestes[i].resultado == 'I')
                                            {
                                                printf("\t\t Inconclusivo");
                                            }

                                            printf("\t %02d:%02d \t",  vetorTestes[i].horaColheita.hora, vetorTestes[i].horaColheita.min );
                                            printf("\t %02d minutos\n",  vetorTestes[i].tempDuracao);
                                }else if(vetorTestes[i].tipoTeste == -1){
                                    printf("\n Nao existem testes agendados ou realizados por esse membro!");
                                }
                     }
                     for (j=0; j < total; j++)
                    {
                        quantPositivos = contaPositivos(vetorTestes, total, numUtente);
                        if (quantPositivos != 0)
                        {
                            total = j;
                            printf("\n\t %d Teste(s) Positivo(s)", quantPositivos);
                        }else{
                            printf("O Membro nao teve testes positivos");
                        }
                        
                    }
        }
}

int contaPositivos(tipoTeste *vetorTestes, int totTestes, int utente){
    int positivos, i;
    positivos = 0;

    for(i = 0; i < totTestes; i++){
        if(utente == vetorTestes[i].numUtente && vetorTestes[i].resultado == 'P'){
            positivos++;
        }
    }
    return positivos;
}

