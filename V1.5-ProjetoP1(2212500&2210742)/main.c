#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MEMBROS 200

typedef struct
{
    int dia;
    int mes;
    int ano;
} tipoData;


typedef struct
{
    int hora;
    int min;
} tipoHora;


typedef struct
{
    int numUtente;
    char nome[50];
    char estadoMembro; //((E)studante, (D)ocente ou (T)�cnico)
    tipoData anoNascimento;
    int estadoConfinamento;//((0)n�o confinado,(1) quarentena ou (2)isolamento profil�tico)
    int diasConfinamento;
    tipoData dataConfinamento;
    int estadoVacinacao;// ((0)sem vacina,(1) dose1,(2) dose2 ou (3)dose3)
    tipoData ultimaVacina;

} tipoMembro;

typedef struct
{
    int tipoTeste; //(PCR,Antigenio)
    tipoData dataRealizacao;
    int numUtente;
    char resultado;//(p)ositivo, (n)egativo ou (i)nconclusivo
    tipoHora horaColheita;
    int tempDuracao;
} tipoTeste;


char menu (int totalM, int totTestesAg, int totTestesRea, int totalMemVac);
tipoMembro lerDadosMembro (void);
int inserirMembro(tipoMembro vetorMembros[],int totMembros);
int procuraMembro(tipoMembro vetorMembros[],int totMembros, int numUtente);

void atualizarConfinamento(tipoMembro vetorMembros[],int totMembros);
void atualizarVacinado(tipoMembro vetorMembros[],int totMembros);
int contarMembrosVacinados(tipoMembro vetorMembros[],int totMembros);
void mostrarDadosMembros(tipoMembro vetorMembros[], int totMembros);

int contaTestesPCR(tipoTeste vetorTestes[],int totTestes, int totMembros, int dataDia, int dataMes, int dataAno);
tipoTeste *agendarTeste(tipoTeste *vetorTestes, tipoMembro vetorMembros[],int *totTestes, int *totTestesAgendados, int totMembros);
tipoTeste *inserirTesteRealizado(tipoTeste *vetorTestes,int *totTestes, int *totTestesRealizados, int *totTestesAgendados, tipoMembro vetorMembros[], int totMembros);
void mostrarDadosTestes(tipoTeste *vetorTestes,int *totTestes, tipoMembro vetorMembros[], int totMembros);
void mostrarTestesUtilizador(tipoTeste *vetorTestes,int *totTestes, tipoMembro vetorMembros[], int totMembros);
int contaPositivos(tipoTeste *vetorTestes, int totTestes, int utente);

void listarConfinamento(tipoMembro vetorMembros[],int totMembros);

void *leFicheiroBinario_Todos(tipoMembro vetorMembros[],int *totMembros, tipoTeste vetorTestes[], int *totTestes,int *totTestesAgendados, int *totTestesRealizados,int *totMembrosVacinados);
void gravaFicheiroBinario_Todos(tipoMembro vetorMembros[], int totMembros, tipoTeste vetorTestes[], int totTestes,int totTestesAgendados,int totTestesRealizados,int totMembrosVacinados);

void limpaBufferStdin(void);
int lerInteiro(int min, int max);
void lerString(char vetor[], int max);
tipoData lerData(void);
tipoHora lerHora(void);



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

        case '1':
                mostrarDadosMembros(vetorMembros, totMembros);
            break;
        case '2':
                mostrarDadosTestes(vetorTestes, &totTestes, vetorMembros, totMembros);
            break;
                break;
        case '3':
                mostrarTestesUtilizador(vetorTestes, &totTestes, vetorMembros, totMembros);
            break;
        case '4':
                listarConfinamento(vetorMembros,totMembros);
            break;
        case 'A':
                vetorTestes = agendarTeste(vetorTestes, vetorMembros, &totTestes, &totTestesAgendados , totMembros);
            break;
        case 'R':
                vetorTestes = inserirTesteRealizado(vetorTestes, &totTestes, &totTestesRealizados, &totTestesAgendados, vetorMembros, totMembros);
            break;
        case 'G':
                gravaFicheiroBinario_Todos(vetorMembros,totMembros,vetorTestes,totTestes,totTestesAgendados,totTestesRealizados,totMembrosVacinados);
           // gravaFicheiroTexto(vetorEstudantes, totEstudantes);
            break;
        case 'U':
                vetorTestes = leFicheiroBinario_Todos(vetorMembros,&totMembros,vetorTestes,&totTestes,&totTestesAgendados,&totTestesRealizados,&totMembrosVacinados);
           // totEstudantes=leFicheiroBinario(vetorEstudantes);leFicheiroBinario(tipoMembro vetorMembros[MAX_MEMBROS],tipoTeste*vetorTestes,*totTestes)
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
    printf("\n 1 - Mostrar Dados Membros");
    printf("\n 2 - Mostrar Dados de Todos os Testes");
    printf("\n 3 - Mostrar Dados dos Testes de um Membro");
    printf("\n 4 - Mostrar Dados Confinamentos");

    printf("\n\n T - Terminar Programa");
    printf("\n\n \t\t Opcao (I,V,C,M,A ou T(erminar) ) --> ");

    op = getchar();
    op = toupper(op);
    limpaBufferStdin();

    return op; 	/* Devolve opcao selecionada pelo utilizador */
}

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

