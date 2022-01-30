#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funcoesLeitura.h"
#include "funcoesMembros.h"
#include "funcoesTestes.h" 
#include "funcoesFicheiros.h"

//!!!!!!!!!!!!      MEMBRO      !!!!!!!!!!!!!!!!

tipoMembro lerDadosMembro (void){
    tipoMembro dadosMembro;
    char opcaoTipoMembro;

    printf("Numero de Utente de Saude: ");
    dadosMembro.numUtente = lerInteiro(1,999999);

    printf("Nome: ");
    lerString(dadosMembro.nome,50);

    do {
        printf("Tipo de Membro{E(studante),D(ocente) ou T(ecnico)} : ");
        scanf(" %c",&opcaoTipoMembro);
        opcaoTipoMembro = toupper(opcaoTipoMembro);
        limpaBufferStdin();

    } while (opcaoTipoMembro!='E' && opcaoTipoMembro!='D' && opcaoTipoMembro!='T');
         dadosMembro.estadoMembro = opcaoTipoMembro;


   /* printf("Data de Nascimento: ");
    dadosMembro.anoNascimento = lerData();                EM COMENTARIO TEMPORARIAMENTE      */

    dadosMembro.estadoVacinacao = -1; /* Identificar que estadoVacinacao se encontra por obter  */
    dadosMembro.estadoConfinamento = -1; /* Identificar que estadoConfinamento se encontra por obter */
    dadosMembro.diasConfinamento = 0;
    dadosMembro.totRealizadosIndiv = 0;
    return dadosMembro;
}

int inserirMembro(tipoMembro vetorMembros[],int totMembros){
    tipoMembro dados;
    int pos;

    if (totMembros == MAX_MEMBROS)
    {
        printf("Impossivel acrescentar novos elementos");
    }
    else
    {
        dados = lerDadosMembro();
          pos = procuraMembro(vetorMembros,totMembros,dados.numUtente);
        if (pos != -1)
            {
                printf("\n Esse membro ja existe! - Nao sera acrescentado \n");
            }
        else{
                vetorMembros[totMembros] = dados;
                totMembros++;
        }
    }
    return totMembros;

}

int procuraMembro(tipoMembro vetorMembros[],int totMembros, int numUtente){
    int i;
    int posicao=-1;
    for(i=0; i<totMembros; i++){
        if (vetorMembros[i].numUtente == numUtente) {   /* Encontrado */
            posicao = i;    /* guarda posi��o de numero em vFunc */
            i = totMembros;  /* para concluir pesquisa (sair do for) */
        }
    }
    return posicao;
}

void atualizarConfinamento(tipoMembro vetorMembros[],int totMembros){

    tipoMembro infoMembro;
    int posicao,opcao;

    printf("Numero de utente:\t");
    infoMembro.numUtente = lerInteiro(1,999999);

    posicao = procuraMembro(vetorMembros,totMembros,infoMembro.numUtente);
    if (posicao == -1){
           printf("Esse numero de utente n�o existe.\n");
        }else{
            do {
        printf("\nIntroduza o estado atual de confinamento");
		 printf("\n(0) Nao confinado, (1) Quarentena ou (2) Isolamento profilatico : ");
        scanf("%d", &opcao);

    } while (opcao!=0 && opcao!=1 && opcao!=2);
            vetorMembros[posicao].estadoConfinamento=opcao;
            if(opcao==1 || opcao==2){
            printf("\nIntroduza a data de inicio de confinamento:");
            vetorMembros[posicao].dataConfinamento = lerData();
            printf("\nIndique o n de dias de confinamento:");
            vetorMembros[posicao].diasConfinamento=lerInteiro(1,100);
            }
                       printf("\nRegisto efetuado com sucesso");
        }

}

void atualizarVacinado(tipoMembro vetorMembros[],int totMembros){

    tipoMembro infoMembro;
    int posicao,opcao;

    printf("Numero de utente:\t");
    infoMembro.numUtente= lerInteiro(1,999999);

    posicao = procuraMembro(vetorMembros,totMembros,infoMembro.numUtente);
    if (posicao == -1){
           printf("Esse numero de utente nao existe.\n");
        }else{
            do {
        printf("\nIntroduza o estado atual de vacinacao");
		printf("\n(0) Sem vacina,(1) Dose 1,(2) Dose 2 ou (3) Dose 3\n");
        scanf("%d", &opcao);
        //printf("\nData da ultima vacina:\n");
       // infoMembro.ultimaVacina = lerData(); 
        
    } while (opcao!=0 && opcao!=1 && opcao!=2 && opcao!=3);
            
            vetorMembros[posicao].estadoVacinacao = opcao;
           printf("\nRegisto efetuado com sucesso");
        }
}


