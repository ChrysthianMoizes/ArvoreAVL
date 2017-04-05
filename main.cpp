#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>


typedef struct tipoNodo {
    char valor[35];
    tipoNodo *dir, *esq;
}TNodo;

TNodo *raiz;

void inicializa(TNodo **R);
void insere(TNodo **R);
void insereNodo(TNodo **R, char nome[35]);
int balanceada(TNodo *R);
int obterAlturaArvore(TNodo *R);
TNodo *geraNovoNodo(char nome[35]);
int obterFatorBalanceamento(TNodo *R);
void visualizarArvore(TNodo *R);
void visualizarArvore2(TNodo *R);
void visualiza(TNodo *R, TNodo *Pai);
void visualiza2(TNodo *R, TNodo *Pai);
void excluirNome(TNodo **raiz);
TNodo *exclui(TNodo **raiz, char *nome);
void gotoxy(int coluna, int linha);
void rotacaoAEsquerda(TNodo **R);
void rotacaoADireita(TNodo **R);
void rotacaoDireitaEsquerda(TNodo **R);
void rotacaoEsquerdaDireita(TNodo **R);

void emOrdem(TNodo *R);
int menu();

int main(){
    int opcao;
    char nome[35];
    
	inicializa(&raiz);

     do{
        opcao = menu();
		
		switch(opcao) {
		
		case 0: system("PAUSE"); exit(1);	
		
		case 1: insere(&raiz); printf("\n\n"); system("PAUSE");	break;
		
		case 2: printf("\n\n\n"); emOrdem(raiz); printf("\n\n"); system("PAUSE"); break;
		
		case 3: visualizarArvore(raiz); printf("\n\n"); system("PAUSE"); break;
			
		case 4: visualizarArvore2(raiz); printf("\n\n"); system("PAUSE"); break; 
				
		case 5: excluirNome(&raiz); printf("\n\n"); system("PAUSE"); break; 		
		}
     } while (opcao != 0);
}

void inicializa(TNodo **R){
    *R = NULL;	
}

int menu(){
	
	int op;
	
	system("CLS");
	printf("\n\n\n\t\t\t===| ARVORE AVL |===\n\n");
	printf("\t\t\t======| MENU |=====\n\n");
	printf("\t\t0 - SAIR (Encerrar)\n\n");
	printf("\t\t1 - INSERIR NOVO ELEMENTO\n");
	printf("\t\t2 - VISUALIZAR em ORDEM\n");
	printf("\t\t3 - VISUALIZAR Hierarquicamente (2 camadas)\n");
	printf("\t\t4 - VISUALIZAR Hierarquicamente (3 camadas)\n");
	printf("\t\t5 - Excluir\n\n\n");
	
	printf("\tInforme OPCAO desejada: ");
	scanf("%d",&op);
	
	return op;
}

int balanceada(TNodo *R){

	int alturaDir = obterAlturaArvore(R->dir);
	int alturaEsq = obterAlturaArvore(R->esq);
	int fatorBalanceamento = alturaDir - alturaEsq;
	int resultado;
	
	if(fatorBalanceamento > 1){
		resultado = 0;
	}else if(fatorBalanceamento < -1){
		resultado = 0;
	}else{
		resultado = 1;
	}
	return resultado;
}

int obterAlturaArvore(TNodo *R){
    int d,e;
    
	if (R == NULL)	{
    	return 0;
    }else{
    	d = 1 + obterAlturaArvore(R->dir);
    	e = 1 + obterAlturaArvore(R->esq);
    	
    	if (d > e){ 
		   return d;
    	}else{
		   return e;
    	}
    }
}

