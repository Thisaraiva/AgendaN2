#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdbool.h>

typedef struct contato{
    char nome[50];
    char telefone[15];
    struct contato *ant;
    struct contato *prox;
}Contato;

typedef struct lista{
    Contato *inicio;
    Contato *final;
    int tam;
}Lista;

Contato *criar_contato();
Lista *criar_lista();
void List_destroy(Lista **L_ref);
bool Lista_is_empty(const Lista *L);
void Lista_add_first(Lista *L, Contato *c);
void Lista_add_last(Lista *L, Contato *c);
void Lista_print(const Lista *L);
void Lista_imprimir_ordem(Lista *L);
void Lista_imprimir_inverso(Lista *L);
Contato *Lista_buscar_um_contato(Lista *L, char nome[50]);
Contato *Lista_atualiza_contato(Lista *L, char nome[50], char telefone[15]);
void *Lista_remove(Lista *L, char nome[50]);


int main(void) {
    char op;
    char nome[50];
    char telefone[15];
    Lista *L = criar_lista();
    Contato *c;

    do {
        system("cls");
        printf("=================MENU=================\n\n");
        printf("Escolha uma das opcoes abaixo:\n\n");
        printf("1 - Inserir um novo contato no inicio\n");
        printf("2 - Inserir um novo contato no final\n");
        printf("3 - Mostrar todos os contatos\n");
        printf("4 - Imprimir contato em ordem\n");
        printf("5 - Imprimir contato em ordem inversa\n");
        printf("6 - Buscar um contato por nome\n");
        printf("7 - Atualizar um contato por nome\n");
        printf("8 - Remover um contato\n");
        printf("9 - Sair\n");
        printf("\nOpcao: ");
        scanf("%c", &op);
        fflush(stdin);
        switch (op) {
            case '1':
                    system("cls");
                    c = criar_contato();
                    Lista_add_first(L, c);
                break;
            case '2':
                    system("cls");
                    c = criar_contato();
                    Lista_add_last(L, c);
                break;
            case '3':
                    system("cls");
                    if(!Lista_is_empty(L)){
                        printf("\nTodos os contatos: \n\n");
                        Lista_print(L);
                    }else{
                        printf("\nNão existem contatos cadastrados.\n");
                    }
                break;
            case '4':
                    system("cls");
                    if (!Lista_is_empty(L)) {
                        printf("\nOrdenando lista de contatos...\n");
                        printf("\nContatos na Ordem: \n\n");
                        Lista_imprimir_ordem(L);
                    } else {
                        printf("\nNao ha contatos para serem impressos.\n");
                    }
                break;
            case '5':
                    system("cls");
                    if (!Lista_is_empty(L)) {
                        printf("\nOrdenando lista de contatos...\n");
                        printf("\nContatos na Ordem inversa: \n\n");
                        Lista_imprimir_inverso(L);
                    } else {
                        printf("\nNao ha contatos para serem impressos.");
                    }
                break;
            case '6':
                    system("cls");
                    if (!Lista_is_empty(L)) {
                        printf("\nDigite o nome a buscar: ");
                        gets(nome);
                        fflush(stdin);                        
                        if (Lista_buscar_um_contato(L, nome)) {
                            printf("\nO contato %s foi encontrado.\n", nome);
                        } else {
                            printf("\nO contato %s nao foi encontrado!\n", nome);
                        }
                    } else {
                        printf("\nNao ha contatos para realizar essa operacao.\n");
                    }
                break;
            case '7':
                    system("cls");
                    if (!Lista_is_empty(L)) {
                        printf("\nDigite o nome a buscar: ");
                        gets(nome);
                        fflush(stdin);                                                                              
                        Contato *aux = Lista_buscar_um_contato(L, nome);
                        if (aux != NULL) {                                                        
                            Lista_atualiza_contato(L, nome, telefone);
                            printf("\nContato %s atualizado com sucesso!\n", nome);
                        } else {
                            printf("\nO contato %s nao foi encontrado!\n", nome);
                        } 
                    }else {
                        printf("\nNao ha contatos para realizar essa operacao.\n");
                    }
                break;
            case '8':
                    system("cls");                    
                    if (!Lista_is_empty(L)) {
                        printf("\nDigite o nome do contato a remover: ");
                        gets(nome);
                        if(Lista_remove(L, nome)){
                        printf("\n%s removido com sucesso!\n", nome);
                        } else{
                            printf("\nO contato %s nao existe!\n", nome);
                        }                    
                    } else {
                        printf("\nNao ha contatos para serem removidos.\n");
                    }
                    
                break;
            case '9':
                    system("cls");
                    List_destroy(&L);
                    L = NULL;
                    printf("\nA lista foi destruida com sucesso!\n");
            break;
            default :
                    printf("\nOpcao invalida. Tente novamente.\n");
            break;
            }
            printf("\nPressione qualquer tecla\n");
		    getch();
	    }while(op!='9');       

    return 0;
}

Contato *criar_contato(){
    Contato *c = (Contato *)malloc(sizeof(Contato));    
    c->ant = NULL;
    c->prox = NULL;
    printf("Nome do novo contato: ");
    gets(c->nome);
    fflush(stdin);
    printf("Telefone do novo contato: ");
    gets(c->telefone);
    fflush(stdin);
    
    return c;
}

