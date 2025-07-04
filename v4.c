/* Aplicar tabelas hash em uma aplicação real e Manipular dados textuais usando hashing.
Crie um programa que funcione como um dicionário: o usuário pode adicionar palavras e seus
significados, buscar e remover termos. Utilize uma tabela hash para organizar os dados.
--------------------------------------------------------------------------------------*/

// BIBLIOTECAS E MÓDULOS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// DECLARAÇÃO DE CONSTANTES
#define suces "\n>> Operação realizada com sucesso.\n\n"
#define falha "\n>> Algo deu errado, tente novamente.\n\n"
#define vazio "\n>> Nenhum item cadastrado no momento.\n\n"
#define max 50

// DECLARAÇÃO DE ESTRUTURAS
typedef struct dicio{
    char palavra[max];
    char signif[max*2];
    struct dicio *prox;
} dicio;

dicio *inicio = NULL;

// ========================= PROTÓTIPOS DE FUNÇÕES ========================= //
void Cadastrar();           // SALVAR TEMPORARIAMENTE NA LISTA
void Remover();             // FUNÇÃO ONDE DEVERÁ SER IMPLEMENTADO A HASH
void Exibir();              // EXIBIR CONTÉUDO DA LISTA E DO ARQUIVO
void Salvar(dicio *atual);  // SALVAR CONTÉUDO DA ESTRUTURA PARA O ARQUIVO
void Liberar();             // LIBERAR MEMÓRIA DAS ESTRUTURAS
   
// ================================== FUNÇÃO PRINCIPAL ================================== //
int main(){
    setlocale(LC_ALL, "");
    int opc = 0;
    printf("\n========== DICIONÁRIO DIGITAL ==========\n\n");
    while(1){
        printf("[1] Cadastrar\n[2] Remover \n[3] Exibir \n[4] Sair \n>> ");
        while(scanf("%d", &opc) != 1) {printf("%s", falha); setbuf(stdin, NULL);}
        setbuf(stdin, NULL);
        switch (opc){
            case 1:   Cadastrar();              break;
            case 2:     Remover();              break;
            case 3:      Exibir();              break;
            case 4:     Liberar(); return 0;    break;
            default:    printf("%s", falha);    break;
        }
    }
}

// ================================= FUNÇÕES AUXILIARES ================================= //
void Cadastrar(){
    dicio *novo = malloc(sizeof(dicio));
    if(novo == NULL) {printf("%s (novo)\n", falha); return;}

    printf("Digite uma palavra. \n>> ");
    fgets(novo->palavra, max, stdin);
    novo->palavra[strcspn(novo->palavra, "\n")] = 0;
    
    printf("Digite o significado. \n>> ");
    fgets(novo->signif, max, stdin);
    novo->signif[strcspn(novo->signif, "\n")] = 0;

    novo->prox = inicio;
    inicio = novo;
    
    printf("%s", suces);
}
// IDEIA: SE UMA PALAVRA DA LISTA ENCADEADA FOR REMOVIDA, A MESMA NO ARQUIVO SERÁ REMOVIDO AUTOMATICAMENTE
void Remover(){ // AQUI DEVERÁ SER IMPLEMENTADO O ALGORITMO HASH
    if(inicio == NULL) {printf("%s", vazio); return;}
    
    char palvr[max] = " ";
    printf("Qual palavra deseja remover? \n>> ");
    fgets(palvr, max, stdin);
    palvr[strcspn(palvr, "\n")] = 0;

    dicio *atual = inicio, *anter = NULL;

    while(atual && strcmp(atual->palavra, palvr) != 0){ 
        anter = atual;
        atual = atual->prox;            
    }
    if (atual == NULL) {printf("\n>> Não encontrado.\n\n"); return;}
    else{
        int opc = 0;
        printf("Tem certeza de que deseja remover { %s }? \n[1] Sim \n[0] Não \n>> ", atual->palavra);
        while( scanf("%d", &opc) != 1){printf("%s", falha); setbuf(stdin, NULL);}
        setbuf(stdin, NULL);
        if (opc == 0) {return;}
    }
    if (anter == NULL){
        inicio = atual->prox;
    } else{
        anter->prox = atual->prox;
    }
    printf("%s", suces);
    free(atual);
}
 
void Exibir(){ // A ESTÉTICA DE EXIBIÇÃO DOS RESULTADOS PODE SER APRIMORADA
    FILE *arquivo = fopen("Texto.txt", "r");
    if(arquivo == NULL) { printf("%s (arquivo)\n", falha); exit(1); }
    
    char c = fgetc(arquivo);
    if(c == EOF && inicio == NULL) {
        printf("%s", vazio); 
        fclose(arquivo); 
        return;
    }

    if(c != EOF){
        printf("\n>> Conteúdo do arquivo:\n\n");
        while(c != EOF){ 
            printf("%c", c); 
            c = fgetc(arquivo); 
        }
    }
    fclose(arquivo);
    
    if(inicio != NULL){
        printf("\n>> Conteúdo da lista:\n\n");
        dicio *atual = inicio;
        while(atual){
            printf("Palavra: %s\n", atual->palavra);
            printf("Significado: %s\n", atual->signif);
            printf("------------\n\n");
            atual = atual->prox;
        }
    }
    printf("%s", suces);
}

void Salvar(dicio *atual){
    FILE *arquivo = fopen("Texto.txt", "a");
    if(arquivo == NULL) { printf("%s (arquivo)\n", falha); exit(1); }
    
    fprintf(arquivo, "%s: ", atual->palavra);
    fprintf(arquivo, "%s\n", atual->signif);

    fclose(arquivo);
}

void Liberar(){
    if(inicio != NULL){
        dicio *atual = inicio, *temp = NULL;
        while (atual) {
            temp = atual;
            Salvar(atual);
            free(atual);
            atual = temp->prox;
        }
    }
    printf("\n>> Conteúdo salvo.\n\n");
    printf("%s", suces);
}

// ==================== CODIGOS DE REFERÊNCIA COM POSSÍVEIS UTILIDADES NO FUTURO ====================

/*
FILE *arquivo = fopen("Texto.txt", "a");
if(arquivo == NULL){ printf("%s", falha); exit(1); }

fprintf(arquivo, "\n%s: ", novo->palavra);
fprintf(arquivo, "%s", novo->signif);

fclose(arquivo);

FILE *arquivo = fopen("Texto.txt", "r");
if(arquivo == NULL) { printf("%s", falha); exit(1); }
char c = fgetc(arquivo);
while(c != EOF) { printf("%c", c); c = fgetc(arquivo); }
fclose(arquivo);
printf("\n----------\n\n");*/
