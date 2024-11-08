#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTES 100
#define MAX_PRODUTOS 100
#define MAX_VENDAS 100

typedef struct Data {
    int dia, mes, ano;
} data;

typedef struct Endereco {
    char rua[100];
    int numero;
    char cidade[100];
    char estado[100];
} endereco;

typedef struct Cliente {
    char cpf[15];
    char nome[100];
    char telefone[20];
    endereco endereco;
    data dataDeNascimento;
} cliente;

typedef struct Produto {
    int codigo;
    char descricao[100];
    int quantidadeNoEstoque;
    float precoUnitario;
} produto;

typedef struct Venda {
    char cpfCliente[15];
    int codigoProduto;
    int quantidadeComprada;
} venda;

cliente clientes[MAX_CLIENTES];
produto produtos[MAX_PRODUTOS];
venda vendas[MAX_VENDAS];

int indiceClientes = 0;
int indiceProdutos = 0;
int indiceVendas = 0;

data criarData (int dia, int mes, int ano) {
    data data;
    data.dia = dia;
    data.mes = mes;
    data.ano = ano;
    return data;
}

endereco criarEndereco(char rua[100], int numero, char cidade[100], char estado[100]) {
    endereco endereco;
    strcpy(endereco.rua, rua);
    endereco.numero = numero;
    strcpy(endereco.cidade, cidade);
    strcpy(endereco.estado, estado);
    return endereco;
}

// validacao do cpf

char* validarFormatoCPF(char cpf[15]) {
    int subIndex = 0;
    char cpfTemporario[12];
    char *cpfFormatado = (char*) malloc(15 * sizeof(char));

    for (int index = 0; index < strlen(cpf); index++) {
        if (cpf[index] >= '0' && cpf[index] <= '9')
            cpfTemporario[subIndex++] = cpf[index];
    } 
    cpfTemporario[subIndex] = '\0';

    if (strlen(cpfTemporario) != 11)
    {
        printf("CPF invalido!\n");
        free(cpfFormatado);
        return NULL;
    }

    sprintf(cpfFormatado, "%c%c%c.%c%c%c.%c%c%c-%c%c", 
    cpfTemporario[0], cpfTemporario[1], cpfTemporario[2],
    cpfTemporario[3], cpfTemporario[4], cpfTemporario[5],
    cpfTemporario[6], cpfTemporario[7], cpfTemporario[8],
    cpfTemporario[9], cpfTemporario[10]);

    return cpfFormatado;
}

int validarData(int dia, int mes, int ano) {
    if (ano < 1900 || ano > 2024) return 0;
    if (mes < 1 || mes > 12) return 0;
    if (dia < 1 || dia > 31) return 0;

    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) 
        return 0;

    if (mes == 2) {
        int bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
        if (dia > 29 || (dia == 29 && !bissexto)) 
            return 0;
    }

    return 1;
    
}

int verificarCpfClienteExiste(char cpf[15]) {
    for (int index = 0; index < indiceClientes; index++) {
        if (strcmp(clientes[index].cpf, cpf))
            return 1;
    }

    return 0;
}

int verificarCodigoProdutoExiste(int codigo) {
    for (int index = 0; index < indiceProdutos; index++) {
        if (produtos[index].codigo == codigo)
            return 1;
    }
    return 0;
}

void cadastrarCliente() {
    if (indiceClientes < MAX_CLIENTES)
    {
        cliente novoCliente;

        printf("Digite o CPF do cliente (apenas numeros): ");
        scanf("%s", novoCliente.cpf);

        if (verificarCpfClienteExiste(novoCliente.cpf))
        {
            printf("CPF ja cadastrado!");
            return;
        }
        
        printf("Digite o nome do cliente: ");
        scanf(" %[^\n]", novoCliente.nome);

        printf("Digite o telefone do cliente: ");
        scanf(" %[^\n]", novoCliente.telefone);

        printf("Dados de endereco:\n");
        printf("Rua: "); scanf(" %[^\n]", novoCliente.endereco.rua);
        printf("Numero: "); scanf("%d", &novoCliente.endereco.numero);
        printf("Cidade: "); scanf(" %[^\n]", novoCliente.endereco.cidade);
        printf("Estado: "); scanf(" %[^\n]", novoCliente.endereco.estado);

        printf("Digite a data de nascimento do cliente (dd/mm/yyyy): ");
            int dia, mes, ano;
            scanf("%d/%d/%d", &dia, &mes, &ano);

            if (!validarData(dia, mes, ano)) {
                printf("Data de nascimento invalida!");
                return;
            }
        novoCliente.dataDeNascimento = criarData(dia, mes, ano);

        clientes[indiceClientes] = novoCliente;
        indiceClientes++;
        printf("Cliente cadastrado com sucesso!");

    } else 
        printf("Nao foi possivel cadastrar o cliente pois o limite de clientes cadastrados (100) ja foi atingido.");
    
}