Lista *criar_lista(){
    Lista *L = (Lista*)malloc(sizeof(Lista));
    L->inicio = NULL;
    L->final = NULL;
    L->tam = 0;
    return L;
}

void List_destroy(Lista **L_ref) {
    Lista *L = *L_ref;

    Contato *p = L->inicio;
    Contato *aux = NULL;

    while (p != NULL) {
        aux = p;
        p = p->prox;
        free(aux);
    }
    free(L);

    *L_ref = NULL;
}

bool Lista_is_empty(const Lista *L){
    return L->tam == 0;
}

void Lista_add_first(Lista *L, Contato *c){
    //c = criar_contato();
    c->prox = L->inicio;
    if(Lista_is_empty(L)){
        L->final = c;
    }
    else{
        L->inicio->ant=c;
    }
    L->inicio = c;
    L->tam++;
    printf("\nContato criado com sucesso!\n");
}

void Lista_add_last(Lista *L, Contato *c){
    //c = criar_contato();
    c->ant = L->final;
    if(Lista_is_empty(L)){
        L->inicio = c;
    }
    else{
        L->final->prox = c;
    }
    L->final = c;
    L->tam++;
}

Contato *Lista_atualiza_contato(Lista *L, char nome[50], char telefone[15]){
    Contato *p = L->inicio;

    while(strcmp(p->nome, nome) != 0){        
        p = p->prox;
    }
    //printf("\nNOME\tTELEFONE\n\n");
    //printf("%s\t%s\n\n", p->nome, p->telefone);
    printf("\nEntre com os novos dados: \n");
    printf("\nDigite o novo nome: ");
    gets(nome);
    fflush(stdin);
    printf("Digite o novo telefone: ");
    gets(telefone);
    fflush(stdin);   
    strcpy(p->nome, nome);
    strcpy(p->telefone, telefone);

    return p;
}

void Lista_print(const Lista *L){
    Contato *p = L->inicio;
    printf("NOME\tTELEFONE\n\n");
    while(p != NULL){
        printf("%s\t", p->nome);
        printf("%s\n", p->telefone);
        p = p->prox;
    }
}

void Lista_imprimir_ordem(Lista *L) {
    if (Lista_is_empty(L)) {
        printf("A lista esta vazia.\n");
        return;
    }

    // Primeiro, vamos criar um vetor de ponteiros para os contatos
    Contato *contatos[L->tam];
    Contato *atual = L->inicio;
    int i = 0;

    // Preencher o vetor com os contatos
    while (atual != NULL) {
        contatos[i] = atual;
        atual = atual->prox;
        i++;
    }

    // Ordenar o vetor de contatos por nome usando um algoritmo de ordenação
    for (int j = 0; j < L->tam - 1; j++) {
        for (int k = j + 1; k < L->tam; k++) {
            if (strcmp(contatos[j]->nome, contatos[k]->nome) > 0) {
                // Troca os ponteiros para contatos no vetor
                Contato *temp = contatos[j];
                contatos[j] = contatos[k];
                contatos[k] = temp;
            }
        }
    }

    // Imprimir os contatos em ordem alfabética
    printf("NOME\tTELEFONE\n");
    for (int j = 0; j < L->tam; j++) {
        printf("%s\t%s\n", contatos[j]->nome, contatos[j]->telefone);
    }
}

void Lista_imprimir_inverso(Lista *L) {
    if (Lista_is_empty(L)) {
        printf("A lista esta vazia.\n");
        return;
    }

    // Primeiro, vamos criar um vetor de ponteiros para os contatos
    Contato *contatos[L->tam];
    Contato *final = L->final;
    int i = 0;

    // Preencher o vetor com os contatos
    while (final != NULL) {
        contatos[i] = final;
        final = final->ant;
        i++;
    }

    // Ordenar o vetor de contatos por nome usando um algoritmo de ordenação
    for (int j = 0; j < L->tam - 1; j++) {
        for (int k = j + 1; k < L->tam; k++) {
            if (strcmp(contatos[j]->nome, contatos[k]->nome) > 0) {
                // Troca os ponteiros para contatos no vetor
                Contato *temp = contatos[j];
                contatos[j] = contatos[k];
                contatos[k] = temp;
            }
        }
    }

    // Imprimir os contatos em ordem inversa
    printf("NOME\tTELEFONE\n");
    for (int j = L->tam - 1; j >= 0; j--) {
        printf("%s\t%s\n", contatos[j]->nome, contatos[j]->telefone);
    }
}

Contato *Lista_buscar_um_contato(Lista *L, char nome[50]) {
    Contato *aux = L->inicio;
    while (aux != NULL) {        
        if (strcmp(aux->nome, nome) == 0) {
            printf("\nNOME\tTELEFONE\n");
            printf("%s\t%s\n", aux->nome, aux->telefone);
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

void *Lista_remove(Lista *L, char nome[50]) {
    Contato *p = L->inicio;

    while (p != NULL) {
        if (strcmp(p->nome, nome) == 0) {
            if (p->ant != NULL) {
                p->ant->prox = p->prox;
            } else {
                L->inicio = p->prox;
            }

            if (p->prox != NULL) {
                p->prox->ant = p->ant;
            } else {
                L->final = p->ant;
            }

            free(p);
            L->tam--;
            return p;            
        }
        p = p->prox;
    }  
    return NULL;  
}