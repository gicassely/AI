#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define UP vizinhos[0]
#define DOWN vizinhos[1]
#define LEFT vizinhos[2]
#define RIGHT vizinhos[3]


/*-----------------------------------------------------------
-------------------------------------------------------------
Itens faltantes:
-- JOGADOR INTELIGENTE
-Escolhe a proxima core pelas n jogada que deixarao o tamanho da borda maior
-------------------------------------------------------------
-----------------------------------------------------------*/

typedef struct no *no;
struct no{
	int x; //Eixo x
	int y; //Eixo y (de cima para baixo)
	no vizinhos[4];//Ponteiro de vizinhos (CIMA|BAIXO|ESQUERDA|DIREITA)
	no prox;//Ponteiro para lista de uniao e lista de borda
	no proxB;
	int cor;
	int visitado;//Indica se o no ja foi inserido na borda ou na união
	int examinado;//Indica se ja foi examinado como possivel proxima borda
};

typedef struct lista *lista;
struct lista{
	no primeiro;
	int tam;
};
/*--------------------------------------------------
--------------------------------------------------*/
no **aloca_matriz(int n,int m){
	no **retorno = malloc(n*sizeof(no*));
	for (int i = 0; i < n; ++i)
	{
		retorno[i] = malloc(m*sizeof(no));
		for (int j = 0; j < m; ++j)
		{
			retorno[i][j] = malloc(sizeof(struct no));
		}
	}
	return retorno;
}

void libera_matriz(no **matriz,int n){
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			free(matriz[i][j]);
		}
		free(matriz[i]);
	}
	free(matriz);
}

lista inicializa_lista(){
	lista l = malloc(sizeof(struct lista));
	l->primeiro = NULL;
	l->tam = 0;
	return l;
}

void libera_lista(lista l){
	free(l);
}

void libera_borda(lista *borda,int n_cor){
	for (int i = 0; i < n_cor; ++i)
	{
		libera_lista(borda[i]);
	}
	free(borda);
}