void cadastrarProduto() {
    if (indiceProdutos < MAX_PRODUTOS)
    {
        produto novoProduto;
        
        printf("Digite o codigo do produto: ");
        scanf("%d", &novoProduto.codigo);

        if (verificarCodigoProdutoExiste(novoProduto.codigo)) {
            printf("Produto ja cadastrado.");
            return;
        }

        printf("Digite a descricao do produto: ");
        scanf(" %[^\n]", novoProduto.descricao);

        printf("Digite qual a quantidade desse produto no estoque: ");
        scanf("%d", &novoProduto.quantidadeNoEstoque);

        printf("Digite o preco da unidade desse produto: ");
        scanf("%f", &novoProduto.precoUnitario);
        
        produtos[indiceProdutos] = novoProduto;
        indiceProdutos++;
        printf("Produto cadastrado com sucesso!");
    } else
        printf("Nao foi possivel cadastrar esse produto pois o limite de produtos cadastrados (100) foi atingido");
    
}

void realizarVenda() {
    if (indiceVendas < MAX_VENDAS)
    {
        venda novaVenda;
        
        printf("Digite o cpf do cliente (apenas numeros): ");
        scanf("%s", novaVenda.cpfCliente);

        int clienteExistente = 0;
            for (int index = 0; index < indiceClientes; index++)
            {
                if (strcmp(novaVenda.cpfCliente, clientes[index].cpf) == 0)
                {
                    clienteExistente = 1;
                    break;
                }
            }

            if (!clienteExistente) {
                printf("Cliente nao encontrado!\n");
                return;
            }

            printf("Digite o codigo do produto: ");
            scanf("%d", &novaVenda.codigoProduto);

            int produtoExistente = 0;

            for (int index = 0; index < indiceProdutos; index++)
            {
                if (produtos[index].codigo == novaVenda.codigoProduto);
                {
                    produtoExistente = 1;
                    break;
                }
            }

            if (!produtoExistente)
            {
                printf("Produto inexistente.");
                return;
            }

            printf("Digite a quantidade comprada: ");
            scanf("%d", &novaVenda.quantidadeComprada);

            for (int index = 0; index < indiceProdutos; index++)
            {
                if (produtos[index].codigo = novaVenda.codigoProduto)
                {
                    if (produtos[index].quantidadeNoEstoque < novaVenda.quantidadeComprada)
                    {
                        printf("Nao tem produtos o suficiente no estoque!");
                        return;
                    }
                    produtos[index].quantidadeNoEstoque -= novaVenda.quantidadeComprada;
                    break;
                }
            }

            vendas[indiceVendas] = novaVenda;
            indiceVendas++;
            printf("Venda realizada com sucesso!");
            
    } else printf("Limite de vendas ja foi atingido!");
    
}

void consultarCliente() {
    char cpf[15];
    printf("Digite o cpf do cliente: "); scanf("%s", cpf);

    for (int index = 0; index < indiceClientes; index++)
    {
        if (strcmp(clientes[index].cpf, cpf) == 0)
        {
            printf("Nome: %s\n", clientes[index].nome);
            printf("Telefone: %s\n", clientes[index].telefone);
            printf("Endereco: %s, %d, %s, %s\n",
                    clientes[index].endereco.rua,
                    clientes[index].endereco.numero,
                    clientes[index].endereco.cidade,
                    clientes[index].endereco.estado);
            printf("Data de nascimento: %02d/%02d/%04d\n", 
                    clientes[index].dataDeNascimento.dia,
                    clientes[index].dataDeNascimento.mes,
                    clientes[index].dataDeNascimento.ano);
            return;
        }
    }

    printf("Cliente nao cadastrado. Verifique o cpf e tente novamente.");
}

void consultarProduto() {
    int codigo;
    printf("Digite o codigo do produto: "); scanf("%d", &codigo);

    for (int index = 0; index < indiceProdutos; index++)
    {
        if (produtos[index].codigo == codigo)
        {
            printf("Descricao: %s\n", produtos[index].descricao);
            printf("Valor unitario: %.2f\n", produtos[index].precoUnitario);
            printf("Quantidade no estoque: %d\n", produtos[index].quantidadeNoEstoque);
            return;
        }
    }

    printf("Produto nao encontrado.");

}
