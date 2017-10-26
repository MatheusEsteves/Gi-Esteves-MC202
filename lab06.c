/*
  Nome: Matheus Esteves Zanoto   RA: 184256
  Nome: Giovanna Batalha         RA: 

  Objetivos:

  Entradas:

  Saídas:
*/

#include <stdio.h>
#include <stdlib.h>

typedef enum Estado{
  LIVRE,OCUPADO,PARTICIONADO
} Estado;

typedef struct Processo{
  int codigo;
  int tamanho;
} Processo;

typedef struct Memoria{
  int valor; //Guarda a potencia exemplo 10 é como se fosse 2^10
  Estado estado;
  int fragmentacao;
  Processo* processo;
} Memoria;

typedef struct No{
  Memoria memoria;
  struct No* esq;
  struct No* dir;
} No;

typedef struct Arvore{
  No* raiz;
} Arvore;

void inicializarNo(No* no, int valor);
void inicializarArvore(Arvore* arvore, int valor);
void percorrerNoParaExcluir(No* no, int cod);
void excluirNoFolha(Arvore* arvore, int cod);

int iniciarProcesso(No* no, Processo processo);
void finalizarProcesso(Arvore* arvore, int cod);
int calcularFragmentacao(Arvore* arvore);
void relatorioSistema(Arvore* arvore);
void imprimirSementesGeradoras(Arvore* arvore);
void imprimirProcessos(Arvore* arvore);
int pot(int base, int expoente);



//teste eeeee gi
int main(){
  int potencia;
  scanf("%d",&potencia);

  Arvore arvore;
  inicializarArvore(&arvore,potencia);

  int op;
  while(scanf("%d", &op) != EOF){
    switch(op){
	  case 1:{
	  	int cod, size;

	  	scanf("%d", &cod);
	  	scanf("%d", &size);
	  	
	  	//Testando potencia
		int pote = pot(2, 10);
		printf("pot 2^10: %d\n",pote);

	  } break;
	  case 2:{

	  } break;
	  case 3:{

	  } break;
	  case 4:{

	  } break;
	  case 5:{

	  } break;
	  default:{

	  }
    }
  }	
}

//Função que retorna potência
int pot(int base, int expoente){
    int i;
    int resp = 1;

    if(expoente == 0){
    	return resp;
    }

    for (i = 0; i < expoente; i++){
    	resp *= base;	
    }

    return resp;
}

//Função recursiva, recebe inicialmente a raíz da árvore
int iniciarProcesso(No* no, Processo processo){
	int metadeAtual = pot(2, no->memoria.valor-1);
	int valorAtual = pot(2, no->memoria.valor);

	//if(processo == NULL){printf("ERRO[iniciarProcesso] Processo nulo\n");}

	if(processo.tamanho > metadeAtual && processo.tamanho <= valorAtual){
		//Chegou no nó que cabe o processo, mas está ocupado
		if(no->memoria.estado == OCUPADO){
			return 0;
		}

		//Chegou no nó que cabe o processo e adicionou o processo
		*(no->memoria.processo) = processo;
		no->memoria.estado = OCUPADO;
		return 1;
	}

	if(no->esq == NULL && no->dir == NULL){
		no->memoria.estado = PARTICIONADO;
	}

	if(no->esq == NULL){
		no->esq = malloc(sizeof(No*));
		inicializarNo(&(*no->esq), no->memoria.valor-1);
	}

	if(no->dir == NULL){
		no->dir = malloc(sizeof(No*));
		inicializarNo(&(*no->dir), no->memoria.valor-1);
	}

	int esqLivre = iniciarProcesso(no->esq, processo);
	int dirLivre;

	if(esqLivre == 0){
		dirLivre = iniciarProcesso(no->dir, processo);

		if(dirLivre==0){
			return 0;
		}
	}

	return 1;
	
}

void inicializarNo(No* no, int valor){
  no->esq = NULL;
  no->dir = NULL;
  no->memoria.valor = valor;
  no->memoria.estado = LIVRE;
  no->memoria.fragmentacao = 0;
  no->memoria.processo = malloc(sizeof(Processo));
} 

void inicializarArvore(Arvore* arvore, int valor){
  arvore->raiz = (No*)malloc(sizeof(No));
  inicializarNo(&(*arvore->raiz),valor);
}

void percorrerNoParaExcluir(No* no, int cod){
  if (no->esq == NULL && no->dir == NULL && no->memoria.processo->codigo == cod)
    free(no);
  else{
    if (no->esq != NULL)
      percorrerNoParaExcluir(&(*no->esq),cod);
    if (no->dir != NULL)
      percorrerNoParaExcluir(&(*no->dir),cod);
  }
}

void excluirNoFolha(Arvore* arvore, int cod){
  No* raiz = arvore->raiz;
  percorrerNoParaExcluir(&(*arvore->raiz),cod);
}