no **cria_tabuleiro_simples(int n,int  c){
	int i,j;
	no **matriz = aloca_matriz(n,n);
	srand((unsigned int)time(NULL));

	matriz[0][0]->cor = rand()% c;
	matriz[0][0]->x = 0;
	matriz[0][0]->y = 0;
	matriz[0][0]->visitado = 0;	
	matriz[0][0]->examinado = 0;	
	matriz[0][0]->prox = NULL;
	matriz[0][0]->UP = NULL;
	matriz[0][0]->DOWN = matriz[1][0];
	matriz[0][0]->LEFT = NULL;
	matriz[0][0]->RIGHT = matriz[0][1];
	for (j = 1; j < n-1; ++j)
	{
			no n = matriz[0][j];
			n->cor = rand()% c;
			n->x = j;
			n->y = 0;
			n->visitado = 0;
			n->examinado = 0;
			n->prox = NULL;
			n->UP = NULL;
			n->DOWN = matriz[1][j];
			n->LEFT = matriz[0][j-1];
			n->RIGHT = matriz[0][j+1];
	}
	matriz[0][j]->cor = rand()% c;
	matriz[0][j]->x = j;
	matriz[0][j]->y = 0;
	matriz[0][j]->visitado = 0;
	matriz[0][j]->examinado = 0;
	matriz[0][j]->prox = NULL;
	matriz[0][j]->UP = NULL;
	matriz[0][j]->DOWN = matriz[1][j];
	matriz[0][j]->LEFT = matriz[0][j-1];
	matriz[0][j]->RIGHT = NULL;

	for (i = 1; i < n-1; ++i){
		matriz[i][0]->cor = rand()% c;
		matriz[i][0]->x = 0;
		matriz[i][0]->y = i;
		matriz[i][0]->visitado = 0;
		matriz[i][0]->examinado = 0;
		matriz[i][0]->prox = NULL;
		matriz[i][0]->UP = matriz[i-1][0];
		matriz[i][0]->DOWN = matriz[i+1][0];
		matriz[i][0]->LEFT = NULL;
		matriz[i][0]->RIGHT = matriz[i][1];
		for (j = 1; j < n-1; ++j){
			no n = matriz[i][j];
			n->cor = rand()% c;
			n->x = j;
			n->y = i;
			n->visitado = 0;
			n->examinado = 0;
			n->prox = NULL;
			n->UP = matriz[i-1][j];
			n->DOWN = matriz[i+1][j];
			n->LEFT = matriz[i][j-1];
			n->RIGHT = matriz[i][j+1];
		}
		matriz[i][j]->cor = rand()% c;
		matriz[i][j]->x = j;
		matriz[i][j]->y = i;
		matriz[i][j]->visitado = 0;
		matriz[i][j]->examinado = 0;
		matriz[i][j]->prox = NULL;
		matriz[i][j]->UP = matriz[i-1][j];
		matriz[i][j]->DOWN = matriz[i+1][j];
		matriz[i][j]->LEFT = matriz[i][j-1];
		matriz[i][j]->RIGHT = NULL;
	}
	matriz[i][0]->cor = rand()% c;
	matriz[i][0]->x = 0;
	matriz[i][0]->y = i;
	matriz[i][0]->visitado = 0;
	matriz[i][0]->examinado = 0;
	matriz[i][0]->prox = NULL;
	matriz[i][0]->UP = matriz[i-1][0];
	matriz[i][0]->DOWN = NULL;
	matriz[i][0]->LEFT = NULL;
	matriz[i][0]->RIGHT = matriz[i][1];
	for (j = 1; j < n-1; ++j)
	{
		matriz[i][j]->cor = rand()% c;
		matriz[i][j]->x = j;
		matriz[i][j]->y = i;
		matriz[i][j]->visitado = 0;
		matriz[i][j]->examinado = 0;
		matriz[i][j]->prox = NULL;
		matriz[i][j]->UP = matriz[i-1][j];
		matriz[i][j]->DOWN = NULL;
		matriz[i][j]->LEFT = matriz[i][j-1];
		matriz[i][j]->RIGHT = matriz[i][j+1];
	}
	matriz[i][j]->cor = rand()% c;
	matriz[i][j]->x = j;
	matriz[i][j]->y = i;
	matriz[i][j]->visitado = 0;
	matriz[i][j]->examinado = 0;
	matriz[i][j]->prox = NULL;
	matriz[i][j]->UP = matriz[i-1][j];
	matriz[i][j]->DOWN = NULL;
	matriz[i][j]->LEFT = matriz[i][j-1];
	matriz[i][j]->RIGHT = NULL;
	return matriz;
}

void imprime_tabuleiro(no ** matriz,int n){
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (matriz[i][j]->visitado == 1){
				printf("   [%d]", matriz[i][j]->cor);
			}
			else if(matriz[i][j]->examinado == 1) {
				printf("   *%d*", matriz[i][j]->cor);
			}else{
				printf("    %d ", matriz[i][j]->cor);
			}
		}
		printf("\n");
	}
}

void imprime_lista(lista l){
	no nb;
	if (l->primeiro == NULL){
		printf("[]\n");
		return;
	}
	printf("[");
	for (nb = l->primeiro; NULL != nb->prox; nb=nb->prox)
	{
		printf("(%d,%d)%d ,",nb->y,nb->x,nb->cor);
	}
	printf("(%d,%d)%d]\n",nb->y,nb->x,nb->cor);
}

void imprime_listaB(lista l){
	no nb;
	if (l->primeiro == NULL){
		printf("[]\n");
		return;
	}
	printf("[");
	for (nb = l->primeiro; NULL != nb->proxB; nb=nb->proxB)
	{
		printf("(%d,%d)%d ,",nb->y,nb->x,nb->cor);
	}
	printf("(%d,%d)%d]\n",nb->y,nb->x,nb->cor);
}

