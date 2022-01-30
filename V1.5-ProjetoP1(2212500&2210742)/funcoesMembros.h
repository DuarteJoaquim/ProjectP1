#ifndef FUNCOESMEMBROS_H_INCLUDED
#define FUNCOESMEMBROS_H_INCLUDED

#define MAX_MEMBROS 200


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
    int totRealizadosIndiv;

} tipoMembro;


tipoMembro lerDadosMembro (void);
int inserirMembro(tipoMembro vetorMembros[],int totMembros);
int procuraMembro(tipoMembro vetorMembros[],int totMembros, int numUtente);

void atualizarConfinamento(tipoMembro vetorMembros[],int totMembros);
void atualizarVacinado(tipoMembro vetorMembros[],int totMembros);
int contarMembrosVacinados(tipoMembro vetorMembros[],int totMembros);
void mostrarDadosMembros(tipoMembro vetorMembros[], int totMembros, tipoTeste *vetorTestes, int totTestes);
void listarConfinamento(tipoMembro vetorMembros[],int totMembros);
void fEstatistica(tipoMembro vetorMembros[],int totMembros,int totTestes,tipoTeste *vetorTestes, int totTestesRealizados);


#endif // FUNCOESMEMBROS_H_INCLUDED