#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "headers/data.h"
void adicionarVoo(auxVoo** inicio){
    Voos *novo=(Voos*)calloc(1,sizeof(Voos));
    printf("Introduza o numero de Voo:");
    scanf("%s",novo->numero);
    auxVoo *auxiliar=NULL;
    for(auxiliar=*inicio;auxiliar!=NULL;auxiliar=auxiliar->seguinte){
        if(strcmp(auxiliar->voo.numero,novo->numero)==0){
            printf("Voo já existente\n");
            return;
        }
    }
    printf("Introduza a origem do voo:");
    scanf("%s",novo->origem);
    printf("Introduza o destino do voo:");
    scanf("%s",novo->destino);
    printf("Introduza a quantidade de lugares disponiveis:");
    scanf("%i",&novo->assentos_disponiveis);
    printf("Introduza a data do Voo:");
    scanf("%s",novo->data);
    printf("Introduza a hora do Voo:");
    scanf("%s",novo->hora);
    auxVoo *aux=(auxVoo*)calloc(1,sizeof(auxVoo));
    if(aux==NULL){
        printf("Erro de memoria, tente novamente.");
        return;
    }
    aux->voo=*novo;
    aux->seguinte=NULL;
    if(*inicio==NULL){
        *inicio=aux;
        return;
    }
    auxVoo *aux2=*inicio;
    while(aux2->seguinte!=NULL){
        aux2=aux2->seguinte;
    }
    aux2->seguinte=aux;
}
void removerVoo(auxVoo** inicio) {
	if (*inicio == NULL) {
		printf("Lista de Voos vazia\n");
		return;
	}
	printf("Introduza o numero do Voo a ser removido:");
	char id[50];
	scanf(" %s", id);
	auxVoo* atual = *inicio;
	if (atual == NULL) {
		printf("Erro: Ponteiro 'inicio' aponta para NULL\n");
		return;
	}
	auxVoo* anterior = NULL;
	while (atual != NULL && strcmp(atual->voo.numero, id) != 0) {
		anterior = atual;
		atual = atual->seguinte;
	}
	if (atual == NULL) {
		printf("Voo nao encontrado\n");
		return;
	}
	if (anterior == NULL) {
		*inicio = atual->seguinte;
	} else {
		anterior->seguinte = atual->seguinte;
	}
	free(atual);
	printf("Voo removido\n");
}

void removerInfoV(auxVoo* inicio){
    auxVoo *novo = (auxVoo*)malloc(sizeof(auxVoo));
    printf("Deseja remover a informação de qual Voo (id):");
    scanf(" %s",novo->voo.numero);
    auxVoo* aux=NULL;
    char escolha;
    for(aux=inicio;aux!=NULL;aux=aux->seguinte){
        if(strcmp(aux->voo.numero, novo->voo.numero)==0){
            printf("Voo encontrado.\nO que deseja mudar?");
            do{
                printf("\na)Origem\nb)Destino\nc)Quantidade de lugares disponiveis\nd)Data\ne)Hora\nf)Sair\nEscolha:");
                fflush(stdin);
                scanf("%c",&escolha);
                switch(escolha){
                    case 'a':
                        printf("Introduza a nova origem do Voo:");
                        scanf("%s",aux->voo.origem);
                    break;
                    case 'b':
                        printf("Introduza o novo destino do Voo:");
                        scanf("%s",aux->voo.destino);
                    break;
                    case 'c':
                        printf("Introduza a nova quantidade de lugares disponiveis:");
                        scanf("%i",&aux->voo.assentos_disponiveis);
                    break;
                    case 'd':
                        printf("Introduza a nova data do Voo:");
                        scanf("%s",aux->voo.data);
                    break;
                    case 'e':
                        printf("Introduza a nova hora do Voo:");
                        scanf("%s",aux->voo.hora);
                    break;
                }
            }while(escolha!='f');
            return;
        }
    }
}
void listarVoos(auxVoo* inicio){
    auxVoo *aux=NULL;
    if(inicio==NULL){
        printf("Lista vazia, tente novamente");
        return;
    }
    for(aux=inicio;aux!=NULL;aux=aux->seguinte){
        printf("%s - %s - %s - %i - %s - %s\n",aux->voo.numero,aux->voo.origem,aux->voo.destino,aux->voo.assentos_disponiveis,aux->voo.data,aux->voo.hora);
    }
}
int compararOrigem(const void *a, const void *b) {
    const Voos *vooA = (const Voos *)a;
    const Voos *vooB = (const Voos *)b;
    return strcmp(vooA->origem, vooB->origem);
}
// Função de comparação para ordenação de voos com base no destino
int compararDestino(const void *a, const void *b) {
    const Voos *vooA = (const Voos *)a;
    const Voos *vooB = (const Voos *)b;
    return strcmp(vooA->destino, vooB->destino);
}
// Função de comparação para ordenação de voos com base na data
int compararData(const void *a, const void *b) {
    const Voos *vooA = (const Voos *)a;
    const Voos *vooB = (const Voos *)b;
    return strcmp(vooA->data, vooB->data);
}
// Função de comparação para ordenação de voos com base na hora
int compararHora(const void *a, const void *b) {
    const Voos *vooA = (const Voos *)a;
    const Voos *vooB = (const Voos *)b;
    return strcmp(vooA->hora, vooB->hora);
}
// Função de comparação para ordenação de voos com base no preço
// Função para listar os voos em uma ordem específica
void listarVoosOrdem(Voos *voos, int numVoos, int criterio) {
    switch(criterio) {
        case 1:
            qsort(voos, numVoos, sizeof(Voos), compararOrigem);
            break;
        case 2:
            qsort(voos, numVoos, sizeof(Voos), compararDestino);
            break;
        case 3:
            qsort(voos, numVoos, sizeof(Voos), compararData);
            break;
        case 4:
            qsort(voos, numVoos, sizeof(Voos), compararHora);
            break;
        default:
            printf("Criterio invalido.\n");
            return;
    }
    for (int i = 0; i < numVoos; i++) {
        printf("Voo %d:\n", i+1);
        printf("Origem: %s\n", voos[i].origem);
        printf("Destino: %s\n", voos[i].destino);
        printf("Data: %s\n", voos[i].data);
        printf("Hora: %s\n", voos[i].hora);
        printf("Assentos Disponiveis: %d\n", voos[i].assentos_disponiveis);
        printf("\n");
    }
}

void procurarVoos(auxVoo *voos) {
    if (voos == NULL) {
        printf("Não há voos disponíveis para pesquisa.\n");
        return;
    }
    char termo[50];
    printf("Introduza um numero, origem, destino ou data para pesquisa de voos: ");
    scanf("%s", termo);
    printf("Voos que correspondem à pesquisa por '%s':\n", termo);
    int count = 0;
    auxVoo *temp = voos;
    while (temp != NULL) {
        if (strstr(temp->voo.numero, termo) != NULL || strstr(temp->voo.origem, termo) != NULL || strstr(temp->voo.destino, termo) != NULL || strstr(temp->voo.data, termo) != NULL) {
            printf("ID: %s\n", temp->voo.numero);
            printf("Origem: %s\n", temp->voo.origem);
            printf("Destino: %s\n", temp->voo.destino);
            printf("Data: %s\n", temp->voo.data);
            printf("Hora: %s\n", temp->voo.hora);
            printf("Assentos disponíveis: %d\n", temp->voo.assentos_disponiveis);
            count++;
        }
        temp = temp->seguinte;
    }
    if (count == 0) {
        printf("Nenhum voo corresponde à pesquisa por '%s'.\n", termo);
    }
}