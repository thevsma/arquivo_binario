#include <stdio.h>
#include <stdlib.h>

typedef struct aluno {
    int matricula;
    char nome[51];
    float media;
}Aluno;

Aluno digitarAluno() {
    Aluno a;
    printf("Digite a matricula: ");
    scanf("%d", &a.matricula);
    printf("Digite o nome: ");
    scanf(" %[^\n]", a.nome);
    printf("Digite a media do aluno: ");
    scanf("%f", &a.media);
    return a;
}

void imprimirAlunos(FILE* fp) {
    Aluno aux;
    fseek(fp, 0, SEEK_SET);
    printf("Matricula          Nome                      Media\n");
    while (fread(&aux, sizeof(Aluno), 1, fp)) {
        printf("%-18d %-25s %-5.2f\n", aux.matricula, aux.nome, aux.media);
    }
}

void inserirAluno(Aluno a, FILE* fp){
    fseek(fp, 0, SEEK_END);
    fwrite(&a, sizeof(Aluno), 1, fp);
    printf("Aluno adicionado!\n");
}

int main() {
    FILE* fp;

    if ((fp = fopen("../alunos.dat", "rb+")) == NULL) {
        if ((fp = fopen("../alunos.dat", "wb+")) == NULL) {
            printf("Erro ao abrir alunos.dat\n");
            exit(1);
        }
    }

    int opcao = 0;
    scanf("%d", &opcao);

    while (opcao != 4) {
        switch (opcao) {
            case 1:
                inserirAluno(digitarAluno(), fp);
                break;
            case 2:
                imprimirAlunos(fp);
                break;
            case 4:
                break;
            default:
                printf("Opcao invalida\n");
        }
        scanf("%d", &opcao);
    }

    return 0;
}