#ifndef _DATA_H_
#define _DATA_H_
#ifdef _WIN32
    #define OS "Windows"
    #define Clear "cls"
#elif __APPLE__
    #define OS "Mac"
    #define Clear "clear"
#else
    #define OS "Outro"
    #define Clear "clear" // Assumindo que o comando clear funciona em outros sistemas Unix-like
#endif
typedef struct {
    char numero[50];
    char origem[50];
    char destino[50];
    char data[20];
    char hora[10];
    int assentos_disponiveis;
} Voos;
typedef struct auxVoo {
    Voos voo;
    struct auxVoo *seguinte;
} auxVoo;
typedef struct {
    char nome[50];
    char localizacao[50];
    int quartos_disponiveis;
    int classificacao;
} Hotel;
typedef struct auxHotel {
    Hotel hotel;
    struct auxHotel *seguinte;
} auxHotel;
typedef struct {
    char id[64];
    Voos *voo;
    int lugares;
} ReservaVoo;
typedef struct {
    char id[64];
    Hotel *hotel;
    int quartos;
} ReservaHotel;
typedef struct auxReserva {
    int identificador;
    ReservaVoo *reservaVoo;
    ReservaHotel *reservaHotel;
    char *estado;
    struct auxReserva *seguinte;
    struct auxReserva *anterior;
} auxReserva;
typedef struct {
    char nome[50];
    char email[50];
    char passe[50];
    auxReserva *reservas;
} utilizador;
typedef struct auxutilizador {
    utilizador utilizador;
    struct auxutilizador *seguinte;
    struct auxutilizador *anterior;
} auxutilizador;
#endif // _DATATYPE_H_
