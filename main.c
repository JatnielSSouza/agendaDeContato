#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

typedef struct data DATA;

struct data {
    int dia, mes, ano;

};

typedef struct contato CONTATO;

struct contato {
    char nome[50];
    char fone[20];
    DATA aniv;

};

void cabecalho();

void inputData();

void listar();

void pesquisar();

void anivMes();

void remover();

void listarLetra();

void editarContato();

int main(){

    setlocale(LC_ALL, "Portuguese");

    int opcao;

    do {

    cabecalho();

    printf("1 - Inserir contato\n");
    printf("2 - Remover contato\n");
    printf("3 - Pesquisar um contato pelo nome\n");
    printf("4 - Listar todos os contatos\n");
    printf("5 - Listar os contatos pela letra inicial do nome\n");
    printf("6 - Imprimir os aniversariantes do mes\n");
    printf("7 - Editar contato\n");
    printf("8 - Sair\n\n");

    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                inputData();
            break;

            case 2:
                remover();
            break;

            case 3:
                pesquisar();
            break;

            case 4:
                listar();
            break;

            case 5:
                listarLetra();
            break;

            case 6:
                anivMes();
            break;

            case 7:
                editarContato();
            break;

            case 8:
                printf("Obrigado por sua visita!\n");
                getch();
            break;

            default:
                printf("Opcao invalida!\n");
                getch();
            break;
        }

    }while(opcao!=8);

    return 0;
}


void cabecalho() {

    system("cls");
    printf("-------------------------------------------------------------------------------------\n");
    printf("AGENDA DE CONTATOS\n");
    printf("-------------------------------------------------------------------------------------\n\n");

}

void inputData() {

    FILE* arquivo;
    CONTATO ctt;

    arquivo=fopen("agenda.txt", "ab");

    if(arquivo==NULL) {

        printf("Problemas na abertura do arquivo!\n");
        printf("ou,\n");
        printf("Arquivo nao encontrado!\n");
        getch();
    }else {

        do {

            cabecalho();

            fflush(stdin);
            printf("Digite o nome: ");
            gets(ctt.nome);

            fflush(stdin);
            printf("Digite o fone: ");
            gets(ctt.fone);

            printf("Digite o dia do aniversario: ");
            scanf("%d", &ctt.aniv.dia);
            printf("Digite o mes do aniversario: ");
            scanf("%d", &ctt.aniv.mes);
            printf("Digite o ano aniversario: ");
            scanf("%d", &ctt.aniv.ano);

            fwrite(&ctt, sizeof(CONTATO), 1 , arquivo);

            printf("Deseja continuar(s/n)?");
        }while (getche() == 's');
        fclose(arquivo);

    }

}


void listar() {

    FILE* arquivo;
    CONTATO ctt;

    arquivo=fopen("agenda.txt", "rb");

    cabecalho();
    if(arquivo==NULL) {

        printf("Problemas na abertura do arquivo!\n");
        printf("ou,\n");
        printf("Arquivo nao encontrado!\n");
        getch();
    }else{
        while (fread(&ctt, sizeof(CONTATO), 1, arquivo)==1){
            printf("Nome: %s\n", ctt.nome);
            printf("Fone: %s\n", ctt.fone);
            printf("Aniversário: %d/%d/%d \n", ctt.aniv.dia, ctt.aniv.mes, ctt.aniv.ano);
            printf("-------------------------------------------------------------------------------------\n\n");

        }

    }

    fclose(arquivo);
    getch();
}

void pesquisar(){

    FILE* arquivo;
    CONTATO ctt;
    char nome[50];

    arquivo=fopen("agenda.txt", "rb");

    cabecalho();
    if(arquivo==NULL){
        printf("Problemas na abertura do arquivo!\n");
        printf("ou,\n");
        printf("Arquivo nao encontrado!\n");
        getch();
    }else{
        fflush(stdin);
        printf("Digite o nome que deseja pesquisar: ");
        gets(nome);

        while(fread(&ctt, sizeof(CONTATO), 1, arquivo )==1){
                if(strcmp(nome, ctt.nome) == 0){
                    printf("Nome: %s\n", ctt.nome);
                    printf("Fone: %s\n", ctt.fone);
                    printf("Aniversário: %d/%d/%d \n", ctt.aniv.dia, ctt.aniv.mes, ctt.aniv.ano);
                    printf("-------------------------------------------------------------------------------------\n\n");
                }else{
                    printf("Nome nao encontrado!\n");
                    getch();
                }
        }
    }

    fclose(arquivo);
    getch();
}

void anivMes(){

    FILE* arquivo;

    CONTATO ctt;

    arquivo=fopen("agenda.txt", "rb");

    cabecalho();
    if(arquivo==NULL){
        printf("Problemas na abertura do arquivo!\n");
        printf("ou,\n");
        printf("Arquivo nao encontrado!\n");
        getch();
    }else{

        int mes;
        printf("Digite o mes: ");
        scanf("%d", &mes);

        while(fread(&ctt, sizeof(CONTATO), 1,   arquivo)==1){
            if (mes==ctt.aniv.mes){
                printf("Nome: %s\n", ctt.nome);
                printf("Fone: %s\n", ctt.fone);
                printf("Aniversário: %d/%d/%d \n", ctt.aniv.dia, ctt.aniv.mes, ctt.aniv.ano);
                printf("-------------------------------------------------------------------------------------\n\n");
            }else{
                    printf("Mes nao encontrado!\n");
                    getch();
                }
        }

    }

    fclose(arquivo);
    getch();
}