int contarMembrosVacinados(tipoMembro vetorMembros[], int totMembros){
    int vacinados, i;
    vacinados = 0;
    for(i=0;i<totMembros;i++){
        if (vetorMembros[i].estadoVacinacao == 1 || vetorMembros[i].estadoVacinacao == 2 || vetorMembros[i].estadoVacinacao == 3){
            vacinados++;
            }else{
                vacinados =+ 0;
            }
    }
    return vacinados;
}

void mostrarDadosMembros(tipoMembro vetorMembros[], int totMembros, tipoTeste *vetorTestes, int totTestes)
{
    int i, k;

    if (totMembros == 0)
    {
        printf("\n Não existem membros inscritos!");
    }
    else
    {
        printf("\nNumero Utente \t Nome \t\t Tipo de Membro \t Estado Vacinacao \t Estado Confinamento \t Testes Realizados");
        for (i=0; i< totMembros; i++)
        {
            printf("\n %d \t\t %s ",vetorMembros[i].numUtente, vetorMembros[i].nome);

            if (vetorMembros[i].estadoMembro == 'E')
            {
                printf("\t Estudante");
            }
            else if (vetorMembros[i].estadoMembro == 'D')
            {
               printf("\t Docente");
            }
            else if (vetorMembros[i].estadoMembro == 'T')
            {
               printf("\t Tecnico");
            }

            if (vetorMembros[i].estadoVacinacao == 0)
            {
                printf("\t\t Sem Vacina");
            }
            else if (vetorMembros[i].estadoVacinacao == 1)
            {
               printf("\t\t Dose 1");
            }
            else if (vetorMembros[i].estadoVacinacao == 2)
            {
               printf("\t\t Dose 2");
            }
            else if (vetorMembros[i].estadoVacinacao == 3)
            {
               printf("\t\t Dose 3");
            }else{
                printf("\t\t [Sem Registo]");
            }

            if (vetorMembros[i].estadoConfinamento == 0)
            {
                printf("\t\t\t Nao Confinado");
            }
            else if (vetorMembros[i].estadoConfinamento == 1)
            {
               printf("\t\t Quarentena");
            }
            else if (vetorMembros[i].estadoConfinamento == 2)
            {
               printf("\t\t Isolamento Profilatico");
            }else{
                printf("\t\t [Sem Registo]\t");
            }

             printf("\t %d \t",vetorMembros[i].totRealizadosIndiv);

                //DADOS TESTES AGENDADOS DO MESMO MEMBRO
                    for (k=0; k < totTestes; k++)
                {
                    if(vetorTestes[k].resultado == '\0' && vetorTestes[k].numUtente == vetorMembros[i].numUtente){ 
                    //        verificar se 'e teste agendado analisando se o resultado se encontra vazio && se o numUtente[vetorMembros] 'e igual ao numUtente[vetorTestes]
                    //                                          (para mostrar apenas os dados agendados e do membro a ser listado)
                        printf("\nDados dos testes agendados\n");
                        printf("\nTipo Teste Agendado \t Data de Agendamento \t \n");
                        if (vetorTestes[k].tipoTeste == 1)
                                                {
                                                    printf("PCR");
                                                }
                                            else if (vetorTestes[k].tipoTeste == 2)
                                                {
                                                    printf("\t\t Antigenio");
                                                }

                                            printf("\t\t\t %02d/%02d/%4d\n", vetorTestes[k].dataRealizacao.dia, vetorTestes[k].dataRealizacao.mes, vetorTestes[k].dataRealizacao.ano);
                    }
                }   
        }
    }
}

void listarConfinamento(tipoMembro vetorMembros[],int totMembros){
    int i, confinados;

    confinados = 0 ;
if (totMembros == 0)
    {
        printf("\n Não existem membros inscritos!");
    }else{
         printf("\nMembro \t Utente \t Confinamento \t Data de confinamento \t Duracao da quarentena");
    for(i=0;i<totMembros;i++){
        if(vetorMembros[i].estadoConfinamento == 1 || vetorMembros[i].estadoConfinamento == 2){

            printf("\n %s\t %d",vetorMembros[i].nome,vetorMembros[i].numUtente);
            if (vetorMembros[i].estadoConfinamento == 1)
            {  
               printf("\t Quarentena");
            }  
            if (vetorMembros[i].estadoConfinamento == 2)
            {
               printf("\t Isolamento Profilatico");

            }
            printf("\t\t %d/%d/%d",vetorMembros[i].dataConfinamento.dia,vetorMembros[i].dataConfinamento.mes,vetorMembros[i].dataConfinamento.ano);

            printf("\t\t %d dias",vetorMembros[i].diasConfinamento);

            confinados++;

        }


    }

            if (confinados == 0){

            printf("Sem Registo de Confinamentos");

            }   
    }
}

