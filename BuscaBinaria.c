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

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	int qt;
	int c,inicio,fim,tb,tr,meio;
	char *aux;

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

	c = 0;
	printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco));
	f = fopen("cep_ordenado.dat","rb");
    fseek(f,0,SEEK_END);
    tb=ftell(f);
    tr=tb/sizeof(Endereco);
    inicio=0;
    fim=tr-1;
	while(inicio <= fim)
	{
		c++;
        meio=(inicio+fim)/2;
        fseek(f,meio*sizeof(Endereco),SEEK_SET);
        qt = fread(&e,sizeof(Endereco),1,f);
		if(strncmp(argv[1],e.cep,8)==0){
			printf("Cep encontrado!%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
            printf("Levou %d tentativas",c);
            fclose(f);
            return 0;
		}else if (strncmp(argv[1],e.cep,8)<0){
            fim=meio-1;
        }else{
            inicio=meio+1;
        };		
	}
	printf("Arquivo não encontrado \n");
	printf("Levou %d tentativas\n",c);
	fclose(f);
}


