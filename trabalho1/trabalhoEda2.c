
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 26
#define low 2000000

//estrutura da arvore trie
typedef struct Trie{
	struct Trie *chave[SIZE];
	char flag;
	char *plv;
}Trie, *NoArvore;

//estrutura da lista
typedef struct Lista{
    char *plv;
    struct Lista *prox;
    struct Lista *ant; 
}Lista, *Nolista;

char loW[low];
int menor = 100,min=10;

///////////////////////////////////// Adcionado para salvar palavra mais proxima
char melhorPalavra[999];
int tamanhoMelhorPalavra = 2000000;
///////////////////////////////////// Adcionado para salvar palavra mais proxima


int levenshtein(char *s, char *t) {
	int i,j;
	int ls = strlen(s), lt = strlen(t);
	int d[ls + 1][lt + 1];
 
	for (i = 0; i <= ls; i++)
		for (j = 0; j <= lt; j++)
			d[i][j] = -1;
 
	int dist(int i, int j) {
		if (d[i][j] >= 0) return d[i][j];
 
		int x;
		if (i == ls)
			x = lt - j;
		else if (j == lt)
			x = ls - i;
		else if (s[i] == t[j])
			x = dist(i + 1, j + 1);
		else {
			x = dist(i + 1, j + 1);
 
			int y;
			if ((y = dist(i, j + 1)) < x) x = y;
			if ((y = dist(i + 1, j)) < x) x = y;
			x++;
		}
		return d[i][j] = x;
	}
	return dist(0, 0);}

void inicializaTrie(NoArvore *node){
	
	*node = NULL;}

void inicializaLista(Nolista *l){
	
	*l = NULL;}

void insertWord(NoArvore *node, char *palavra ,char * noPalavra){
	int i;
	
	if(*node == NULL){
		
		*node = (Trie *)malloc(sizeof(Trie));
		
	
		for(i=0;i<SIZE;i++)
		
		(*node)->chave[i]= NULL;
		
		if(palavra[0] != '\0'){
			insertWord(&(*node)->chave[palavra[0] - 'a'], palavra +1,noPalavra);
			(*node)->flag = 0;
		
	
		}else {
			(*node)->flag = 1;
			(*node)->plv = malloc ( (strlen(noPalavra)) * sizeof(char) );
			strcpy((*node)->plv,noPalavra);
		}



		}else{
			 if(palavra[0] != '\0'){
				insertWord(&(*node)->chave[palavra[0] - 'a'], palavra +1,noPalavra);
			
			}else
			(*node)->flag = 1;
		}}

int searchWord(NoArvore node, char *palavra){
	if(node == NULL)
		return 0;
	else
		if(palavra[0] == '\0')
			return (node->flag ? 1:0); 
		else
			return searchWord(node->chave[palavra[0] - 'a'], palavra + 1);}

bool searchList(Nolista l, char *palavra){
	Nolista p;
	for(p = l; (p && (strcmp(p->plv, palavra))); p = p->prox);
	
	return p;}

bool insertOrd (Nolista* l, char *palavra){
	Nolista p;
	if(searchList(*l, palavra)|| !(p = ((Lista*) malloc(sizeof(Lista)))))
	
		return false;

		p->plv= malloc(strlen(palavra));
		strcpy(p->plv,palavra);
		Nolista ant = NULL;
		Nolista q = *l;

	while (q && (strcmp(q->plv,palavra)<0)){
		ant = q;
		q = q->prox;
	}
	if (!ant){
		p->prox = *l;
		*l = p;
	}else{
		p->prox = ant->prox;
		ant->prox = p;
	}
	return true;}

bool insertEnd (Nolista* l, char *palavra){
	Nolista p;
	if(!(p = ((Lista*) malloc(sizeof(Lista)))))
	
		return false;

		p->plv= malloc(strlen(palavra));
		strcpy(p->plv,palavra);
		Nolista ant = NULL;
		Nolista q = *l;

	while (q && (strcmp(q->plv,palavra))){
		ant = q;
		q = q->prox;
	}
	if (!ant){
		p->prox = *l;
		*l = p;
	}else{
		p->prox = ant->prox;
		ant->prox = p;
	}
	return true;}

void imprimeLista(Nolista *l){
	Nolista p;
	for(p = *l; (p!=NULL); p = p->prox)
		printf("%s\n", p->plv);}

void buscaBestWord(NoArvore *no, char *palavra){
	int i;
	int d;
	if ( (*no) != NULL ) {
		if ( (*no)->flag == 1) {
			
			d = levenshtein(palavra,(*no)->plv);	

			if ( d < tamanhoMelhorPalavra  )
				strcpy(melhorPalavra,(*no)->plv);
				tamanhoMelhorPalavra = d;
			//printf("\nAchou %s",(*no)->plv);
		}

		for (i = 0; i < SIZE; ++i)
		{
			if ((*no)->chave[i] != NULL) {
				buscaBestWord(&(*no)->chave[i],palavra);
			}
		}
	}
	else
		return;
}


