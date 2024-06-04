#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "headers/data.h"
void listarReservas(utilizador *utilizador) {
    printf("Iniciando historico de reservas...\n\n");
    sleep(2);
    if (utilizador->reservas == NULL) {
        printf("Não há reservas disponíveis.\n");
        return;
    }
    auxReserva *atual = utilizador->reservas;
    int numReserva = 1;
    printf("Quais são as reservas que pretende visualizar?\n1)Todas\n2)Ativas\n3)Canceladas\n4)Cancelamentos Aceites\n");
    int escolha;
    char aux[20];
    scanf("%d", &escolha);
    switch(escolha){
        case 1:
            strcpy(aux, "Todas");
            break;
        case 2:
            strcpy(aux, "Reservado");
            break;
        case 3:
            strcpy(aux, "Cancelamento");
            break;
        case 4:
            strcpy(aux, "Cancelamento-Aceite");
            break;
        default:
            printf("Opção inválida\n");
            return;
    }
    fflush(stdin);
    while (atual != NULL) {
        if(strcmp(atual->estado, aux) == 0 || strcmp(aux, "Todas") == 0){
            printf("\n\n_Reserva %i_\n",numReserva++);
            printf("Identificador da Reserva: %d\n", atual->identificador);
            printf("Estado: %s\n", atual->estado);
            if (atual->reservaVoo != NULL) {
                printf("Voo:\n");
                printf("ID: %s\n", atual->reservaVoo->voo->numero);
                printf("Origem: %s\n", atual->reservaVoo->voo->origem);
                printf("Destino: %s\n", atual->reservaVoo->voo->destino);
                printf("Data: %s\n", atual->reservaVoo->voo->data);
                printf("Hora: %s\n", atual->reservaVoo->voo->hora);
                printf("Lugares: %d\n", atual->reservaVoo->lugares);
            }
            if (atual->reservaHotel != NULL) {
                printf("Hotel:\n");
                printf("Nome: %s\n", atual->reservaHotel->hotel->nome);
                printf("Local: %s\n", atual->reservaHotel->hotel->localizacao);
                printf("Nº de quartos: %d\n", atual->reservaHotel->quartos);
            }
            printf("\n");
        }
        printf("\n");
        atual = atual->seguinte;
    }
    printf("Fim da lista de reservas\n");
}
void cancelarReserva(auxutilizador* utilizador) {
    if (utilizador == NULL) {
        printf("Utilizador não encontrado\n");
        return;
    }
    auxReserva* reserva = utilizador->utilizador.reservas;
    if (reserva == NULL) {
        printf("Utilizador sem reservas\n");
        return;
    }
    printf("Introduza o identificador da reserva a ser cancelada: ");
    int id;
    scanf("%i", &id);
    while (reserva != NULL && reserva->identificador != id) {
        reserva = reserva->seguinte;
    }
    if (reserva == NULL) {
        printf("Reserva não encontrada\n");
        return;
    }
    strcpy(reserva->estado, "Cancelamento");
    printf("Reserva em Cancelamento, a aguardar\n");
}
void listarCancelamentos(auxutilizador* utilizador, auxVoo* voos, auxHotel* hoteis) {
    if (utilizador == NULL) {
        printf("Utilizador não encontrado\n");
        return;
    }
    auxReserva* reserva = utilizador->utilizador.reservas;
    if (reserva == NULL) {
        printf("Não há reservas para cancelar\n");
        return;
    }
    auxReserva* anterior = NULL;
    while (reserva != NULL) {
        if (strcmp(reserva->estado, "Cancelamento") == 0) {
            printf("Identificador da Reserva: %i\n", reserva->identificador);
            if (reserva->reservaVoo != NULL) {
                printf("_Voo_\nID: %s\nOrigem: %s\nDestino: %s\nData: %s\nHora: %s\nLugares: %i\n\n",
                    reserva->reservaVoo->voo->numero,
                    reserva->reservaVoo->voo->origem,
                    reserva->reservaVoo->voo->destino,
                    reserva->reservaVoo->voo->data,
                    reserva->reservaVoo->voo->hora,
                    reserva->reservaVoo->lugares);
            } else {
                printf("_Voo_: Informação indisponível\n");
            }
            if (reserva->reservaHotel != NULL) {
                printf("_Hotel_\nNome: %s\nLocal: %s\nNº de quartos: %i\n",
                    reserva->reservaHotel->hotel->nome,
                    reserva->reservaHotel->hotel->localizacao,
                    reserva->reservaHotel->quartos);
            } else {
                printf("_Hotel_: Informação indisponível\n");
            }
        }
        reserva = reserva->seguinte;
    }
    printf("Fim da lista de cancelamentos\n");
    printf("Deseja aceitar um cancelamento? (s/n ou todas): ");
    char escolha[20];
    scanf(" %s", escolha);
    if (strcmp(escolha, "todas") == 0) {
        auxReserva* temp = utilizador->utilizador.reservas;
        while (temp != NULL) {
            if (strcmp(temp->estado, "Cancelamento") == 0) {
                strcpy(temp->estado, "Cancelamento-Aceite");
                if(temp->reservaVoo != NULL) {
                    auxVoo* tempVoo = voos;
                    while (tempVoo != NULL) {
                        if (strcmp(tempVoo->voo.numero, temp->reservaVoo->voo->numero) == 0) {
                            tempVoo->voo.assentos_disponiveis += temp->reservaVoo->lugares;
                            break;
                        }
                        tempVoo = tempVoo->seguinte;
                    }
                }
                if(temp->reservaHotel != NULL) {
                    auxHotel* tempHotel = hoteis;
                    while (tempHotel != NULL) {
                        if (strcmp(tempHotel->hotel.nome, temp->reservaHotel->hotel->nome) == 0 &&
                            strcmp(tempHotel->hotel.localizacao, temp->reservaHotel->hotel->localizacao) == 0) {
                            tempHotel->hotel.quartos_disponiveis += temp->reservaHotel->quartos;
                            break;
                        }
                        tempHotel = tempHotel->seguinte;
                    }
                }
            }
            temp = temp->seguinte;
        }
        printf("Todas as reservas foram canceladas e recursos repostos\n");
        return;
    }
    if (escolha[0] == 's' || escolha[0] == 'S') {
        printf("Introduza o identificador da reserva a ser aceite: ");
        int id;
        scanf("%i", &id);
        reserva = utilizador->utilizador.reservas;
        while (reserva != NULL && reserva->identificador != id) {
            anterior = reserva;
            reserva = reserva->seguinte;
        }
        if (reserva == NULL) {
            printf("Reserva não encontrada\n");
            return;
        }
        if (anterior == NULL) {
            utilizador->utilizador.reservas = reserva->seguinte;
        } else {
            anterior->seguinte = reserva->seguinte;
        }
        strcpy(reserva->estado, "Cancelamento-Aceite");
        if(reserva->reservaVoo != NULL) {
            auxVoo* tempVoo = voos;
            while (tempVoo != NULL) {
                if (strcmp(tempVoo->voo.numero, reserva->reservaVoo->voo->numero) == 0) {
                    tempVoo->voo.assentos_disponiveis += reserva->reservaVoo->lugares;
                    break;
                }
                tempVoo = tempVoo->seguinte;
            }
        }
        if(reserva->reservaHotel != NULL) {
            auxHotel* tempHotel = hoteis;
            while (tempHotel != NULL) {
                if (strcmp(tempHotel->hotel.nome, reserva->reservaHotel->hotel->nome) == 0 &&
                    strcmp(tempHotel->hotel.localizacao, reserva->reservaHotel->hotel->localizacao) == 0) {
                    tempHotel->hotel.quartos_disponiveis += reserva->reservaHotel->quartos;
                    break;
                }
                tempHotel = tempHotel->seguinte;
            }
        }
        printf("Reserva cancelada e recursos repostos\n");
    }
    printf("Fim da lista de cancelamentos\n");
}
void adminListarCancelamentos(auxutilizador* utilizadores,auxVoo* voos,auxHotel* hoteis) {
    auxutilizador* tempUser = utilizadores;
    auxHotel* tempHotel = hoteis;
    auxVoo* tempVoo = voos;
    while (tempUser != NULL) {
        if(strcmp(tempUser->utilizador.nome, "admin") == 0) {
            tempUser = tempUser->seguinte;
            continue;
        }
        listarCancelamentos(tempUser, tempVoo, tempHotel);
        tempUser = tempUser->seguinte;
    }
}
void trocarReservas(auxReserva *reserva1, auxReserva *reserva2) {
    int tempID = reserva1->identificador;
    reserva1->identificador = reserva2->identificador;
    reserva2->identificador = tempID;
    ReservaVoo *tempVoo = reserva1->reservaVoo;
    reserva1->reservaVoo = reserva2->reservaVoo;
    reserva2->reservaVoo = tempVoo;
    ReservaHotel *tempHotel = reserva1->reservaHotel;
    reserva1->reservaHotel = reserva2->reservaHotel;
    reserva2->reservaHotel = tempHotel;
    char *tempEstado = reserva1->estado;
    reserva1->estado = reserva2->estado;
    reserva2->estado = tempEstado;
}

void ordenarReservas(auxReserva *inicio) {
    int trocado;
    auxReserva *atual;
    auxReserva *anterior = NULL;
    if (inicio == NULL)
        return;

    do {
        trocado = 0;
        atual = inicio;
        while (atual->seguinte != anterior) {
            // Comparação por origem do voo
            if (strcmp(atual->reservaVoo->voo->origem, atual->seguinte->reservaVoo->voo->origem) > 0) {
                trocarReservas(atual, atual->seguinte);
                trocado = 1;
            }
            // Se a origem for igual, então comparação por destino do voo
            else if (strcmp(atual->reservaVoo->voo->origem, atual->seguinte->reservaVoo->voo->origem) == 0 &&
                     strcmp(atual->reservaVoo->voo->destino, atual->seguinte->reservaVoo->voo->destino) > 0) {
                trocarReservas(atual, atual->seguinte);
                trocado = 1;
            }
            atual = atual->seguinte;
        }
        anterior = atual;
    } while (trocado);
}