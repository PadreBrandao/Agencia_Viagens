#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/func.h"
#include "headers/data.h"
void menuUsers(auxutilizador* currentUser, auxVoo* voos, auxHotel* hoteis){
    int escolha;
            do {
                printf("_MENU_\n1-Voos\n2-Hoteis\n3-Reservas\n0-Sair\nEscolha:");
                scanf("%d", &escolha);
                switch(escolha){
                    case 1:
                        system(Clear);
                        printf("\nDeseja Listar voos(1) ou procurar voos(2)?\nEscolha:");
                        int escolha1;
                        scanf("%d", &escolha1);
                        switch(escolha1) {
                            case 1:
                                listarVoos(voos);
                                sleep(2);
                                break;
                            case 2:
                                procurarVoos(voos);
                                sleep(2);
                                break;
                            default:
                                printf("Opção inválida. Tente novamente.\n");
                                break;
                        }   
                        break;
                    case 2:
                        system(Clear);
                        printf("Deseja listar hoteis(1) ou procurar hoteis(2)?\nEscolha:");
                        int escolha2;
                        scanf("%d", &escolha2);
                        switch(escolha2) {
                            case 1:
                                listarHoteis(hoteis);
                                sleep(2);
                                break;
                            case 2:
                                procurarHoteis(hoteis);
                                sleep(2);
                                break;
                            default:
                                printf("Opção inválida. Tente novamente.\n");
                                break;
                        }
                        break;
                    case 3:
                        printf("Deseja listar reservas(1), criar nova reservas(2) ou cancelar reserva(3)?\nEscolha:");
                        int escolha3;
                        scanf("%d", &escolha3);
                        switch(escolha3) {
                            case 1:
                                listarReservas(currentUser);
                                sleep(2);
                                break;
                            case 2:
                                criarReserva(&currentUser->utilizador, voos, hoteis);
                                sleep(2);
                                break;
                            case 3:
                                cancelarReserva(currentUser);
                                sleep(2);
                                break;
                            default:
                                printf("Opção inválida. Tente novamente.\n");
                                break;
                        }
                        break;
                    case 0:
                        printf("A sair...\n");
                        break;
                    default:
                        printf("Opção inválida. Tente novamente.\n");
                        break;
                }
            } while(escolha != 0);
            system(Clear);
}
void listarUtilizadores(auxutilizador* inicio){
    auxutilizador *aux=NULL;
    if(inicio==NULL){
        printf("Lista vazia, tente novamente");
        return;
    }
    printf("1-Listar todos os utilizadores\n2-Procurar utilizador\nEscolha:");
    int escolha;
    scanf("%d", &escolha);
    if(escolha == 1){
        for(aux=inicio;aux!=NULL;aux=aux->seguinte){
            printf("Nome:%s - Passe:%s\n",aux->utilizador.nome,aux->utilizador.passe);
        }
    } else if(escolha == 2){
        char termo[50];
        printf("Introduza o nome para pesquisa de Utilizadores: ");
        scanf("%s", termo);
        printf("Utilizadores que correspondem à pesquisa por '%s':\n", termo);
        int count = 0;
        auxutilizador *temp = inicio;
        while (temp != NULL) {
            if (strstr(temp->utilizador.nome, termo) != NULL) {
                printf("Nome: %s\nPasse:%s\n", temp->utilizador.nome,temp->utilizador.passe);
                count++;
                printf("Pretende editar algumas das informações? (s/n)\nEscolha:");
                char escolha1;
                scanf(" %c", &escolha1);
                if(escolha1 == 's'){
                    printf("Editar nome(1) ou passe(2)?\nEscolha:");
                    int escolha2;
                    scanf("%d", &escolha2);
                    if(escolha2 == 1){
                        printf("Introduza o novo nome:");
                        scanf("%s", temp->utilizador.nome);
                    } else if(escolha2 == 2){
                        printf("Introduza a nova passe:");
                        scanf("%s", temp->utilizador.passe);
                    }
                }
                printf("Deseja ver reservas do utilizador? (s/n)\nEscolha:");
                char escolha2;
                scanf(" %c", &escolha2);
                if(escolha2 == 's'){
                    listarReservas(temp);
                }
            }
            temp = temp->seguinte;
        }
        if (count == 0) {
            printf("Nenhum utilizador corresponde à pesquisa por '%s'.\n", termo);
        }
    } else {
        printf("Opção inválida. Tente novamente.\n");
    }
}