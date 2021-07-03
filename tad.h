#ifndef TAD_H_INCLUDED
#define TAD_H_INCLUDED

#define MAX 80
#define NOT_FOUND -1 // Item não existe
#define OK 0 // Operação realizada com sucesso
#define LIST_EMPTY 2 // Lista vazia
#define NO_SPACE 3 // Não há espaço de memória
#define ERROR -3 // Erro na operacao
#define POSSIBLE_INSTRUTION 4 // Codigo para uma possivel instrucao

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
  Pós-Condições:Retornar um codigo ;

*/
int numInstrucao( char instrucao[]);


/* 
  Entrada: Um TDLEnc ;
  Saída : Um TDLEnc criado;
  Pré-Condições:Deve ser uma variável do tipo TDLEnc;
  Pós-Condições: Inicializar os ponteiros primeiro, ultimo e variavel numElem;
*/
void criarLista(TDLEnc *lista);


/* 
  Entrada: Um TDLEnc ;
  Saída:TRUE ou FALSE;
  Pré-Condições:Deve ser uma variável do tipo TDLEnc;
  Pós-Condições: Verificar o conteudo dos ponteiros primeiro e último;
*/
Boolean vaziaLista(TDLEnc *lista);

/* 
  Entrada: Um TDLEnc ;
  Saída:Lista imprensa;
  Pré-Condições:Deve ser uma variável do tipo TDLEnc; 
  A lista nao pode estar vazia;
  Pós-Condições:Imprimir o conteudo dos atomos;
*/
void imprimirLista(TDLEnc *lista);


/* 
  Entrada: Um TDLEnc, uma string e um inteiro ;
  Saída:Codigo de erro:
  OK: Caso a insercao seja efectuada com sucesso;
  NO_SPACE: Caso nao haja para alocar memoria;
  NOT_FOUND: Caso nao seja encontrado nenhuma linha corrente;
  Pré-Condições:Deve ter espaco na memoria;
  Caso esteja no caso do Atomo corrente, deve ser encontrado um atomo corrente;
  Pós-Condições: Inserir um atomo na lista;
*/
int inserirElemento(TDLEnc *lista, char st[], int flagLinha);


/* 
  Entrada: Um TDLEnc ;
  Saída:Lista imprensa de acordo com o n e o m;
  Pré-Condições:Deve ser uma variável do tipo TDLEnc; 
  Nao pode Faltar um número de linha ou a virgula no comando;
  O n nao pode menor do que m;
  O m nao pode ser menor que 1 ou o n nao pode ser maior que o último número de linha do texto.
  Pós-Condições:Imprimir o conteudo das linhas m até n, inclusive n;
*/
void imprimirLinhaMAteN(TDLEnc *lista, int m, int n);


/* 
  Entrada: Um TDLEnc ;
  Saída:O numero da ultima frase inserida;
  Pré-Condições:Deve ser uma variável do tipo TDLEnc, a lista nao pode estar vazia; 
  Pós-Condições:Imprmir o numLinha do ultimo elemento inseriro;
*/
void imprimirUltimo(TDLEnc *lista);


/* 
  Entrada: Um TDLEnc ;
  Saída:Caso encontre: Um ponteiro do tipo Atomo;
  Caso nao: Um ponteiro NULL;
  Pré-Condições:Deve ser uma variável do tipo TDLEnc; 
  Pós-Condições:Verificar se existe um atomo corrente;
*/
TAtomo *buscarAtomoCorrente(TDLEnc *lista);


/* 
  Entrada: Uma string ;
  Saída:OK: caso seja um caracter valido;
  POSSIBLE_INSTRUTION:Caso contenha o caracter $;
  ERROR: caso nao seja :  ' ' , '-' , '.' , ',' , ';' , ':' , '+'
  Pré-Condições:A string nao pode ser vazia; 
  Pós-Condições:Verificar cada posicao da string;
*/
int ehCaracterValido(char st[]);


/* 
  Entrada: Uma string ;
  Saída:A linha m sendo linha corrente;
  Pré-Condições:n<0 || n< lista.ultimo.numLinha; 
  Pós-Condições:Verificar se ja nao ha uma linha corrente, caso haja por essa linha como false e por a linha actual como true;
*/
void linha(TDLEnc *lista,int n,int *flagLinha);


/* 
  Entrada:indice de inicio, indice fim, a string de destino e a string de origem;
  Saída:Nada;
  Pré-Condições:n<0 || n< lista.ultimo.numLinha; 
  Pós-Condições:Verificar se ja nao ha uma linha corrente, caso haja por essa linha como false e por a linha actual como true;
*/
void copiarStringDadoIndice(int indiceInicio, int indiceFim, char destino[],char origem[]);

