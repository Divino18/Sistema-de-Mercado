#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 50
#define MAX_CARRINHO 50

typedef struct {
    int codigo;
    char nome[30];
    float preco;
} Produto;

typedef struct {
    Produto produto;
    int quantidade;
} Carrinho;

Produto produtos[MAX_PRODUTOS];
Carrinho carrinho[MAX_CARRINHO];
int totalProdutos = 0;
int totalCarrinho = 0;


void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {} 
}


void cadastrarProduto() {
    if (totalProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }

    Produto p;
    printf("Digite o codigo do produto: ");
    scanf("%d", &p.codigo);
    limparBuffer(); 

    printf("Digite o nome do produto: ");
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0'; 

    printf("Digite o preco do produto: ");
    scanf("%f", &p.preco);
    limparBuffer();  
    
    produtos[totalProdutos] = p;
    totalProdutos++;
    
    printf("Produto cadastrado com sucesso!\n");
}

void listarProdutos() {
    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Produtos ---\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("Codigo: %d, Nome: %s, Preco: %.2f\n", produtos[i].codigo, produtos[i].nome, produtos[i].preco);
    }
}


void comprarProduto() {
    int codigo, qtd;
    listarProdutos();
    printf("Digite o codigo do produto que deseja comprar: ");
    scanf("%d", &codigo);
    
    Produto *p = NULL;
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            p = &produtos[i];
            break;
        }
    }
    
    if (p == NULL) {
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("Digite a quantidade: ");
    scanf("%d", &qtd);
    limparBuffer();  
    
    int indexCarrinho = -1;
    for (int i = 0; i < totalCarrinho; i++) {
        if (carrinho[i].produto.codigo == codigo) {
            indexCarrinho = i;
            break;
        }
    }
    
    if (indexCarrinho != -1) {
        carrinho[indexCarrinho].quantidade += qtd;
        printf("Quantidade atualizada no carrinho.\n");
    } else {
        Carrinho c;
        c.produto = *p;
        c.quantidade = qtd;
        carrinho[totalCarrinho] = c;
        totalCarrinho++;
        printf("Produto adicionado ao carrinho.\n");
    }
}


void visualizarCarrinho() {
    if (totalCarrinho == 0) {
        printf("O carrinho esta vazio.\n");
        return;
    }

    printf("\n--- Carrinho de Compras ---\n");
    for (int i = 0; i < totalCarrinho; i++) {
        printf("Codigo: %d, Nome: %s, Quantidade: %d, Preco Unitario: %.2f\n", 
            carrinho[i].produto.codigo, carrinho[i].produto.nome, 
            carrinho[i].quantidade, carrinho[i].produto.preco);
    }
}


void fecharPedido() {
    if (totalCarrinho == 0) {
        printf("O carrinho esta vazio.\n");
        return;
    }

    float total = 0;
    printf("\n--- Fechamento do Pedido ---\n");
    for (int i = 0; i < totalCarrinho; i++) {
        float subtotal = carrinho[i].produto.preco * carrinho[i].quantidade;
        total += subtotal;
        printf("Produto: %s, Quantidade: %d, Subtotal: %.2f\n", 
            carrinho[i].produto.nome, carrinho[i].quantidade, subtotal);
    }
    printf("Valor total do pedido: %.2f\n", total);
    totalCarrinho = 0; 
    printf("Pedido finalizado e carrinho esvaziado.\n");
}


void removerProdutoCarrinho() {
    if (totalCarrinho == 0) {
        printf("Carrinho vazio.\n");
        return;
    }

    int codigo;
    visualizarCarrinho();
    printf("Digite o codigo do produto a remover: ");
    scanf("%d", &codigo);
    limparBuffer();  
    
    int indexCarrinho = -1;
    for (int i = 0; i < totalCarrinho; i++) {
        if (carrinho[i].produto.codigo == codigo) {
            indexCarrinho = i;
            break;
        }
    }

    if (indexCarrinho == -1) {
        printf("Produto nao encontrado no carrinho.\n");
        return;
    }
    
    for (int i = indexCarrinho; i < totalCarrinho - 1; i++) {
        carrinho[i] = carrinho[i + 1];
    }
    totalCarrinho--;
    printf("Produto removido do carrinho.\n");
}


int main() {
    int opcao;
    
    do {
        printf("\n--- Sistema de Supermercado ---\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Comprar Produto\n");
        printf("4. Visualizar Carrinho\n");
        printf("5. Fechar Pedido\n");
        printf("6. Remover Produto do Carrinho\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();  
        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                listarProdutos();
                break;
            case 3:
                comprarProduto();
                break;
            case 4:
                visualizarCarrinho();
                break;
            case 5:
                fecharPedido();
                break;
            case 6:
                removerProdutoCarrinho();
                break;
            case 7:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 7);
    
    return 0;
}

//espero que esteja tudo de acordo com o que foi solicitado professor, grato!