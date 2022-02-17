/* ----------------------------------------------------------------------------------------------- *
 * INF01147 - Compiladores - 2021/2
 * Etapa 2 do Trabalho
 * 134090 - Willian Reichert
 * ---------------------------------------------------------------------------------------------- */

/* definições topo ---------------------------------------------------------------------------------
 * > protótipo da função necessário para suprimir avisos durante a compilação deste arquivo. */

%{
    void yyerror(char const *s);
%}

/* tokens ------------------------------------------------------------------------------------------
 * > o token de erro não é diretamente utilizado aqui. */

%token KW_CHAR
%token KW_INT
%token KW_FLOAT
%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_GOTO
%token KW_READ
%token KW_PRINT
%token KW_RETURN
%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_DIF
%token TK_IDENTIFIER
%token LIT_INTEGER
%token LIT_CHAR
%token LIT_STRING
%token TOKEN_ERROR

/* associatividade e precedência de operadores -----------------------------------------------------
 * > operadores lógicos possuem a menor precedência.
 * > operadores de multiplicação e divisão possuem a maior precedência.
 * > todos os operadores de mesmo nível são associados à esquerda. */

%left '<' '>' OPERATOR_DIF OPERATOR_EQ OPERATOR_GE OPERATOR_LE
%left '+' '-'
%left '*' '/'

%%

/* programa ----------------------------------------------------------------------------------------
 * > é uma lista de declarações de variáveis e funções. */

program: declist;

/* declarações globais -----------------------------------------------------------------------------
 * > incluem declarações de variáveis e funções.
 * > um arquivo vazio é considerado como um arquivo sintaticamente correto. */

declist: dec declist
    | /* vazio */;

dec: nfloatdecdatatype TK_IDENTIFIER nfloatdectype
    | KW_FLOAT TK_IDENTIFIER floatdectype;

nfloatdecdatatype: KW_CHAR
    | KW_INT;

nfloatdectype: vardec
    | arraydec
    | funcdec;

floatdectype: ':' LIT_INTEGER '/' LIT_INTEGER ';'
    | arraydec
    | funcdec;

/* declarações de variáveis e vetores --------------------------------------------------------------
 * > a inicialização das variáveis é obrigatória.
 * > a inicialização dos vetores é opcional. */

vardec: ':' varlit ';'

varlit: LIT_INTEGER
    | LIT_CHAR;

arraydec: '[' LIT_INTEGER ']' arrayinit ';'

arrayinit: ':' arraylit arrayinittail
    | /* vazio */;

arrayinittail: arraylit arrayinittail
    | /* vazio */;

arraylit: LIT_INTEGER
    | LIT_CHAR;

/* definições de funções ---------------------------------------------------------------------------
 * > a lista de parâmetros pode ser vazia.
 * > parâmetros não podem ser vetores.
 * > parâmetros não são inicializados (sim, são parâmetros posicionais). */

funcdec: '(' paramlist ')' cmd;

paramlist: paramdec paramlisttail
    | /* vazio */;

paramlisttail: ',' paramdec paramlisttail
    | /* vazio */;

paramdec: paramdatatype TK_IDENTIFIER;

paramdatatype: KW_CHAR
    | KW_FLOAT
    | KW_INT;

/* blocos de comandos -------------------------------------------------------------------------------
 * > comandos devem ser terminados por ponto e vírgula.
 * > rótulos (comandos especiais) devem ser terminados por dois pontos.
 * > a lista de comandos pode ser vazia e pode possuir comandos vazios que são terminados por
 *   ponto e vírgula, de acordo com a regra de separação de comandos da lista. */

cmdblock: '{' cmdlist '}';

cmdlist: cmdlistitem cmdlisttail
    | /* vazio */;

cmdlisttail: cmdlistitem cmdlisttail
    | /* vazio */;

cmdlistitem: cmd ';'
    | fluxlabel;

/* comandos ----------------------------------------------------------------------------------------
 * > o comando vazio é aceito e segue as mesmas regras dos demais. */

cmd: attrib
    | flux
    | print
    | return
    | cmdblock
    | /* vazio */;

return: KW_RETURN expr;

/* comandos de atribuição --------------------------------------------------------------------------
 * > o opcional de atribução de vetor permite definir as atribuições em uma única produção. */

attrib: TK_IDENTIFIER arrayattribopt '=' expr;

arrayattribopt: '[' expr ']'
    | /* vazio */;

/* comandos de impressão ---------------------------------------------------------------------------
 * > a lista de elementos a serem impressos deve ter pelo menos um item.
 * > apenas literais string e expressões são aceitos dentro de comandos de impressão. */

print: KW_PRINT printlistitem printlisttail;

printlisttail: ',' printlistitem printlisttail
    | /* vazio */;

printlistitem: LIT_STRING
    | expr;

/* comandos de controle de fluxo -------------------------------------------------------------------
 * > o opcional de fluxo alternativo permite definir os fluxos em uma única produção. */

flux: KW_IF expr KW_THEN cmd fluxelseopt
    | KW_WHILE expr cmd
    | KW_GOTO TK_IDENTIFIER;

fluxelseopt: KW_ELSE cmd
    | /* vazio */;

fluxlabel: TK_IDENTIFIER ':';

/* expressões --------------------------------------------------------------------------------------
 * > identificadores podem ser seguidos por uma expressão entre colchetes para acesso a vetores.
 * > a lista de argumentos de chamadas de funções não pode ser vazia.
 * > a palavra reservada 'read' retorna um valor lido. */

expr: TK_IDENTIFIER exprarrayopt
    | LIT_INTEGER
    | LIT_CHAR
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '<' expr
    | expr '>' expr
    | expr OPERATOR_LE expr
    | expr OPERATOR_GE expr
    | expr OPERATOR_EQ expr
    | expr OPERATOR_DIF expr
    | '(' expr ')'
    | exprfunc
    | KW_READ;

exprarrayopt: '[' expr ']'
    | /* vazio */;

exprfunc: TK_IDENTIFIER '(' exprfuncarglist ')';

exprfuncarglist: expr exprfuncargtail;

exprfuncargtail: ',' expr exprfuncargtail
    | /* vazio */;

%%

/* indicação de erro de sintaxe. */
void yyerror(char const *str)
{
    fprintf(stderr, "%s at line %d\n", str, getLineNumber());
    exit(3);
}