void insere(TNodo **R){
	
	int fb,fbD, fbE, fbFilho;
	char nome[35];
	
	printf("\n\n\tInforme NOME: "); 
	fflush(stdin); 
	gets(nome); 
	
    insereNodo(R,nome);
        
	if (!balanceada(*R)){				// se retornar 0 entra
	   printf("\n\nARVORE AVL desbalanceada !!!");
	   fb = obterFatorBalanceamento(*R);
	   printf("\n\n>>>> fb = %d",fb);
	   fbD = obterFatorBalanceamento((*R)->dir);
	   printf("\n\n>>>> fbD = %d",fbD);
	   fbE = obterFatorBalanceamento((*R)->esq);
	   printf("\n\n>>>> fbE = %d",fbE);
	   
	   
	   if(strcmp(nome,(*R)->valor) >= 0){
	   	  
	      fbFilho = fbD;

        	printf("\n\nFB da Raiz = %d\tFB do FILHO = %d",fb,fbFilho);
        	printf("\nRotacao Simples para a ESQUERDA de %s",(*R)->valor);

		  if((fb == 2)&&(fbFilho >= 1)){
	      	//Rotação Simples à Esquerda
	      	rotacaoAEsquerda(R);
	      }

		  if((fb == 2)&&(fbFilho <= -1)){
	      	//Rotação Dupla Direita_Esquerda
	      	rotacaoDireitaEsquerda(R);
	      }
	      
	   } else {
	      fbFilho = fbE;

         printf("\n\nFB da Raiz = %d\tFB do Filho = %d",fb,fbFilho);
         printf("\nRotacao Simples para a DIREITA de %s",(*R)->valor);
	      
	      if((fb == -2) && (fbFilho <= -1)){
	         //Rotação Simples à Direita
	         rotacaoADireita(R);
		  }

          if((fb == -2) && (fbFilho >= 1)){
          	//Rotacao Dupla Esquerda_Direita
          	rotacaoEsquerdaDireita(R);
		  }
	   }
	}
}

void insereNodo(TNodo **R, char nome[35]){
	int fb,fbD, fbE, fbFilho;
	
	printf("\n\tINSERINDO: %s",nome);
	
	if (*R != NULL){
		printf("  apos  %s\n\n",(*R)->valor);
	    if (strcmp(nome, (*R)->valor) >= 0){
	    	//Inserir nome à direita de R
	    	if ((*R)->dir == NULL){
	    		(*R)->dir = geraNovoNodo(nome);
	    	}else {
	    		insereNodo(&(*R)->dir, nome);
	    	}
	    	
	    } else {
	    	//Inserir nome à esquerda de R
	    	if ((*R)->esq == NULL){
	    		(*R)->esq = geraNovoNodo(nome);
	    	}else{
	    		insereNodo(&(*R)->esq,nome);
	    	}
	    }
	} else {
		//Insere nome em R
	    *R = geraNovoNodo(nome);
	}		
}

TNodo *geraNovoNodo(char nome[35]){
	TNodo *novo = (TNodo *)malloc(sizeof(TNodo));
	
	strcpy(novo->valor, nome);
	novo->dir = NULL;
	novo->esq = NULL;
	
	return novo;
}

int obterFatorBalanceamento(TNodo *R){
	
    if (R == NULL){
    	return 0;
	}else {
        int alturaDir = obterAlturaArvore(R->dir);
	    int alturaEsq = obterAlturaArvore(R->esq);
	    int fatorBalanceamento = alturaDir - alturaEsq;
	
	    return fatorBalanceamento;		
	}
}

void rotacaoAEsquerda(TNodo **R){
	TNodo *filho, *temp;
	filho = (*R)->dir;
	temp = filho->esq;
	filho->esq = *R;
	(*R)->dir = temp;
	(*R) = filho;
}

void rotacaoADireita(TNodo **R){
	TNodo *filho, *temp;
	
	filho = (*R)->esq;
	temp = filho->dir;
	filho->dir = *R;
	
	(*R)->esq = temp;
	(*R) = filho;
}

void rotacaoDireitaEsquerda(TNodo **R){
    rotacaoADireita(&(*R)->dir);
    rotacaoAEsquerda(R);
}

void rotacaoEsquerdaDireita(TNodo **R){
	rotacaoAEsquerda(&(*R)->esq);
	rotacaoADireita(R);
}

