#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "headers/func.h"
#include "headers/data.h"

// Declaração de variáveis globais
auxVoo* voos = NULL;
auxHotel* hoteis = NULL;
auxutilizador* utilizadores = NULL;
int funcVoos(auxVoo** voos) {
    int choice;
    do {
        printf("1-Listar os Voos\n2-Adicionar Voos\n3-Editar Voos\n4-Remover Voos\n5-Sair\nEscolha:\n");
        
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                listarVoos(*voos);
                break;
            case 2:
                adicionarVoo(voos);
                break;
            case 3:
                removerInfoV(*voos);
                break;
            case 4:
                removerVoo(voos);
                break;
            case 5:
                printf("A sair...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
        printf("\n");
    } while(choice != 5);
    return 0;
}
int funcHoteis(auxHotel** hoteis) {
    int escolha;
    do {
        printf("_MENU_\n1-Listar os Hoteis\n2-Adicionar Hoteis\n3-Editar Hoteis\n4-Remover Hoteis\n5-Sair\nEscolha:");
        scanf("%d", &escolha);
        fflush(stdin);
        switch(escolha) {
            case 1:
                listarHoteis(*hoteis);
                break;
            case 2:
                adicionarHoteis(hoteis);
                break;
            case 3:
                removerInfoH(*hoteis);
                break;
            case 4:
                removerHoteis(hoteis);
                break;
            case 5:
                printf("A sair...\n");
                return 0;
        }
    } while(escolha != 5);
    return 0;
}
// Função principal
int main() {
    // Inicialização do gerador de números aleatórios
    srand(time(NULL));
    // Carregamento de dados
    loadData(&voos, &hoteis);
    printf("A carregar utilizadores\n");
    sleep(2);
    utilizadores = ler_utilizadores();
    // Caso não haja nenhum usuário registrado, cria-se um usuário "admin"
    if(utilizadores == NULL) {
        utilizadores = (auxutilizador*)malloc(sizeof(auxutilizador));
        strcpy(utilizadores->utilizador.nome, "admin");
        strcpy(utilizadores->utilizador.passe, "admin");
        utilizadores->utilizador.reservas = NULL;
        utilizadores->seguinte = NULL;
    }

    // Apresentação do menu inicial
    printf("Bem vindo, por favor faça login (a) ou criar uma conta nova (b).\n");
    char escolha;
    scanf(" %c", &escolha);
    if(escolha == 'b') {
        // Código para criação de uma nova conta
        auxutilizador* novoUtilizador = (auxutilizador*)malloc(sizeof(auxutilizador));
        if (novoUtilizador == NULL) {
            fprintf(stderr, "Erro de alocação de memória\n");
            return 1;
        }
        novoUtilizador->utilizador.reservas = NULL;
        novoUtilizador->seguinte = NULL;
        printf("Nome de Utilizador: ");
        scanf("%s", novoUtilizador->utilizador.nome);
        if (strcmp(novoUtilizador->utilizador.nome, "admin") == 0) {
            printf("Erro, não pode criar uma conta administradora\n");
            free(novoUtilizador); 
            return 1;
        }
        auxutilizador* temp = utilizadores;
        while(temp->seguinte != NULL) {
            if(strcmp(temp->utilizador.nome, novoUtilizador->utilizador.nome) == 0) {
                printf("Erro, nome de utilizador já existe\n");
                free(novoUtilizador); 
                return 1;
            }
            temp = temp->seguinte;
        }
        if(strcmp(temp->utilizador.nome, novoUtilizador->utilizador.nome) == 0) {
            printf("Erro, nome de utilizador já existe\n");
            free(novoUtilizador); 
            return 1;
        }
        get_password(novoUtilizador->utilizador.passe, sizeof(novoUtilizador->utilizador.passe));
        temp->seguinte = novoUtilizador;
        // Adicionado código para vincular o anterior
        novoUtilizador->anterior = temp;
        printf("Conta criada com sucesso.\n");
        // Prossiga para o menu do utilizador recém-criado
        auxutilizador* currentUser = novoUtilizador;
        menuUsers(currentUser,voos,hoteis);
    } else {
        // Código para login de usuário existente
        printf("Introduza o seu nome de utilizador: ");
        char nome[50], passe[50];
        scanf("%s", nome);

        // Verifica se o nome de usuário é "admin"
        if(strcmp(nome, "admin") == 0) {
            // Solicita a senha ao usuário
            get_password(passe, sizeof(passe));
            // Verifica se a senha corresponde à senha do administrador
            if(strcmp(passe, "admin") == 0) {
                printf("Bem vindo administrador.\n");

                char choice;
                do {
                    printf("Deseja mexer em hoteis(h), voos(v), reservas(r) ou utilizadores(u) [s para sair]?\nEscolha: ");
                    fflush(stdin);
                    scanf(" %c", &choice); 
                    switch(choice) {
                        case 'h':
                            funcHoteis(&hoteis);
                            break;
                        case 'v':
                            funcVoos(&voos);
                            break;
                        case 'r':
                            // Função para listar cancelamentos
                            adminListarCancelamentos(utilizadores,voos,hoteis);
                            break;
                        case 'u':
                            // Função para listar utilizadores
                            listarUtilizadores(utilizadores);
                            break;
                        case 's':
                            printf("A sair...\n");
                            break;
                        default:
                            printf("Tente novamente\n");
                    }
                } while(choice != 's');
            } else {
                printf("Erro, password incorreta\n");
                return 1;
            }
        } else {
            // Código para login de um usuário comum
            auxutilizador* temp = utilizadores;
            while(temp != NULL && strcmp(temp->utilizador.nome, nome) != 0) {
                temp = temp->seguinte;
            }
            if(temp == NULL) {
                printf("Erro, nome de utilizador não encontrado\n");
                return 1;
            }

            get_password(passe, sizeof(passe));
            if(strcmp(temp->utilizador.passe, passe) != 0) {
                printf("Erro, password incorreta\n");
                return 1;
            }
            printf("Bem vindo %s\n", temp->utilizador.nome);
            auxutilizador* currentUser = temp;
            menuUsers(currentUser,voos,hoteis);
        }
    }

    // Salvando dados antes de sair
    saveData(voos, hoteis);
    if(utilizadores != NULL) {
        salvar_utilizador(utilizadores);
    }

    // Liberando a memória alocada
    limpaListas(voos, hoteis, utilizadores);
    
    return 0;
}
