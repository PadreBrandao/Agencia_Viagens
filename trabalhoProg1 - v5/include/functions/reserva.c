#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/func.h"
#include "headers/data.h"

void criarReserva(utilizador *utilizador, auxVoo *voo, auxHotel *hotel) {
    printf("Deseja fazer reserva de Voo ou de Hotel?\na)Voos\nb)Hoteis\nc)Ambos\nd)Sair\nEscolha: ");
    int tempo = rand();
    auxReserva *novaReserva = (auxReserva *)malloc(sizeof(auxReserva));
    if (novaReserva == NULL) {
        printf("Erro de alocação de memória.\n");
        return;
    }
    novaReserva->identificador = tempo;
    novaReserva->seguinte = NULL;
    novaReserva->estado = (char *)malloc(20 * sizeof(char));
    if (novaReserva->estado == NULL) {
        printf("Erro de alocação de memória.\n");
        free(novaReserva);
        return;
    }
    char aux;
    scanf(" %c", &aux);
    switch (aux) {
        case 'a':
            if (voo == NULL) {
                printf("Não existem voos disponíveis\n");
                free(novaReserva->estado);
                free(novaReserva);
                return;
            }
            reservaVoo(utilizador, voo, novaReserva);
            novaReserva->reservaHotel = NULL;
            break;
        case 'b':
            if (hotel == NULL) {
                printf("Não existem hotéis disponíveis\n");
                free(novaReserva->estado);
                free(novaReserva);
                return;
            }
            reservaHotel(utilizador, hotel, novaReserva);
            novaReserva->reservaVoo = NULL;
            break;
        case 'c':
            if (voo == NULL) {
                printf("Não existem voos disponíveis\n");
                free(novaReserva->estado);
                free(novaReserva);
                return;
            }
            if (hotel == NULL) {
                printf("Não existem hotéis disponíveis\n");
                free(novaReserva->estado);
                free(novaReserva);
                return;
            }
            reservaVoo(utilizador, voo, novaReserva);
            reservaHotel(utilizador, hotel, novaReserva);
            break;
        case 'd':
            free(novaReserva->estado);
            free(novaReserva);
            return;
        default:
            printf("Erro, tente novamente\n");
            free(novaReserva->estado);
            free(novaReserva);
            return;
    }
    
    // Encontre o último nó da lista de reservas
    auxReserva *ultimo = utilizador->reservas;
    if (ultimo == NULL) {
        utilizador->reservas = novaReserva;
    } else {
        while (ultimo->seguinte != NULL) {
            ultimo = ultimo->seguinte;
        }
        ultimo->seguinte = novaReserva;
    }
}
void reservaVoo(utilizador *utilizador, auxVoo *voo, auxReserva *novaReserva) {
    printf("Introduza o número de voo: ");
    char numVoo[24];
    scanf("%s", numVoo);
    auxVoo *aux = voo;
    novaReserva->reservaVoo = (ReservaVoo*)malloc(sizeof(ReservaVoo));
    if (novaReserva->reservaVoo == NULL) {
        printf("Erro de alocação de memória.\n");
        return;
    }
    while (aux != NULL) {
        if (strcmp(aux->voo.numero, numVoo) == 0) {
            printf("\nVoo encontrado\n");
            novaReserva->reservaVoo->voo = &aux->voo;
            printf("%i Lugares vagos\nQuantos lugares deseja?\nEscolha: ", aux->voo.assentos_disponiveis);
            int n;
            scanf("%d", &n);
            while(n <= 0) {
                printf("Número inválido, tente novamente\nLugares:");
                scanf("%d", &n);
            }
            if (n > aux->voo.assentos_disponiveis) {
                printf("Impossível concluir ação\nTente novamente\n");
                free(novaReserva->reservaVoo);
                return;
            }
            aux->voo.assentos_disponiveis -= n;
            novaReserva->reservaVoo->lugares = n;
            strcpy(novaReserva->estado, "Reservado");
            printf("Reserva de Voo concluída.\n");
            return;
        }
        aux = aux->seguinte;
    }
    printf("Impossível concluir ação, tente novamente\n");
}
void reservaHotel(utilizador *utilizador, auxHotel* hotel, auxReserva *novaReserva) {
    printf("Introduza o nome do Hotel: ");
    char nomeHotel[24];
    scanf("%s", nomeHotel);
    auxHotel *aux = hotel;
    printf("Introduza a localização do Hotel: ");
    char localizacaoHotel[24];
    scanf("%s", localizacaoHotel);
    novaReserva->reservaHotel = (ReservaHotel*)malloc(sizeof(ReservaHotel));
    if (novaReserva->reservaHotel == NULL) {
        printf("Erro de alocação de memória.\n");
        return;
    }
    while (aux != NULL) {
        if (strcmp(aux->hotel.nome, nomeHotel) == 0 && strcmp(aux->hotel.localizacao, localizacaoHotel) == 0) {
            printf("\nHotel encontrado\n");
            novaReserva->reservaHotel->hotel = &aux->hotel;
            printf("%i Quartos vagos\nQuantos quartos deseja?\nEscolha: ", aux->hotel.quartos_disponiveis);
            int n;
            scanf("%d", &n);
            while(n<=0) {
                printf("Número inválido, tente novamente\nQuartos:");
                scanf("%d", &n);
            }
            if (n > aux->hotel.quartos_disponiveis) {
                printf("Impossível concluir ação\nTente novamente\n");
                free(novaReserva->reservaHotel);
                return;
            }
            aux->hotel.quartos_disponiveis -= n;
            novaReserva->reservaHotel->quartos = n;
            strcpy(novaReserva->estado, "Reservado");
            printf("Reserva de Hotel concluída.\n");
            return;
        }
        aux = aux->seguinte;
    }
    printf("Impossível concluir ação, tente novamente\n");
}