void visualizarArvore(TNodo *R){
	char nome[5];
	char resp;
	
	system("CLS");
	printf("\n\n\t\t\t=====| VISUALIZACAO da ARVORE AVL |=====\n");
	
	gotoxy(38,5);
	printf("RAIZ");
	gotoxy(40,6);
	printf("|");
	gotoxy(40,7);
	printf("|");
	gotoxy(40,8);
	printf("V");

    gotoxy(38,9);
    if (R == NULL){
        strcpy(nome,"NULO");
	} else {
		strncpy(nome, R->valor, 5);
	}
	printf(nome);
	
	gotoxy(18,11);
    if(R != NULL) {
    	if(R->esq == NULL){
    		strcpy(nome,"NULO");
		}else{
			strncpy(nome,R->esq->valor, 5);
		}
		printf(nome);
	}

	gotoxy(58,11);
    if(R != NULL) {
    	if(R->dir == NULL){
    		strcpy(nome,"NULO");
		}else{
			strncpy(nome,R->dir->valor, 5);
		}
		printf(nome);
	}

	do{
	    gotoxy(5,14);
	    printf("OPCAO DESEJADA (S = SAIR ... E = Esquerda ... D = Direita): ");
	    resp = getchar();
	    resp = toupper(resp);
	}while((resp != 'D') && (resp != 'E') && (resp != 'S'));
	
	if (resp != 'S'){
		if(resp == 'D'){
			visualiza(R->dir, R);
		}
		
		if(resp == 'E'){
			visualiza(R->esq, R);
		}
	}	
}

void visualizarArvore2(TNodo *R){
	char nome[5];
	char resp;
	
	system("CLS");
	printf("\n\n\t\t\t=====| VISUALIZACAO da ARVORE AVL |=====\n");
	
	gotoxy(38,5);
	printf("RAIZ");
	gotoxy(40,6);
	printf("|");
	gotoxy(40,7);
	printf("V");

    gotoxy(38,9);
    if (R == NULL){
        strcpy(nome,"NULO");
	} else {
		strncpy(nome, R->valor, 5);
	}
	printf(nome);
	
	gotoxy(28,11);
    if(R != NULL) {
    	if(R->esq == NULL){
    		strcpy(nome,"NULO");
		}else{
			strncpy(nome,R->esq->valor, 5);
		}
		printf(nome);
	}
    
	gotoxy(48,11);
    if(R != NULL) {
    	if(R->dir == NULL){
    		strcpy(nome,"NULO");
		}else{
			strncpy(nome,R->dir->valor, 5);
		}
		printf(nome);
	}
//=============================================== ESQUERDA ===========================================	
	gotoxy(33,13);
    if(R != NULL) {
    	if(R->esq == NULL){
    		strcpy(nome,"NULO");
		}else{
			if(R->esq->esq == NULL){
				strcpy(nome,"NULO");	
			}else{
				strncpy(nome,R->esq->esq->valor, 5);
			}	
		}
	}
    printf(nome);
    
	gotoxy(23,13);
    if(R != NULL) {
    	if(R->esq == NULL){
    		strcpy(nome,"NULO");
		}else{
			if(R->esq->dir == NULL){
				strcpy(nome,"NULO");	
			}else{
				strncpy(nome,R->esq->dir->valor, 5);
			}	
		}
	}
	printf(nome);

//====================================== DIREITA ==============================================

	gotoxy(43,13);
    if(R != NULL) {
    	if(R->dir == NULL){
    		strcpy(nome,"NULO");
		}else{
			if(R->dir->esq == NULL){
				strcpy(nome,"NULO");	
			}else{
				strncpy(nome,R->dir->esq->valor, 5);
			}	
		}
	}
    printf(nome);
    
	gotoxy(53,13);
    if(R != NULL) {
    	if(R->dir == NULL){
    		strcpy(nome,"NULO");
		}else{
			if(R->dir->dir == NULL){
				strcpy(nome,"NULO");	
			}else{
				strncpy(nome,R->dir->dir->valor, 5);
			}	
		}
	}
	printf(nome);

//=========================================== MENU ========================================================	
	do{
	    gotoxy(5,16);
	    printf("OPCAO DESEJADA (S = SAIR A = 1 Esq. B = 1 Dir. C = 2 Esq. D = 2 Dir.): ");
	    resp = getchar();
	    resp = toupper(resp);
	}while((resp != 'A') && (resp != 'B') && (resp != 'C') && (resp != 'D')&& (resp != 'S'));
	
	if (resp != 'S'){
		
		if(resp == 'A'){
			visualiza2(R->esq->esq, R->esq);
			
		}else if(resp == 'B'){
			visualiza2(R->esq->dir, R->esq);
			
		}else if(resp == 'C'){
			visualiza2(R->dir->esq, R->dir);
			
		}else if(resp == 'D'){
			visualiza2(R->dir->dir, R->dir);
		}
	}	
}