/* 
  Entrada:indice de inicio, indice fim, a string de destino e a string de origem;
  Saída:Nada;
  Pré-Condições:n<0 || n< lista.ultimo.numLinha; 
  Pós-Condições:Verificar se ja nao ha uma linha corrente, caso haja por essa linha como false e por a linha actual como true;
*/
void pegarN(int indiceInicio, int indiceFim, char destino[],char origem[], int *n);

/* 
  Entrada:indice de inicio, indice fim, a string de destino e a string de origem;
  Saída:Nada;
  Pré-Condições:n<0 || n< lista.ultimo.numLinha; 
  Pós-Condições:Verificar se ja nao ha uma linha corrente, caso haja por essa linha como false e por a linha actual como true;
*/
void pegarM(int indiceInicio, int indiceFim, char destino[],char origem[], int *m);

/* 
  Entrada:indice de inicio, indice fim, a string de destino e a string de origem;
  Saída:Nada;
  Pré-Condições:n<0 || n< lista.ultimo.numLinha; 
  Pós-Condições:Verificar se ja nao ha uma linha corrente, caso haja por essa linha como false e por a linha actual como true;
*/
void pegarNM(char st[], int indiceInicio, int *n, int *m);

/* 
  Entrada:indice de inicio, indice fim, a string de destino e a string de origem;
  Saída:Nada;
  Pré-Condições:n<0 || n< lista.ultimo.numLinha; 
  Pós-Condições:Verificar se ja nao ha uma linha corrente, caso haja por essa linha como false e por a linha actual como true;
*/
void pegarMLinha(char st[], int indiceInicio,int *m);

/* 
  Entrada:indice de inicio, indice fim, a string de destino e a string de origem;
  Saída:Nada;
  Pré-Condições:n<0 || n< lista.ultimo.numLinha; 
  Pós-Condições:Verificar se ja nao ha uma linha corrente, caso haja por essa linha como false e por a linha actual como true;
*/
int pegarInstrucao(char st[], char inst [], int *pos);


/* 
  Entrada:indice de inicio, indice fim, a string de destino e a string de origem;
  Saída:Nada;
  Pré-Condições:n<0 || n< lista.ultimo.numLinha; 
  Pós-Condições:Verificar se ja nao ha uma linha corrente, caso haja por essa linha como false e por a linha actual como true;
*/
int removerMN(TDLEnc *lista, int n, int m);

/* 
  Entrada:indice de inicio, indice fim, a string de destino e a string de origem;
  Saída:Nada;
  Pré-Condições:n<0 || n< lista.ultimo.numLinha; 
  Pós-Condições:Verificar se ja nao ha uma linha corrente, caso haja por essa linha como false e por a linha actual como true;
*/
void pegarSubstring(char string[], int pos, char subString[]);

/* 
  Entrada:indice de inicio, indice fim, a string de destino e a string de origem;
  Saída:Nada;
  Pré-Condições:n<0 || n< lista.ultimo.numLinha; 
  Pós-Condições:Verificar se ja nao ha uma linha corrente, caso haja por essa linha como false e por a linha actual como true;
*/
int localizarString(TDLEnc *lista, char subs[]);

/* 
  Entrada:indice de inicio, indice fim, a string de destino e a string de origem;
  Saída:Nada;
  Pré-Condições:n<0 || n< lista.ultimo.numLinha; 
  Pós-Condições:Verificar se ja nao ha uma linha corrente, caso haja por essa linha como false e por a linha actual como true;
*/
int encontrardelimitador(char frase [], int pos);

/* 
  Entrada:indice de inicio, indice fim, a string de destino e a string de origem;
  Saída:Nada;
  Pré-Condições:n<0 || n< lista.ultimo.numLinha; 
  Pós-Condições:Verificar se ja nao ha uma linha corrente, caso haja por essa linha como false e por a linha actual como true;
*/
void pegarStringsEmAlterar(char string[], char subString1[], char subString2[]);


/* 
  Entrada:indice de inicio, indice fim, a string de destino e a string de origem;
  Saída:Nada;
  Pré-Condições:n<0 || n< lista.ultimo.numLinha; 
  Pós-Condições:Verificar se ja nao ha uma linha corrente, caso haja por essa linha como false e por a linha actual como true;
*/
void pegarPosicaoString(TAtomo *paux, char subs[], int *posInicial, int *posFinal);


/* 
  Entrada:a lista, a string a procurar e a string a substituir;
  Saída:Nada;
  Pré-Condições:n<0 || n< lista.ultimo.numLinha; 
  Pós-Condições:Verificar se ja nao ha uma linha corrente, caso haja por essa linha como false e por a linha actual como true;
*/
void alterarString(TDLEnc *lista, char subString1[], char subString2[]);


#endif // RACIONAL_H_INCLUDED