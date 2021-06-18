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

    TAtomo *primeiro;
    TAtomo *ultimo;
    int numElem;

}TDLEnc;

int ehMinuscula(char c);
int numInstrucao( char instrucao[]);
void criarLista(TDLEnc *lista);
Boolean vaziaLista(TDLEnc *lista);
void imprimirLista(TDLEnc *lista);
Boolean listaUnitaria(TDLEnc *lista);
int inserirElemento(TDLEnc *lista, char st[]);
//int pegarInstrucao(char st[], char instrucao[]);


#endif // RACIONAL_H_INCLUDED