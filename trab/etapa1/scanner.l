/* ----------------------------------------------------------------------------------------------- *
 * INF01147 - Compiladores - 2021/2
 * Etapa 1 do Trabalho
 * 00134090 - Willian Reichert
 * ---------------------------------------------------------------------------------------------- */

/* definições topo --------------------------------------------------------------------------------
 * > headers inclusos aqui para dar visibilidade às funções e constantes ao analisador. */
%{
    #include <string.h>
    #include "tokens.h"
    #include "hash.h"

    int running = 1;
    int line_count = 1;
%}

/* contextos --------------------------------------------------------------------------------------
 * > o contexto abaixo é utilizado para permitir a contagem de novas linhas dentro de comentários
 *   de múltiplas linhas, além de facilitar o controle do fechamento dos comentários */
%x MLCOMMENT

%%

 /* palavras reservadas --------------------------------------------------------------------------------
  * > cada palavra reservada possui um token próprio que é retornado. */

"char"    { return KW_CHAR; }
"int"     { return KW_INT; }
"float"   { return KW_FLOAT; }
"if"      { return KW_IF; }
"then"    { return KW_THEN; }
"else"    { return KW_ELSE; }
"while"   { return KW_WHILE; }
"goto"    { return KW_GOTO; }
"read"    { return KW_READ; }
"print"   { return KW_PRINT; }
"return"  { return KW_RETURN; }

 /* caracteres especiais --------------------------------------------------------------------------
  * > os tokens dos caracteres especiais são seus códigos ascii.
  * > o caractere '-' precisa ir no início do grupo por ele também definir intervalos. */

[-,;:()\[\]\{\}+*/<>=]  { return (int)yytext[0]; }

 /* operadores compostos --------------------------------------------------------------------------
  * > cada operador composto possui um token próprio que é retornado. */

"<="  { return OPERATOR_LE; }
">="  { return OPERATOR_GE; }
"=="  { return OPERATOR_EQ; }
"!="  { return OPERATOR_DIF; }

 /* identificadores -------------------------------------------------------------------------------
  * > identificadores são armazenados na tabela de símbolos por serem definidos pelo usuário.
  * > "-"?[...], apesar de ser desnecessário por causa da ordem de precedência da regra dos
  *   caracteres especiais definida nesse arquivo, garante que identificadores que começam com '-'
      devam possuir um outro caractere pertecente ao grupo [-_a-z]. */

"-"?[-_a-z]+  { add_table(TK_IDENTIFIER, yytext); return TK_IDENTIFIER; }

 /* literais --------------------------------------------------------------------------------------
  * > literais também são armazenados na tabela de símbolos por serem definidos pelo usuário.
  * > ...("\\\""|...)+... garante que aspas duplas sejam consideradas em um literal string apenas
  *   quando precedidas por uma contrabarra. */

[0-9]+                    { add_table(LIT_INTEGER, yytext); return LIT_INTEGER; }
"'"."'"                   { add_table(LIT_CHAR, yytext);    return LIT_CHAR; }
"\""("\\\""|[^"\n])+"\""  { add_table(LIT_STRING, yytext);  return LIT_STRING; }

 /* comentários -----------------------------------------------------------------------------------
  * > comentários de múltiplas linhas possuem um contexto separado. */

"\\\\".*          { /* nada */ }
"\\*"             { BEGIN(MLCOMMENT); }
<MLCOMMENT>"*\\"  { BEGIN(INITIAL); }
<MLCOMMENT>"\n"   { line_count++; }
<MLCOMMENT>.      { /* nada */ }

 /* espaços em branco -----------------------------------------------------------------------------
  * > espaços em branco e tabulações não são contabilizadas e possuem uma regra específica para não
  *   gerarem erros de sintaxe, visto que são caracteres esperados nos arquivos. */

[ \t]  { /* nada */ }

 /* nova linha ------------------------------------------------------------------------------------
  * > são utilizadas para contabilizar a quantidade de linhas presente nos arquivos analisados */

"\n"  { line_count++; }

 /* caracteres inesperados ------------------------------------------------------------------------
  * > caracteres inesperados retornam um token de erro. */

.  { return TOKEN_ERROR; }

%%

/* outras definições ---------------------------------------------------------------------------- */

/* retorna a contagem de linhas */
int getLineNumber(void)
{
    return line_count;
}

/* retorna o estado da análise */
int isRunning(void)
{
    return running;
}

/* os arquivos com as definições da tabela de símbolos e da função principal para testes foram
 * incluídos aqui para facilitar a compilação e execução do projeto. além disso, o arquivo da tabela
 * foi incluso antes porque a função de testes controla a tabela. */
#include "hash.c"

void initMe(void)
{
  init_table();
}

#include "main.c"

/* função executada no fim da análise */
int yywrap()
{
    running = 0;
    return 1;
}
