/* Objetivos de aprendizagem:
• Aplicar tabelas hash em uma aplicação real.
• Manipular dados textuais usando hashing.
Descrição da atividade: Crie um programa que funcione como um dicionário: o usuário pode
adicionar palavras e seus significados, buscar e remover termos. Utilize uma tabela hash 
para organizar os dados.
--------------------------------------------------------------------------------------*/

// BIBLIOTECAS E MÓDULOS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// DECLARAÇÃO DE CONSTANTES
#define suces "\n>> Operação realizada com sucesso.\n\n"
#define falha "\n>> Algo deu erro, tente novamente.\n\n"
#define max 50

// DECLARAÇÃO DE ESTRUTURAS
typedef struct{
    char palavra[max];
    char signif[max*2];
} dicio;

// PROTÓTIPOS DE FUNÇÕES
void Remover();
void Cadastrar(dicio *p);
void Exibir();
   
// ================================== FUNÇÃO PRINCIPAL ================================== //
int main(){
    setlocale(LC_ALL, "");
    dicio *d = malloc(sizeof(dicio));
    int opc = 0;
    printf("\n========== DICIONÁRIO DIGITAL ==========\n\n");
    while(1){
        printf("[1] Cadastrar\n[2] Remover \n[3] Exibir \n[4] Sair \n>> ");
        while(scanf("%d", &opc) != 1) {printf("%s", falha);    setbuf(stdin, NULL);}
        setbuf(stdin, NULL);
        switch (opc){
            case 1:             Cadastrar(d);   break;
            case 2:                Remover();   break;
            case 3:                 Exibir();   break;
            case 4:      free(d);   return 0;   break;
            default:     printf("%s", falha);   break;
        }
    }
}

// ================================= FUNÇÕES AUXILIARES ================================= //
void Cadastrar(dicio *p){
    FILE *arquivo = fopen("Texto.txt", "a");
    if(arquivo == NULL){ printf("%s", falha); exit(1); }

    printf("Digite uma palavra. \n>> ");
    fgets(p->palavra, max, stdin);
    p->palavra[strcspn(p->palavra, "\n")] = 0;
    
    printf("Digite o significado. \n>> ");
    fgets(p->signif, max, stdin);
    p->signif[strcspn(p->signif, "\n")] = 0;
    
    fprintf(arquivo, "\n%s: ", p->palavra);
    fprintf(arquivo, "%s", p->signif);

    printf("%s", suces);
    fclose(arquivo);
}

void Remover() { printf("\nEscolheu remover.\n\n"); }

void Exibir(){
    FILE *arquivo = fopen("Texto.txt", "r");
    if(arquivo == NULL) { printf("%s", falha); exit(1); }
    char c = fgetc(arquivo);
    while(c != EOF) { printf("%c", c); c = fgetc(arquivo); }
    fclose(arquivo);
    printf("\n----------\n\n");
}
