#ifndef FUNCOESTESTES_H_INCLUDED
#define FUNCOESTESTES_H_INCLUDED

typedef struct
{
    int tipoTeste; //(PCR,Antigenio)
    tipoData dataRealizacao;
    int numUtente;
    char resultado;//(p)ositivo, (n)egativo ou (i)nconclusivo
    tipoHora horaColheita;
    int tempDuracao;
} tipoTeste;


int contaTestesPCR(tipoTeste vetorTestes[],int totTestes, int totMembros, int dataDia, int dataMes, int dataAno);
tipoTeste *agendarTeste(tipoTeste *vetorTestes, tipoMembro vetorMembros[],int *totTestes, int *totTestesAgendados, int totMembros);
tipoTeste *inserirTesteRealizado(tipoTeste *vetorTestes,int *totTestes, int *totTestesRealizados, int *totTestesAgendados, tipoMembro vetorMembros[], int totMembros);
void mostrarDadosTestes(tipoTeste *vetorTestes,int *totTestes, tipoMembro vetorMembros[], int totMembros);
void mostrarTestesUtilizador(tipoTeste *vetorTestes,int *totTestes, tipoMembro vetorMembros[], int totMembros);
int contaPositivos(tipoTeste *vetorTestes, int totTestes, int utente);

#endif // FUNCOESTESTES_H_INCLUDED