void insereLista(lista l,no n){
	l->tam++;
	//Caso lista vazia
	if (l->primeiro == NULL){
		l->primeiro = n;
		n->prox = NULL;
		return;
	}
	n->prox = l->primeiro;
	l->primeiro = n;
}

void insereListaB(lista l,no n){
	l->tam++;
	//Caso lista vazia
	if (l->primeiro == NULL){
		l->primeiro = n;
		n->proxB = NULL;
		return;
	}
	n->proxB = l->primeiro;
	l->primeiro = n;
}

void acha_borda(no n,int cor,lista *borda,lista uniao){
	//Base: Se n for nó nulo ou se ja foi visitado
	if ((NULL == n)||(n->visitado == 1)){
		return;
	}
	//Base: Se n for nó Borda
	if(n->cor != cor){
		n->visitado = 1;
		//printf("INSERIU BORDA:(%d,%d)\n",n->y,n->x);
		insereLista(borda[n->cor],n);
		return;
	}

	//Procura a borda nos vizinhos
	n->visitado = 1;
	insereLista(uniao,n);
	acha_borda(n->UP,cor,borda,uniao);
	acha_borda(n->DOWN,cor,borda,uniao);
	acha_borda(n->LEFT,cor,borda,uniao);
	acha_borda(n->RIGHT,cor,borda,uniao);
}


lista* inicializa_borda(no **matriz,int n,lista uniao,int n_cor){
	lista *borda = malloc(n_cor*sizeof(lista));
	for(int i = 0; i<n_cor; ++i){
		borda[i] = inicializa_lista();
	}
	int cor = matriz[0][0]->cor;
	acha_borda(matriz[0][0],cor,borda,uniao);
	return borda;
}


void colorir(no **matriz,lista *borda,int cor,lista uniao){
	no nb;
	no nb_aux;
	no un_aux;
	no n;

	//Muda a cor das posicoes ja alcancadas
	for(un_aux = uniao->primeiro; NULL != un_aux; un_aux= un_aux->prox){
		un_aux->cor = cor;
	}

	nb = borda[cor]->primeiro;
	while( NULL != nb){
		nb_aux = nb;
		nb = nb->prox;
		insereLista(uniao,nb_aux);
		acha_borda(nb_aux->UP,cor,borda,uniao);
		acha_borda(nb_aux->DOWN,cor,borda,uniao);
		acha_borda(nb_aux->LEFT,cor,borda,uniao);
		acha_borda(nb_aux->RIGHT,cor,borda,uniao);
	}
	borda[cor]->primeiro = NULL;
	borda[cor]->tam = 0;
}

int escolhe_cor_aleatorio(lista *borda,int cor,int n_cor){
	int aux = (int) rand() % n_cor;
	int i;
	for (i = (aux+1)%n_cor; i != aux; i = (i+1)%n_cor){
		if (borda[i]->tam > 0)
			return i;
	}
	return aux;
}

void possivel_borda(no n,int cor,lista *bordaB, lista uniaoB){
	//Base: Se n for nó nulo ou se ja foi visitado ou ja foi examinado
	if ((NULL == n)||(n->visitado == 1)||(n->examinado == 1)){
		return;
	}
	//Base: Se n for nó Borda
	if(n->cor != cor){
		n->examinado = 1;
		insereListaB(bordaB[n->cor],n);
		return;
	}

	//Procura a borda nos vizinhos
	n->examinado = 1;
	insereListaB(uniaoB,n);
	possivel_borda(n->UP,cor,bordaB,uniaoB);
	possivel_borda(n->DOWN,cor,bordaB,uniaoB);
	possivel_borda(n->LEFT,cor,bordaB,uniaoB);
	possivel_borda(n->RIGHT,cor,bordaB,uniaoB);
}


