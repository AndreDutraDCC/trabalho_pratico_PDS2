#ifndef FUNCOES_AUXILIARES_H
#define FUNCOES_AUXILIARES_H
#include<iostream>
#include<vector>
#include<string>

using namespace std;

class FuncoesAuxiliares{
    public:
        //Recebe uma string e retorna sua equivalente sem sinais de pontuação e com todas as letras minúsculas
        //PRECONDIÇÃO: A string não contém espaços ou quebras de linha (uma palavra apenas)
        string padronizar_string(string s);

        //Retorna o cosseno entre dois vetores v1 e v2 a partir de suas coordenadas.
        //PRECONDIÇÃO: os dois vetores são de mesmo tamanho
        double cosseno_vetorial(vector<double> v1,vector<double> v2);
        
        //Retorna uma string com o diretório do projeto.
        string obter_diretorio_atual();
        
        //Retorna um vector com os nomes de cada um dos arquivos dentro do diretório recebido.
        //PRECONDIÇÃO: o diretorio dado existe
        vector<string> obter_arquivos_em(string diretorio);
};

#endif //FUNCOES_AUXILIARES_H