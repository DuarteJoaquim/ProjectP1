#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funcoesLeitura.h"
#include "funcoesMembros.h"
#include "funcoesTestes.h" 
#include "funcoesFicheiros.h"

char menu (int totalM, int totTestesAg, int totTestesRea, int totalMemVac);

//////////////////////////////////////////////////////////////

int main()
{
    tipoMembro vetorMembros[MAX_MEMBROS];
    tipoTeste  *vetorTestes; /* Ponteiro (para vetor dinamico) */
    int totMembros, totTestes, totTestesAgendados, totTestesRealizados, totMembrosVacinados;
    char opcao;

    vetorTestes = NULL;    /* Inicializa ponteiro para vetor dinamico */           
    
    totMembros = 0;				/* inicia contadores */
    totTestes = 0;
    totTestesAgendados = 0;
    totTestesRealizados = 0;
    totMembrosVacinados = 0;

    do
    {
        opcao = menu(totMembros, totTestesAgendados, totTestesRealizados, totMembrosVacinados);

        switch (opcao)
        {
        case 'I':
                totMembros = inserirMembro(vetorMembros, totMembros);
            break;
        case 'V':
                atualizarVacinado(vetorMembros, totMembros);
                totMembrosVacinados = contarMembrosVacinados(vetorMembros,totMembros);
            break;
        case 'C':
                atualizarConfinamento(vetorMembros, totMembros);
            break;
        case 'A':
                vetorTestes = agendarTeste(vetorTestes, vetorMembros, &totTestes, &totTestesAgendados , totMembros);
            break;

        case '1':
                mostrarDadosMembros(vetorMembros, totMembros, vetorTestes, totTestes);
            break;
        case '2':
                mostrarDadosTestes(vetorTestes, &totTestes, vetorMembros, totMembros);
            break;
        case '3':
                mostrarTestesUtilizador(vetorTestes, &totTestes, vetorMembros, totMembros);
            break;
        case '4':
                listarConfinamento(vetorMembros,totMembros);
            break;
        case 'R':
                vetorTestes = inserirTesteRealizado(vetorTestes, &totTestes, &totTestesRealizados, &totTestesAgendados, vetorMembros, totMembros);
            break;
        case 'G':
                gravaFicheiroBinario_Todos(vetorMembros,totMembros,vetorTestes,totTestes,totTestesAgendados,totTestesRealizados,totMembrosVacinados);
            break;
        case 'L':
                vetorTestes = leFicheiroBinario_Todos(vetorMembros,&totMembros,vetorTestes,&totTestes,&totTestesAgendados,&totTestesRealizados,&totMembrosVacinados);
            break;
        case 'E':
                fEstatistica(vetorMembros,totMembros,totTestes,vetorTestes,totTestesRealizados);
            break;
                
        }
    }while(opcao != 'T');

    free(vetorTestes); /* Liberta memoria do vetor din�mico */

    return 0;

}

char menu (int totalM, int totTestesAg, int totTestesRea, int totalMemVac)
{
    char op;

    printf("\n\n\n********* Menu Principal ********* \n");
    printf("\n Quantidade de membros da comunidade: %d \n Quantidade de testes agendados: %d \n Quantidade de testes realizados: %d \n Quantidade de membros vacinados: %d \n", totalM, totTestesAg, totTestesRea, totalMemVac);
    //printf("\n Total Testes: %d \n", totT);
    printf("\n I - Inserir Novo Membro");
    printf("\n V - Atualizar Estado de Vacinacao");
    printf("\n C - Atualizar Estado de Confinamento");
    printf("\n A - Agendar Novo Teste");
    printf("\n R - Inserir Teste Realizado");
    printf("\n E - Estatistica");
    printf("\n 1 - Mostrar Dados Membros");
    printf("\n 2 - Mostrar Dados de Todos os Testes");
    printf("\n 3 - Mostrar Dados dos Testes de um Membro");
    printf("\n 4 - Mostrar Dados Confinamentos");
    printf("\n G - Gravar Ficheiro");
    printf("\n L - Ler Ficheiro");

    printf("\n\n T - Terminar Programa");
    printf("\n\n \t\t Opcao (I,V,C,M,A ou T(erminar) ) --> ");

    op = getchar();
    op = toupper(op);
    limpaBufferStdin();

    return op; 	/* Devolve opcao selecionada pelo utilizador */
}