void fEstatistica(tipoMembro vetorMembros[],int totMembros,int totTestes,tipoTeste *vetorTestes, int totTestesRealizados)
{

    int i,numEstudantes,numTecnicos,numDocentes,menor,a;
    float mediaTestesTempo,testesInconclusivos;
    tipoData menorTeste;
    mediaTestesTempo = 0, numDocentes = 0, numEstudantes = 0, numTecnicos = 0;
    testesInconclusivos= 0;
    menor = vetorMembros[0].totRealizadosIndiv;

    printf("Estatistica\n");


    for(i=0;i<totMembros;i++)
    {

        if(vetorMembros[i].estadoMembro =='E'){       // conta o numero de cada tipo de membro existente nas variaveis num numEstudantes,numTecnicos,numDocentes para depois dar printf

            numEstudantes++;
        }

        if(vetorMembros[i].estadoMembro =='T'){

            numTecnicos++;
        }

        if(vetorMembros[i].estadoMembro =='D'){

            numDocentes++;
        }
    }


        for(i=0;i<totTestes;i++)
    {
        mediaTestesTempo =(float) mediaTestesTempo + vetorTestes[i].tempDuracao;
        if(vetorTestes[i].resultado == 'I')
        {
            testesInconclusivos++;

        }
    }
        testesInconclusivos = (testesInconclusivos/totTestesRealizados)*100;
        mediaTestesTempo = (mediaTestesTempo/totTestesRealizados);

            
                printf("Numero de Estudantes : %d\n",numEstudantes);
                printf("Numero de Docentes : %d\n",numDocentes);
                printf("Numero de Tecnicos : %d\n",numTecnicos);
                if( totTestes == 0){

                    printf("Sem testes realizados");
                }
                else{

                printf("Tempo Medio de duracao de cada Teste : %.2fmin\n",mediaTestesTempo);
                printf("Percentagem testes inconclusivos : %.2f%%\n",testesInconclusivos);
                }
        if (totMembros == 0) {
            // Sem membros registados
        }
        else 
        {       

                menor = vetorMembros[0].totRealizadosIndiv;

                for (i=1; i<totMembros; i++) 
                {

                    if (vetorMembros[i].totRealizadosIndiv<menor)
                    {

                    menor = vetorMembros[i].totRealizadosIndiv;
                    }
                }
                printf("\nMembro(s) com menos testes:\n");
                for (i=0;i<totMembros;i++)
                {
                    if (vetorMembros[i].totRealizadosIndiv == menor)
                    {
                        
                        printf("\nNome: %s Testes Realizados: %d ",vetorMembros[i].nome,vetorMembros[i].totRealizadosIndiv);


                    }

                }
            
        }
    

        if (totTestes == 0) 
        {

        }
        
        else 
        
        {   
            
            for(a=0;a<totTestes;a++){

                if(vetorTestes[a].tempDuracao>=0){                                      //Identifica o primeiro Teste realizado no Vetor Testes 

                    menorTeste = vetorTestes[a].dataRealizacao;

                    a = totTestes;
                }

                
            }


            for (i=1; i<totTestes; i++) 
            {

                if (vetorTestes[i].dataRealizacao.ano>menorTeste.ano && vetorTestes[i].tempDuracao>=0)
                {

                    menorTeste = vetorTestes[i].dataRealizacao;

                }
                else                                                                                                        //Compara a data dos testes realizados uns com os outros
                {
                    
                    if(vetorTestes[i].dataRealizacao.mes>menorTeste.mes){

                        menorTeste = vetorTestes[i].dataRealizacao;


                    }

                        else
                        {

                            if(vetorTestes[i].dataRealizacao.dia>menorTeste.dia)
                            {
                                menorTeste = vetorTestes[i].dataRealizacao;

                            }

                        }

                    

                }

            }
                printf("\n\nTeste(s) Mais Recente(s):\n");
            for (i=0;i<totTestes;i++)
            {
                    
                if (vetorTestes[i].dataRealizacao.ano == menorTeste.ano && vetorTestes[i].tempDuracao>=0)                                       //Imprime os testes realizados mais recentes
                {
                    if(vetorTestes[i].dataRealizacao.mes == menorTeste.mes){

                        if(vetorTestes[i].dataRealizacao.dia == menorTeste.dia){

                            printf("\nTipo de Teste: ");
                            if (vetorTestes[i].tipoTeste == 1)
                                {
                                    printf("\t\t PCR");
                                }
                            else if (vetorTestes[i].tipoTeste == 2)
                                {
                                    printf("\t\t Antigenio");
                                }
                            printf("\t Data:%d/%d/%d",vetorTestes[i].dataRealizacao.ano,vetorTestes[i].dataRealizacao.mes,vetorTestes[i].dataRealizacao.dia);

                        }


                    }
                    


                }

            }





        
        }
              
}
