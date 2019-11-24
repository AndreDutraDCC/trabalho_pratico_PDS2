#include <fstream>
#include <cstdio>
#include <map>
#include "Busca.h"
#include "Documento.h"
#include "Indice_invertido.h"
#include "Funcoes_auxiliares.h"

using namespace std;

Busca::Busca(string consulta, IndiceInvertido dados){
	dados_= dados;
	ofstream arq_consulta;

	arq_consulta.open("consulta.txt");
	arq_consulta<<consulta;
	arq_consulta.close();

	Documento d("consulta_","consulta.txt");
	consulta_= d;
	remove("consulta.txt");
}

vector<double> Busca::Vetorizar(const Documento& doc){
	int frequencia;
	double importancia;
	vector<double> v;
	
	for (auto it=dados_.palavras().begin();it!=dados_.palavras().end();it++)
	{
		frequencia = doc.quantas(*it);
		importancia = dados_.idf(*it);
		v.push_back(frequencia * importancia);
	}
	return v;
}

multimap<double,string> Busca::Cosine_rank(){
	FuncoesAuxiliares f;
	vector<Documento> documentos;
	vector<vector<double>> docs_vetorizados;
	vector<double> consulta_vetorizada;
	multimap<double,string> cos_para_nome;
	vector<string> resultado;
	
	documentos=dados_.documentos();

	for(auto it=documentos.begin();it!=documentos.end();it++){
		docs_vetorizados.push_back(Vetorizar(*it));
	}

	consulta_vetorizada=Vetorizar(consulta_);

	for(int i=0;i<(int)documentos.size();i++){
		cos_para_nome.emplace(f.cosseno_vetorial(docs_vetorizados[i],consulta_vetorizada),documentos[i].nome());
	}

	return cos_para_nome;
}

int main(){
	return 0;
}