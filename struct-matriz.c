//Desenvolvido por: Cau� Pires Soares - caua-3301
//Data: 28/08/2023

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//Vari�veis de escopo global
int ordem;
int num;

/*Estrutura de cada nodo da matriz*/
typedef struct nodo{
	
	struct nodo * direita;
	struct nodo * baixo;
	int i;
	int j;
	int valor;
	
}Nodo;

/*Estrutura da matriz*/
typedef struct{
	
	Nodo * inicio;
	
}Matriz;

/*Fun��o respons�vel por retornar um ponteiro mara minha matriz*/
Matriz * criarMatriz(){
	
	Matriz * mat = (Matriz *)malloc(sizeof(Matriz));
	mat -> inicio = NULL;
	return mat;
	
}

void construirMatriz(Matriz * mat, int ordem){
	int k = 0; //Controle do for
	int i = 0; //Representa��o linha
	int j = 0; //Representa��o coluna
	for (k; k <= ordem*ordem; k++){
		/*Criando um nodo definitivamente (como medida de seguran�a, o mesmo come�a com 0, o usu�ro poder� alterar futuramente)*/
		Nodo * novo = (Nodo *)malloc(sizeof(Nodo));
		novo -> i = i;
		novo -> j = j;
		novo -> valor = 0;
		novo -> direita = NULL;
		novo -> baixo = NULL;
		if(mat -> inicio == NULL){
			mat -> inicio = novo;
		}
		else{
			Nodo * aux = mat -> inicio;
			if (j < ordem){
			//Ajustando a linha de adi��o de valores
				int a = i;
				while(a > 0 && j != 0){
					aux = aux -> baixo;
					a--;
				}
			
			//Verificando se o elemento ir� se localizar abaixo ou do lado de outro elemento
				if (j == 0){
					while (aux -> baixo != NULL){
						aux = aux -> baixo;
					}
					aux -> baixo = novo;
					j++;
				}
				
			//Ajustando ponteiro para adiconar o 0
				else{
					while(aux -> direita != NULL){
						aux = aux -> direita; 
					}
					aux -> direita = novo;
					j++;	
				}
			}
			
			//Alterando a linha quando atingir o numero da ordem da matriz (tamanho)
			if (j == ordem){
				j = 0;
				i++;
			}
		}
	}	
}

//Printando matriz, basicamente percorrendo por todos os seus valores
void printMatriz(Matriz * mat, int ordem){
	int k = 0, controle = 0, i = 0;
	Nodo * aux = mat -> inicio;
	for (k; k <ordem; k++){	
		int a = i;
		while (a > 0){
			aux = aux -> baixo;
			a--;
		}
		while(controle < ordem){
			printf ("%d    ", aux -> valor);
			aux = aux -> direita;
			controle++;
		}
		printf ("\n");
		i++;
		controle = 0;
		aux  = mat -> inicio;			
	}
	printf ("\n\n");
}

//Adicionar numero
void adicionarNum(Matriz * mat, int i, int j, int num){
	Nodo * aux = mat -> inicio;
	while (i > 0){
		aux = aux -> baixo;
		i--;
	}
	while (aux -> j != j){
		aux = aux -> direita;
	}
	aux -> valor = num;
}	

//Verificar se numero existe na matriz, por pecoorre ela inteira, caso o valor seja encontrado, o subprograma encerra
int existeNum(Matriz * mat, int num, int ordem){
	int k = 0, controle = 0, i = 0;
	Nodo * aux = mat -> inicio;
	for (k; k <ordem; k++){	
		int a = i;
		while (a > 0){
			aux = aux -> baixo;
			a--;
		}
		while(controle < ordem){
			if (num == aux -> valor){
				return 1;
			}
			aux = aux -> direita;
			controle++;
		}
		i++;
		controle = 0;
		aux  = mat -> inicio;			
	}
	return 0;
}

//Informa��es da matriz a ser criada (dimens�es)
void infoMat(Matriz * mat){
	printf ("Informe o tamanho da matriz: \n");
	scanf ("%d", &ordem);
	construirMatriz(mat, ordem);
	
}

//Obtendo o local (id) onde o valor ser� adiconado
void infoInd (Matriz * mat){
	int i, j;
	printf ("Agora, informe os indices da matriz para o valor ser adicionado ( i e j ) entre 0 e %d: \n", ordem-1);
	scanf ("%d%d", &i, &j);
	adicionarNum(mat, i, j, num);
}

//Informa��es para o novo valor a ser adicionado, no caso, o n�mero
void infoAdd(Matriz * mat){
	printf ("Informe um numero : \n");
	scanf ("%d", &num);
	infoInd(mat);
}


void main(){
	
	setlocale(LC_ALL, "portuguese");
	
	int k, quantidade, fazer, continuar, proc;
	//Criando ponteiro para a matriz
	Matriz * mat = criarMatriz();
	//Definindo as dimens�es da matriz
	
	printf ("============= MENU ===========\n\n");
	while(continuar != 0){

		printf ("Configurar matriz (dimens�es) [1]: \n");
		printf ("Adicionar numeros [2]: \n");
		printf ("Exibir matriz [3]: \n");
		printf ("Conferir valor [4]: \n");
		printf ("Encerrar [5]: \n\n");
		scanf ("%d", &fazer);
		
		switch (fazer){
			case 1: infoMat(mat);
				break;
				
			case 2: printf ("Quantos valores ser�o adicionados?\n");
					scanf ("%d", &quantidade);
					for (k = 0; k < quantidade; k++){
						infoAdd(mat);
					}
				break;
				
			case 3:	printMatriz(mat, ordem);
				break;
			
			case 4: printf ("Informe o numero desejado para procurar: \n");
					scanf ("%d", &proc);
	
					if (existeNum(mat, proc, ordem) == 1){
						printf ("\nEXISTE na matriz\n\n");
					}
					else{
						printf ("\nN�O exite na matriz\n\n");
					}
				break;
			
			case 5: printf ("AT� MAIS!\n");
					continuar = 0;
				break;
			
			default: printf ("Op��o inv�lida, tente novamente: \n");
		}
	}
	
	//End - 23:11:27 - 28/08/2023
}
