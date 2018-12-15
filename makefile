COMPILER=gcc
DEBUG_COMPILER=-Wall -pedantic -std=c99 -g -fsanitize=address -DDEBUG=1
OUTPUT_FILE=censo

all: back.o
	$(COMPILER) -o $(OUTPUT_FILE) censo2.c listaAeropuertoADT2.o listaAerolineaADT2.o listaParesADT2.o

debug:COMPILER+=$(DEBUG_COMPILER)
debug: all
back.o: listaAeropuertoADT2.c listaAerolineaADT2.c listaParesADT2.c
	$(COMPILER) -c listaAeropuertoADT2.c listaAerolineaADT2.c listaParesADT2.c

clean:
	rm -r listaAeropuertoADT2.o listaAerolineaADT2.o listaParesADT2.o
