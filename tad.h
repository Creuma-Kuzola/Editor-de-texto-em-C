#ifndef TAD_H_INCLUDED
#define TAD_H_INCLUDED

#define MAX 80
#define NOT_FOUND -1 // Item não existe
#define OK 0 // Operação realizada com sucesso
#define LIST_EMPTY 2 // Lista vazia
#define NO_SPACE 3 // Não há espaço de memória
#define ERROR -3 // Erro na operacao

typedef enum Boolean{FALSE = 0, TRUE = 1}Boolean;

typedef struct TInfo
{
    char frase[MAX+1];
    Boolean linhaCorrente;
    int numLinha;
}TInfo;

typedef struct TAtomo
{
    TInfo info;
    struct TAtomo *seguinte;
    struct TAtomo *anterior;
    
}TAtomo;

typedef struct TDLEnc{

  struct  TAtomo *primeiro;
  struct  TAtomo *ultimo;
  int numElem;

}TDLEnc;

/* 
  Entrada: Uma string com a instrucao;
  Saída : Um codigo correspondente a instrucao;
  Pré-Condições: A string nao pode ser fazia;
  Pós-Condições: ;

*/
int numInstrucao( char instrucao[]);

/* 
  Entrada: Uma stri;
  Saída : Um codigo correspondente a instrucao;
  Pré-Condições: A string nao pode ser fazia;
  Pós-Condições: ;

*/
void copiarString(char dest[], char orig[]);
void criarLista(TDLEnc *lista);
Boolean vaziaLista(TDLEnc *lista);
void imprimirLista(TDLEnc *lista);
Boolean listaUnitaria(TDLEnc *lista);
int inserirElemento(TDLEnc *lista, char st[]);
Boolean listaUnitaria(TDLEnc *lista);
void imprimirLista(TDLEnc *lista);
void imprimirLinhaMAteN(TDLEnc *lista, int m, int n);
void imprimirUltimo(TDLEnc *lista);
TAtomo *buscarAtomoCorrente(TDLEnc *lista);
int inserirElemento(TDLEnc *lista, char st[]);
int ehCaracterValido(char st[]);
void linha(TDLEnc *lista,int n );
void copiarStringDadoIndice(int indiceInicio, int indiceFim, char destino[],char origem[]);
void pegarN(int indiceInicio, int indiceFim, char destino[],char origem[], int *n);
void pegarM(int indiceInicio, int indiceFim, char destino[],char origem[], int *m);
void pegarNM(char st[], int indiceInicio, int *n, int *m);
void pegarMLinha(char st[], int indiceInicio,int *m);
int pegarInstrucao(char st[], char inst [], int *pos);
TAtomo *buscarAtomoDadaChave(TDLEnc *lista, int chave);
int removerMN(TDLEnc *lista, int n, int m);
void pegarSubstring(char string[], int pos, char subString[]);
int localizarString(TDLEnc *lista, char subs[]);
int encontrardelimitador(char frase [], int pos);
void pegarStringsEmAlterar(char string[], char subString1[], char subString2[]);
TAtomo *pegarAtomo(TDLEnc *lista);
void pegarPosicaoString(TAtomo *paux, char subs[], int *posInicial, int *posFinal);
void alterarString(TDLEnc *lista, char subString1[], char subString2[]);

#endif // RACIONAL_H_INCLUDED