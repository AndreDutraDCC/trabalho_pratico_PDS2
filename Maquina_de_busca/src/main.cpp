#include <iostream>
#include <string>
#include "Funcoes_auxiliares.h"
#include "Documento.h"
#include "Indice_invertido.h"
#include "Busca.h"

int main(){
    string pasta,consulta;
    
    cout<<"Insira o nome da pasta de onde os arquivos serão lidos."<<endl;
    cout<<"Certifique-se de que a mesma está dentro da pasta do projeto."<<endl;
    cin>>pasta;
    cout<<"O que deseja pesquisar?"<<endl;
    cin>>consulta;
    cout<<"Os documentos mais proximos da sua consulta sao:"<<endl;
    
    IndiceInvertido I(pasta);
    Busca b(consulta,I);
    multimap<double,string> resultado=b.Cosine_rank();
    double cos_anterior,cos_atual;
    int i=1;
    auto it=resultado.rbegin();
    
    cos_atual=it->first;
    cout<<i<<"    "<<it->second;
    it++;
    
    while(it!=resultado.rend()){
        cos_anterior=cos_atual;
        cos_atual=it->first;
        if(cos_atual==cos_anterior){
            cout<<"  "<<it->second;
        }
        else{
            i++;
            cout<<endl<<i<<"    "<<it->second;
        }
        it++;
    }
    cout<<endl;
    return 0;
}