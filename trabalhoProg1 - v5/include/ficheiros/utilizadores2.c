#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // Para mkdir
#include "headers/func.h"
#include "headers/data.h"

// Função para salvar reservas em arquivos de texto
void salvar_reservas_texto(auxReserva *reservas, const char *nome_arquivo) {
    const char *dir = "data/";
    char caminho_completo[256]; // Buffer para o caminho completo

    // Inicializar o caminho_completo com o diretório
    strcpy(caminho_completo, dir);
    // Concatenar o nome do arquivo
    strcat(caminho_completo, nome_arquivo);

    // Certificar-se de que o diretório existe
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        if (mkdir(dir) == -1) {
    // Handle error appropriately
}
// Set permissions for the created directory
if (chmod(dir, 0700) == -1) {
    perror("Erro ao definir permissões do diretório");
    // Handle error appropriately
} // Criar o diretório se não existir
    }

    // Abrir o arquivo no novo caminho
    FILE *fp = fopen(caminho_completo, "w");
    if (!fp) {
        perror("Erro ao abrir o ficheiro de reservas");
        return;
    }

    // Contar o número de reservas
    int count = 0;
    auxReserva *temp = reservas;
    while (temp != NULL) {
        count++;
        temp = temp->seguinte;
    }
    fprintf(fp, "%d\n", count);

    // Escrever as reservas no arquivo
    while (reservas != NULL) {
        fprintf(fp, "%d %s\n", reservas->identificador, reservas->estado);
        if (reservas->reservaVoo != NULL) {
            fprintf(fp, "Voos:%s %i %s %s %s %s %i\n",
                    reservas->reservaVoo->voo->numero,
                    reservas->reservaVoo->lugares,
                    reservas->reservaVoo->voo->origem,
                    reservas->reservaVoo->voo->destino,
                    reservas->reservaVoo->voo->data,
                    reservas->reservaVoo->voo->hora,
                    reservas->reservaVoo->lugares);
        } else {
            fprintf(fp, "Voos:\n");
        }

        if (reservas->reservaHotel != NULL) {
            fprintf(fp, "Hoteis:%s %s %i %i\n",
                    reservas->reservaHotel->hotel->nome,
                    reservas->reservaHotel->hotel->localizacao,
                    reservas->reservaHotel->quartos,
                    reservas->reservaHotel->hotel->classificacao);
        } else {
            fprintf(fp, "Hoteis:\n");
        }

        fprintf(fp, "\n");
        reservas = reservas->seguinte;
    }

    fclose(fp);
}

void salvar_utilizador(auxutilizador *utilizadores) {
    const char *dir = "data/";

    // Certificar-se de que o diretório existe
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        if (mkdir(dir) == -1) {
    // Handle error appropriately
}
// Set permissions for the created directory
if (chmod(dir, 0700) == -1) {
    perror("Erro ao definir permissões do diretório");
    // Handle error appropriately
} // Criar o diretório se não existir
    }

    FILE *fp = fopen("data/dataUtilizadores.bin", "wb");
    if (!fp) {
        perror("Erro ao abrir o ficheiro");
        return;
    }

    while (utilizadores != NULL) {
        // Salva os dados do usuário atual
        fwrite(&(utilizadores->utilizador), sizeof(utilizadores->utilizador), 1, fp);

        // Gera o nome do arquivo de reservas
        char nome_arquivo[256];
        strcpy(nome_arquivo, utilizadores->utilizador.nome);
        strcat(nome_arquivo, "_reservas.txt");

        printf("\n%s\n", nome_arquivo);
        // Salva as reservas associadas ao usuário atual
        printf("Salvando reservas do utilizador %s\n", utilizadores->utilizador.nome);
        salvar_reservas_texto(utilizadores->utilizador.reservas, nome_arquivo);

        // Move para o próximo usuário na lista
        utilizadores = utilizadores->seguinte;
    }
    fclose(fp);
}

