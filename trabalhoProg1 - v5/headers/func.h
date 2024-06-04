#ifndef _FUNCTIONS
#define _FUNCTIONS
#include "data.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#ifndef _WIN32
    void disable_echo(struct termios *old_tio);
    void enable_echo(struct termios *old_tio);
#endif
void get_password(char *password, size_t size); 
void adicionarHoteis(auxHotel** inicio);
void removerHoteis(auxHotel** inicio);
void removerInfoH(auxHotel* inicio);
void listarHoteis(auxHotel* inicio);
void adicionarVoo(auxVoo** inicio);
void removerVoo(auxVoo** inicio);
void removerInfoV(auxVoo* inicio);
void listarVoos(auxVoo* inicio);
void criarReserva(utilizador *utilizador, auxVoo *voo, auxHotel *hotel);
void reservaVoo(utilizador *utilizador, auxVoo *voo, auxReserva *novaReserva);
void reservaHotel(utilizador *utilizador, auxHotel *hotel, auxReserva *novaReserva);
void get_password(char *password, size_t size);
void saveData(auxVoo* voos, auxHotel* hoteis);
void loadData(auxVoo** voos, auxHotel** hoteis);
void adicionarVooLista(auxVoo** voos, Voos* voo);
void adicionarHotelLista(auxHotel** hoteis, Hotel* hotel);
auxReserva* ler_reservas(FILE *fp);
auxutilizador* ler_utilizadores();
void listarReservas(auxutilizador* utilizador);
void listarUtilizadores(auxutilizador* utilizador);
void cancelarReserva(auxutilizador* utilizador);
void listarCancelamentos(auxutilizador* utilizador);
void limpaListas(auxVoo* voos, auxHotel* hoteis, auxutilizador* utilizadores);
void limpaReservas(auxReserva* reservas);
void limparBufferEntrada();
void salvar_reservas_texto(auxReserva *reservas, const char *nome_arquivo);
void salvar_utilizador(auxutilizador *utilizadores);
auxReserva* ler_reservas_texto(const char *nome_arquivo);
auxutilizador* ler_utilizadores();
void adminListarCancelamentos(auxutilizador* utilizadores,auxVoo* voos,auxHotel* hoteis);
void ordenarReservas(auxReserva *inicio);
void trocarReservas(auxReserva *reserva1, auxReserva *reserva2);
void ordenarHoteis(auxHotel *inicio);
void trocarHoteis(auxHotel *hotel1, auxHotel *hotel2);
void ordenarVoos(auxVoo *inicio);
void trocarVoos(auxVoo *voo1, auxVoo *voo2);
void procurarVoos(auxVoo *voos);
void procurarHoteis(auxHotel *hoteis);
void menuUsers(auxutilizador* currentUser, auxVoo* voos, auxHotel* hoteis);
#endif