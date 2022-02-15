# -------------------------------------------------------------------------------------------------
# INF01147 - Compiladores - 2021/2
# Etapa 2 do Trabalho
# 134090 - Willian Reichert
# -------------------------------------------------------------------------------------------------

etapa2: y.tab.c lex.yy.c
	gcc lex.yy.c -o etapa2

y.tab.c:
	yacc -d parser.y

lex.yy.c:
	lex scanner.l

clean:
	rm y.tab* lex.yy.c etapa2
