/* Universidade Federal da Bahia
 * Wendel de Araujo Dourado
 * Estruturas de Dados e Algoritmos II
 * Professor Mauricio Pamplona*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 35000
int achou = 0;

struct no {
	struct no *chave[27]; 
	struct no *pai;
	char flag;
	int filhos;
}no, *NoTrie;

typedef struct no node;

//função para a Trie ***


void inicializa(node **No){
	*No = NULL;
	}
	
void inserir(node **No, char *word){
	int i;
	if(*No == NULL){
	
		*No = malloc(sizeof(node));
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

int busca_palavra(node **No, char *word){
    if(*No == NULL)
        return 0;
    
    else if(word[0]=='\0')
        return((*No)->flag ? 1:0);
        
    else
        return busca_palavra(&(*No)->chave[word[0]- 'a'], word+1);
        
        
}


int main(int argc, char *argv[]){
	int i,j=0,k=0;
	node *raiz;
	char aux, op, sel, *palavra;
	char url[]="testar.txt",ch;
	char url2[] = "testar2.txt",ch2;
	
	char word[200000], word2[200000];
	//int num=0;
	inicializa(&raiz);
	FILE *arq, *arq2;
	
	arq = fopen(url, "r");
	arq2 = fopen(url2, "r");
	if(arq && arq2 == NULL)
		printf("Erro, nao foi possivel abrir os arquivos\n");
	else
		while( (ch=fgetc(arq))!= EOF ){
			
			if(ch != '\n'){
				word[j] = ch;
				j++;
			
			}else{
				word[j]= '\0';
				j = 0;
				inserir(&raiz,word);
				
			}
			
	}
	while( (ch2=fgetc(arq2))!= EOF ){
			int opt, cont=0;
			if(ch2 != '\n'){
				word2[k] = ch2;
				k++;
			
			}else{
				word2[k]= '\0';
				k = 0;
				opt=busca_palavra(&raiz,word2);
				if(opt ==1)
				cont+=1;
				printf("achou\n");
				
				
			}
			
	}
	
	scanf("%c", &sel);

	while(sel != '@'){
		if ((sel == 'b') || (sel == 'i') || (sel == 'r')){
			scanf("%c", &aux);

			if (!(palavra = malloc(sizeof(char)*(TAM + 1)))){
				printf("Falha a alocar memória.\n");
				exit(1);
			}
			
			scanf("%c", &aux);
			i = 0;
			while((aux != '\n')){
				palavra[i] = aux;
				i++;
				scanf("%c", &aux);
			}
			
			palavra[i] = '\0';

			op = 1;
			
			switch(sel){
				case 'b': op = busca_palavra(&raiz, palavra);
				if (op == 1)
				printf("%s\n",palavra);
				else{
				
				printf("Não achou!");
				//printall(raiz,palavra);
			}
					break;
				case 'i': 
				inserir(&raiz, palavra);
					break;
				/*case 'r': op = delete(raiz, palavra);
					break;*/
			}
			
			free(palavra);

		}
		
		scanf("%c", &sel);
	}
	fclose(arq);
	fclose(arq2);
	return 0;
}
