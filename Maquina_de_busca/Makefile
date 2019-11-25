CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++14 -ggdb


all: bin/main bin/teste

clean:
	rm -rf bin/*

run: bin/main
	cls
	./bin/main

teste: bin/teste
	cls
	./bin/teste

bin/Funcoes_auxiliares.o: src/Funcoes_auxiliares.cpp
	$(CXX) $(CXX_FLAGS) -c -I src/ $^ -o $@

bin/Documento.o: src/Documento.cpp
	$(CXX) $(CXX_FLAGS) -c -I src/ $^ -o $@

bin/Indice_invertido.o: src/Indice_invertido.cpp
	$(CXX) $(CXX_FLAGS) -c -I src/ $^ -o $@

bin/Busca.o: src/Busca.cpp
	$(CXX) $(CXX_FLAGS) -c -I src/ $^ -o $@

bin/teste: bin/Funcoes_auxiliares.o bin/Documento.o bin/Indice_invertido.o bin/Busca.o teste/Teste.cpp
	$(CXX) $(CXX_FLAGS) -I include/ -I src/ $^ -o $@

bin/main: bin/Funcoes_auxiliares.o bin/Documento.o bin/Indice_invertido.o bin/Busca.o src/main.cpp
	$(CXX) $(CXX_FLAGS) -I src/ $^ -o $@