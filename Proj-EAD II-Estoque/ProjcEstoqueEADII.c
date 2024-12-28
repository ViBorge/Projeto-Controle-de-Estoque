#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//strucs Lista: Fornecedor
typedef struct fornecedordado
{
    char nome[100];
    int cep;
    char categoria[100];

} FornecedorDado;
typedef struct nof
{
    FornecedorDado dado;
    struct nof *ant;
    struct nof *prox;

} NoF;
typedef struct listacde
{
    NoF *inicio;
    NoF *fim;
    int tam;

} ListaCDE;

//Funcoes para a manipulaçoes de Fornecedores
void criarLista(ListaCDE *l);
int inserirFornecedor(ListaCDE *l, FornecedorDado dado);
int removerFornecedor(ListaCDE *l, char nome[100]);
FornecedorDado colocaForn();

//Funcoes para visualizacao de Fornecedores
int estaVaziaFornecedor(ListaCDE l);
void mostraFornecedor(ListaCDE l);




//strucs Fila: Produtos
typedef struct produtosdado
{
    int id;
    char nome[50];
    char fornecedor[100];

} ProdutosDado;
typedef struct nop
{
    ProdutosDado dado;
    struct nop *prox;

} NoP;
typedef struct fila
{
    NoP *inicio;
    NoP *fim;
    int tamFila;

} Fila;

//Funcoes para a manipulaçoes de Produtos
void criaFila(Fila *q);
int insereProduto(Fila *q, ProdutosDado dado);
int retiraProduto(Fila *q, int *id);
ProdutosDado colocaProduto();

//Funcoes para visualizacao de Produtos
int estaVaziaProduto(Fila q);
void mostraProduto(Fila q);


//Funcoes para salvar
int ChamarLista(ListaCDE *l, FornecedorDado *dado);
int leLista(FILE *f, FornecedorDado *dado);
int salvarListaCDE(ListaCDE *l);
int salvarFila(Fila *q);
int leFila(FILE *p, ProdutosDado *dado);


