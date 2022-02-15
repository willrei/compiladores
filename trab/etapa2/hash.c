/* ----------------------------------------------------------------------------------------------- *
 * INF01147 - Compiladores - 2021/2
 * Etapa 2 do Trabalho
 * 134090 - Willian Reichert
 * ---------------------------------------------------------------------------------------------- */
#include <stdio.h>
#include "hash.h"

/* declaração da tabela de símbolos. */
TABLE_ITEM* table[TABLE_SIZE];

/* inicialização da tabela de símbolos. */
void init_table(void)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table[i] = NULL;
    }
}

/* função que calcula o hash de uma string.
 * > utilizada para calcular o endereço um item na tabela de símbolos com base em seu valor.
 * > utiliza a função de hash djb2 (http://www.cse.yorku.ca/~oz/hash.html), escolhida por ser
 *   simples e distribuir bem os endereços. */
int hash(char* value)
{
    /* valor inicial mágico */
    unsigned long int hash = 5381;
    char ch;
    while ((ch = *value++) != '\0')
    {
        /* hash * 32 + hash == hash * 33 */
        hash = ((hash << 5) + hash) + (int)ch;
    }
    /* resto da divisão da hash pelo tamanho da tabela forma o endereço do item */
    return (int)(hash % TABLE_SIZE);
}

/* busca um item na tabela de símbolos.
 * > utilizada nas inserções para evitar repetição de itens.
 * > retorna um item caso o encontre, ou nulo. */
TABLE_ITEM* find_table(char* value)
{
    TABLE_ITEM* item;
    int index = 0;
    /* laço para percorrer o vetor principal */
    while (index < TABLE_SIZE)
    {
        /* laço para percorrer as listas de colisões */
        item = table[index];
        while (item != NULL)
        {
            if (strcmp(value, item->value) == 0)
            {
                return item;
            }
            item = item->next_item;
        }
        index++;
    }
    return NULL;
}

/* insere um item na tabela de símbolos.
 * > é utilizada pelo analisador léxico sempre que ele encontra um identificador ou literal. */
TABLE_ITEM* add_table(int type, char* value)
{
    /* busca por um item já existente para evitar repetições. */
    TABLE_ITEM* new_item;
    if ((new_item = find_table(value)) != NULL)
    {
        return new_item;
    }

    /* cálculo do endereço. */
    int index = hash(value);
    /* alocação de memória para um item. */
    new_item = (TABLE_ITEM*)calloc(1, sizeof(TABLE_ITEM));
    new_item->type = type;
    /* alocação de memória para a string que representa o valor do item. */
    new_item->value = (char*)calloc(strlen(value) + 1, sizeof(char));
    strcpy(new_item->value, value);
    /* (crédito: prof. Johann) inserção no início da lista que empurra os itens já existentes. */
    new_item->next_item = table[index];
    table[index] = new_item;
    return new_item;
}

/* imprime a tabela de símbolos */
void print_table(void)
{
    printf("\ntabela de símbolos ----------------------------------------\n\n");
    /* laço para percorrer o vetor principal. */
    TABLE_ITEM* item;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        /* laço para percorrer as listas de colisões. */
        item = table[i];
        while (item != NULL)
        {
            printf("table[%d] item type: %d", i, item->type);
            printf(", value: %s", item->value);
            printf(", has next: %s\n\n", item->next_item != NULL ? "true" : "false");
            item = item->next_item;
        }
    }
}
