#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "tad.h"
#include <ctype.h>

int main (){

    TInfo info;
    int num = -2;
    TInfo *pilha = (TInfo *)(malloc(sizeof(TInfo) * MAX));
    int cabecaPilha = 0; 
    TDLEnc lista;
    char string[MAX];
    char *inst = (char*)(malloc(sizeof(15)));
    char *subString = (char*)(malloc(sizeof(20)));
    char *subStringAlterar = (char*)(malloc(sizeof(20)));

    criarLista(&lista);
    int flagInsercao = 0, indiceInicio=-1, indiceFim,n,m;
    int flagLinha = 0, flagInsercaoInicio=0;
    
    while(num != 8){

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
        }
        if(num == 3){
            pegarMLinha(string,indiceInicio,&m);
            linha(&lista,m,&flagLinha);
        } 
        if(num == 4)
        {
            pegarSubstring(string,indiceInicio,subString);
            localizarString(&lista, subString);
            memset(subString,'\0',20);
        } 
        if(num == 5){
            memset(subStringAlterar,'\0',20);
            memset(subString,'\0',20);
            pegarStringsEmAlterar(string, subString, subStringAlterar);
            alterarString(&lista,subString, subStringAlterar);
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
        if(num == 9)
        {
            pegarNM(string,indiceInicio,&n,&m);
            mostrarDeFormaInversa(&lista,n,m);
        }

        if(num == 10)
        {
            memset(subString,'\0',20);
            pegarStringsEmDeletar(string, subString);
            adicionarPilhaUndo(lista, pilha, &cabecaPilha);
            deletarString(&lista,subString);
        }

        if(num == 11)
        {
            opearacaoUndo(&lista, pilha, &cabecaPilha);
        }
      
        if(flagInsercao == 1){

            while (num == 1)
            {
                memset(string,'\0',80);
                scanf("%[^\n]", string);
                __fpurge(stdin);

                if(ehCaracterValido(string) == OK ){
                    inserirElemento(&lista,string, flagLinha);
                    memset(string,'\0',80);
                }
                else if(ehCaracterValido(string) == POSSIBLE_INSTRUTION)
                {
                    pegarInstrucao(string,inst,&indiceInicio);
                    if(numInstrucao(inst) != -1){
                        flagInsercao = 0;
                        goto num;
                        break;
                    }
                }
                else{
                    printf("O texto contem caracteres invalidos\n");
                }
                    
            }
            
        }
    
    }

    return 0;

}