void mostrarDadosMembros(tipoMembro vetorMembros[], int totMembros)
{
    int i;

    if (totMembros == 0)
    {
        printf("\n Não existem membros inscritos!");
    }
    else
    {
        printf("\nNumero Utente \t Nome \t\t Tipo de Membro \t Estado Vacinacao \t Estado Confinamento ");
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
                printf("\t\t [Sem Registo]");
            }
        }
    }
}

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
                        printf("%d PCR's na Data Inserida", totalPCR);
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
                            vetorTestes[*totTestes].tipoTeste = dadosTeste.tipoTeste; // para os dados irem para o ultimo espaco do vetor
                            vetorTestes[*totTestes].numUtente = dadosTeste.numUtente; 
                            vetorTestes[*totTestes].dataRealizacao.dia = dadosTeste.dataRealizacao.dia;
                            vetorTestes[*totTestes].dataRealizacao.mes = dadosTeste.dataRealizacao.mes; 
                            vetorTestes[*totTestes].dataRealizacao.ano = dadosTeste.dataRealizacao.ano; 
                            vetorTestes[*totTestes].resultado = '\0'; 
                            vetorTestes[*totTestes].horaColheita.hora = -1; 
                            vetorTestes[*totTestes].horaColheita.min = -1; 
                            vetorTestes[*totTestes].tempDuracao = -1;

                            (*totTestesAgendados)++;
                            (*totTestes)++;
                            printf("\nAgendado com sucesso");
                        
                    }
    return vetorTestes;
}

