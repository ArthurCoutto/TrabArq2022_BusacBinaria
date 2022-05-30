#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

// registroCEP = struct.Struct("72s72s72s72s2s8s2s")

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

int main(int argc, char**argv)  //Inicia funçao e recebe qtd de argumentos e criar array de argumentos 
{
	FILE *f;
	Endereco e;
	int qt;
	int c,inicio,fim,tb,tr,meio;
	char *aux;

	if(argc != 2) //Caso use o código errado, retorna erro
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

	c = 0;
	printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco)); //Indica tamanho do arquivo
	f = fopen("cep_ordenado.dat","rb");
    fseek(f,0,SEEK_END); //Coloca a cabeça de leitura no fim do arquivo
    tb=ftell(f);  //tb recebe a posiçao do ultimo byte do arquivo
    tr=tb/sizeof(Endereco); //tr divide tb pelo tamanho do struct Endereço para achar o número total de endereços
    inicio=0;
    fim=tr-1; //Arrays em C começam em 0, então fim tem que ser a qtd de lotes-1 para funcionar
	while(inicio <= fim)
	{
		c++; 
        meio=(inicio+fim)/2;
        fseek(f,meio*sizeof(Endereco),SEEK_SET); //Busca o endereço do meio no arquivo
        qt = fread(&e,sizeof(Endereco),1,f); //Lê endereço do meio
		if(strncmp(argv[1],e.cep,8)==0){ //Se encontrou, imprime informaços do CEP, numero de tentativas, fecha arquivo e finaliza funcao
			printf("Cep encontrado!%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
            printf("Levou %d tentativas",c);
            fclose(f); 
            return 0;
		}else if (strncmp(argv[1],e.cep,8)<0){ //caso o CEP desejado seja menor que o meio, diminui fim e continua loop
            fim=meio-1;
        }else{   //caso o CEP desejado seja maior que o meio, aumenta inicio e continua loop
            inicio=meio+1;
        };		
	}
	//Caso o CEP não seja encontrado, imprime a falha, quantas vezes tentou e fecha o arquivo
	printf("Arquivo não encontrado \n");
	printf("Levou %d tentativas\n",c);
	fclose(f);
}


