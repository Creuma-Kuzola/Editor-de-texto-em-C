#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#define MAX 80
#define NOT_FOUND -1 // Item não existe
#define OK 0 // Operação realizada com sucesso
#define LIST_EMPTY 2 // Lista vazia
#define NO_SPACE 3 // Não há espaço de memória
#define ERROR 4 // Não há espaço de memória 

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
    struct TAtomo *seguinte;
    struct TAtomo *anterior;
    
}TAtomo;

typedef struct TDLEnc{

    TAtomo *primeiro;
    int numElem;

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
    lista->numElem = 0;
}

Boolean vaziaLista(TDLEnc *lista){

    return (lista->primeiro == NULL && lista->numElem == 0);
}

void imprimirLista(TDLEnc *lista){

    printf("Entrei em imprimir");
    for(TAtomo *paux = lista->primeiro; paux->seguinte != lista->primeiro; paux = paux->seguinte){
        printf("%s\n", paux->info.frase);
    }
    printf("\n");
}

Boolean listaUnitaria(TDLEnc *lista){

    return (lista->primeiro != NULL && lista->numElem == 1);
}

int inserirElemento(TDLEnc *lista, char st[], TAtomo *pnovo){

    strcpy(pnovo->info.frase, st);
    printf("String em inserir: %s",pnovo->info.frase);
    lista->numElem++;
    pnovo->info.numLinha = lista->numElem;
    if(vaziaLista(lista)){
        pnovo->seguinte = pnovo->anterior = NULL;
        lista->primeiro = pnovo;
    }
    if(listaUnitaria(lista)){
        pnovo->seguinte=pnovo->anterior = lista->primeiro;
        lista->primeiro->seguinte = lista->primeiro->anterior = pnovo;  
    }
    else{
        pnovo->anterior = lista->primeiro->anterior;
        pnovo->seguinte = lista->primeiro;
        lista->primeiro->anterior = pnovo;
    }
    return OK;
}

int pegarInstrucao(char st[], char instrucao[])
{
    if(st[0]!= '$')return ERROR;

    for(int i=0; st[i]!= '\0'; i++){


    }
}

int main (){

    char instrucao[10];
    TInfo info;
    int num = -2;
    TDLEnc lista;
    char string[80];
    criarLista(&lista);
    int flagInsercao = 0;
    
    while(num != 0){

        printf("Entre com a instrucao\n");
        scanf("%[^\n]", string);
         __fpurge(stdin);

        num = numInstrucao(string);
        printf("Num: %d\n", num);

        if(num == -1){
            printf("Instrucao invalida\n");
        }
         if(num == 0){
            break;
        } 
        if(num == 1){
            flagInsercao = 1;
        }
        if(num == 2){
            flagInsercao = 0;
        }

        if(flagInsercao == 1){

            while (num == 1)
            {
               scanf("%[^\n]", string);
                 __fpurge(stdin);
               TAtomo *pnovo = (TAtomo*) malloc(sizeof(TAtomo));
               if(pnovo == NULL){
                    printf("E null");
                    return NO_SPACE;
                }
                inserirElemento(&lista,string, pnovo);
                imprimirLista(&lista);
                 printf("Entrei\n");   
            }
        
        }
    }
    //imprimirLista(&lista);
    printf("Sai\n");
    return 0;
}