int main()
{
    FornecedorDado forn;
    ProdutosDado prod;

    Fila q;
    ListaCDE l;

    int tecla, sucesso, id;
    char nome[100];

    criaFila(&q);
    criarLista(&l);

    FILE *p = fopen("FilaProduto.txt", "rb");
    if(p == NULL)
    {
        printf("Erro ao abrir o arquivo Fila");
        return 0;
    }
    while(leFila(p, &prod) > 0)
    {
        insereProduto(&q, prod);
    }
    fclose(p);

    FILE *f = fopen("ListaFornecedor.txt", "rb");
    if(f == NULL)
    {
        printf("Erro ao abrir o arquivo lista");
        return 0;
    }
    while(leLista(f, &forn) > 0)
    {
        inserirFornecedor(&l, forn);
    }
    fclose(f);

    do
    {
        printf("\n====== Controle De Estoque ======\t\n\n");

        printf("=================================\n");
        printf("| (1)\tCadastrar Produto\t|\n");
        printf("| (2)\tRetirar Produto\t\t|\n");
        printf("| (3)\tEstoque Dos Produtos\t|\n");

        printf("| (4)\tCadastrar Fornecedor\t|\n");
        printf("| (5)\tRetirar Fornecedor\t|\n");
        printf("| (6)\tLista de Fornecedor\t|\n");

        printf("| (7)\tSalvar e Sair \t\t|\n");
        printf("=================================\n");


        scanf("%d", &tecla);
        fflush(stdin);

        switch(tecla)
        {
        case 1:
            printf("\nCadastrando Produto...\n");
            prod = colocaProduto();
            sucesso = insereProduto(&q, prod);
            system("cls");
            if(!sucesso)
            {
                printf("Falha ao inserir o novo Produto!!\n\n");
                break;
            }
            printf("Produto %s, Inserido com sucesso!\n\n", prod.nome);


            break;
        case 2:
            printf("\nRomevendo um Produto...");
            printf("Quantos Produtos deseja remover? \n");
            scanf("%d", &id);

            printf("Removendo %d primeiros Produtos da Fila\n", id);
            for (int i = 0; i < id; i++)
            {
                if (retiraProduto(&q, &prod))
                {
                    printf("Produto retirado: Id: %d \tNome: %s\n", prod.id, prod.nome);
                }
                else
                {
                    printf("Nenhum produto para remover.\n");
                    break;
                }
            }


            break;
        case 3:
            system("cls");
            printf("\nFila de Produtos...\n");
            printf("| Id                        Nome                                               Fornecedor       |\n");
            printf("|===============================================================================================|\n");
            mostraProduto(q);
            printf("|===============================================================================================|\n");
            printf("\n\n");

            break;



        case 4:
            printf("\nCadastrando Fornecedor...\n\n");
            forn = colocaForn();
            sucesso = inserirFornecedor(&l, forn);
            system("cls");
            if(!sucesso)
            {
                printf("Falha ao inserir o novo Fornecedor!!\n\n");
                break;
            }
            printf("Fornecedor %s, Inserido com sucesso!\n\n", forn.nome);
            break;


        case 5:
            printf("\nRomevendo um Fornecedor...");
            printf("\nDigite o nome do Fornecedor que deseja remover: \n");
            fgets(nome, 100, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            sucesso = removerFornecedor(&l, nome);
            if(!sucesso)
            {
                break;
            }

            printf("Fornecedor removido com sucesso!\n\n");
            break;


        case 6:
            printf("\nLista de Fornecedor...\n");
            printf("Exibindo todos os Fornecedores salvos:\n\n");

            if(estaVaziaFornecedor(l))
            {
                printf("Lista Vazia!\n\n");
                break;
            }
            system("cls");
            printf("\n\n");
            printf("| Nome \t\t\t\t\t Categoria \t\t\t CEP \t    |\n");
            printf("|===================================================================================|\n");

            mostraFornecedor(l);
            printf("|===================================================================================|\n");
            printf("\n\n");
            break;
        case 7:
            printf("Salvando...\n");
            if (!salvarListaCDE(&l))
            {
                printf("Erro ao salva Lista.\n");
            }
            if (!salvarFila(&q))
            {
                printf("Erro ao salva Fila.\n");
            }

            printf("Dados salvos com sucesso!\n\n");
            break;

        default:
            printf("Opcao invalida! Tente novamente.\n");
        }
    }
    while(tecla != 7);

    return 0;
}

//Funcoes para a manipulaçoes de Fornecedores
void criarLista(ListaCDE *l)
{
    l->inicio = NULL;
    l->fim = NULL;
    l->tam = 0;
}

int inserirFornecedor(ListaCDE *l, FornecedorDado dado)
{
    NoF *aux = (NoF *) malloc(sizeof(NoF));
    if(aux == NULL)
        return 0;


    aux->dado = dado;
    l->tam++;

    //caso 1
    if(l->inicio == NULL)
    {
        aux->ant = aux;
        aux->prox = aux;
        l->inicio = aux;
        l->fim = aux;
        return 1;
    }

    //caso 2
    if(strcmp(dado.nome, l->inicio->dado.nome) < 0)
    {
        aux->ant = l->fim;
        aux->prox = l->inicio;
        l->inicio->ant = aux;
        l->fim->prox = aux;
        l->inicio = aux;
        return 1;
    }

    //caso 3
    if(strcmp(dado.nome, l->fim->dado.nome) >= 0)
    {
        aux->ant = l->fim;
        aux->prox = l->inicio;
        l->fim->prox = aux;
        l->inicio->ant = aux;
        l->fim = aux;
        return 1;
    }


    NoF *anterior = l->inicio;
    NoF *atual = anterior->prox;

    while(atual != l->inicio && strcmp(dado.nome, atual->dado.nome) > 0)
    {
        anterior = atual;
        atual = atual->prox;
    }
    aux->prox = atual;
    aux->ant = anterior;
    anterior->prox = aux;
    atual->ant = aux;

    return 1;
}

int removerFornecedor(ListaCDE *l, char nome[100])
{
    if(l->inicio == NULL)
    {
        printf("Lista vazia\n");
        return 0;
    }

    NoF *aux = l->inicio;

    //1o caso
    if(l->inicio == l->fim && strcmp(l->inicio->dado.nome, nome) == 0)
    {
        aux = l->inicio;
        l->inicio = NULL;
        l->fim = NULL;
        free(aux);
        l->tam--;
        return 1;
    }

    //2o caso
    if(strcmp(nome, l->inicio->dado.nome) == 0)
    {
        aux = l->inicio;
        l->inicio = aux->prox;
        l->inicio->ant = l->fim;
        l->fim->prox = l->inicio;
        free(aux);
        l->tam--;
        return 1;
    }

    //3o caso
    if(strcmp(nome, l->fim->dado.nome) == 0)
    {
        aux = l->fim;
        l->fim = aux->ant;
        l->fim->prox = l->inicio;
        l->inicio->ant = l->fim;
        free(aux);
        l->tam--;
        return 1;
    }

    //4o caso
    aux = l->inicio->prox;

    while(aux != l->fim && strcmp(nome, aux->dado.nome) != 0)
        aux = aux->prox;

    if(aux == l->fim)
    {
        printf("O Fornecedor %s nao esta na lista\n", nome);
        return 0;
    }

    aux->prox->ant = aux->ant;
    aux->ant->prox = aux->prox;
    free(aux);
    l->tam--;
    return 1;
}

int estaVaziaFornecedor(ListaCDE l)
{

    return l.inicio == NULL;
}

void mostraFornecedor(ListaCDE l)
{

    if(l.inicio == NULL)
    {
        printf("Lista vazia!\n");
        return;
    }

    NoF *aux = l.inicio;
    do
    {
        printf("| %-30s \t %-25s \t %-10d |\n", aux->dado.nome, aux->dado.categoria,aux->dado.cep);
        aux = aux->prox;
    }
    while(aux != l.inicio);

}

FornecedorDado colocaForn()
{
    FornecedorDado novoFornecedor;

    printf("Digite o Nome do Fornecedor: ");
    fgets(novoFornecedor.nome, 100, stdin);
    novoFornecedor.nome[strcspn(novoFornecedor.nome, "\n")] = '\0';

    printf("Digite sua Categoria: ");
    fgets(novoFornecedor.categoria, 100, stdin);
    novoFornecedor.categoria[strcspn(novoFornecedor.categoria, "\n")] = '\0';

    printf("Digite o CEP: ");
    scanf("%d", &novoFornecedor.cep);


    return novoFornecedor;
}

int leLista(FILE *f, FornecedorDado *dado)
{
    return fread(dado, sizeof(FornecedorDado), 1, f);
}

int salvarListaCDE(ListaCDE *l)
{
    if (l->inicio == NULL) {
        printf("Lista está vazia, nada para salvar.\n");
        return 0;
    }

    FILE *f = fopen("ListaFornecedor.txt", "wb");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo para escrita Lista.\n");
        return 0;
    }

    NoF *aux = l->inicio;
    do {
        if (fwrite(&aux->dado, sizeof(FornecedorDado), 1, f) != 1) {
            printf("Erro ao escrever no arquivo Lista.\n");
            fclose(f);
            return 0;
        }
        aux = aux->prox;
    } while (aux != l->inicio);

    fclose(f);
    return 1;
}