tipoTeste *inserirTesteRealizado(tipoTeste *vetorTestes, int *totTestes, int *totTestesRealizados, int *totTestesAgendados, tipoMembro vetorMembros[], int totMembros){

    tipoTeste dadosTeste;
    tipoTeste *paux; /* ponteiro para restaurar valor de vFunc  */
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
                                }else{
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

                                            printf("Hora da Colheita: ");
                                            dadosTeste.horaColheita = lerHora();

                                            printf("Tempo de Duracao(0min a 59min): ");
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

                                                // printf(" \n %d numUtente do ultimo membro inserido",vetorTestes[*totTestes].numUtente); // #TESTE# // #TESTE# // #TESTE# // #TESTE# // #TESTE#
                                                // printf(" \n %d numUtente do ultimo membro inserido",vetorTestes[*totTestes].numUtente);  // #TESTE# // #TESTE# // #TESTE# // #TESTE# // #TESTE#

                                                (*totTestes)++;
                                                printf(" \n %d totTestes", *totTestes);
                                                printf("\nTeste Realizado com sucesso");
                                }
                        }else{
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

                                                printf("Hora da Colheita: ");
                                                vetorTestes[pos].horaColheita = lerHora();

                                                printf("Tempo de Duracao(0min a 59min): ");
                                                vetorTestes[pos].tempDuracao = lerInteiro(0,59);

                                                (*totTestesAgendados)--;
                                                (*totTestesRealizados)++;
                                                // if Condicao, break the loop
                                               /* if (vetorTestes[pos].numUtente == numUtente) {
                                                    (*totTestes)--;
                                                    break;
                                                }*/
                                        }
                                    else{                     //caso nao exista adiciona +1 espaco no vetor
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
                                            printf("Hora da Colheita: ");
                                            dadosTeste.horaColheita = lerHora();

                                            printf("Tempo de Duracao(0min a 59min): ");
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
                                                    // dadosTeste.dataRealizacao = -1;
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
                                                    
                                                }
                                        }    
                                       /* if (vetorTestes[pos].numUtente == numUtente) {
                                                    break;
                                                    }   */
                                    }
                                        vetorTestes[*totTestes].tipoTeste = dadosTeste.tipoTeste; // para os dados irem para o ultimo espaco do vetor
                                        vetorTestes[*totTestes].numUtente = dadosTeste.numUtente; 
                                        vetorTestes[*totTestes].dataRealizacao.dia = dadosTeste.dataRealizacao.dia;
                                        vetorTestes[*totTestes].dataRealizacao.mes = dadosTeste.dataRealizacao.mes; 
                                        vetorTestes[*totTestes].dataRealizacao.ano = dadosTeste.dataRealizacao.ano; 
                                        vetorTestes[*totTestes].resultado = dadosTeste.resultado; 
                                        vetorTestes[*totTestes].horaColheita = dadosTeste.horaColheita; 
                                        vetorTestes[*totTestes].tempDuracao = dadosTeste.tempDuracao; 

                                       // printf(" \n %d numUtente do ultimo membro inserido",vetorTestes[*totTestes].numUtente); // #TESTE# // #TESTE# // #TESTE# // #TESTE# // #TESTE#
                                       // printf(" \n %d numUtente do ultimo membro inserido",vetorTestes[*totTestes].numUtente);  // #TESTE# // #TESTE# // #TESTE# // #TESTE# // #TESTE#

                                        (*totTestes)++;
                                        printf(" \n %d totTestes", *totTestes);
                                        printf("\nTeste Realizado com sucesso");

                               
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
                if(vetorTestes[i].resultado == '\0'){ //        verificar se 'e teste agendado analisando se o resultado se encontra vazio
                        //printf("**Teste Agendado**");
                        //printf("\nNumero Utente \t Nome \t Tipo de Membro \t Tipo Teste Agendado \t Data de Agendamento ");

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
                
                else if(vetorTestes[i].resultado != '\0'){ //verificar se e realizado

                            //printf("**Teste Realizado**");
                            //printf("\nNumero Utente \t Nome \t Tipo de Membro \t Tipo Teste Realizado \t Data de Realizacao \t Resultado \t Hora da Colheita \t Duracao");

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


/*!!!!!!!!!!!!FUNCOES EM MANUTENCAO!!!!!!!!!!!!!!!!

void mostrartestes(tipoTeste *testes.int quantidadeTestes){

    int i;

    for(i=0; i<quantidadeTestes; i++){
        displayteste(*testes[i]);
    }
}


void displayteste (tipoTeste*testes[]){


    printf("Numero utente",*testes[i].numUtente);
    printf("dataAgendada",*testes[i].dataAgendada);
    printf("tipoTeste",*testes[i].tipoTeste);
    printf("resultado",*testes[i].resultado);
    printf("tempDuracao",*testes[i].tempDuracao);
    printf("horaColheita",*testes[i].horaColheita);
}

///////////////////////////////////////////////


void fEstatistica(tipoMembro vetorMembros[],int totMembros){

int i,numEstudantes,numTecnicos,numDocentes;

for(i=0;i<totMembros;i++){

        if(vetorMembros[i].estadoMembro =='E'){                 // conta o numero de cada tipo de membro existente nas variaveis num numEstudantes,numTecnicos,numDocentes para depois dar printf

            numEstudantes++;
        }

        if(vetorMembros[i].estadoMembro =='T'){

            numTecnicos++;
        }

        if(vetorMembros[i].estadoMembro =='D'){

            numDocentes++;
        }

    }
}

*/

void listarConfinamento(tipoMembro vetorMembros[],int totMembros){
    int i, confinados;

    confinados = 0 ;

    for(i=0;i<totMembros;i++){

        if(vetorMembros[i].estadoConfinamento == 1 || vetorMembros[i].estadoConfinamento == 2){

            printf("\nMembro:%s\t Utente:%d",vetorMembros[i].nome,vetorMembros[i].numUtente);
            printf("\tConfinamento:");
            if (vetorMembros[i].estadoConfinamento == 1)
            {  
               printf("\t Quarentena");
            }  
            if (vetorMembros[i].estadoConfinamento == 2)
            {
               printf("\t Isolamento Profilatico");

            }
            printf("\t\tData de confinamento:%d/%d/%d",vetorMembros[i].dataConfinamento.dia,vetorMembros[i].dataConfinamento.mes,vetorMembros[i].dataConfinamento.ano);

            printf("\tDuracao da quarentena : %d dias",vetorMembros[i].diasConfinamento);

            confinados++;

        }


    }

            if (confinados == 0){

            printf("Sem Registo de Confinamentos");

            }   

}


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
//FICHEIROS          



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

