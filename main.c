#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 80
#define NOT_FOUND -1 // Item não existe
#define OK 0 // Operação realizada com sucesso
#define LIST_EMPTY 2 // Lista vazia
#define NO_SPACE 3 // Não há espaço de memória

typedef enum Boolean{FALSE = 0, TRUE = 1}Boolean;

typedef struct TInfo
{
    char frase[MAX];
    Boolean linhaCorrente;
    int numLinha;
}TInfo;


typedef struct TAtomo
{
    TInfo info;
    struct TAtomo *eprox;
    struct TAtomo *dprox;
    
}TAtomo;

typedef struct TDLEnc{

    TAtomo *primeiro;

}TDLEnc;

int ehMinuscula(char c)
{
    if(c>='a' && c<='z') return 1;
    return 0;
}

int numInstrucao( char instrucao[]){

    if(strcmp(instrucao,"$inserir") == 0){
        return 1;
    }
    if(strcmp(instrucao,"$remover")  == 0){
        return 2;
    }
    if(strcmp(instrucao,"$linha")  == 0){
        return 3;
    }
    if(strcmp(instrucao,"$localizar") == 0){
        return 4;
    }
    if(strcmp(instrucao,"$alterar") == 0){
        return 5;
    }
    if(strcmp(instrucao,"$ultimo") == 0){
        return 6;
    }
    if(strcmp(instrucao,"$imprimir") == 0){
        return 7;
    }
    if(strcmp(instrucao,"$fim") == 0){
        return 0;
    }
    return -1;
}

void criarLista(TDLEnc *lista){

    lista->primeiro = NULL;
}

Boolean vaziaLista(TDLEnc *lista){

    return (lista->primeiro == NULL);
}

void imprimirLista(TDLEnc *lista){

    for(TAtomo *paux = lista->primeiro; paux->dprox != lista->primeiro; paux = paux ->dprox){
        printf("%s\n", paux->info.frase);
    }
    printf("\n");
}

Boolean listaUnitaria(TDLEnc *lista){

    return (lista->primeiro != NULL && lista->primeiro->dprox == NULL);
}

int inserirElemento(TDLEnc *lista, TInfo info){

    TAtomo *pnovo = (TAtomo*) malloc(sizeof(TAtomo));
    if(pnovo == NULL) return NO_SPACE;
    pnovo->info = info;
    if(vaziaLista(lista)){
        lista->primeiro = pnovo;
    }
    if(listaUnitaria(lista)){
        lista->primeiro->dprox = pnovo;
    }
    else{

        pnovo->eprox = lista->primeiro->eprox;
        pnovo->dprox = lista->primeiro;
    }

    lista->primeiro->eprox = pnovo;
    return OK;
}

//void pegarInstrucao(char inst[], )

int main (){
    char instrucao[10];
    char frase[MAX];
    int num = -2;
    TDLEnc *lista;
    //char instCopy[MAX];
    while(num != 0){
        printf("Entre com a instrucao\n");
        //fgets(instrucao,sizeof(instrucao),stdin);
        //scanf("%[^\n]", instrucao);
        scanf("%s", instrucao);
        printf("Instrucao: %s", instrucao);
        //strcpy(instCopy, instrucao);
        //printf("%s", instCopy);
        num = numInstrucao(instrucao);
        printf("%d\n", num);

        if(num == -1){
            printf("Instrucao invalida\n");
        }
        if(num == 0){
            break;
        }
        if(num == 1){
            
         
           
        }    

    }
    printf("Sai\n");
    return 0;
}