//Funcoes de FILA
void criaFila(Fila *q)
{

    q->inicio = NULL;
    q->fim = NULL;
    q->tamFila = 0;
}

int insereProduto(Fila *q, ProdutosDado dado)
{

    NoP *aux;
    aux = (NoP *) malloc(sizeof(NoP));
    if(aux == NULL)
        return 0;

    aux->dado = dado;
    aux->prox = NULL;

    q->tamFila++;

    if(q->inicio == NULL)
    {
        q->inicio = aux;
        q->fim = aux;
        return 1;
    }

    q->fim->prox = aux;
    q->fim = aux;
    return 1;
}

int retiraProduto(Fila *q, int *id)
{

    NoP *aux;
    aux = q->inicio;
    if(aux == NULL)
        return 0;

    *id = aux->dado.id;
    q->tamFila--;
    q->inicio = aux->prox;


    if(q->inicio == NULL)
        q->fim = NULL;
    free(aux);

    return 1;
}
int estaVaziaProduto(Fila q)
{
    if(q.inicio == NULL)
        return 1;

    return 0;
}
void mostraProduto(Fila q)
{
    NoP *aux;
    aux = q.inicio;
    if (aux == NULL)
    {
        printf("Fila vazia!\n");
        return;
    }

    while(aux != NULL)
    {
        printf("| %-25d %-30s %-30s\t|\n", aux->dado.id, aux->dado.nome, aux->dado.fornecedor);
        aux = aux->prox;
    }
}


ProdutosDado colocaProduto()
{
    ProdutosDado produtoNovo;

    printf("Digite Id: ");
    scanf("%d", &produtoNovo.id);
    getchar();

    printf("Digite Nome: ");
    fgets(produtoNovo.nome, 100, stdin);
    produtoNovo.nome[strcspn(produtoNovo.nome, "\n")] = '\0';

    printf("Digite Fornecedor: ");
    fgets(produtoNovo.fornecedor, 100, stdin);
    produtoNovo.fornecedor[strcspn(produtoNovo.fornecedor, "\n")] = '\0';

    return produtoNovo;
}
int salvarFila(Fila *q)
{
    if (q->inicio == NULL)
    {
        printf("Fila está vazia, nada para salvar.\n");
        return 0;
    }

    FILE *p = fopen("FilaProduto.txt", "wb");
    if (p == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita de Fila.\n");
        return 0;
    }

    NoP *aux = q->inicio;

    while (aux != NULL)
    {
        if (fwrite(&aux->dado, sizeof(ProdutosDado), 1, p) != 1)
        {
            printf("Erro ao escrever no arquivo na Fila.\n");
            fclose(p);
            return 0;
        }
        aux = aux->prox;
    }

    fclose(p);
    return 1;
}
int leFila(FILE *p, ProdutosDado *dado)
{
    return fread(dado, sizeof(ProdutosDado), 1, p);
}
