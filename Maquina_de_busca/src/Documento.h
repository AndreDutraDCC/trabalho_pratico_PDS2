#ifndef DOCUMENTO_H
#define DOCUMENTO_H
#include<iostream>
#include<string>
#include<map>
#include<vector>

using namespace std;

class Documento{
    public:
        //Cria um documento vazio e de nome ""
        Documento();

        //Cria um documento vazio de nome 'nome'
        Documento(string nome);
        
        //Cria um documento 'nome' e o lê do diretorio em que o arquivo está presente
        Documento(string nome,string diretorio);
        
        //Retorna o nome do documento
        string nome() const;

        //Retorna quantas vezes determinada palavra aparece no documento
        int quantas(string palavra) const;

        //Retorna um vector com todas as palavras diferentes do documento em ordem alfabética
        vector<string> conteudo() const;

        //Retorna se dois documentos têm o mesmo nome
        bool operator==(Documento d) const;

        //Retorna se o nome do documento vem antes do nome do documento d em ordem lexicográfica
        bool operator>(Documento d) const;

        //Iguala os atributos do documento aos atributos de d.
        void operator=(Documento d);
        
        friend class Teste;
    private:
        //Nome do documento
        string nome_;

        //Relação entre cada palavra do documento e a frequencia com que ela aparece nele
        map<string,int> frequencias_;
        
};
#endif //DOCUMENTO_H
