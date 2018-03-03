hoo: hc
	gcc -m32 -I ./include -o hoo \
		src/hoomain.c
hc: lexer
	gcc -m32 -I ./include -o ./hc \
		src/hcmain.c \
		src/hclexer.c \
		src/hcparser.c \
		src/literaltype.c \
		src/hclogger.c \
		src/hcexpr.c \
		src/hcintops.c

lexer: parser
	flex --outfile=./src/hclexer.c \
		--header-file=./include/hclexer.h \
		./grammar/hclexer.l

parser:
	bison --output=./src/hcparser.c \
		--defines=./include/hcparser.h \
		./grammar/hcparser.y
		
clean:
	rm -f ./hc.exe
	rm -f ./hc
	rm -f ./include/hclexer.h
	rm -f ./include/hcparser.h
	rm -f ./src/hclexer.c
	rm -f ./src/hcparser.c