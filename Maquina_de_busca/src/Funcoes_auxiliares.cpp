#include "Funcoes_auxiliares.h"
#include <cmath>
#include <cstdio>
#include <dirent.h>
#include <experimental/filesystem>

using namespace std;

string FuncoesAuxiliares::padronizar_string(string s){
    string novastring;
    for(auto it=s.begin();it!=s.end();it++){
        if(isalnum(*it)!=0){
            novastring.push_back(tolower(*it));
        }
    }
    return novastring;
}

double FuncoesAuxiliares::cosseno_vetorial(vector<double> v1, vector<double> v2){
    auto it1=v1.begin();
    auto it2=v2.begin();
    double cos;
    double v1v2=0;
    double normv1=0;
    double normv2=0;
    
    while(it1!=v1.end()){
        v1v2+=(*it1)*(*it2);
        normv1+=(*it1)*(*it1);
        normv2+=(*it2)*(*it2);
        it1++;
        it2++;
    }
    normv1=sqrt(normv1);
    normv2=sqrt(normv2);
    cos=v1v2/(normv1*normv2);
    return cos;
}

string FuncoesAuxiliares::obter_diretorio_atual(){
    std::experimental::filesystem::path p=std::experimental::filesystem::current_path();
    string dir=p.string();
    return dir;
}

vector<string> FuncoesAuxiliares::obter_arquivos_em(string diretorio){
    vector<string> resultado;
    string path = diretorio,newpath,nome;
    for (const auto & entry : std::experimental::filesystem::directory_iterator(path)){
        for(auto it=entry.path().string().rbegin();it!=entry.path().string().rend();it++){
            if(*it=='/'||*it=='\\'){
                break;
            }
            newpath.push_back(*it);
        }
        for(auto it=newpath.rbegin();it!=newpath.rend();it++){
            nome.push_back(*it);
        }
        resultado.push_back(nome);
    }
    return resultado;
}
