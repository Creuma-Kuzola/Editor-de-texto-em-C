#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "tad.h"
#include <ctype.h>

int main (){

    TInfo info;
    int num = -2;
    TDLEnc lista;
    char string[80];
    char inst[15];
    char subString[20];
    char subStringAlterar[20];

    criarLista(&lista);
    int flagInsercao = 0, indiceInicio=-1, indiceFim,n,m;
    
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
            imprimirLista(&lista);
        }
        if(num == 3){
            pegarMLinha(string,indiceInicio,&m);
            linha(&lista,m);
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
      
        if(flagInsercao == 1){

            while (num == 1)
            {
                memset(string,'\0',80);
                scanf("%[^\n]", string);
                __fpurge(stdin);

                if(ehCaracterValido(string) == OK ){
                    inserirElemento(&lista,string);
                    memset(string,'\0',80);
                }
                else 
                {
                    pegarInstrucao(string,inst,&indiceInicio);
                    if(numInstrucao(inst) != -1){
                        flagInsercao = 0;
                        goto num;
                        break;
                    }
                }
                    
            }
            
        }
    
    }

    return 0;

}