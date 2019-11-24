#ifndef BUSCA_H
#define BUSCA_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Indice_invertido.h"
#include "Documento.h"

class Busca{
    public:        
        //Cria uma busca a partir de uma consulta e um indice invertido onde os documentos estão representados.
        Busca(string consulta,IndiceInvertido dados);
        
        //Retorna a representação vetorial do documento doc sobre o espaço definido pelas palavras do índice invertido em que a pesquisa está sendo feita.
        vector<double> Vetorizar(const Documento& doc);
        
        //Retorna os nomes de cada um dos documentos no indice invertido, em ordem de proximidade à consulta feita, usando como criério o cosine rank.
        multimap<double,string> Cosine_rank();

        friend class Teste;
    private:
        //Documento criado a partir da consulta feita
        Documento consulta_;

        //Indice invertido onde  busca será feita
        IndiceInvertido dados_;
};

#endif //BUSCA_H