void visualiza(TNodo *R, TNodo *Pai){
    char resp;
	char nome[5];
	
	system("CLS");
	printf("\n\n\t\t\t=====| VISUALIZACAO da ARVORE AVL |=====\n");
	
	gotoxy(38,5);
	strncpy(nome, Pai->valor, 5);
	printf(nome);
	gotoxy(40,6);
	printf("|");
	gotoxy(40,7);
	printf("|");
	gotoxy(40,8);
	printf("V");

    gotoxy(38,9);
    if (R == NULL){
        strcpy(nome,"NULO");
	} else {
		strncpy(nome, R->valor, 5);
	}
	printf(nome);
	
	gotoxy(18,11);
    if(R != NULL) {
    	if(R->esq == NULL){
    		strcpy(nome,"NULO");
		}else{
			strncpy(nome,R->esq->valor, 5);
		}
		printf(nome);
	}
	
    
	gotoxy(58,11);
    if(R != NULL) {
    	if(R->dir == NULL){
    		strcpy(nome,"NULO");
		}else{
			strncpy(nome,R->dir->valor, 5);
		}
		printf(nome);
	}

   if (R != NULL){
    	do{
	        gotoxy(5,14);
	        printf("OPCAO DESEJADA (S = SAIR ... E = Esquerda ... D = Direita): ");
    	    resp = getchar();
    	    resp = toupper(resp);
    	}while((resp != 'D') && (resp != 'E') && (resp != 'S'));
	
    	if (resp != 'S'){
	    	if(resp == 'D'){
		    	visualiza(R->dir, R);
    		}
		
	    	if(resp == 'E'){
		    	visualiza(R->esq, R);
    		}
    	}
   }		
}

void visualiza2(TNodo *R, TNodo *Pai){
    char resp;
	char nome[5];
	
	system("CLS");
	printf("\n\n\t\t\t=====| VISUALIZACAO da ARVORE AVL |=====\n");
	
	gotoxy(38,5);
	strncpy(nome, Pai->valor, 5);
	printf(nome);
	gotoxy(40,6);
	printf("|");
	gotoxy(40,7);
	printf("V");

    gotoxy(38,9);
    if (R == NULL){
        strcpy(nome,"NULO");
	} else {
		strncpy(nome, R->valor, 5);
	}
	printf(nome);
	
	gotoxy(28,11);
    if(R != NULL) {
    	if(R->esq == NULL){
    		strcpy(nome,"NULO");
		}else{
			strncpy(nome,R->esq->valor, 5);
		}
		printf(nome);
	}
    
	gotoxy(48,11);
    if(R != NULL) {
    	if(R->dir == NULL){
    		strcpy(nome,"NULO");
		}else{
			strncpy(nome,R->dir->valor, 5);
		}
		printf(nome);
	}
//=============================================== ESQUERDA ===========================================	
	gotoxy(33,13);
    if(R != NULL) {
    	if(R->esq == NULL){
    		strcpy(nome,"NULO");
		}else{
			if(R->esq->esq == NULL){
				strcpy(nome,"NULO");	
			}else{
				strncpy(nome,R->esq->esq->valor, 5);
			}	
		}
	}
    printf(nome);
    
	gotoxy(23,13);
    if(R != NULL) {
    	if(R->esq == NULL){
    		strcpy(nome,"NULO");
		}else{
			if(R->esq->dir == NULL){
				strcpy(nome,"NULO");	
			}else{
				strncpy(nome,R->esq->dir->valor, 5);
			}	
		}
	}
	printf(nome);

//====================================== DIREITA ==============================================

	gotoxy(43,13);
    if(R != NULL) {
    	if(R->dir == NULL){
    		strcpy(nome,"NULO");
		}else{
			if(R->dir->esq == NULL){
				strcpy(nome,"NULO");	
			}else{
				strncpy(nome,R->dir->esq->valor, 5);
			}	
		}
	}
    printf(nome);
    
	gotoxy(53,13);
    if(R != NULL) {
    	if(R->dir == NULL){
    		strcpy(nome,"NULO");
		}else{
			if(R->dir->dir == NULL){
				strcpy(nome,"NULO");	
			}else{
				strncpy(nome,R->dir->dir->valor, 5);
			}	
		}
	}
	printf(nome);

//=========================================== MENU ========================================================	
	do{
	    gotoxy(5,16);
	    printf("OPCAO DESEJADA (S = SAIR A = 1 Esq. B = 1 Dir. C = 2 Esq. D = 2 Dir.): ");
	    resp = getchar();
	    resp = toupper(resp);
	}while((resp != 'A') && (resp != 'B') && (resp != 'C') && (resp != 'D')&& (resp != 'S'));
	
	if (resp != 'S'){
		
		if(resp == 'A'){
			visualiza2(R->esq->esq, R->esq);
			
		}else if(resp == 'B'){
			visualiza2(R->esq->dir, R->esq);
			
		}else if(resp == 'C'){
			visualiza2(R->dir->esq, R->dir);
			
		}else if(resp == 'D'){
			visualiza2(R->dir->dir, R->dir);
		}
	}	
}