auxReserva* ler_reservas_texto(const char *nome_arquivo) {
    const char *dir = "data/";
    char caminho_completo[256]; // Buffer para o caminho completo

    // Inicializar o caminho_completo com o diretório
    strcpy(caminho_completo, dir);
    // Concatenar o nome do arquivo
    strcat(caminho_completo, nome_arquivo);

    FILE *fp = fopen(caminho_completo, "r");
    if (!fp) {
        perror("Erro ao abrir o ficheiro de reservas");
        return NULL;
    }

    int count;
    if (fscanf(fp, "%d\n", &count) != 1) {
        printf("Erro ao ler o número de reservas\n");
        fclose(fp);
        return NULL;
    }

    auxReserva *reservas = NULL;
    auxReserva *atual = NULL;
    for (int i = 0; i < count; i++) {
        auxReserva *novo = (auxReserva*)malloc(sizeof(auxReserva));
        novo->reservaVoo = NULL;
        novo->reservaHotel = NULL;
        novo->estado = (char*)malloc(50 * sizeof(char));
        if (fscanf(fp, "%d %49s\n", &novo->identificador, novo->estado) != 2) {
            printf("Erro ao ler o estado da reserva %d\n", i + 1);
            free(novo->estado);
            free(novo);
            continue;
        }

        // Tentativa de leitura dos dados do voo
        novo->reservaVoo = (ReservaVoo*)malloc(sizeof(ReservaVoo));
        novo->reservaVoo->voo = (Voos*)malloc(sizeof(Voos));
        char voo_line[256];
        if (fgets(voo_line, sizeof(voo_line), fp) && strncmp(voo_line, "Voos:", 5) == 0) {
            if (sscanf(voo_line, "Voos:%49s %d %49s %49s %49s %49s",
                       novo->reservaVoo->voo->numero,
                       &novo->reservaVoo->lugares,
                       novo->reservaVoo->voo->origem,
                       novo->reservaVoo->voo->destino,
                       novo->reservaVoo->voo->data,
                       novo->reservaVoo->voo->hora) == 6) {
                // Sucesso
            } else {
                free(novo->reservaVoo->voo);
                free(novo->reservaVoo);
                novo->reservaVoo = NULL;
            }
        } else {
            free(novo->reservaVoo->voo);
            free(novo->reservaVoo);
            novo->reservaVoo = NULL;
        }

        // Tentativa de leitura dos dados do hotel
        novo->reservaHotel = (ReservaHotel*)malloc(sizeof(ReservaHotel));
        novo->reservaHotel->hotel = (Hotel*)malloc(sizeof(Hotel));
        char hotel_line[256];
        if (fgets(hotel_line, sizeof(hotel_line), fp) && strncmp(hotel_line, "Hoteis:", 7) == 0) {
            if (sscanf(hotel_line, "Hoteis:%49s %49s %d %d",
                       novo->reservaHotel->hotel->nome,
                       novo->reservaHotel->hotel->localizacao,
                       &novo->reservaHotel->quartos,
                       &novo->reservaHotel->hotel->classificacao) == 4) {
                // Sucesso
            } else {
                free(novo->reservaHotel->hotel);
                free(novo->reservaHotel);
                novo->reservaHotel = NULL;
            }
        } else {
            free(novo->reservaHotel->hotel);
            free(novo->reservaHotel);
            novo->reservaHotel = NULL;
        }
        if (novo->reservaVoo || novo->reservaHotel) {
            novo->seguinte = NULL;
            if (atual == NULL) {
                reservas = novo;
            } else {
                atual->seguinte = novo;
            }
            atual = novo;
        } else {
            free(novo->estado);
            free(novo);
        }
    }
    fclose(fp);
    return reservas;
}
auxutilizador* ler_utilizadores() {
    const char *dir = "data/";

    // Certificar-se de que o diretório existe
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        if (mkdir(dir) == -1) {
    // Handle error appropriately
}
// Set permissions for the created directory
if (chmod(dir, 0700) == -1) {
    perror("Erro ao definir permissões do diretório");
    // Handle error appropriately
} // Criar o diretório se não existir
    }

    FILE *fp = fopen("data/dataUtilizadores.bin", "rb");
    if (!fp) {
        perror("Erro ao abrir o ficheiro");
        return NULL;
    }
    auxutilizador *utilizadores = NULL;
    auxutilizador *atual = NULL;
    while (1) {
        auxutilizador *novo = (auxutilizador*)malloc(sizeof(auxutilizador));
        if (fread(&(novo->utilizador), sizeof(novo->utilizador), 1, fp) != 1) {
            free(novo);
            break;
        }
        char nome_arquivo[256];
        strcpy(nome_arquivo, novo->utilizador.nome);
        strcat(nome_arquivo, "_reservas.txt");
        novo->utilizador.reservas = ler_reservas_texto(nome_arquivo);
        novo->seguinte = NULL;
        novo->anterior = atual;
        if (atual == NULL) {
            utilizadores = novo;
        } else {
            atual->seguinte = novo;
        }
        atual = novo;
    }
    fclose(fp);
    return utilizadores;
}