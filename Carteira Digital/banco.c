
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "historico.h"


// Procura um cliente pelo nome
int buscarCliente(Cliente clientes[], int qtd, char nome[]) {

    int i;

    for (i = 0; i < qtd; i++) {

        if (strcmp(clientes[i].nome, nome) == 0) {
            return i;
        }

    }

    return -1;
}


// Adiciona uma operacao ao historico
void adicionarHistorico(Conta *conta, char texto[]) {

    if (conta->qtdHistorico < MAX_HISTORICO) {

        strcpy(conta->historico[conta->qtdHistorico], texto);

        conta->qtdHistorico++;

    }

}


// Cadastra cliente e cria uma conta
void cadastrarConta(Cliente clientes[], int *qtdClientes, int *proximoNumero) {

    char nome[50];

    int tipo;
    int posicao;
    int i;

    printf("\nNome do cliente: ");
    scanf(" %49[^\n]", nome);

    posicao = buscarCliente(clientes, *qtdClientes, nome);

    // Verifica se o cliente ja existe
    if (posicao == -1) {

        if (*qtdClientes >= MAX_CLIENTES) {
            printf("\nLimite de clientes atingido!\n");
            return;
        }

        posicao = *qtdClientes;

        strcpy(clientes[posicao].nome, nome);

        clientes[posicao].qtdContas = 0;

        clientes[posicao].pediuEmprestimo = 0;

        (*qtdClientes)++;

    }

    // Verifica o limite de contas
    if (clientes[posicao].qtdContas >= MAX_CONTAS) {

        printf("\nCliente ja possui o limite de contas!\n");
        return;

    }

    printf("\nTipos de conta:\n");
    printf("1 - Conta corrente\n");
    printf("2 - Conta salario\n");
    printf("3 - Conta poupanca\n");

    printf("Escolha: ");
    scanf("%d", &tipo);

    if (tipo < 1 || tipo > 3) {

        printf("\nTipo de conta invalido!\n");
        return;

    }

    // Verifica as regras dos tipos de conta
    for (i = 0; i < clientes[posicao].qtdContas; i++) {

        if (clientes[posicao].contas[i].tipo == tipo) {

            printf("\nCliente ja possui esse tipo de conta!\n");
            return;

        }

        if ((tipo == 1 && clientes[posicao].contas[i].tipo == 2) ||
            (tipo == 2 && clientes[posicao].contas[i].tipo == 1)) {

            printf("\nO cliente nao pode possuir conta salario e corrente simultaneamente!\n");
            return;

        }

    }

    if (*proximoNumero > 9999) {

        printf("\nNao ha mais numeros de conta disponiveis!\n");
        return;

    }

    // Cria a conta
    i = clientes[posicao].qtdContas;

    clientes[posicao].contas[i].numero = *proximoNumero;

    clientes[posicao].contas[i].tipo = tipo;

    clientes[posicao].contas[i].saldo = 0;

    clientes[posicao].contas[i].qtdHistorico = 0;

    (*proximoNumero)++;

    clientes[posicao].qtdContas++;

    printf("\nConta criada com sucesso!\n");

    printf("Numero da conta: %04d-%02d\n",
           clientes[posicao].contas[i].numero, tipo);

    adicionarHistorico(&clientes[posicao].contas[i],
                       "Conta criada.");

}


// Realiza deposito
void depositar(Cliente clientes[], int qtdClientes) {

    int numero;
    int i, j;

    float valor;

    char texto[100];

    printf("\nNumero da conta: ");
    scanf("%d", &numero);

    for (i = 0; i < qtdClientes; i++) {

        for (j = 0; j < clientes[i].qtdContas; j++) {

            if (clientes[i].contas[j].numero == numero) {

                printf("Valor do deposito: R$ ");
                scanf("%f", &valor);

                if (valor <= 0) {

                    printf("\nValor invalido!\n");
                    return;

                }

                clientes[i].contas[j].saldo += valor;

                printf("\nDeposito realizado com sucesso!\n");

                printf("Saldo atual: R$ %.2f\n",
                       clientes[i].contas[j].saldo);

                sprintf(texto, "Deposito de R$ %.2f", valor);

                adicionarHistorico(&clientes[i].contas[j], texto);

                return;

            }

        }

    }

    printf("\nConta nao encontrada!\n");

}


