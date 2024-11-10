#include "./customer.c"
#include "./product.c"
#include "./sale.c"

void menu() {
    int opcao;

    for(;;) {
        printf("1 - Cadastrar cliente\n");
        printf("2 - Cadastrar produto\n");
        printf("3 - Realizar venda\n");
        printf("4 - Consultar cliente\n");
        printf("5 - Listar produtos\n");
        printf("6 - Consultar produto\n");
        printf("7 - Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Cadastrando cliente...\n");
                createCustomer();
                break;
            case 2:
                printf("Cadastrando produto...\n");
                createProduct();
                break;
            case 3:
                printf("Realizando venda...\n");
                doSale();
                break;
            case 4:
                printf("Consultando cliente...\n");
                readCustomer();
                break;
            case 5:
                printf("Listando produtos...\n");
                readProducts();
                break;
            case 6:
                printf("Consultando produto...\n");
                readProduct();
                break;
            case 7:
                printf("Saindo do programa...\n");
                return;
            default:
                printf("Opcao invalida!\n");
        }
    }
}