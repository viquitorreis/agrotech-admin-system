#ifndef TYPES_H
#define TYPES_H

typedef struct {
    int dia, mes, ano;
} Data;

typedef struct {
    char rua[100];
    int numero;
    char cidade[100];
    char estado[100];
} Endereco;

typedef struct {
    char cpf[15];
    char nome[100];
    char telefone[20];
    Endereco endereco;
    Data dataDeNascimento;
} Cliente;

typedef char IDProduto[3];

typedef struct {
    IDProduto ID;
    char descricao[100];
    int quantidadeNoEstoque;
    float precoUnitario;
} Produto;

typedef struct {
    char cpfCliente[15];
    IDProduto IDProduto;
    int quantidadeComprada;
} Venda;

#endif