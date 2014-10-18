/* Universidade Federal da Bahia
 * Wendel de Araujo Dourado
 * Estruturas de Dados e Algoritmos II
 * Professor Mauricio Pamplona*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
int lv=0;
int linha=1;

typedef struct no {
	struct no *chave[27]; 
	char flag;
}no, *NoTrie;

//typedef struct no node;

typedef struct NolistaInt{

	char *palavra;
	struct NolistaInt *prox;
}NolistaInt, *Listaint;

void inicializa(NoTrie *No);
void inicializaLista(Listaint *l);
void inserir(NoTrie *No, char *word);
int busca_palavra(NoTrie *No, char *word);
bool consultaLista(Listaint *l, char *plv);
bool insereLista(Listaint *l, char *plv);
int levenshtein(char *s1, char *s2);



int main(int argc, char *argv[]){

	FILE *arq, *arq2;
	NoTrie raiz;
	Listaint lst;
	
	int j=0,k=0,i=0;
	int tam1,tam2;
	char ch,ch2;
	char *palavra;

	inicializa(&raiz);
	inicializaLista(&lst);
	

	arq = fopen(argv[2], "r");
	arq2 = fopen(argv[1], "r");

	if(arq && arq2 == NULL)
		printf("Erro, nao foi possivel abrir os arquivos\n");
	else
	// pegar o tamanho dos arquivos //
	//arquivo1
	while( (ch=fgetc(arq))!= EOF )
		tam1++;
		char word[tam1];
	
	//arquivo2	
	while( (ch2=fgetc(arq2))!= EOF )
		tam2++;
	int ar=tam2;
		char word2[tam2];
		printf("Dicionario###\n");
	//inserindo o arquivo 1
		rewind(arq);
		while( (ch=fgetc(arq))!= EOF){
			
			if ((ch != '\n')&&(ch != ' ')&&(ch != '-')&&(ch != '.')&&(ch != ',')&&(ch != '!')&&(ch != '?')){
				word[j] = ch;
				j++;
			
			}else{
				
				word[j]= '\0';
				j = 0;
				inserir(&raiz,word);
				//printf("%s\n",word);
			}
		}
		printf("TESTE");

		
		if (word[0] != '\0'){
			word[j] = '\0';
			inserir(&raiz,word);
			
			//printf("%s\n",word);

		}printf("Texto###\n");
	//buscando o arquivo2
	palavra = malloc(sizeof(tam2));
	rewind(arq2);
	while( (ch2=fgetc(arq2))!= EOF){
		if((ch2 != '\n')&&(ch2 != ' ')&&(ch2 != '-')&&(ch2 != '.')&&(ch2 != ',')&&(ch2 != '!')&&(ch2 != '?')){
			word2[k] = ch2;
			k++;
		}else{

			word2[k]= '\0';
			
			if(busca_palavra(&raiz,word2)){
				
				for(i=0;i<=strlen(word2);i++)
				palavra[i]=word2[i];
		
				printf("%s %d\n",word2,linha);

			}else{
				lv=levenshtein(palavra,word2);
			
			printf("nao achou %s %d\n",word2,lv);
		}
			k = 0;
			
			if(ch2 == '\n')
				linha++;
		}
	}if (word2[0] != '\0'){
			word2[k]= '\0';

			if(busca_palavra(&raiz,word2)){
				

				for(i=0;i<=strlen(word2);i++)
				palavra[i]=word2[i];
				printf("%s %d\n",word2,linha);
			}else{
			lv=levenshtein(palavra,word2);
			printf("não achou %s %d\n",word2,lv);
		}
			k = 0;
			
			if(ch2 == '\n')
				linha++;
	}
	//scanf("%d",&a);// variável apenas para aguardar outro caractere para não fechar terminal
	fclose(arq);
	fclose(arq2);
	return 0;
}

//INICIALIZANDO TRIE
void inicializa(NoTrie *No){
	*No = NULL;
}

//INICIALIZANDO LISTA ENCADEADA
void inicializaLista(Listaint *l){

	(*l) = NULL;
}


//INSERINDO NA TRIE
void inserir(NoTrie *No, char *word){
	int i;
	
	if(*No == NULL){
		
		*No = malloc(sizeof(no));
		for(i=0;i<27;i++)
		(*No)->chave[i]= NULL;
		
		if(word[0] != '\0'){
			inserir(&(*No)->chave[word[0] - 'a'], word +1);
			(*No)->flag = 0;
		}else
			(*No)->flag = 1;
		}else{
			 if(word[0] != '\0'){
				inserir(&(*No)->chave[word[0] - 'a'], word +1);
			
			}else
			(*No)->flag = 1;
		}
}

//BUSCANDO NA TRIE
int busca_palavra(NoTrie *No, char *word){
    if(*No == NULL){
        return 0;
    }
    
    else if(word[0]=='\0')
        return((*No)->flag ? 1:0);
        
    else
		return busca_palavra(&(*No)->chave[word[0]- 'a'], word+1);

}


//CONSULTA NA LISTA
bool consultaLista(Listaint *l, char *plv){

	Listaint p;

	for(p=(*l); (p) && (p->palavra != plv);p=p->prox);
			
		return p;	
}

//INSERINDO NA LISTA
bool insereLista(Listaint *l, char *plv){

	NolistaInt *p;

	if(consultaLista(l,plv)||! (p=((NolistaInt*)malloc(sizeof(NolistaInt))))){
		
		return false;
	}
	p->prox = *l;
	*l = p;
	p->palavra = plv;
	
	return true;
}

//LEVENSTHEIN
int levenshtein(char *s1, char *s2) {
    unsigned int x, y, s1len, s2len;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int matrix[s2len+1][s1len+1];
    matrix[0][0] = 0;
    for (x = 1; x <= s2len; x++)
        matrix[x][0] = matrix[x-1][0] + 1;
    for (y = 1; y <= s1len; y++)
        matrix[0][y] = matrix[0][y-1] + 1;
    for (x = 1; x <= s2len; x++)
        for (y = 1; y <= s1len; y++)
            matrix[x][y] = MIN3(matrix[x-1][y] + 1, matrix[x][y-1] + 1, matrix[x-1][y-1] + (s1[y-1] == s2[x-1] ? 0 : 1));
 
    return(matrix[s2len][s1len]);
}
