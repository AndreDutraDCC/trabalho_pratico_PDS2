#include <iostream>
#include <string>
#include "Funcoes_auxiliares.h"
#include "Documento.h"
#include "Indice_invertido.h"
#include "Busca.h"

int main(){
    string pasta,consulta;
    
    cout<<"Insira o nome da pasta de onde os arquivos serao lidos."<<endl;
    cout<<"Certifique-se de que a mesma esta dentro da pasta do projeto."<<endl;
    cin>>pasta;
    cout<<"O que deseja pesquisar?"<<endl;
    cin>>consulta;
    
    IndiceInvertido I("arquivos");
    Busca b("A B",I);
    multimap<double,string> resultado=b.Cosine_rank();
    it=resultado.rbegin();
    double cos_anterior,cos_atual;
    cos_atual=it->first;
    i=1;
    cout<<"Os documentos mais proximos da sua consulta sao:"<<endl;
    cout<<i<<"    "<<cos_atual;
    it++;
    while(it!=resultado.rend()){
        cos_anterior=cos_atual;
        cos_atual=it->first;
        if(cos_anterior==cos_atual){
            cout<<"    "<<it->second;
        }
        else{
            i++;
            cout<<endl<<i<<"    "<<it->second;
        }
    }
    cout<<endl;
    return 0;
}