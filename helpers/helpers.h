#ifndef HELPERS_H
#define HELPERS_H // define HELPERS_H para evitar redefinição

#include <stdio.h>
#include "types.h"

const char customerStoreFilePath[] = "db/customer_store.txt";
const char lastProductIDFilePath[] = "db/last_product_id.txt";
const char productStoreFilePath[] = "db/products_store.txt";

// função openFileHelper vai abrir um arquivo e retornar um ponteiro para o arquivo
// recebe o nome do arquivo, o modo de abertura (append, read, write, etc) e o nome da função que chamou, para debugar erros
FILE *openFileHelper(const char *fileName, const char *mode, char const *callerFunctionName, const char *callerFileName, int callerLineNumber) {
    FILE *fptr = fopen(fileName, mode);
    if (fptr == NULL) {
        printf("Erro ao abrir arquivo. Função que chamou: %s\nArquivo: %s\nLinha: %d\n",
        callerFunctionName, callerFileName, callerLineNumber);
        return NULL;
    }

    return fptr;
}

// definindo macro para debugar erros. Vai printar nome da função e linha onde ocorreu o erro
#define OPEN_FILE_HELPER(fileName, mode) openFileHelper(fileName, mode, __func__, __FILE__, __LINE__)

unsigned int getLastProductIDHelper() {
    FILE *fptr = OPEN_FILE_HELPER(lastProductIDFilePath, "r");
    if (fptr == NULL) {
        printf("Criando primeira id...\n");
        
        // criando o arquivo e escrevendo a primeira ID
        fptr = OPEN_FILE_HELPER(lastProductIDFilePath, "w");
        fprintf(fptr, "id: %d", 0);
        
        fclose(fptr);

        return 0;
    }

    char line[100];
    unsigned int lastID = 0;

    // pega a linha no arquivo, a cada iteração, até o fim dele
    while (fgets(line, sizeof(line), fptr)) {
        // strstr vai buscar a substring que tenha 'id:'
        if (strstr(line, "id:") != NULL) {
            // passando o número da ID depois de "id:"
            sscanf(line, "id: %u", &lastID);
            printf("Ultima id: %u\n", lastID);
            break;
        }
    }

    fclose(fptr);

    return lastID;
}

int getFileLinesCountHelper(const char path[]) {
    FILE *fptr = OPEN_FILE_HELPER(path, "r");
    if (fptr == NULL) {
        fclose(fptr);
        return 0;
    }

    char line[1000];
    unsigned count = 0;

    while(fgets(line, sizeof(line), fptr)) {
        count++;
    }

    fclose(fptr);

    return count;
}

int newProductIDHelper() {
    int lastProductID = getLastProductIDHelper();
    FILE *fptr = OPEN_FILE_HELPER(lastProductIDFilePath, "w"); // w modo de escrita
    if (fptr == NULL) {
        printf("Erro ao atualizar arquivo de ID\n");
        return -1;
    }
    int newProductID = lastProductID + 1;
    // escrevendo nova id no arquivo
    fprintf(fptr, "id: %u", newProductID);
    fclose(fptr);
    
    return newProductID;
}

Data createDateHelper(int dia, int mes, int ano) {
    Data data;
    data.dia = dia;
    data.mes = mes;
    data.ano = ano;

    return data;
}

int validateDateHelper(int dia, int mes, int ano) {
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900 || ano > 2024) {
        return 0;
    }

    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) {
        return 0;
    }

    if (mes == 2) {
        int bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
        if (dia > 29 || (dia == 29 && !bissexto)) {
            return 0;
        }
    }

    return 1;
}

Endereco createAddressHelper(char rua[100], int numero, char cidade[100], char estado[100]) {
    Endereco endereco;
    strcpy(endereco.rua, rua);
    endereco.numero = numero;
    strcpy(endereco.cidade, cidade);
    strcpy(endereco.estado, estado);

    return endereco;
}

int validateAddressHelper(Endereco endereco) {
    if (strlen(endereco.rua) == 0 || endereco.numero == 0 || strlen(endereco.cidade) == 0 || strlen(endereco.estado) == 0) {
        return 0;
    }

    return 1;
}

