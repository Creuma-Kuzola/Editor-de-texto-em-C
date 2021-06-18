#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "tad.h"
#include <ctype.h>

int ehMinuscula(char c)
{
    if(c>='a' && c<='z') return 1;
    return 0;
}

int numInstrucao( char instrucao[]){

    if(instrucao[0] == '$'){
        
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
            return 8;
        }
           return -1;
    }
    return -1;
    
}

void copiarString(char dest[], char orig[]){
    
    int i=0;
    for(;orig[i] != '\0';i++)
    {
        dest[i] = orig[i];
    }
    dest[i]='\0';
}

void criarLista(TDLEnc *lista){

    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->numElem = 0;
    printf("Lista criada com sucesso\n");
}

Boolean vaziaLista(TDLEnc *lista){

    return (lista->primeiro == NULL &&  lista->ultimo == NULL && lista->numElem == 0);
}

Boolean listaUnitaria(TDLEnc *lista){

    return (lista->primeiro != NULL && lista->ultimo != NULL && lista->numElem == 1);
}

void imprimirLista(TDLEnc *lista){

    for(TAtomo *paux = lista->primeiro; paux != NULL; paux = paux->seguinte)
    {
        printf("%d %s\n",paux->info.numLinha, paux->info.frase);
    }
}

void imprimirLinhaMAteN(TDLEnc *lista, int m, int n){

    if(lista != NULL){

        if(m >= 1 && n <= lista->ultimo->info.numLinha){
           
            for(TAtomo *paux = lista->primeiro; paux != NULL; paux = paux->seguinte)
            {
                if( paux->info.numLinha >= m && paux->info.numLinha <= n){
                    printf("%d %s\n",paux->info.numLinha, paux->info.frase);
                }
                
            }
        }
        else if(m < 1){
            printf("Erro: o M é menor do que 1\n");
        }
        else if(n > lista->ultimo->info.numLinha){
            printf("Erro: o N é maior do o que número da última linha\n");
        }
        
    }
    else{
        printf("Erro: Lista Vazia");
    }
    
}

void imprimirUltimo(TDLEnc *lista){

    if(lista != NULL){
        printf("%d %s\n", lista->ultimo->info.numLinha, lista->ultimo->info.frase);
    }
    else{
        printf("Erro: Lista Vazia");
    }
    
}

int inserirElemento(TDLEnc *lista, char st[]){

    TAtomo *pnovo = (TAtomo*) malloc(sizeof(TAtomo));
    if(pnovo == NULL)   return NO_SPACE;

    strcpy(pnovo->info.frase, st);
    pnovo->info.numLinha = lista->numElem+1;
    pnovo->seguinte = NULL;
    if(vaziaLista(lista))
    {
        pnovo->anterior = NULL;
        lista->primeiro= lista->ultimo= pnovo;  
    }
    else{
        pnovo->anterior = lista->ultimo;
        lista->ultimo->seguinte = pnovo;
        lista->ultimo = pnovo;
    }
    lista->numElem +=1;
    return OK;
}

int ehCaracterValido(char st[]){

    for(int i=0; st[i] != '\0';i++)
    {
        if(!isalpha(st[i])) 
        {
            if(st[i] != ' ')
             {
                 if(st[i]!= '-')
                     return ERROR;
             }   
        }
       
    }
    return OK;

}

void linha(TDLEnc *lista,int n ){

    for(TAtomo *paux= lista->primeiro; paux != NULL; paux = paux->seguinte)
    {
        if(paux->info.numLinha == n)
        {
            paux->info.linhaCorrente = TRUE;
            break;
        } 
    }

}

/*void copiarStringDadoIndice(int indiceInicio, int indiceFim, char destino[],char origem[])
{
    int k=0;
    while(indiceInicio<=indiceFim){
        destino[k++] = origem[indiceInicio++];
    }
    destino[k] = '\0';
}*/


void copiarStringDadoIndice(int indiceInicio, int indiceFim, char destino[],char origem[])
{
    int k=0;
    while(indiceInicio<=indiceFim){
        
        if(origem[0] == '$'){
            destino[k] = origem[indiceInicio];
        }
        else{
            break;
        }

        if(k>0){
            if(isalpha(origem[k]))
            {
                destino[k] = origem[indiceInicio];
            }
            else{
                printf("Erro: a instrucao contem caracteres que nao sao letras\n");
                break;
            }
        }
        k++;
        indiceInicio++;
        
    }
    destino[k] = '\0';
}

void pegarN(int indiceInicio, int indiceFim, char destino[],char origem[], int *n)
{
    int k=0;
    for(int i=indiceInicio; i<=indiceFim+1;i++)
    {
        if(isdigit(origem[i])){
            destino[k] = origem[indiceInicio];
            k++;
            indiceInicio++;
        }
    }
    destino[k] = '\0';
    *n = atoi(destino);
}

void pegarM(int indiceInicio, int indiceFim, char destino[],char origem[], int *m)
{
    int k=0;
    for(int i=indiceInicio; i<=indiceFim-1;i++)
    {
        if(isdigit(origem[i])){
            destino[k] = origem[indiceInicio];
            k++;
            indiceInicio++;
        }
    }
    destino[k] = '\0';
    *m = atoi(destino);
}

void separarOsDadosDaInstrucaoComVariosParametros(char st[]){
    char inst [15], numNInicio[30], numMFim[30]; 
    int indiceInicio = 0,n,m;
    int i;
    for(i=0;st[i] != '\0';i++){

        if(st[i] == ' ' && isalpha(st[i-1]))
        {
            copiarStringDadoIndice(indiceInicio,i-1,inst,st);
            indiceInicio = i;
        }
        else if(st[i] == ','){
            pegarN(indiceInicio,i,numNInicio,st,&n);
            indiceInicio=i;
        }
    }
    printf("ind:%d\n", indiceInicio);
    printf("i:%d\n",i);
    pegarM(indiceInicio+1,i,numMFim,st,&m);
    printf("Inst:%s\n",inst);
    printf("n: %d & m:%d\n", n,m);
    
}


int main (){

    char instrucao[10];
    TInfo info;
    int num = -2;
    TDLEnc lista;
    char string[80];
    criarLista(&lista);
    int flagInsercao = 0;
    //char st[80];
    while(num != 8){

        printf("Entre com a instrucao\n");
        scanf("%[^\n]", string);
         __fpurge(stdin);
        
        separarOsDadosDaInstrucaoComVariosParametros(string);
        num: num = numInstrucao(string);
        printf("Num: %d\n",num);

        if(num == -1){
            printf("Instrucao invalida\n");
        }
        if(num == 8){
            break;
        } 
        if(num == 1){
            flagInsercao = 1;
        }
        if(num == 3){
            
        }
        if(num == 6){
            imprimirUltimo(&lista);
        }

        if(flagInsercao == 1){

            while (num == 1)
            {
                string[0]='\0';
                scanf("%[^\n]", string);
                __fpurge(stdin);

                if(ehCaracterValido(string) == OK ){
                    inserirElemento(&lista,string);
                    string[0]='\0';
                }
                else if(numInstrucao(string) != -1)
                {
                    printf("Saindo do modo de insercao\n");
                    flagInsercao = 0;
                    imprimirLista(&lista);
                    goto num;
                    break;
                }
                else{
                    printf("O texto contem caracteres invalidos/n");
                }

            }
            
        }
        string[0]='\0';
   
    }

    return 0;

}