void encontra_prox_bordas(lista borda,lista *bordaB,lista uniaoB, int cor){
	no nb = borda->primeiro;
	while(NULL != nb){
		// printf("testando (%d,%d):%d\n",nb->y,nb->x,nb->cor);
		possivel_borda(nb->UP,cor,bordaB,uniaoB);
		possivel_borda(nb->DOWN,cor,bordaB,uniaoB);
		possivel_borda(nb->LEFT,cor,bordaB,uniaoB);
		possivel_borda(nb->RIGHT,cor,bordaB,uniaoB);
		nb = nb->prox;
	}
}

void reseta_listaB(lista l){
	for (no n = l->primeiro; NULL != n; n = n->proxB){
		n->examinado = 0;
	}
	l->primeiro = NULL;
	l->tam = 0;	
}

void reseta_bordaB(lista *borda,int n_cor){
	for (int i = 0; i < n_cor; ++i){
		reseta_listaB(borda[i]);
	}
}

void troca_listas(lista a,lista b){
	for (no n = b->primeiro; NULL !=n ; n = n->prox){
		n->examinado = 0;
		n->prox = n->proxB;
		n->proxB = NULL;		
	}
	// no n = b->primeiro;
	// while(n != NULL){
	// 	n->examinado = 0;
	// 	n->prox = n->proxB;
	// 	n->proxB = NULL;
	// 	n = n->prox;
	// }
	a->primeiro =  b->primeiro;
	a->tam  = b->tam;
	b->primeiro = NULL;
	b->tam = 0;	
//	reseta_lista(b);
}

void troca_bordas(lista *bordaA,lista *bordaB,int n_cor){
	for (int i = 0; i < n_cor; ++i){
		troca_listas(bordaA[i],bordaB[i]);
	}
}

int tam_borda(lista *borda,int n_cor){
	int tam = 0;
	for (int i = 0; i < n_cor; ++i){
		tam += borda[i]->tam;
	}
	return tam;
}

int escolhe_cor_max_borda(lista *borda,lista *bordaA,lista *bordaB,
						  lista uniaoA,lista uniaoB,
						  int n_cor,int cor_atual, no **matriz){
	int tamB = 0;
	int tamA = 0;
	int cor;
	int i = (cor_atual+1) % n_cor;

	cor  = i;
	encontra_prox_bordas(borda[i],bordaB,uniaoB,i);
	// printf("Borda B COR(%d) TAM(%d):\n",i,tamB);
	// for (int j = 0; j < n_cor; ++j){
	// 	imprime_listaB(bordaB[j]);
	// }
	// imprime_tabuleiro(matriz,n_cor	);
	tamA = tam_borda(bordaB,n_cor);
	troca_bordas(bordaA,bordaB,n_cor);
	troca_listas(uniaoA,uniaoB);

	// printf("######################################################\n");
	// printf("##CALCULANDO PROXIMA BORDA###(%d)#####################\n",cor_atual);
	// printf("i: %d\n",i );

	for (i = ((i+1)%n_cor); i != cor_atual; i = ((i+1)%n_cor)){
		encontra_prox_bordas(borda[i],bordaB,uniaoB,i);
		tamB = tam_borda(bordaB,n_cor);
		// printf("Entrou i: %d\n",i );
		// printf("Borda B COR(%d) TAM(%d):\n",i,tamB);
		// for (int j = 0; j < n_cor; ++j){
		// 	imprime_lista(bordaA[j]);
		// }
		// printf("Borda B COR(%d) TAM(%d):\n",i,tamB);
		// for (int j = 0; j < n_cor; ++j){
		// 	imprime_listaB(bordaB[j]);
		// }
		// imprime_tabuleiro(matriz,n_cor);

		if(tamA < tamB){
			// printf("ENTROU\n");
			tamA = tamB;
			cor = i;
			troca_bordas(bordaA,bordaB,n_cor);
			troca_listas(uniaoA,uniaoB);
		}else{
			reseta_bordaB(bordaB,n_cor);
			reseta_listaB(uniaoB);
		}
	// printf("------------------------------------------------------\n");		
	}
	// printf("######################################################\n");
	return cor;
}

