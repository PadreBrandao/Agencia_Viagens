#include<stdio.h>
#include<stdlib.h>
#include "headers/func.h"
#include "headers/data.h"
void limpaListas(auxVoo* voos, auxHotel* hoteis, auxutilizador* utilizadores) {
    // Limpa a lista de voos
    while (voos != NULL) {
        auxVoo* temp = voos;
        voos = voos->seguinte;
        free(temp);
    }
    // Limpa a lista de hotéis
    while (hoteis != NULL) {
        auxHotel* temp = hoteis;
        hoteis = hoteis->seguinte;
        free(temp);
    }
    // Limpa a lista de utilizadores
    while (utilizadores != NULL) {
        auxutilizador* temp = utilizadores;
        utilizadores = utilizadores->seguinte;
        // Limpa as reservas do utilizador atual
        limpaReservas(temp->utilizador.reservas);
        // Libera a própria estrutura do utilizador
        free(temp);
    }
}
void limpaReservas(auxReserva* reservas) {
    while (reservas != NULL) {
        auxReserva* temp = reservas;
        reservas = reservas->seguinte;
        // Libera os dados internos
        if (temp->reservaVoo != NULL) {
            if (temp->reservaVoo->voo != NULL) {
                free(temp->reservaVoo->voo);
            }
            free(temp->reservaVoo);
        }
        if (temp->reservaHotel != NULL) {
            if (temp->reservaHotel->hotel != NULL) {
            free(temp->reservaHotel->hotel);
            }
            free(temp->reservaHotel);
        }
        if (temp->estado != NULL) {
            free(temp->estado);
        }
        // Libera a própria estrutura da reserva
        free(temp);
    }
}
