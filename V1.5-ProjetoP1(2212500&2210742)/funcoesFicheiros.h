#ifndef FUNCOESFICHEIROS_H_INCLUDED
#define FUNCOESFICHEIROS_H_INCLUDED

void *leFicheiroBinario_Todos(tipoMembro vetorMembros[],int *totMembros, tipoTeste vetorTestes[], int *totTestes,int *totTestesAgendados, int *totTestesRealizados,int *totMembrosVacinados);
void gravaFicheiroBinario_Todos(tipoMembro vetorMembros[], int totMembros, tipoTeste vetorTestes[], int totTestes,int totTestesAgendados,int totTestesRealizados,int totMembrosVacinados);
void LogTestesInfo(tipoMembro dadosMembro, tipoTeste dadosTeste);

#endif // FUNCOESFICHEIROS_H_INCLUDED