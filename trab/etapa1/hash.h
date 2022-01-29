/* ----------------------------------------------------------------------------------------------- *
 * INF01147 - Compiladores - 2021/2
 * Etapa 1 do Trabalho
 * 00134090 - Willian Reichert
 * ---------------------------------------------------------------------------------------------- */

/* tabela com um tamanho pequeno para facilitar testes de colisões. */
#define TABLE_SIZE 21

/* definição do tipo de dado dos itens da tabela.
 * > type: tipo do item (token).
 * > value: valor do item (identificador ou literal).
 * > next_item: ponteiro para o próximo item na lista de colisões. */
typedef struct table_item
{
    int type;
    char* value;
    struct table_item* next_item;
} TABLE_ITEM;

/* protótipos. */
void init_table(void);
int hash(char* value);
TABLE_ITEM* find_table(char* value);
TABLE_ITEM* add_table(int type, char* value);
void print_table(void);
