#include "Indice_invertido.h"
#include "Funcoes_auxiliares.h"
#include <cmath>

using namespace std;

IndiceInvertido::IndiceInvertido(){
    tamanho_=0;
    docs_.clear();
    indice_.clear();
}

IndiceInvertido::IndiceInvertido(string diretorio){
    FuncoesAuxiliares f;
    vector<string> documentos=f.obter_arquivos_em(diretorio);
    docs_.clear();
    indice_.clear();
    for(string arquivo : documentos){
        Documento d(arquivo,(diretorio+"/"+arquivo));
        docs_.push_back(d);
    }
    for(Documento& doc : docs_){
        for(string& palavra : doc.conteudo()){
            if(indice_.find(palavra)==indice_.end()){
                set<Documento*> s;
                s.insert(&(doc));
                indice_.emplace(palavra,s);
            }
            else{
                indice_[palavra].insert(&(doc));
            }
        }
    }
    tamanho_=indice_.size();
}

int IndiceInvertido::tamanho(){
    return tamanho_;
}

vector<Documento> IndiceInvertido::documentos(){
    return docs_;
}
        
bool IndiceInvertido::presente(string palavra, string nome){
    if(indice_.find(palavra)==indice_.end()){
        return false;
    }
    for(auto it=indice_.find(palavra)->second.begin();it!=indice_.find(palavra)->second.end();it++){
        if((*it)->nome()==nome){
            return true;
        }
    }
    return false;
}

vector<string> IndiceInvertido::palavras(){
    vector<string> palavras;
    for(auto it=indice_.begin();it!=indice_.end();it++){
        palavras.push_back(it->first);
    }
    return palavras;
}

double IndiceInvertido::idf(string palavra){
    if(indice_.find(palavra)==indice_.end()){
        return 0;
    }
    double N,nx,idf;
    N= docs_.size();
    nx= indice_.find(palavra)->second.size();
    idf=log(N/nx);
    return idf;
}

void IndiceInvertido::operator=(IndiceInvertido indice2){
    tamanho_=indice2.tamanho_;
    docs_.clear();
    indice_.clear();
    for(auto it=indice2.docs_.begin();it!=indice2.docs_.end();it++){
        docs_.push_back(*it);
    }
    for(auto it=indice2.indice_.begin();it!=indice2.indice_.end();it++){
        indice_[it->first]=it->second;
    }
}
