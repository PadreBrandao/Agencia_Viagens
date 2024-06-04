#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "headers/func.h"
#include "headers/data.h"
void adicionarVooLista(auxVoo** voos, Voos* voo) {
    auxVoo* novoNoVoo = (auxVoo*)malloc(sizeof(auxVoo));
    if (novoNoVoo == NULL) {
        fprintf(stderr, "Erro ao alocar de memória\n");
        exit(EXIT_FAILURE);
    }
    novoNoVoo->voo = *voo;
    novoNoVoo->seguinte = NULL;
    auxVoo* ultimo = *voos;
    if (*voos == NULL) {
        *voos = novoNoVoo;
        return;
    }
    while (ultimo->seguinte != NULL) {
        ultimo = ultimo->seguinte;
    }
    ultimo->seguinte = novoNoVoo;
}
void adicionarHotelLista(auxHotel** hoteis, Hotel* hotel) {
    auxHotel* novoNoHotel = (auxHotel*)malloc(sizeof(auxHotel));
    if (novoNoHotel == NULL) {
        fprintf(stderr, "Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    novoNoHotel->hotel = *hotel;
    novoNoHotel->seguinte = NULL;

    auxHotel* ultimo = *hoteis;
    if (*hoteis == NULL) {
        *hoteis = novoNoHotel;
        return;
    }
    while (ultimo->seguinte != NULL) {
        ultimo = ultimo->seguinte;
    }
    ultimo->seguinte = novoNoHotel;
}
