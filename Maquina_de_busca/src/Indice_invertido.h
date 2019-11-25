#ifndef INDICE_INVERTIDO_H
#define INDICE_INVERTIDO_H
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include "Documento.h"

using namespace std;

class IndiceInvertido{
    public:
        //Cria um índice invertido vazio.
        IndiceInvertido();
        
        //Cria um índice invertido a partir do diretorio em que os arquivos estão
        //PRECONDIÇÃO: o diretorio existe
        IndiceInvertido(string diretorio);
        
        //Retorna a quantidade de palavras diferentes no índice invertido formado
        int tamanho();
        
        //Retorna um vector com os documentos presentes no indice invertido
        vector<Documento> documentos();
        
        //Retorna se uma palavra está presente no documento de nome 'nome'
        bool presente(string palavra, string nome);

        //Retorna um vector contendo todas as palavras diferentes do índice invertido.
        vector<string> palavras();

        //Retorna a importância de uma palavra no índice invertido em questão.
        double idf(string palavra);

        //Atribui ao índice invertido os valores de indice2
        void operator=(IndiceInvertido indice2);

        friend class Teste;
    private:
        //Guarda o indice invertido, associando cada palavra a um conjunto de nomes de documentos em que a palavra está presente.
        map<string,set<string>> indice_;
        
        //Guarda a quantidade de palavras no índice invertido.
        int tamanho_;

        //Guarda os documentos a que o índice invertido referencia.
        vector<Documento> docs_;
};

#endif //INDICE_INVERTIDO_H