void remover(){

    FILE* arquivo;
    FILE* temp;
    CONTATO ctt;
    char nome[50];

    cabecalho();

    arquivo = fopen("agenda.txt","rb"); //abrir em modo rb leitura binaria
    temp = fopen("tmp.txt","wb"); //abrir em modo wb ele limpa e grava binario

    if(arquivo==NULL&&temp==NULL){

        printf("Problemas na abertura do arquivo!\n");
        printf("ou,\n");
        printf("Arquivo nao encontrado!\n");
        getch();

        }else{

        fflush(stdin);
        printf("Digite o nome que deseja deletar: ");
        gets(nome);

        while(fread(&ctt,sizeof(CONTATO),1,arquivo)==1){

            if(strcmp(nome,ctt.nome)==0){

                printf("Nome: %s\n",ctt.nome);
                printf("Fone: %s\n",ctt.fone);
                printf("Aniversario: %d/%d/%d\n",ctt.aniv.dia,ctt.aniv.mes,ctt.aniv.ano);
                printf("-------------------------------------------------\n");
            }else{
                fwrite(&ctt,sizeof(CONTATO),1,temp); //gravando os dados no arquivo temp
                }
        }

    fclose(arquivo); //fechar o arquivo
    fclose(temp); //fechar o temp

    fflush(stdin);

    printf("Deseja deletar (s/n)? ");

        if(getche()=='s'){ //vamos remover o arquivo "agenda.txt" e renomear o arquivo "tmp.txt" para "agenda.txt"

            if(remove("agenda.txt")==0&&rename("tmp.txt","agenda.txt")==0){ //verifica se as operacoes foram realizadas com sucesso!

                printf("\nOperacao realizada com sucesso!");
            }else{
                remove("tmp.txt"); //remover o arquivo tmp se a condicao foi "n" na hora de deletar
                }
        }

    fclose(temp);
    fclose(arquivo);
    getch();

    }
}

void listarLetra(){

    FILE* arquivo;
    CONTATO ctt;
    char nome[50];

    arquivo = fopen("agenda.txt", "rb");

    cabecalho();
   if(arquivo == NULL){
    printf("Problemas na abertura do arquivo!\n");
        printf("ou,\n");
        printf("Arquivo nao encontrado!\n");
   }else{

        fflush(stdin);
        printf("Digite a letra inicial dos nomes que deseja pesquisar: ");
        gets(nome);

        while(fread(&ctt, sizeof(CONTATO), 1, arquivo) == 1){
            if(ctt.nome[0] == nome[0]){
                printf("\tNome: %s\n",ctt.nome);
                printf("\tFone: %s\n",ctt.fone);
                printf("\tAniversário: %d/%d/%d \n", ctt.aniv.dia, ctt.aniv.mes, ctt.aniv.ano);
                printf("----------------------------------------------\n\n");
            }
        }
    }
   fclose(arquivo);
   getch();
}

void editarContato(){

    FILE* arquivo;
    FILE* temp;
    CONTATO ctt;
    char nome[50];

    cabecalho();

    arquivo = fopen("agenda.txt","rb");
    temp = fopen("tmp.txt","wb");

    if(arquivo == NULL && temp == NULL){
	    printf("Problemas na abertura do arquivo!\n");
        printf("ou,\n");
        printf("Arquivo nao encontrado!\n");
	    getch();
    }else{

    	fflush(stdin);
    	printf("Digite o nome do contato que deseja editar: ");
    	gets(nome);

    	while(fread(&ctt, sizeof(CONTATO), 1, arquivo) == 1){

        	if(strcmp(nome, ctt.nome) == 0){

	            printf("Nome: %s\n",ctt.nome);
                printf("Fone: %s\n",ctt.fone);
                printf("Aniversario: %d/%d/%d\n",ctt.aniv.dia,ctt.aniv.mes,ctt.aniv.ano);
                printf("-------------------------------------------------\n");
        	}else{
	            fwrite(&ctt, sizeof(CONTATO), 1, temp);
	        }
	    }
        fclose(arquivo);
        fclose(temp);

        fflush(stdin);

        printf("Tem certeza que pertende alterar os dados deste contato(s/n)?");

	  	if(getche() == 's'){
	        if(remove("agenda.txt")==0&&rename("tmp.txt","agenda.txt")==0){

	            	FILE* arquivo;
					CONTATO ctt;

					arquivo = fopen("agenda.txt","ab");

                    fflush(stdin);
                    printf("\n\nDigite o nome: ");
                    gets(ctt.nome);

                    fflush(stdin);
                    printf("Digite o fone: ");
                    gets(ctt.fone);

                    printf("Digite o dia do aniversario: ");
                    scanf("%d", &ctt.aniv.dia);
                    printf("Digite o mes do aniversario: ");
                    scanf("%d", &ctt.aniv.mes);
                    printf("Digite o ano aniversario: ");
                    scanf("%d", &ctt.aniv.ano);

                    fwrite(&ctt, sizeof(CONTATO), 1 , arquivo);

					printf("\nContato alterado com sucesso!\n");
	            }else{
                    remove("tmp.txt");
                    }
            }

        fclose(temp);
        fclose(arquivo);
        getch();

    }
}
