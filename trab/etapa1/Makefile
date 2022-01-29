# -------------------------------------------------------------------------------------------------
# INF01147 - Compiladores - 2021/2
# Etapa 1 do Trabalho
# 00134090 - Willian Reichert
# -------------------------------------------------------------------------------------------------

etapa1: lex.yy.c
	gcc lex.yy.c -o etapa1

lex.yy.c:
	lex scanner.l

clean:
	rm lex.yy.c etapa1