void concatena_lista(lista a, lista b){
	if (b->tam == 0)
		return;
	if(a->tam == 0){
		a->primeiro = b->primeiro;
		a->tam = b->tam;
		return;
	}
	no n = b->primeiro;
	while(NULL != n->prox){
		n = n->prox;
	}
	n->prox = a->primeiro;
	a->primeiro = b->primeiro;
	a->tam += b->tam;

}

void colorir_max_borda(lista *borda,lista *bordaA,lista uniao,lista uniaoA,int prox_cor,int n_cor){
	for (int i = 0; i < n_cor; ++i){
		for (no n = bordaA[i]->primeiro; n != NULL; n=n->prox){
			n->visitado = 1;
		}
	}
	for (no n = uniaoA->primeiro; n != NULL; n=n->prox){
		n->visitado = 1;
	}
	for (int i = 0; i < n_cor; ++i){
		concatena_lista(borda[i], bordaA[i]);
	}
	concatena_lista(uniao,uniaoA);
	concatena_lista(uniao,borda[prox_cor]);
	borda[prox_cor]->primeiro = NULL;
	borda[prox_cor]->tam = 0;
	for(no n = uniao->primeiro; n != NULL; n = n->prox){
		n->cor = prox_cor;
	}
}

void resolvedor_max_bordas(no **matriz,int n,int n_cor){
	lista uniao = inicializa_lista();
	lista *borda = inicializa_borda(matriz,n,uniao,n_cor);
	lista *bordaA = malloc(n_cor*sizeof(lista));
	lista *bordaB = malloc(n_cor*sizeof(lista));

	for (int i = 0; i < n_cor; ++i){
		bordaA[i] = inicializa_lista();
		bordaB[i] = inicializa_lista();
	}
	lista uniaoA = inicializa_lista();
	lista uniaoB = inicializa_lista();

	int cont = 0;
	int prox_cor = matriz[0][0]->cor;
	int tam_matriz  = (n*n);
	while( (tam_borda(borda,n_cor) + uniao->tam) < tam_matriz){
	 	// printf("BORDA(%d) + UNIAO (%d)= (%d)|TOTAL (%d)\n",tam_borda(borda,n_cor),
			// 												uniao->tam,(tam_borda(borda,n_cor) + uniao->tam),tam_matriz );
	// while(cont < 4){
//	while( (tam_borda(borda,n_cor) >0)){
		prox_cor = escolhe_cor_max_borda(borda,bordaA,bordaB,uniaoA,uniaoB,n_cor,prox_cor,matriz);
		printf("===== Cont: %d ===== Cor: %d =========================================\n",cont,prox_cor);
		printf("===TABULEIRO==========================================================\n");
		imprime_tabuleiro(matriz,n);
		// printf("===BORDA==============================================================\n");
		// for (int i = 0; i < n_cor; ++i){
		// 	imprime_lista(borda[i]);
		// }
		 printf("===PROX_BORDA=========================================================\n");
		 for (int i = 0; i < n_cor; ++i){
			imprime_lista(bordaA[i]);
		}
		// printf("===UNIAO==============================================================\n");
		// imprime_lista(uniao);
		// printf("===PROX_UNIAO=========================================================\n");
		// imprime_lista(uniaoA);
		// printf("\n**********************************************************************\n\n\n");
		colorir_max_borda(borda,bordaA,uniao,uniaoA,prox_cor,n_cor);
		cont++;

	}
	 // printf("BORDA(%d) + UNIAO (%d)= (%d)|TOTAL (%d)\n",tam_borda(borda,n_cor),
		// 												uniao->tam,(tam_borda(borda,n_cor) + uniao->tam),tam_matriz );
	prox_cor = 0;
	while(tam_borda(borda,n_cor) > 0){
		for (; borda[prox_cor]->tam == 0; prox_cor++);
		printf("===== Cont: %d ===== Cor: %d =========================================\n",cont,prox_cor);
		printf("===TABULEIRO==========================================================\n");
		imprime_tabuleiro(matriz,n);
		// printf("===BORDA==============================================================\n");
		// for (int i = 0; i < n_cor; ++i){
		// 	imprime_lista(borda[i]);
		// }
		// printf("===PROX_BORDA=========================================================\n");
		// for (int i = 0; i < n_cor; ++i){
		// 	imprime_lista(bordaA[i]);
		// }
		// printf("===UNIAO==============================================================\n");
		// imprime_lista(uniao);
		// printf("===PROX_UNIAO=========================================================\n");
		// imprime_lista(uniaoA);
		printf("\n**********************************************************************\n\n\n");
		colorir(matriz,borda,prox_cor,uniao);
		cont++;
	}
	printf("===== Cont: %d ===== Cor: x  =========================================\n",cont);
	printf("===TABULEIRO==========================================================\n");
	imprime_tabuleiro(matriz,n);
	printf("\n**********************************************************************\n\n\n");
	libera_borda(borda,n_cor);
	libera_borda(bordaA,n_cor);
	libera_borda(bordaB,n_cor);
	libera_lista(uniao);
	libera_lista(uniaoA);
	libera_lista(uniaoB);

}