int main(int argc, char *argv[]){

	FILE *file1, *file2;
	NoArvore arvore;
	Nolista listaOrd, listaFim, p, z;
	inicializaTrie(&arvore);
	inicializaLista(&listaOrd);
	inicializaLista(&listaFim);

	char txt, dic; // caracteres do texto e dicionário
	
	int i=0, j=0, k, t1=0,t2=0; 
	int aux=1,num,linhas=1,lv=0,cont;
	
	file1 = fopen(argv[1], "r");
	file2 = fopen(argv[2], "r");

	//pegar o tamanho dos arquivos 1 e 2

	while((dic = fgetc(file1)) != EOF)
		t1++;
	char word[t1];

	while((txt = fgetc(file2)) != EOF)
		t2++;
	char word2[t2];
	char plv1[t2];
	

	//recarregando o arquivo1
	rewind(file1);

	while((dic = fgetc(file1)) != EOF){
		if ((dic != '\n')&&(dic != ' ')&&(dic != '-')&&(dic != '.')&&(dic != ',')&&(dic != '!')&&(dic != '?')){
			word[i] = dic;
			i++;

		}else{
			word[i] = '\0';
			i = 0;
			insertWord(&arvore, word,word);

		}
	}if (word[0] != '\0'){
		word[i] = '\0';

		insertWord(&arvore, word,word);
	}

	//recarregando o arquivo 2
	rewind(file2);
	i = 0;
	while((txt = fgetc(file2)) != EOF){

		word2[i] = txt;
		i++;
	}

	word2[i] = '\0'; 

	i = 0;

	for(j = 0; j < t2; j++){

		//Verificar se existem caracteres especiais
		if((word2[j] == '\n')||(word2[j] == ' ')||(word2[j] == '-')||(word2[j] == '.')||(word2[j] == ',')||(word2[j] == '!')||(word2[j] == '?')){

				plv1[i] = '\0';
				
				i = 0;
				
				for(k = 0; k < strlen(plv1); k++){

					if(plv1[k]>= 'A' && plv1[k] <= 'Z')
							plv1[k]= plv1[k] + 'a' - 'A';
				}
					
				if(searchWord(arvore, plv1)){
					insertOrd(&listaOrd, plv1);
				}

		}else{

			plv1[i] = word2[j];
			i++;

		}

	}

	i = 0;
	for(p = listaOrd; (p); p = p->prox){
		
		printf("%s", p->plv);
		
		for(j = 0; j < t2; j++){
			//Verificar se existem caracteres especiais
			if((word2[j] == '\n')||(word2[j] == ' ')||(word2[j] == '-')||(word2[j] == '.')||(word2[j] == ',')||(word2[j] == '!')||(word2[j] == '?')){
				
				plv1[i] = '\0';

				i = 0;

				for(k = 0; k < strlen(plv1); k++){

					if(plv1[k]>= 'A' && plv1[k] <= 'Z')
						plv1[k]= plv1[k] + 'a' - 'A';
					}

				if(!(strcmp(plv1,p->plv))){
					if (linhas != num){

						if(aux == linhas){
								printf(" %d", linhas);
								num = linhas;
						}
						else{
							if(aux== 1)

								printf(", %d", linhas);
								num = linhas;
						}
					
					}
				}

				if(word2[j] == '\n'){
					
					linhas++;
					
					num = linhas-1;
				}

			}
			else{
				plv1[i] = word2[j];
				i++;
			}
		}
		linhas = 1;
		aux=linhas;
		printf("\n");
	}
	imprimeLista(&listaFim);

	i = 0;
	for(j = 0; j < t2; j++){
		if((word2[j] == '\n')||(word2[j] == ' ')||(word2[j] == '-')||(word2[j] == '.')||(word2[j] == ',')||(word2[j] == '!')||(word2[j] == '?')){
			plv1[i] = '\0';
			i = 0;
			
			for(k = 0; k < strlen(plv1); k++){
				if(plv1[k]>= 'A' && plv1[k] <= 'Z')
						plv1[k]= plv1[k] + 'a' - 'A';
			}
			
			if( ! (searchWord(arvore, plv1))){
				
				if (plv1[0] != (char)0 ) {
				//printf("\nPalavra '%s' Nao encontrada",plv1);
				
				printf("%s ",plv1);
				buscaBestWord(&arvore,plv1);
				printf("%s\n",melhorPalavra);

				}

			}
		}else{
			plv1[i] = word2[j];
			i++;
		}
	}
	

return 0;	
}


