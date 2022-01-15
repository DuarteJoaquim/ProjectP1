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
    char tipoTeste; //(PCR,Antigenio)
    tipoData dataRealizacao;
    int numUtente;
    char resultado;//(p)ositivo, (n)egativo ou (i)nconclusivo
    tipoHora horaColheita;
    char tempDuracao;
    tipoData dataAgendada;
} tipoTeste;


char menu (int totalM, int totTestesAg, int totTestesRea, int totalMemVac);
tipoMembro lerDadosMembro (void);
int inserirMembro(tipoMembro vetorMembros[],int totMembros);
int procuraMembro(tipoMembro vetorMembros[],int totMembros, int numUtente);

void atualizarConfinamento(tipoMembro vetorMembros[],int totMembros);
void atualizarVacinado(tipoMembro vetorMembros[],int totMembros);
int contarMembrosVacinados(tipoMembro vetorMembros[],int totMembros);
void mostrarDadosMembros(tipoMembro vetorMembros[], int totMembros);

void agendarTeste(tipoTeste vetorTestes[],int quantidadeTestes);
int contaTestes (tipoTeste vetorTestes[],int quantidadeTestes,tipoData data);

void listarConfinamento(tipoMembro vetorMembros[],int totMembros);

void limpaBufferStdin(void);
int lerInteiro(int min, int max);
void lerString(char vetor[], int max);
tipoData lerData(void);



int main()
{
    tipoMembro vetorMembros[MAX_MEMBROS];
    tipoTeste  vetorTestes[50];
    int totMembros, totTestesAgendados, totTestesRealizados, totMembrosVacinados;
    char opcao;

    totMembros = 0;				/* inicia contadores */
    totTestesAgendados = 0;
    totTestesRealizados = 0;
    totMembrosVacinados = 0;

    do
    {
        //mostrarTestes(vetorTestes,totMembros,&totTestesAgendados,&totTestesRealizados);

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

        case 'M':
                mostrarDadosMembros(vetorMembros, totMembros);
            break;
        case 'L':
                listarConfinamento(vetorMembros,totMembros);
            break;
        /*case 'G':
           // gravaFicheiroBinario(vetorEstudantes, totEstudantes);
           // gravaFicheiroTexto(vetorEstudantes, totEstudantes);
            break;
        case 'L':
           // totEstudantes=leFicheiroBinario(vetorEstudantes);
            break;

      */

        }
    }while(opcao != 'F');


    return 0;

}

char menu (int totalM, int totTestesAg, int totTestesRea, int totalMemVac)
{
    char op;

    printf("\n\n\n********* Menu Principal ********* \n");
    printf("\n Quantidade de membros da comunidade: %d \n Quantidade de testes agendados: %d \n Quantidade de testes realizados: %d \n Quantidade de membros vacinados: %d \n", totalM, totTestesAg, totTestesRea, totalMemVac);

    printf("\n I - Inserir Novo Membro");
    printf("\n V - Atualizar Estado de Vacinacao");
    printf("\n C - Atualizar Estado de Confinamento");
    printf("\n M - Mostrar Dados Membros");
    printf("\n L - Mostrar Confinamentos");
    /*printf("\n G - Gravar dados em ficheiro");
    printf("\n L - Ler dados de ficheiro");*/
    printf("\n T - Terminar Programa");
    printf("\n \t\t Opcao (I,V,C,M ou T(erminar) ) --> ");

    op = getchar();
    op = toupper(op);
    limpaBufferStdin();

    return op; 	/* Devolve opcao selecionada pelo utilizador */
}



tipoMembro lerDadosMembro (void){
    tipoMembro dadosMembro;
    char opcaoTipoMembro;

    printf("Numero de Utente de Saude: ");
    dadosMembro.numUtente = lerInteiro(1,9999999);

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

    dadosMembro.estadoVacinacao = -1; /* Identificar que estadoVacinacao se encontra como (sem vacina) */
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
    for(i=0;i<totMembros;i++){
        if (vetorMembros[i].estadoVacinacao == 1 || vetorMembros[i].estadoVacinacao == 2 || vetorMembros[i].estadoVacinacao == 3){
                vacinados++;
        }else{vacinados =+ 0;
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

/**/

//!!!!!!!!!!!!FUNCOES EM MANUTENCAO!!!!!!!!!!!!!!!!a

/*

void agendarTeste(tipoTeste vetorTestes[],int quantidadeTestes){

    tipoMembro infoMembro;
    tipoData data;
    int posicao,opcao,a;

    infoMembro.numUtente= lerInteiro("Insira o n� de utente:", 1,999999);
    posicao = procuraMembro(vetorMembros,totMembros,infoMembro.numUtente);

    if (posicao == -1){
           printf("Esse numero de utente n�o existe.\n");
        }else{
            vetorTestes.numUtente = infoMembro.numUtente;

            printf("Insira a data do Teste\n");

            data = lerData();
            a = contatestes(vetorTestes,quantidadeTestes,data);

            if(a>=15){

                printf ("N�o � poss�vel fazer mais testes neste dia");
            }
            else{

                do {
                printf("Insira o tipo de Teste\n");
                printf("(1)PCR ||(2)Antigeneo");
                scanf("%d", &opcao);

    }           while (opcao!=1 && opcao!=2);
            }

            vetorTestes.tipoTeste[quantidadetestes]=opcao;

           printf("\nRegisto efetuado com sucesso");

        }
}


int contaTestes (tipoTeste vetorTestes[],int quantidadeTestes,tipoData data){

    int a,i;
    a = 0;
    

    for(i=0; i<quantidadeTestes; i++){
        if (vetorTestes[i].dataAgendada == data) {
            i = quantidadeTestes;
            if(vetorTestes[i].tipoTeste== 1){

                 a = a+1;

            }
        }
    }

    return a;
}



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

*/


/*void fEstatistica(tipoMembro vetorMembros[],int totMembros){

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
/* Funcoes para leitura de dadosaa */

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

void limpaBufferStdin(void) 	/* Chamar ap�s leituras de dados atrav�s do teclado */{
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

    printf("\n Ano (%d a %d): ",1900,2100);
    data.ano = lerInteiro(1900,2100);

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
