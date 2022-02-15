/* ----------------------------------------------------------------------------------------------- *
 * INF01147 - Compiladores - 2021/2
 * Etapa 2 do Trabalho
 * 134090 - Willian Reichert
 * ---------------------------------------------------------------------------------------------- */
#include <stdio.h>
extern FILE *yyin;

/* ponto de entrada do compilador. */
int main(int argc, char **argv)
{
    /* verificação da correta chamada do compilador. */
    if (argc != 2)
    {
        fprintf(stderr, "usage: ./etapa2 <file>\n");
        exit(1);
    }

    /* abertura do arquivo que contém o código a ser compilado. */
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        fprintf(stderr, "couldn't open file %s\n", argv[1]);
        exit(2);
    }
    yyin = infile;

    /* inicialização da tabela de símbolos. */
    initMe();

    /* execução do analisador sintático (e léxico). */
    yyparse();
    fclose(infile);

    /* impressão da tabela de símbolos. */
    print_table();

    exit(0);
}
