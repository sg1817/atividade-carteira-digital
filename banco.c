#include <stdio.h>
#include <string.h>


Cliente clientes[MAX_CLIENTES];
int qtdClientes = 0;
int proximoNumero = 1000;
int bancoAberto = 0;

void cadastrarCliente(char nome[]) {
    if (qtdClientes == MAX_CLIENTES) {
        printf("Banco cheio!\n");
        return;
    }
    strcpy(clientes[qtdClientes].nome, nome);
    clientes[qtdClientes].qtdContas = 0;
    clientes[qtdClientes].temEmprestimo = 0;
    qtdClientes++;
    printf("Cliente cadastrado!\n");
}