#include "Funcoes_auxiliares.h"
#include <cmath>
#include <unistd.h>
#include <cstdio>
#include <dirent.h>

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

string obter_diretorio_atual(){
    char buff[PATH_MAX];
    getcwd(buff,PATH_MAX);
    string diretorio_atual(buff);
    for(int i=0;i<5;i++){
        diretorio_atual.pop_back();
    }
    return diretorio_atual;
}

vector<string> obter_arquivos_em(string diretorio){
    DIR *dir;
    vector<string> arquivos;
    struct dirent *ent;
    int contador=0;
    if ((dir = opendir (diretorio.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if(contador<2){
                continue;
            }
            string s(ent->d_name);
            arquivos.push_back(s);
            contador++;
        }
        closedir (dir);
    }
    return arquivos;
}
