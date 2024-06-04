#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "headers/data.h"
void adicionarHoteis(auxHotel** inicio){
    Hotel novo;
    printf("Introduza o nome do hotel:");
    scanf("%s",novo.nome);
    auxHotel *aux=NULL;
    printf("Introduza a respectiva localização:");
    scanf("%s",novo.localizacao);
    for(aux=*inicio;aux!=NULL;aux=aux->seguinte){
        if(strcmp(aux->hotel.nome,novo.nome)==0 && strcmp(aux->hotel.localizacao,novo.localizacao)==0){
            printf("Hotel já presente na memoria.");
            return;
        }
    }
    printf("Introduza a quantidade de quartos disponiveis:");
    scanf("%i",&novo.quartos_disponiveis);
    printf("Introduza a classificação do hotel (quantidade de estrelas):");
    scanf("%i",&novo.classificacao);
    aux=(auxHotel*)calloc(1,sizeof(auxHotel));
    if(aux==NULL){
        printf("Erro de memoria, tente novamente.");
        return;
    }
    aux->hotel=novo;
    aux->seguinte=NULL;
    if(*inicio==NULL){
        *inicio=aux;
        return;
    }
    auxHotel *aux2=*inicio;
    while(aux2->seguinte!=NULL){
        aux2=aux2->seguinte;
    }
    aux2->seguinte=aux;
}
void removerHoteis(auxHotel** inicio){
    printf("Introduza o nome do Hotel a ser removido:");
    char nome[64];
    scanf("%s",nome);
    auxHotel *atual=*inicio;
    auxHotel *anterior=NULL;
    if(atual==NULL){
        printf("Lista de Hoteis vazia");
        return;
    }
    if(strcmp(atual->hotel.nome,nome)==0){
        *inicio=atual->seguinte;
        free(atual);
        return;
    }
    while(atual!=NULL && strcmp(atual->hotel.nome,nome)!=0){
        anterior=atual;
        atual=atual->seguinte;
    }
    if(atual!=NULL){
        anterior->seguinte=atual->seguinte;
        free(atual);
    }
    printf("Hotel removido");
}
void removerInfoH(auxHotel* inicio){
    auxHotel *novo=(auxHotel*)calloc(1,sizeof(auxHotel));
    printf("\nDeseja remover a informação de qual Hotel(nome):");
    scanf("%s",novo->hotel.nome);
    printf("Deseja remover a informação de qual Hotel(localização):");
    scanf("%s",novo->hotel.localizacao);
    auxHotel* aux=NULL;
    char escolha;
    for(aux=inicio;aux!=NULL;aux=aux->seguinte){
        if(strcmp(aux->hotel.localizacao,novo->hotel.localizacao)==0 &&strcmp(aux->hotel.nome,novo->hotel.nome)==0){
            printf("Hotel encontrado.\nO que deseja mudar?\n");
            do{
                printf("a)Nome\nb)localização\nc)Numero de quartos disponiveis\nd)Classificação\ne)Sair\n");
                fflush(stdin);
                scanf("%c",&escolha);
                switch(escolha){
                    case 'a':
                        printf("Introduza o novo nome do Hotel:");
                        scanf("%s",aux->hotel.nome);
                    break;
                    case 'b':
                        printf("Introduza a nova localização do Hotel:");
                        scanf("%s",aux->hotel.localizacao);
                    break;
                    case 'c':
                        printf("Introduza o novo numero de quartos disponiveis:");
                        scanf("%i",&aux->hotel.quartos_disponiveis);
                    break;
                    case 'd':
                        printf("Introduza a nova classificação:");
                        scanf("%i",&aux->hotel.classificacao);
                    break;
                }
            }while(escolha!='e');
            return;
        }
    }
    printf("Hotel nao encontrado, ocorreu um erro. Tente novamente.\n");
    return;
}
void listarHoteis(auxHotel* inicio){
    auxHotel *aux=NULL;
    if(inicio==NULL){
        printf("Lista vazia, tente novamente");
        return;
    }
    for(aux=inicio;aux!=NULL;aux=aux->seguinte){
        printf("%s - %s - %i - %i\n",aux->hotel.nome,aux->hotel.localizacao,aux->hotel.quartos_disponiveis,aux->hotel.classificacao);
    }
}
void procurarHoteis(auxHotel *hoteis) {
    if (hoteis == NULL) {
        printf("Não há hotéis disponíveis para pesquisa.\n");
        return;
    }
    char termo[50];
    printf("Introduza o nome ou a localização para pesquisa de Hoteis: ");
    scanf("%s", termo);
    printf("Hotéis que correspondem à pesquisa por '%s':\n", termo);
    int count = 0;
    auxHotel *temp = hoteis;
    while (temp != NULL) {
        if (strstr(temp->hotel.nome, termo) != NULL || strstr(temp->hotel.localizacao, termo) != NULL) {
            printf("Nome: %s\n", temp->hotel.nome);
            printf("Localização: %s\n", temp->hotel.localizacao);
            printf("Classificação: %d\n", temp->hotel.classificacao);
            printf("Quartos disponíveis: %d\n", temp->hotel.quartos_disponiveis);
            count++;
        }
        temp = temp->seguinte;
    }
    if (count == 0) {
        printf("Nenhum hotel corresponde à pesquisa por '%s'.\n", termo);
    }
}