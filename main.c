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

    if(lista->primeiro != NULL && lista->ultimo != NULL)
    {
        printf("--------------------------------------------------------------\n");
        for(TAtomo *paux = lista->primeiro; paux != NULL; paux = paux->seguinte)
        {
            printf("%d %s\n",paux->info.numLinha, paux->info.frase);
        }
        printf("--------------------------------------------------------------\n\n");
    }
    else{
        printf("Erro: Impossivel imprimir, a lista esta vazia");
    }
    
}

void imprimirLinhaMAteN(TDLEnc *lista, int m, int n){

    if(lista->primeiro != NULL && lista->ultimo != NULL){

        if(m >= 1 && n <= lista->ultimo->info.numLinha)
        {
            if(m<n){

                printf("--------------------------------------------------------------\n");
                for(TAtomo *paux = lista->primeiro; paux != NULL; paux = paux->seguinte)
                {
                    if( paux->info.numLinha >= m && paux->info.numLinha <= n){
                        printf("%d %s\n",paux->info.numLinha, paux->info.frase);
                    }
                    
                }
                printf("--------------------------------------------------------------\n\n");
            }
            else{
                printf("O m é maior do que o n\n");
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
        printf("Erro:Impossivel imprimir, a lista esta vazia\n");
    }
    
}

void imprimirUltimo(TDLEnc *lista){

    if(lista->primeiro != NULL && lista->ultimo != NULL){
        printf("%d\n", lista->ultimo->info.numLinha);
    }
    else{
        printf("Erro: Lista Vazia\n");
    }
    
}

TAtomo *buscarAtomoCorrente(TDLEnc *lista){

    for(TAtomo *paux=lista->primeiro; paux !=NULL; paux= paux->seguinte)
    {
       if(paux->info.linhaCorrente == TRUE)
       {
           return paux;
       }
    }
    return NULL;
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

        TAtomo *pcorrente = buscarAtomoCorrente(lista);
        if(pcorrente != NULL){

            if( pcorrente == lista->ultimo){
                lista->ultimo->seguinte = pnovo;
                lista->ultimo = pnovo;
            }
            else
            {   pnovo->seguinte = lista->primeiro->seguinte;
                lista->primeiro->seguinte->anterior= pnovo;
                lista->primeiro->seguinte = pnovo;
            }

        }
        else{
             pnovo->anterior = lista->ultimo;
             lista->ultimo->seguinte = pnovo;
            lista->ultimo = pnovo;
        }
       
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
                 {
                    printf("O texto contem caracteres invalidos\n");
                    return ERROR;
                 }
             }   
        }
       
    }
    return OK;

}

void linha(TDLEnc *lista,int n ){

    if(n == 0)
    {

    }

    for(TAtomo *paux= lista->primeiro; paux != NULL; paux = paux->seguinte)
    {
        if(paux->info.numLinha == n)
        {
            printf("n:%d foi marcado como corrente",n);
            paux->info.linhaCorrente = TRUE;
            break;
        } 
    }

}

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

void pegarNM(char st[], int indiceInicio, int *n, int *m){
    
    char inst [15], numNInicio[10], numMFim[10]; 
    int i;
    
    for(i = indiceInicio;st[i] != '\0';i++){

        if(st[i] == ','){
            pegarN(indiceInicio,i,numNInicio,st,n);
            indiceInicio=i;
        }
    }
    pegarM(indiceInicio+1,i,numMFim,st,m);
}

void pegarMLinha(char st[], int indiceInicio,int *m){
    
    char inst [15], numNInicio[10], numMFim[10]; 
    int i;

    for(i = indiceInicio;st[i] != '\0';i++);
    pegarM(indiceInicio+1,i,numMFim,st,m);
}

int pegarInstrucao(char st[], char inst [], int *pos){
    
    int indiceInicio = 0;
    int i;

    for(i=0;st[i] != '\0';i++){

        if(st[i] == ' ' && isalpha(st[i-1]))
        {
           copiarStringDadoIndice(indiceInicio,i-1,inst,st);
           *pos = i;
           return OK;
        }
    
    }

    if(isalpha(st[i-1])){
      copiarStringDadoIndice(indiceInicio,i-1,inst,st);
      return OK;
    }

    return NOT_FOUND;   
}

