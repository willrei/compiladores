#include <stdio.h>
#include <stdlib.h>

#define PARAMC 5

int main()
{
    // Aquecimento
    // imprimir 10 linhas, de 1 a 10, cada uma com os numeros de um ao numero da linha
    printf("\naquecimento\n------------------------------\n\n");
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            printf("%d ", j);
        }
        putchar('\n');
    }

    // TASK 0 
    // Imprimir uma funcao em C com n parametros int
    printf("\ntask 0\n------------------------------\n\n");
    printf("int function(");
    if (PARAMC == 0)
    {
        printf(");\n");
    }
    else if (PARAMC == 1)
    {
        printf("int param0);\n");
    }
    else
    {
        for (int i = 0; i < (PARAMC - 1); i++)
        {
            printf("int param%d, ", i);
        }
        printf("int param%d);\n", PARAMC - 1);
    }

    // TASK 1 
    // contar quantos numeros existem 
    // arquivo in1.txt
    // resposta: 33
    printf("\ntask 1\n------------------------------\n\n");
    int is_prevc_num = 0;
    int numc = 0;
    char c;
    FILE *infile = fopen("in1.txt", "r");

    c = fgetc(infile);
    while (c != EOF)
    {
        if (c >= '0' && c <= '9')
        {
            is_prevc_num = 1;
        }
        else if (is_prevc_num == 1)
        {
            numc++;
            is_prevc_num = 0;
        }
        c = fgetc(infile);
    }

    fclose(infile);
    printf("numc: %d\n", numc);

    // TASK 2 
    // imprimir quantos numeros existem em cada linha logica terminada por ;
    // arquivo in2.txt
    // resposta: 1 1 1 3 12 3 5 2 1 2 1 4 2 2 2 3 3 1
    printf("\ntask 2\n------------------------------\n\n");
    is_prevc_num = 0;
    numc = 0;
    infile = fopen("in2.txt", "r");

    printf("numc: ");
    c = fgetc(infile);
    while (c != EOF)
    {
        if (c >= '0' && c <= '9')
        {
            is_prevc_num = 1;
        }
        else if (is_prevc_num == 1)
        {
            numc++;
            is_prevc_num = 0;
        }
        if (c == ';')
        {
            printf("%d ", numc);
            numc = 0;
        }
        c = fgetc(infile);
    }

    fclose(infile);
    putchar('\n');

    // TASK 3 
    // Fazer a tarefa 2 contando o numero de linhas fisicas no mesmo arquivo in2.txt
    printf("\ntask 3\n------------------------------\n\n");
    int numl = 1;
    is_prevc_num = 0;
    numc = 0;
    infile = fopen("in2.txt", "r");

    printf("numc: ");
    c = fgetc(infile);
    while (c != EOF)
    {
        if (c == '\n')
        {
            numl++;
        }
        if (c >= '0' && c <= '9')
        {
            is_prevc_num = 1;
        }
        else if (is_prevc_num == 1)
        {
            numc++;
            is_prevc_num = 0;
        }
        if (c == ';')
        {
            printf("%d ", numc);
            numc = 0;
        }
        c = fgetc(infile);
    }

    fclose(infile);
    printf("\nnuml: %d\n", numl);

    // TASK 4 
    // Ler o arquivo in4.txt e fazer a soma dos numeros em cada nivel de parenteses (contando ou nao os que estao dentro de
    // outro nivel), imprimindo o numero da linha onde inicia cada grupo entre parenteses.
    printf("\ntask 4\n------------------------------\n\n");
    numl = 1;
    is_prevc_num = 0;
    int sum[5] = {0, 0, 0, 0, 0};
    char num[10];
    int sump = 0;
    int nump = 0;
    infile = fopen("in4.txt", "r");
    c = fgetc(infile);
    while (c != EOF)
    {
        if (c >= '0' && c <= '9')
        {
            is_prevc_num = 1;
            num[nump] = c;
            nump++;
        }
        else if (is_prevc_num == 1)
        {
            is_prevc_num = 0;
            num[nump] = '\0';
            nump = 0;
            sum[sump] += atoi(num);
        }

        if (c == '(')
        {
            sump++;
            printf("grupo de nivel %d iniciou na linha %d\n", sump, numl);
        }
        else if (c == ')')
        {
            sump--;
        }

        if (c == '\n')
        {
            numl++;
        }
        c = fgetc(infile);
    }
    fclose(infile);
    for (int i = 0; i < 5; i++)
    {
        printf("sum nivel %d: %d\n", i, sum[i]);
    }
}
