#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "headers/func.h"
#include "headers/data.h"
void loadData(auxVoo** voos, auxHotel** hoteis) {
    FILE* arquivoVoos=fopen("data/dataVoos.bin", "rb");
    if (arquivoVoos== NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para leitura\n");
        return;
    }
    Voos voo;
    while (fread(&voo, sizeof(Voos), 1, arquivoVoos) == 1) {
        adicionarVooLista(voos, &voo);
    }
    fclose(arquivoVoos);
    FILE* arquivoHoteis = fopen("data/dataHoteis.bin", "rb");
    if (arquivoHoteis==NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para leitura\n");
        return;
    }
    Hotel hotel;
    while (fread(&hotel, sizeof(Hotel), 1, arquivoHoteis) == 1) {
        adicionarHotelLista(hoteis, &hotel);
    }
    fclose(arquivoHoteis);
}
void saveData(auxVoo* voos, auxHotel* hoteis) {
    FILE* fileVoos = fopen("data/dataVoos.bin", "wb");
    if (fileVoos == NULL) {
        fprintf(stderr, "Error opening file for writing\n");
        return;
    }
    auxVoo* currentVoo = voos;
    while (currentVoo != NULL) {
        fwrite(&(currentVoo->voo), sizeof(Voos), 1, fileVoos);
        currentVoo = currentVoo->seguinte;
    }
    fclose(fileVoos);
    FILE* fileHoteis = fopen("data/dataHoteis.bin", "wb");
    if(fileHoteis == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita\n");
        return;
    }
    auxHotel* currentHotel = hoteis;
    while (currentHotel != NULL) {
        fwrite(&(currentHotel->hotel), sizeof(Hotel), 1, fileHoteis);
        currentHotel = currentHotel->seguinte;
    }
    fclose(fileHoteis);
}
