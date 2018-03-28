HOO_BASE_SOURCE=src/hoocodebuffer.c \
		src/hoojit.c \
		src/hooutil.c \
		src/hootype.c \
		src/hoojitfunccall.c \
		src/hoonumop.c

HOO_SOURCE=$(HOO_BASE_SOURCE) src/hoomain.c
	
HC_BASE_SOURCE=src/hclexer.c \
		src/hcparser.c \
		src/hcliteral.c \
		src/hclogger.c \
		src/hcexpr.c \
		src/hccompiler.c \
		src/hcoperator.c \
		src/hcbaseexpression.c \
		src/hcbinaryexpression.c
	
HC_SOURCE=$(HC_BASE_SOURCE) src/hcmain.c

all: hc hoo

hoo:
	gcc -g -m32 -I ./include -o hoo $(HOO_SOURCE)
		
		
hc: lexer
	gcc -g -m32 -I ./include -o ./hc $(HC_SOURCE)
		
		

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
	rm -f ./hoo.exe
	rm -f ./hoo
	rm -f ./include/hclexer.h
	rm -f ./include/hcparser.h
	rm -f ./src/hclexer.c
	rm -f ./src/hcparser.c