TAtomo *buscarAtomoDadaChave(TDLEnc *lista, int chave){

    for(TAtomo *paux=lista->primeiro; paux !=NULL; paux= paux->seguinte)
    {
       if(paux->info.numLinha == chave)
       {
           return paux;
       }
    }
    return NULL;
}

int removerMN(TDLEnc *lista, int n, int m)
{
    TAtomo *pdel;
    if(lista->primeiro != NULL && lista->ultimo != NULL)
    {
        if( n >= 1 && m > n )
        {
            for(int i=n; i<=m;i++)
            {
                pdel = buscarAtomoDadaChave(lista,i);

                if(pdel != NULL)
                {
                    if(pdel == lista->primeiro)
                    {
                        lista->primeiro = pdel->seguinte;
                    }
                    else if(pdel == lista->ultimo)
                    {
                        pdel->anterior->seguinte = NULL;
                        lista->ultimo = pdel->anterior;
                    }
                    else
                    {
                        pdel->anterior->seguinte = pdel->seguinte;
                        pdel->seguinte->anterior = pdel->anterior;
                    }

                    if(pdel->info.linhaCorrente == TRUE && pdel != lista->primeiro)
                    {
                        pdel->anterior->info.linhaCorrente= TRUE;
                    }
                    free(pdel);
                }
            }
        }
        else{
            printf("Verifique os parametros\n");
        }       
    }
    else{
        printf("Erro:Impossivel remover, a lista esta Vazia\n");
    }
    
}

void pegarSubstring(char string[], int pos, char subString[])
{
    int i,j, k=0;
    for(i=pos; string[i] != '\0';i++)
    {
        if(isalpha(string[i]) && string[i-1] == '%')
        break;
    }

    if(string[i] != '\0')
    {
        for(j=i; string[j] != '\0'; j++)
        {
            subString[k++] = string[j];
        }
        subString[j] = '\0';
    }
    else{
        printf("Erro: Sintaxe do comando $localizar invalida \n");
    }
    
}

void localizarString(TDLEnc *lista, char subs[]){

    int tamanhoSubs = strlen(subs);

    for(TAtomo *paux = lista->primeiro; paux != NULL; paux= paux->seguinte)
    {
        for(int i=0; paux->info.frase[i] != '\0'; i++)
        {
            if(tamanhoSubs > 1)
            {   int k = 0;
                for(int j = 0; j<=tamanhoSubs-1; j++)
                {
                    if(paux->info.frase[i+k] != subs[j])
                    {
                        break;
                    }
                }
            }
        }
    }
}

int main (){

    TInfo info;
    int num = -2;
    TDLEnc lista;
    char string[80];
    char inst[15];
    char subString[20];

    criarLista(&lista);
    int flagInsercao = 0, indiceInicio=-1, indiceFim,n,m;
    
    while(num != 8){

        printf("Entre com a instrucao\n");
        scanf("%[^\n]", string);
         __fpurge(stdin);

        pegarInstrucao(string,inst,&indiceInicio);
       
        num: num = numInstrucao(inst); 
        
        if(num == -1){
            printf("Instrucao invalida\n");
        }
        if(num == 1){
            flagInsercao = 1;
        }
        if(num == 2){
            pegarNM(string,indiceInicio,&n,&m);
            removerMN(&lista,n,m);
            imprimirLista(&lista);
        }
        if(num == 3){
            pegarMLinha(string,indiceInicio,&m);
            linha(&lista,m);
        } 
        if(num == 4)
        {
            printf("Entrei em localizar\n");
            pegarSubstring(string,indiceInicio,subString);
            printf("%d\n", indiceInicio);
            printf("SubString: %s\n", subString);
        } 
        if(num == 6){
            imprimirUltimo(&lista);
        }
        if(num == 7){
            pegarNM(string,indiceInicio,&n,&m);
            imprimirLinhaMAteN(&lista, n,m);
        }
        if(num == 8){
            break;
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
                else 
                {
                    pegarInstrucao(string,inst,&indiceInicio);
                    if(numInstrucao(inst) != -1){
                        flagInsercao = 0;
                        imprimirLista(&lista);
                        goto num;
                        break;
                    }
                }
                    

            }
            
        }
    
    }

    return 0;

}