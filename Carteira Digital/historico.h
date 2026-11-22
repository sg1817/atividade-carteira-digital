
#ifndef HISTORICO_H
#define HISTORICO_H

#define MAX_CLIENTES 50
#define MAX_CONTAS 3
#define MAX_HISTORICO 30

// Estrutura da conta
typedef struct {
    int numero;
    int tipo;
    float saldo;

    char historico[MAX_HISTORICO][100];
    int qtdHistorico;

} Conta;


// Estrutura do cliente
typedef struct {
    char nome[50];

    Conta contas[MAX_CONTAS];
    int qtdContas;

    int pediuEmprestimo;

} Cliente;


// Declaracao das funcoes

int buscarCliente(Cliente clientes[], int qtd, char nome[]);

void adicionarHistorico(Conta *conta, char texto[]);

void cadastrarConta(Cliente clientes[], int *qtdClientes, int *proximoNumero);

void depositar(Cliente clientes[], int qtdClientes);

void sacar(Cliente clientes[], int qtdClientes);

void solicitarEmprestimo(Cliente clientes[], int qtdClientes);

void consultarHistorico(Cliente clientes[], int qtdClientes);

void realizarSorteio(Cliente clientes[], int qtdClientes);

#endif

