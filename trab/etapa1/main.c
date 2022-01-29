/* ----------------------------------------------------------------------------------------------- *
 * INF01147 - Compiladores - 2021/2
 * Etapa 1 do Trabalho
 * 00134090 - Willian Reichert
 * ---------------------------------------------------------------------------------------------- */

/* essa função para testes não foi feita para ser executada fora do arquivo do analisador léxico
 * nesta etapa, visto que muitos dos nomes utilizados estão definidos lá.
 * > a definição do nome do arquivo para testes foi realizada no próprio código porque o nome dele
 *   não mudará. */
int main(void)
{
    FILE *infile = fopen("test.txt", "r");
    yyin = infile;

    /* inicialização da tabela de símbolos */
    initMe();

    /* laço que utiliza o analisador léxico */
    int token;
    printf("\nanálise léxica ----------------------------------------\n\n");
    while (isRunning())
    {
        /* o teste pula o caractere de fim de arquivo */
        token = yylex();
        if (isRunning() != 0)
        {
            switch (token)
            {
                case 256: printf("KW_CHAR\n");                   break;
                case 257: printf("KW_INT\n");                    break;
                case 258: printf("KW_FLOAT\n");                  break;
                case 261: printf("KW_IF\n");                     break;
                case 262: printf("KW_THEN\n");                   break;
                case 263: printf("KW_ELSE\n");                   break;
                case 264: printf("KW_WHILE\n");                  break;
                case 265: printf("KW_GOTO\n");                   break;
                case 266: printf("KW_READ\n");                   break;
                case 267: printf("KW_PRINT\n");                  break;
                case 268: printf("KW_RETURN\n");                 break;
                case 270: printf("OPERATOR_LE\n");               break;
                case 271: printf("OPERATOR_GE\n");               break;
                case 272: printf("OPERATOR_EQ\n");               break;
                case 273: printf("OPERATOR_DIF\n");              break;
                case 280: printf("TK_IDENTIFIER: %s\n", yytext); break;
                case 281: printf("LIT_INTEGER: %s\n", yytext);   break;
                case 285: printf("LIT_CHAR: %s\n", yytext);      break;
                case 286: printf("LIT_STRING: %s\n", yytext);    break;
                case 290: printf("TOKEN_ERROR: %s\n", yytext);   break;
                default:  printf("SPECIAL_CHAR: %s\n", yytext);
            }
        }
    }
    fclose(infile);
    printf("\nline_count: %d\n", getLineNumber());

    /* impressão da tabela de símbolos */
    print_table();
    return 0;
}
