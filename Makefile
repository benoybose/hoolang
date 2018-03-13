hoo: hc
	gcc -g -m32 -I ./include -o hoo \
		src/hoomain.c \
		src/hoocodebuffer.c \
		src/hoojit.c \
		src/hooutil.c \
		src/hootype.c \
		src/hoojitfunccall.c
		
hc: lexer
	gcc -g -m32 -I ./include -o ./hc \
		src/hcmain.c \
		src/hclexer.c \
		src/hcparser.c \
		src/literaltype.c \
		src/hclogger.c \
		src/hcexpr.c

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