// Realiza saque
void sacar(Cliente clientes[], int qtdClientes) {

    int numero;
    int i, j;

    float valor;

    char texto[100];

    printf("\nNumero da conta: ");
    scanf("%d", &numero);

    for (i = 0; i < qtdClientes; i++) {

        for (j = 0; j < clientes[i].qtdContas; j++) {

            if (clientes[i].contas[j].numero == numero) {

                printf("Valor do saque: R$ ");
                scanf("%f", &valor);

                if (valor <= 0) {

                    printf("\nValor invalido!\n");
                    return;

                }

                if (valor > clientes[i].contas[j].saldo) {

                    printf("\nSaldo insuficiente!\n");
                    return;

                }

                clientes[i].contas[j].saldo -= valor;

                printf("\nSaque realizado com sucesso!\n");

                printf("Saldo atual: R$ %.2f\n",
                       clientes[i].contas[j].saldo);

                sprintf(texto, "Saque de R$ %.2f", valor);

                adicionarHistorico(&clientes[i].contas[j], texto);

                return;

            }

        }

    }

    printf("\nConta nao encontrada!\n");

}


// Solicita emprestimo
void solicitarEmprestimo(Cliente clientes[], int qtdClientes) {

    char nome[50];
    char texto[100];

    int posicao;
    int i;

    int temCorrente = 0;
    int temPoupanca = 0;

    int indiceCorrente = -1;

    float saldoTotal = 0;
    float limite;
    float valor;

    printf("\nNome do cliente: ");
    scanf(" %49[^\n]", nome);

    posicao = buscarCliente(clientes, qtdClientes, nome);

    if (posicao == -1) {

        printf("\nCliente nao encontrado!\n");
        return;

    }

    if (clientes[posicao].pediuEmprestimo == 1) {

        printf("\nEste cliente ja solicitou um emprestimo!\n");
        return;

    }

    // Verifica as contas e soma os saldos
    for (i = 0; i < clientes[posicao].qtdContas; i++) {

        saldoTotal += clientes[posicao].contas[i].saldo;

        if (clientes[posicao].contas[i].tipo == 1) {

            temCorrente = 1;
            indiceCorrente = i;

        }

        if (clientes[posicao].contas[i].tipo == 3) {

            temPoupanca = 1;

        }

    }

    if (temCorrente == 0 || temPoupanca == 0) {

        printf("\nPrecisa possuir conta corrente e poupanca!\n");
        return;

    }

    limite = (saldoTotal * 10) * 0.25;

    printf("\nSaldo total: R$ %.2f\n", saldoTotal);

    printf("Limite do emprestimo: R$ %.2f\n", limite);

    printf("\nQual valor deseja solicitar? R$ ");
    scanf("%f", &valor);

    if (valor <= 0 || valor > limite) {

        printf("\nValor solicitado invalido ou acima do limite!\n");
        return;

    }

    // Deposita o emprestimo na conta corrente
    clientes[posicao].contas[indiceCorrente].saldo += valor;

    clientes[posicao].pediuEmprestimo = 1;

    sprintf(texto, "Emprestimo recebido: R$ %.2f", valor);

    adicionarHistorico(&clientes[posicao].contas[indiceCorrente], texto);

    printf("\nEmprestimo aprovado!\n");

    printf("Novo saldo: R$ %.2f\n",
           clientes[posicao].contas[indiceCorrente].saldo);

}


// Consulta historico
void consultarHistorico(Cliente clientes[], int qtdClientes) {

    char nome[50];

    int posicao;
    int i, j;

    printf("\nNome do cliente: ");
    scanf(" %49[^\n]", nome);

    posicao = buscarCliente(clientes, qtdClientes, nome);

    if (posicao == -1) {

        printf("\nCliente nao encontrado!\n");
        return;

    }

    printf("\n========== HISTORICO ==========\n");

    printf("Cliente: %s\n", clientes[posicao].nome);

    for (i = 0; i < clientes[posicao].qtdContas; i++) {

        printf("\nConta: %04d-%02d\n",
               clientes[posicao].contas[i].numero,
               clientes[posicao].contas[i].tipo);

        printf("Saldo: R$ %.2f\n",
               clientes[posicao].contas[i].saldo);

        for (j = 0; j < clientes[posicao].contas[i].qtdHistorico; j++) {

            printf("- %s\n",
                   clientes[posicao].contas[i].historico[j]);

        }

    }

    printf("\n===============================\n");

}


// Realiza sorteio
void realizarSorteio(Cliente clientes[], int qtdClientes) {

    int sorteado;

    if (qtdClientes == 0) {

        printf("\nNao existem clientes cadastrados!\n");
        return;

    }

    sorteado = rand() % qtdClientes;

    printf("\n========== SORTEIO ==========\n");

    printf("Cliente sorteado: %s\n",
           clientes[sorteado].nome);

    printf("============================\n");

}

