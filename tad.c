#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "tad.h"
#include <ctype.h>

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

void criarLista(TDLEnc *lista){

    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->numElem = 0;
}

Boolean vaziaLista(TDLEnc *lista){

    return (lista->primeiro == NULL &&  lista->ultimo == NULL && lista->numElem == 0);
}
void imprimirLista(TDLEnc *lista){

    if(lista->primeiro != NULL && lista->ultimo != NULL)
    {
        printf("--------------------------------------------------------------\n");
        for(TAtomo *paux = lista->primeiro; paux != NULL; paux = paux->seguinte)
        {
            if(paux->info.linhaCorrente == TRUE)
            {
                printf("→ %d %s\n",paux->info.numLinha, paux->info.frase);
            }
            else{
                printf("%d %s\n",paux->info.numLinha, paux->info.frase);
            }
            
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
            if(m<=n){

                printf("--------------------------------------------------------------\n");
                for(TAtomo *paux = lista->primeiro; paux != NULL; paux = paux->seguinte)
                {
                    if( paux->info.numLinha >= m && paux->info.numLinha <= n){
                        printf("%d %s\n",paux->info.numLinha, paux->info.frase);
                    }
                    
                }
                printf("--------------------------------------------------------------\n\n");
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

TAtomo *buscarAtomoCorrente(TDLEnc *lista)
{
    for(TAtomo *paux=lista->primeiro; paux !=NULL; paux= paux->seguinte)
    {
       if(paux->info.linhaCorrente == TRUE)
       {
           return paux;
       }
    }
    return NULL;
}

int inserirElemento(TDLEnc *lista, char st[], int flagLinha)
{
    TAtomo *pnovo = (TAtomo*) malloc(sizeof(TAtomo));

    if(pnovo == NULL) 
    {
        return NO_SPACE;
    }
    strcpy(pnovo->info.frase, st);
    pnovo->seguinte = NULL;
    pnovo->info.linhaCorrente = TRUE;

    if(vaziaLista(lista))
    {
        pnovo->anterior = NULL;
        pnovo->info.numLinha = 1;
        lista->primeiro = lista->ultimo = pnovo;
    }
    else{

        TAtomo *pcorrente = buscarAtomoCorrente(lista);
        if(pcorrente == NULL)
        {
            free(pnovo);
            return NOT_FOUND;
        }
        
        if(pcorrente == lista->ultimo)
        {
            lista->ultimo->info.linhaCorrente = FALSE;
            lista->ultimo->seguinte = pnovo;
            pnovo->anterior = lista->ultimo;
            pnovo->info.numLinha = lista->ultimo->info.numLinha + 1;
            lista->ultimo = pnovo;
        }
        else{
            pcorrente->seguinte->anterior = pnovo;
            pnovo->seguinte = pcorrente->seguinte;
            pnovo->anterior = pcorrente;
            pcorrente->seguinte = pnovo;
            pnovo->info.numLinha = pcorrente->info.numLinha + 1; 
            pcorrente->info.linhaCorrente = FALSE;

            if(flagLinha == 1)
            {
                pnovo->seguinte->info.numLinha++;
            }
        }
    }
    lista->numElem++;
    return OK;
 }
   

int ehCaracterValido(char st[]){

    for(int i=0; st[i] != '\0';i++)
    {
        if(!isalpha(st[i])) 
        {
            if(st[i] == '$')
                return POSSIBLE_INSTRUTION;
 
            if(st[i] != ' ' &&  st[i]!= '-' && st[i] != '.' && st[i] != ',' && st[i] != ';' && st[i] != ':' && st[i] != '+')
            {
                return ERROR;
            }
                
        }
       
    }
    return OK;

}

void linha(TDLEnc *lista,int n, int *flagLinha){

    if(n == 0)
    {
        *flagLinha = 1;
    }
    else if(n < 0)
    {
        printf("Erro: O numero da linha é menor do que 0\n");
    }
    else if( n > lista->numElem)
    {
        printf("Erro: O numero da linha é maior do que o número de elementos na string \n");
    }
    else
    {
        *flagLinha = 0;
        TAtomo *pcorrente = buscarAtomoCorrente(lista);
        if(pcorrente!= NULL)
        {
            pcorrente->info.linhaCorrente = FALSE;
        }

        for(TAtomo *paux= lista->primeiro; paux != NULL; paux = paux->seguinte)
        {
            if(paux->info.numLinha == n)
            {
                paux->info.linhaCorrente = TRUE;
                break;
            } 
        }
    }
    
    
}

void copiarStringDadoIndice(int indiceInicio, int indiceFim, char destino[],char origem[])
{
    int k=1;
    printf("%s: origem", origem);
    if(origem[0] == '$'){
        destino[0] = origem[0];
        indiceInicio++;
        while(indiceInicio<=indiceFim){
            printf("ini: %d  fim:%d", indiceInicio, indiceFim);
            if(isalpha(origem[indiceInicio]))
            {
                printf("Entrei");
                destino[k] = origem[indiceInicio];
                printf("Dentro: k: %d i:%d\n", k, indiceInicio);
                printf("%c: origem", origem[indiceInicio]);
            }
            k++;
            indiceInicio++;
            printf("Fora: k: %d i:%d\n", k, indiceInicio);
        }
            destino[k] = '\0';
            printf("\nstring:%s\n", destino);
    }
    else{
        printf("Bla bla\n");
    }
    
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

void pegarInstrucao(char st[], char inst [], int *pos){
    int i;
    int k=0;
    for(i=0;st[i] != '\0';i++){
        if(isalpha(st[i]) && st[i+1] == '\0' || isalpha(st[i]) && st[i+1] == ' ')
        {
            int j = 0;
            for(; j<= i; j++)
            {
                if(j== 0 && st[j] == '$')
                {
                    inst[k] = st[j];
                    k++;
                }
                if(isalpha(st[j]))
                {
                    inst[k++] = st[j];
                }
            }
            inst[k] = '\0';
            tolower(inst);
           *pos = i;
        }

        if(isalpha(st[i]) && st[i+1] == ' ')
        {
            *pos = i+1;
        }   
       
    }
    
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
                    
                    if(lista->numElem == 1)
                    {
                        criarLista(lista);
                        break;
                    }
                    else{
                        free(pdel);
                        lista->numElem--;
                    }
                }
            }
        }
        else{
            printf("Verifique os parametros\n");
        }       
    }
    else
    {
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
        for(j=i; string[j] != '%'; j++)
        {
            subString[k++] = string[j];
        }
        subString[j] = '\0';

    }
    else{
        printf("Erro: Sintaxe do comando $localizar invalida \n");
    }
    
}

int localizarString(TDLEnc *lista, char subs[]){

    if(lista->primeiro != NULL && lista->ultimo != NULL)
    {
        int tamanhoSubs = strlen(subs);
        TAtomo *paux;
        int i, k = 0, tamStringLocalizada = 0 , flagImpressao = 0, vezesAImprimir = 0;
        for(paux = lista->primeiro; paux != NULL; paux= paux->seguinte)
        {
            for(i=0; paux->info.frase[i] != '\0'; i++)
            {
                k=0;
                tamStringLocalizada = 0;
            
                for(int j = 0; j<=tamanhoSubs-1; j++)
                {
                    if(paux->info.frase[i+k] == subs[j])
                    {
                        tamStringLocalizada++;
                    }
                    k++;
                }

                if(tamanhoSubs == tamStringLocalizada) 
                {
                    flagImpressao = 1;
                    vezesAImprimir = tamStringLocalizada;
                }

                if(flagImpressao == 1)
                {
                    if(vezesAImprimir != 0)
                    {
                        printf("\033[32;1m%c\033[0m",paux->info.frase[i]);
                        vezesAImprimir--;
                    }
                    else{
                        printf("%c",paux->info.frase[i]);
                        flagImpressao = 0;
                        vezesAImprimir = 0;
                    }
                }
                else{
                    printf("%c",paux->info.frase[i]);
                }
                
            }
            printf("\n");

        }

    }
    else{
        printf("Erro: Impossível localizar '%s' , a lista está vazia\n", subs);
    }
}

int encontrardelimitador(char frase [], int pos)
{
    for(int i = pos; frase[i] != '\0';i++)
    {
        if(frase[i] == '%')
        {
            return i;
        }
    }
    return NOT_FOUND;
}


void pegarStringsEmAlterar(char string[], char subString1[], char subString2[])
{
    int posIni = 0;
    int posDelimitador1 = encontrardelimitador(string, posIni);
    int posDelimitador2 = encontrardelimitador(string, posDelimitador1+1);
    int posDelimitador3 = strlen(string) - 1;
    int i=posDelimitador1+1, k=0;

    if(posDelimitador1 != -1 && posDelimitador2 != -1)
    {
        for(; i < posDelimitador2; i++)
        {
            if(isalpha(string[i]))
            {
                subString1[k++] = string[i];
            }
            
        }
        subString1[k] = '\0';
        k = 0;
    
        i=posDelimitador2+1;
        for(; i < posDelimitador3; i++)
        {
            if(isalpha(string[i]))
            {
                subString2[k++] = string[i];
            }
            
        }
        subString2[k] = '\0';
    }
    
}

void pegarPosicaoString(TAtomo *paux, char subs[], int *posInicial, int *posFinal){

        int i = *posInicial;
        int sizeSub = strlen(subs);
        int sizeFrase = strlen(paux -> info.frase);
        int flagFound = 1;

        for (; i + sizeSub <= sizeFrase; i++ ) {
            flagFound = 1;
            for (int j = 0; j < sizeSub; j++) {
                if (subs[j] != paux -> info.frase[j + i]) {
                    flagFound = 0;
                    break;
                }
            }
            if (flagFound == 1) {
                *posInicial = i;
                *posFinal = i + sizeSub;
                break;
            }
        }
}


void alterarString(TDLEnc *lista, char subString1[], char subString2[])
{
    TAtomo *paux = buscarAtomoCorrente(lista);
    if(paux == NULL)
    {
        printf("Impossiver alterar,nao existe uma linha corrente \n");
    }
    else
    {
        char texto[MAX];
        int posInicial = 0, posFinal = 0, j=0, i=0, k=0, flagParagem=0, f=0;
        int tamString = strlen(paux->info.frase), tamString2=0;
        while(flagParagem==0)
        {
            pegarPosicaoString(paux,subString1, &posInicial, &posFinal);

            if(posInicial != posFinal)
            {
                for(; i<posInicial;i++)
                {
                    texto[k++] = paux->info.frase[i];
                }

                for(j = 0; subString2[j] != '\0'; j++)
                {
                    texto[k++] = subString2[j];
                }
            }
            else{

                for(int c = posInicial; c < tamString;c++)
                {
                    texto[k++] = paux->info.frase[c];
                }
                texto[k] = '\0';
            }

            if(posInicial == tamString)
            {
                flagParagem =1;
            }
            else{
                i= posFinal;
                posInicial = posFinal;
            }
            
        }

        tamString2= strlen(texto);
        
        for(; f< tamString2; f++)
        {
            paux->info.frase[f] = texto[f];
        } 
        paux->info.frase[f] = '\0';
    }    
}
