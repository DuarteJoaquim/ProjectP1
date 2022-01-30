#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funcoesLeitura.h"
#include "funcoesMembros.h"
#include "funcoesTestes.h" 
#include "funcoesFicheiros.h"


/* FICHEIROS */         

void gravaFicheiroBinario_Todos(tipoMembro vetorMembros[], int totMembros, tipoTeste vetorTestes[], int totTestes,int totTestesAgendados,int totTestesRealizados,int totMembrosVacinados)
{
    FILE *ficheiro;

    ficheiro = fopen("dados.dat", "wb");
    if (ficheiro == NULL)
    {
        printf ("Erro ao abrir ficheiro");
    }
    else
    {   fwrite(&totTestesAgendados, sizeof(int), 1, ficheiro);
        fwrite(&totTestesRealizados, sizeof(int), 1, ficheiro);
        fwrite(&totMembrosVacinados, sizeof(int), 1, ficheiro);
        fwrite(&totMembros, sizeof(int), 1, ficheiro);
        fwrite(vetorMembros,sizeof(tipoMembro),totMembros, ficheiro);
        fwrite(&totTestes, sizeof(int), 1, ficheiro); 	// escreve reservas
        fwrite(vetorTestes, sizeof(tipoTeste), totTestes, ficheiro);
        fclose(ficheiro);
    }
}

void *leFicheiroBinario_Todos(tipoMembro vetorMembros[],int *totMembros, tipoTeste *vetorTestes, int *totTestes,int *totTestesAgendados, int *totTestesRealizados,int *totMembrosVacinados)
{
    FILE *ficheiro;

    ficheiro = fopen("dados.dat", "rb");
    if (ficheiro == NULL)
    {
        printf ("Erro ao abrir ficheiro");
        *totTestes = 0;
    }
    else
    {   
        fread(&(*totTestesAgendados), sizeof(int), 1, ficheiro);
        fread(&(*totTestesRealizados), sizeof(int), 1, ficheiro);
        fread(&(*totMembrosVacinados), sizeof(int), 1, ficheiro);

        fread(&(*totMembros), sizeof(int), 1, ficheiro);
        fread(vetorMembros,sizeof(tipoMembro),*totMembros, ficheiro);
        fread(&(*totTestes),sizeof(int),1,ficheiro);

        vetorTestes= realloc(vetorTestes,(*totTestes)*sizeof(tipoTeste));
        if (vetorTestes==NULL && *totTestes!=0)
        {
            printf ("Erro - Impossivel criar vetor dinamico");
            *totTestes = 0;
            *totMembros=0;
        }
        else  		 /* Obtem dados da reserva e armazena no vetor */
        {   
            fread(vetorTestes, sizeof(tipoTeste), *totTestes, ficheiro);
        }
        fclose(ficheiro);
    }
    return vetorTestes;
}

void LogTestesInfo(tipoMembro dadosMembro, tipoTeste dadosTeste)
{
    FILE *ficheiro;
    ficheiro = fopen("TestesInfo.txt", "a");
    if (ficheiro == NULL)
    {
        printf ("Erro ao abrir ficheiro");
    }
    else
    {
        fprintf(ficheiro, "\nNumero Utente \t Nome \t Tipo de Membro \t Tipo Teste Realizado \t Data de Realizacao \t Resultado \t Hora da Colheita \t Duracao");
                        fprintf(ficheiro, "\n %d \t",dadosTeste.numUtente);

                                    fprintf(ficheiro, "\t %s", dadosMembro.nome);

                                    if (dadosMembro.estadoMembro == 'E')
                                        {
                                            fprintf(ficheiro, "\t Estudante");
                                        }
                                        else if (dadosMembro.estadoMembro == 'D')
                                        {
                                        fprintf(ficheiro, "\t Docente");
                                        }
                                        else if (dadosMembro.estadoMembro == 'T')
                                        {
                                        fprintf(ficheiro, "\t Tecnico");
                                        }


                            if (dadosTeste.tipoTeste == 1)
                                {
                                    fprintf(ficheiro, "\t\t PCR");
                                }
                            else if (dadosTeste.tipoTeste == 2)
                                {
                                    fprintf(ficheiro, "\t\t Antigenio");
                                }

                            fprintf(ficheiro, "\t\t\t %02d/%02d/%4d", dadosTeste.dataRealizacao.dia, dadosTeste.dataRealizacao.mes, dadosTeste.dataRealizacao.ano );

                            if(dadosTeste.resultado == 'P')
                                            {
                                                fprintf(ficheiro, "\t\t Positivo");
                                            }else if (dadosTeste.resultado == 'N')
                                            {
                                                fprintf(ficheiro, "\t\t Negativo");
                                            }else if (dadosTeste.resultado == 'I')
                                            {
                                                fprintf(ficheiro, "\t\t Inconclusivo");
                                            }else{
                                                fprintf(ficheiro, "\t\t [Sem Registo]");
                                            }
                                        if(dadosTeste.tempDuracao >= 0 && dadosTeste.tempDuracao <= 59){
                                            fprintf(ficheiro, "\t %02d:%02d \t",  dadosTeste.horaColheita.hora, dadosTeste.horaColheita.min );
                                            fprintf(ficheiro, "\t %02d minutos\n",  dadosTeste.tempDuracao);
                                        }else{
                                            fprintf(ficheiro, "\t [Sem Registo] \t");
                                            fprintf(ficheiro, "\t [Sem Registo]\n");
                                        }

                                        if(dadosMembro.estadoVacinacao == 0 && dadosMembro.estadoVacinacao == 1 && dadosMembro.estadoVacinacao == 2 && dadosMembro.estadoVacinacao == 3){
                                            fprintf(ficheiro,"\t\n %d  Estado confinamento \n", dadosMembro.estadoVacinacao);
                                        }else{
                                            printf("\n");
                                        }

                                        if (dadosMembro.estadoVacinacao == 0)
                                            {
                                            fprintf(ficheiro,"\t\n  Estado confinamento: Sem Vacina\n");
                                            }
                                            else if (dadosMembro.estadoVacinacao == 1)
                                            {
                                            fprintf(ficheiro,"\t\n  Estado confinamento: Dose 1\n");
                                            }
                                            else if (dadosMembro.estadoVacinacao == 2)
                                            {
                                            fprintf(ficheiro,"\t\n  Estado confinamento: Dose 2\n");
                                            }
                                            else if (dadosMembro.estadoVacinacao == 3)
                                            {
                                            fprintf(ficheiro,"\t\n  Estado confinamento: Dose 3\n");
                                            }else{
                                                fprintf(ficheiro,"\n");
                                            }

                            }

                     fclose(ficheiro);
            }
