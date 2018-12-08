
EXECUTAVEL=trab2

CC= g++
CFLAGS= -std=c++11 -Wall -g  # -D NDEBUG -O3


# Arquivos de bibliotecas
SRCS=$(wildcard src/*.cpp)
OBJS=$(patsubst src/%.cpp,build/%.o,$(SRCS))

# Arquivos de executáveis
MAINS=$(wildcard main/*.cpp)
EXES=$(patsubst main/%.cpp,bin/%,$(MAINS))


# Marca as regras de arquivos que não devem ser excluídos
.PRECIOUS: %/  build/%.o


# Target padrão
all: exe

# run: exe
# 	@ ./bin/$(EXECUTAVEL) #divulga.csv

clean:
	rm -f -r ./.dep
	rm -f -r ./build
	rm -f -r ./bin


# Cria uma pasta
%/:
	mkdir -p $@

# Compila todos os executáveis
exe: $(EXES)


# Compila bibliotecas de src/ para build/
build/%.o: src/%.cpp | build/  $(dir .dep/src/%)/
	$(CC) -o $@  -c  $<  $(CFLAGS)

	@ $(CC) -MM -MT "$@"  $< $(CFLAGS)  > .dep/$<.d

# Compila de main/ para para bin/
bin/%: main/%.cpp $(OBJS) | bin/  $(dir .dep/main/%)/
	$(CC) -o $@  -I "./src/"  $< $(OBJS)  $(CFLAGS)
	
	@ $(CC) -I "./src/" -MM -MT "$@"  $< $(CFLAGS)  > .dep/$<.d


# Inclui as listas de dependências
include $(wildcard .dep/**/*)