void resolvedor_aleatorio(no **matriz,int n,int n_cor){
	lista uniao = inicializa_lista();
	lista *borda = inicializa_borda(matriz,n,uniao,n_cor);
	int cont = 0;
	int prox_cor;
	int tam_borda = 0;
	for (int i = 0; i < n_cor; ++i)
	{
		tam_borda += borda[i]->tam;
	}
	while(tam_borda > 0){
		prox_cor = escolhe_cor_aleatorio(borda,prox_cor,n_cor);
		printf("======================================================================\n");
		printf("===== Cont: %d ===== Cor: %d =========================================\n",cont,prox_cor);
		printf("===TABULEIRO==========================================================\n");
		imprime_tabuleiro(matriz,n);
		colorir(matriz,borda,prox_cor,uniao);
		printf("\n**********************************************************************\n\n\n");
		tam_borda = 0;
		for (int i = 0; i < n_cor; ++i)
		{
			tam_borda += borda[i]->tam;
		}
		cont++;
	}
	printf("======================================================================\n");
	printf("===== Cont: %d ===== Cor: %d =========================================\n",cont,prox_cor);
	printf("======================================================================\n");
	imprime_tabuleiro(matriz,n);
	printf("======================================================================\n");
	printf("**********************************************************************\n");

	libera_borda(borda,n_cor);
	libera_lista(uniao);
}


/*----------------------------------------------------------
-----Resolvedor do jogo floodit --------------------------
-----Euristica busca melhor caminho através da------------
-----escolha da maior borda resultante--------------------
----------------------------------------------------------*/
/*void resolvedor_max_bordas(no **matriz,int n,int c){
	lista uniao = inicializa_lista();
	lista borda = inicializa_borda(matriz,n,uniao);
	int cont = 0;
	int prox_cor;
	while(borda->tam > 0){
		
	}
}
*/
int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		printf("<flood> <nMatriz> <nCores>\n");
		exit(0);
	}

	//Dimensao da matriz nxn
	int n = atoi(argv[1]);
	// Numero de cores da matriz
	int c = atoi(argv[2]);
	no **matriz;
	matriz = cria_tabuleiro_simples(n, c);

	//imprime_tabuleiro(matriz,n);
	//resolvedor_aleatorio(matriz,n,c);
	resolvedor_max_bordas(matriz,n,c);
	libera_matriz(matriz,n);
}