char *validateCPFHelper(char cpf[15]) {
    int subIndex = 0;
    char cpfTemporario[12];
    char *cpfFormatado = (char *) malloc(15 * sizeof(char));

    for (int index = 0; index < strlen(cpf); index++) {
        if (cpf[index] >= '0' && cpf[index] <= '9') {
            cpfTemporario[subIndex++] = cpf[index];
        }
    }
    cpfTemporario[subIndex] = '\0';

    if (strlen(cpfTemporario) != 11) {
        printf("CPF invalido!\n");
        free(cpfFormatado);
        return NULL;
    }

    sprintf(cpfFormatado, "%c%c%c.%c%c%c.%c%c%c-%c%c",
        cpfTemporario[0], cpfTemporario[1], cpfTemporario[2],
        cpfTemporario[3], cpfTemporario[4], cpfTemporario[5],
        cpfTemporario[6], cpfTemporario[7], cpfTemporario[8],
        cpfTemporario[9], cpfTemporario[10]
    );

    return cpfFormatado;
}

int validateProductHelper(Produto produto) {
    if (produto.ID == 0 || strlen(produto.descricao) == 0 || produto.precoUnitario == 0 || produto.quantidadeNoEstoque == 0) {
        return 0;
    }

    return 1;
}

int checkProductExistsByIDHelper(IDProduto code) {
    FILE *fptr = OPEN_FILE_HELPER(productStoreFilePath, "r");
    if (fptr == NULL) {
        fclose(fptr);
        return 0;
    }

    char line[1000];
    char id[10];
    while(fgets(line, sizeof(line), fptr)) {
        // le ID do produto até a vírgula
        sscanf(line, "ID: %[^,]", id);

        // ID existe
        if (strcmp(id, code) == 0) {
            fclose(fptr);
            return 1;
        }
    }

    fclose(fptr);
    return 0;
}

int checkCustomerExistsByCPFHelper(char cpf[15]) {
    FILE *fptr = OPEN_FILE_HELPER(customerStoreFilePath, "r");
    if (fptr == NULL) {
        fclose(fptr);
        return 0;
    }

    char line[1000];
    char cpfTemp[15];
    while(fgets(line, sizeof(line), fptr)) {
        // lendo o CPF até a vírgula
        sscanf(line, "cpf: %[^,]", cpfTemp);

        // cpf existe
        if (strcmp(cpfTemp, cpf) == 0) {
            fclose(fptr);
            return 1;
        }
    }

    fclose(fptr);

    return 0;
}

Produto getProductByIDHelper(IDProduto ID) {
    FILE *fptr = OPEN_FILE_HELPER(productStoreFilePath, "r");
    if (fptr == NULL) {
        Produto emptyProduct;
        emptyProduct.ID[0] = '\0';
        return emptyProduct;
    }

    Produto product;
    char line[1000];
    IDProduto productID;
    while (fgets(line, sizeof(line), fptr)) {
        sscanf(line, "ID: %[^,], descricao: %[^,], quantidade: %d, preco: %f",
            productID,
            product.descricao,
            &product.quantidadeNoEstoque,
            &product.precoUnitario
        );

        if (strcmp(productID, ID) == 0) {
            strcpy(product.ID, productID);
            fclose(fptr);
            return product;
        }
    }

    fclose(fptr);
    product.ID[0] = '\0';
    return product;
}

int newProductQuantity(Produto newProduct) {
    FILE *fptr = OPEN_FILE_HELPER(productStoreFilePath, "r+");
    if (fptr == NULL) {
        return 0;
    }

    char line[1000];
    char id[10];
    long pos = 0; // posição na linha para atualizar
    int found = 0;

    while (fgets(line, sizeof(line), fptr)) {
        pos = ftell(fptr); // pega a posição atual do ponteiro na linha
        // le ID do produto até a vírgula
        sscanf(line, "ID: %[^,]", id);

        // ID existe
        if (strcmp(id, newProduct.ID) == 0) {
            found = 1;
            
            // movendo de volta para a posição onde o produto foi encontrado
            fseek(fptr, pos - strlen(line), SEEK_SET);

            fprintf(fptr, "ID: %s, descricao: %s, quantidade: %d, preco: %.2f\n",
                newProduct.ID,
                newProduct.descricao,
                newProduct.quantidadeNoEstoque,
                newProduct.precoUnitario
            );

            break;
        }
    }

    fclose(fptr);
    return found ? newProduct.quantidadeNoEstoque : -1;
}

#endif // necessário para evitar redefinição de variáveis e funções. Vai manter dentro desse escopo
