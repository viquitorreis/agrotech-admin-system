#include "../helpers/helpers.h"

#define MAX_CLIENTES 100

int insertCustomer(Cliente newCustomer) {
    FILE *fptr = OPEN_FILE_HELPER(customerStoreFilePath, "a+");
    if (fptr == NULL) {
        fptr = OPEN_FILE_HELPER(customerStoreFilePath, "w");
        if (fptr == NULL) {
            return 0;
        }
    }

    fprintf(fptr, "cpf: %s, nome: %s, telefone: %s, endereco: %s, %d, %s, %s, dataNascimento: %d, %d, %d\n",
        newCustomer.cpf,
        newCustomer.nome,
        newCustomer.telefone,
        newCustomer.endereco.rua,
        newCustomer.endereco.numero,
        newCustomer.endereco.cidade,
        newCustomer.endereco.estado,
        newCustomer.dataDeNascimento.dia,
        newCustomer.dataDeNascimento.mes,
        newCustomer.dataDeNascimento.ano
    );

    fclose(fptr);

    return 1;
}

void createCustomer() {
    int customersCount = getFileLinesCountHelper(customerStoreFilePath);

    if (customersCount < MAX_CLIENTES) {
        Cliente newCustomer;

        printf("Digite o CPF do cliente (apenas numeros): ");
        scanf("%s", newCustomer.cpf);

        if (checkCustomerExistsByCPFHelper(newCustomer.cpf)) {
            printf("CPF ja cadastrado!\n");
            return;
        }
        
        printf("Digite o nome do cliente: ");
        scanf(" %[^\n]", newCustomer.nome);

        printf("Digite o telefone do cliente: ");
        scanf(" %[^\n]", newCustomer.telefone);

        printf("Dados de endereco:\n");
        printf("Rua: "); scanf(" %[^\n]", newCustomer.endereco.rua);
        printf("Numero: "); scanf("%d", &newCustomer.endereco.numero);
        printf("Cidade: "); scanf(" %[^\n]", newCustomer.endereco.cidade);
        printf("Estado: "); scanf(" %[^\n]", newCustomer.endereco.estado);

        printf("Digite a data de nascimento do cliente (dd/mm/yyyy): ");
        int dia, mes, ano;
        scanf("%d/%d/%d", &dia, &mes, &ano);

        if (!validateDateHelper(dia, mes, ano)) {
            printf("Data de nascimento invalida!\n");
            return;
        }
        newCustomer.dataDeNascimento = createDateHelper(dia, mes, ano);

        if (insertCustomer(newCustomer)) {
            printf("Cliente cadastrado com sucesso!\n");
        } else {
            printf("Nao foi possivel cadastrar o cliente.\n");
        }

        return;
    } else {
        printf("Nao foi possivel cadastrar o cliente pois o limite de clientes cadastrados (100) ja foi atingido.\n");
    }
}

int readCustomerByCPF(char cpf[15]) {
    FILE *fptr = OPEN_FILE_HELPER(customerStoreFilePath, "r");
    if (fptr == NULL) {
        fclose(fptr);
        return 0;
    }

    char line[1000];
    while(fgets(line, sizeof(line), fptr)) {
        // checa se na linha contém o cpf especificado
        if (strstr(line, cpf) != NULL) {
            printf("%s", line);
            fclose(fptr);
            return 1;
        }
    }

    fclose(fptr);
    printf("Cliente nao encontrado!\n");
    return 0;
}

void readCustomer() {
    char cpf[15];
    printf("Digite o cpf do cliente: "); scanf("%s", cpf);
    
    readCustomerByCPF(cpf);
}