
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "historico.h"


int main() {

    Cliente clientes[MAX_CLIENTES];

    int qtdClientes = 0;

    int proximoNumero = 1000;

    int opcao;

    int bancoAberto = 0;

    srand(time(NULL));

    do {

        printf("\n========== CARTEIRA DIGITAL ==========\n");

        printf("1 - Abrir banco\n");
        printf("2 - Cadastrar cliente/conta\n");
        printf("3 - Depositar\n");
        printf("4 - Sacar\n");
        printf("5 - Solicitar emprestimo\n");
        printf("6 - Consultar historico\n");
        printf("7 - Efetuar sorteio\n");
        printf("8 - Sair\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:

                if (bancoAberto == 0) {

                    bancoAberto = 1;

                    printf("\nBanco aberto com sucesso!\n");

                } else {

                    printf("\nO banco ja esta aberto!\n");

                }

                break;


            case 2:

                cadastrarConta(clientes, &qtdClientes, &proximoNumero);

                break;


            case 3:

                depositar(clientes, qtdClientes);

                break;


            case 4:

                sacar(clientes, qtdClientes);

                break;


            case 5:

                solicitarEmprestimo(clientes, qtdClientes);

                break;


            case 6:

                if (bancoAberto == 1) {

                    consultarHistorico(clientes, qtdClientes);

                } else {

                    printf("\nO banco precisa estar aberto!\n");

                }

                break;


            case 7:

                if (bancoAberto == 1) {

                    realizarSorteio(clientes, qtdClientes);

                } else {

                    printf("\nO banco precisa estar aberto!\n");

                }

                break;


            case 8:

                printf("\nEncerrando o programa...\n");

                break;


            default:

                printf("\nOpcao invalida!\n");

        }

    } while (opcao != 8);

    return 0;

}

