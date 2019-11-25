#include "Documento.h"
#include "Funcoes_auxiliares.h"
#include <fstream>

using namespace std;

Documento::Documento(){
    map<string,int> m;
    nome_="";
    frequencias_=m;
}

Documento::Documento(string nome){
    map<string,int> m;
    nome_=nome;
    frequencias_=m;
}

Documento::Documento(string nome, string diretorio){
    nome_=nome;
    ifstream arquivo;
    arquivo.open(diretorio);
    char c;
    string palavra;
    FuncoesAuxiliares f;
    arquivo>>noskipws;
    while(arquivo.good()){
        arquivo>>c;
        if((((c==' ')||(c=='\n')||(c=='\0'))||arquivo.eof())&&(f.padronizar_string(palavra)!="")){
            palavra=f.padronizar_string(palavra);
            if(frequencias_.find(palavra)==frequencias_.end()){
                frequencias_[palavra]=1;
            }
            else{
                frequencias_[palavra]+=1;
            }
            palavra.clear();
            continue;
        }
        palavra.push_back(c);
    }
}

string Documento::nome() const{
    return nome_;
}

int Documento::quantas(string palavra) const{
    if(frequencias_.find(palavra)!=frequencias_.end()){
        return frequencias_.find(palavra)->second;
    }
    else{
        return 0;
    }
}

vector<string> Documento::conteudo() const{
    vector<string> v;
    for(auto it=frequencias_.begin();it!=frequencias_.end();it++){
        v.push_back(it->first);
    }
    return v;
}

bool Documento::operator==(Documento d) const{
    return (nome_==d.nome());
}

bool Documento::operator>(Documento d) const{
    return (nome_>d.nome_);
}

void Documento::operator=(Documento d){
    nome_=d.nome_;
    frequencias_=d.frequencias_;
}