void excluirNome(TNodo **raiz){
	
	char nome[50];
	
	printf("\n\n\t Digite o nome: ");
	fflush(stdin);
	gets(nome);
	
	TNodo *aux = exclui(raiz, nome);
	
	if(aux == NULL){
		printf("\n\n\t No nao Encontrado!\n\n");
	}else{
		printf("\n\n\t No Excluido Com Sucesso!\n\n");
	}
	
	system("PAUSE");
	system("CLS");
}

TNodo *exclui(TNodo **raiz, char *nome){
	
    if ((*raiz) == NULL){
    	return NULL;
    
    }else if (strcmp((*raiz)->valor, nome) == 1){
		(*raiz)->esq = exclui(&(*raiz)->esq, nome);
    	
    }else if (strcmp((*raiz)->valor, nome) == -1){
		(*raiz)->dir = exclui(&(*raiz)->dir, nome);
		
    }else{
    	
    	if(((*raiz)->esq == NULL) && ((*raiz)->dir == NULL)){
    		
    		//Nó (a ser excluído) SEM FILHOS...
			free(*raiz);
    		*raiz = NULL;
    		
    	} else if ((*raiz)->esq == NULL){
    		
    		//Nó (a ser excluído) tem apena UM FILHO à direita...
    		
    		TNodo *temp = *raiz;
			*raiz = (*raiz)->dir;
    		free(temp);
    		
    	} else if ((*raiz)->dir == NULL){
    		
    		//Nó (a ser excluído) tem apena UM FILHO à esquerda ...
    		
			TNodo *temp = *raiz;
    		*raiz = (*raiz)->esq;
    		free(temp);
    		
    	} else {
    		
    		//Nó (a ser excluído) tem DOIS FILHOS ...
    		TNodo *filho = (*raiz)->esq;
    		
    		while(filho->dir != NULL){
    			filho = filho->dir;
			}
    		
    		strcpy((*raiz)->valor, filho->valor);
    		strcpy(filho->valor, nome);
    		
    		(*raiz)->esq = exclui(&(*raiz)->esq, nome);
    		
    	}
    }
    return *raiz;
}

void gotoxy(int coluna, int linha){ 
        COORD point; 
        point.X = coluna; point.Y = linha; 
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point); 
}

void emOrdem(TNodo *R){
	if (R != NULL){
		emOrdem(R->esq);
		printf("[%s]\n",R->valor);
		emOrdem(R->dir);
	}
}

