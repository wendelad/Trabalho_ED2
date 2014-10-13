/* Universidade Federal da Bahia
 * Wendel de Araujo Dourado
 * Estruturas de Dados e Algoritmos II
 * Professor Mauricio Pamplona*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int achou;

struct no {
	struct no *chave[27]; 
	struct no *pai;
	char flag;
	int nil;
}no, *NoTrie;

typedef struct no node;

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
	int j=0,k=0,i=0;
	node *raiz;
	int linha=0;
	//char word[200000]word2[200000];
	FILE *arq, *arq2;
	char ch,ch2;
	int tam1,tam2,a;
	inicializa(&raiz);
	arq = fopen(argv[1], "r");
	arq2 = fopen(argv[2], "r");
	char *palavra;
	int nl=0;
	
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
		char word2[tam2];
		
	//inserindo o arquivo 1

		rewind(arq);
		while( (ch=fgetc(arq))!= EOF ){
			
			if(ch != '\n'){
				word[j] = ch;
				j++;
			
			}else{
				word[j]= '\0';
				j = 0;
				inserir(&raiz,word);
				nl++;	
				
			}
		}
	//buscando o arquivo2
		
	rewind(arq2);
	palavra = malloc(sizeof(tam2));
	while( (ch2=fgetc(arq2))!= EOF ){
		if(ch2 != '\n'){
			word2[k] = ch2;
			k++;
		
		}else{
			linha++;
			
			word2[k]= '\0';
			k = 0;
			
			achou=busca_palavra(&raiz,word2);
			
			if(achou ==1){
				
				for(i=0;i<=strlen(word2);i++)
				palavra[i]=word2[i];
				//printf("%d",i);
				
				if(busca_palavra(&raiz,palavra))
				
				printf("achou! %s %d",palavra,linha);
				printf("\n");
			
			}
		}
	}
	scanf("%d",&a);// variável apenas para aguardar outro caractere para não fechar terminal
	fclose(arq);
	fclose(arq2);
	return 0;
}

