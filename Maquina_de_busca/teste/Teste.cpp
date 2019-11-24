#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "Funcoes_auxiliares.h"
#include "Documento.h"
#include "Indice_invertido.h"
#include "Busca.h"

#include "doctest.h"

#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<cmath>
#include<fstream>


using namespace std;

class Teste{
    public:
        
        static string nome(const Documento& d){
            return d.nome_;
        }

        static map<string,int> frequencias(const Documento& d){
            return d.frequencias_;
        }

        static map<string,set<Documento*>> indice(const IndiceInvertido& i){
            return i.indice_;
        }
        
        static int tamanho(const IndiceInvertido& i){
            return i.tamanho_;
        }
        
        static vector<Documento> docs(const IndiceInvertido& i){
            return i.docs_;
        }
        
        static Documento consulta(const Busca& b){
            return b.consulta_;
        }
        
        static IndiceInvertido dados(const Busca& b){
            return b.dados_;
        }

};

int main(){
}

TEST_SUITE("Funcoes_auxiliares.h"){
    
   TEST_CASE("padronizar_string(string)"){
       FuncoesAuxiliares f;
       string s1=f.padronizar_string("TesTaNdO123");
       string s2=f.padronizar_string("(t.s,e;t:!an?d@o3{A2}B1)");
       string s3=f.padronizar_string("T-E$t_A(N)/d#o|1<2][3>");
       CHECK(s1=="testando123");
       CHECK(s2=="tsetando3a2b1");
       CHECK(s3=="tetando123");
   }

   TEST_CASE("cosseno_vetorial(vector<double>,vector<double>)"){
       FuncoesAuxiliares f;
       vector<double> v1={2};
       vector<double> v2={-7};
       vector<double> v3={2,4};
       vector<double> v4={9,-3};
       vector<double> v5={4,8,3};
       vector<double> v6={6,0,-11};
       CHECK(fabs(f.cosseno_vetorial(v1,v2)-(-1))<=0.000001);
       CHECK(fabs(f.cosseno_vetorial(v3,v4)-0.1414213562)<=0.000001);
       CHECK(fabs(f.cosseno_vetorial(v5,v6)-0.0761373365)<=0.000001); 
    }
    
    TEST_CASE("obter_diretorio_atual()"){
        FuncoesAuxiliares f;
        string diretorio=f.obter_diretorio_atual()+"\\Teste\\teste1.txt";
        string palavra;
        ifstream arquivo;
        char c;

        arquivo.open(diretorio);
        REQUIRE(arquivo.is_open());
        for(int i=0;i<6;i++){
            arquivo>>c;
            palavra.push_back(c);
        } 
        arquivo.close();
        CHECK(palavra=="Lagoa,");
    }

    TEST_CASE("obter_arquivos_em(string)"){
        FuncoesAuxiliares f;
        vector<string> arquivos=f.obter_arquivos_em(f.obter_diretorio_atual()+"\\Teste");
        REQUIRE(arquivos.size()==3);
        CHECK(arquivos[0]=="teste1.txt");
        CHECK(arquivos[1]=="teste2.txt");
        CHECK(arquivos[2]=="teste3.txt");
    }

}

TEST_SUITE("Documento.h"){
    TEST_CASE("Documento()"){
        Documento d;
        map<string,int> f;
        CHECK(Teste::nome(d)=="");
        CHECK(Teste::frequencias(d)==f);
    }

    TEST_CASE("Documento(string)"){
        Documento d("documento1");
        map<string,int> f;
        CHECK(Teste::nome(d)=="documento1");
        CHECK(Teste::frequencias(d)==f);
    }

    TEST_CASE("Documento(string,string)"){
        Documento d("documento2","Teste\\teste2.txt");
        map<string,int> f;
        f["lagoa"]=2;
        f["pato"]=1;
        f["rio"]=1;
        CHECK(Teste::nome(d)=="documento2");
        CHECK(Teste::frequencias(d)==f);
    }

    TEST_CASE("nome()"){
        Documento d1,d2("Documento1"),d3("Documento2","Teste\\teste2.txt");
        CHECK(d1.nome()=="");
        CHECK(d2.nome()=="Documento1");
        CHECK(d3.nome()=="Documento2");
    }

    TEST_CASE("quantas(string)"){
        Documento d1("d1","Teste\\teste1.txt"),d2("d2","Teste\\teste2.txt");
        CHECK(d1.quantas("")==0);
        CHECK(d1.quantas("rio")==0);
        CHECK(d1.quantas("lagoa")==1);
        CHECK(d1.quantas("pato")==1);
        CHECK(d1.quantas("carrapatoestrela")==1);

        CHECK(d2.quantas("carrapatoestrela")==0);
        CHECK(d2.quantas("lagoa")==2);
        CHECK(d2.quantas("rio")==1);
        CHECK(d2.quantas("pato")==1);
    }

    TEST_CASE("conteudo()"){
        Documento d3("d3","Teste\\teste3.exe");
        vector<string> v={"palito","pato","rio"};
        CHECK(d3.conteudo().size()==3);
        CHECK(d3.conteudo()==v);
    }

    TEST_CASE("operator==(Documento)"){
        Documento d1("d1","Teste\\teste1.txt"), d2("d2","Teste\\teste2.txt"),d3,d4;
        CHECK((d1==d1)==true);
        CHECK((d1==d2)==false);
        CHECK((d1==d3)==false);
        CHECK((d2==d1)==false);
        CHECK((d2==d2)==true);
        CHECK((d2==d3)==false);
        CHECK((d3==d1)==false);
        CHECK((d3==d2)==false);
        CHECK((d3==d3)==true);
        CHECK((d3==d4)==true);
    }

    TEST_CASE("operator>(Documento)"){
        Documento d1("d1","Teste\\teste1.txt"), d2("d2","Teste\\teste2.txt"),d3,d4;
        CHECK((d1>d1)==false);
        CHECK((d1>d2)==false);
        CHECK((d1>d3)==true);
        CHECK((d2>d1)==true);
        CHECK((d2>d2)==false);
        CHECK((d2>d3)==true);
        CHECK((d3>d1)==false);
        CHECK((d3>d2)==false);
        CHECK((d3>d3)==false);
        CHECK((d3>d4)==false);
    }

    TEST_CASE("operator=(Documento)"){
        Documento d1("teste1","Teste\\teste1.txt"),d2;
        d2=d1;
        CHECK(Teste::nome(d2)==Teste::nome(d1));
        CHECK(Teste::frequencias(d2)==Teste::frequencias(d1));
    }
    
}

TEST_SUITE("Indice_invertido.h"){
    TEST_CASE("IndiceInvertido()"){
        IndiceInvertido I;
        CHECK(Teste::tamanho(I)==0);
        CHECK(Teste::docs(I).size()==0);
        CHECK(Teste::indice(I).size()==0);
    }
    TEST_CASE("IndiceInvertido(string)"){
        IndiceInvertido I("teste\\Teste");
        Documento teste1("teste1.txt","Teste\\teste1.txt");
        Documento teste2("teste2.txt","Teste\\teste2.txt");
        Documento teste3("teste3.txt","Teste\\teste3.txt");
        vector<Documento> v={teste1,teste2,teste3};
        vector<string> u={"carrapatoestrela","lagoa","palito","pato","rio"};
        map<string,set<Documento*>> m;

        CHECK(Teste::tamanho(I)==5);
        CHECK(Teste::docs(I)==v);

        m["carrapatoestrela"]={&teste1};
        m["lagoa"]={&teste1,&teste2};
        m["pato"]={&teste1,&teste2,&teste3};
        m["rio"]={&teste2,&teste3};
        m["palito"]={&teste3};
        
        for(string s: u){
            auto it1=Teste::indice(I)[s].begin();
            auto it2=m[s].begin();
            while((it1!=Teste::indice(I)[s].end())||(it2!=m[s].end())){
                CHECK(**it1==**it2);
                it1++;
                it2++;
            }
        }
    }

    TEST_CASE("tamanho()"){
        IndiceInvertido I("teste\\Teste");
        CHECK(I.tamanho()==4);
    }

    TEST_CASE("documentos()"){
        IndiceInvertido I("teste\\Teste");
        Documento d1("teste1","Teste/teste1.txt");
        Documento d2("teste2","Teste/teste2.txt");
        vector<Documento> v={d1,d2};
        CHECK(I.documentos()==v);

    }

    TEST_CASE("presente(string,string)"){
        IndiceInvertido I("teste\\Teste");
        CHECK(I.presente("","teste1")==false);
        CHECK(I.presente("rio","teste1")==false);
        CHECK(I.presente("lagoa","teste1")==true);
        CHECK(I.presente("pato","teste1")==true);
        CHECK(I.presente("","teste2")==false);
        CHECK(I.presente("carrapatoestrela","teste2")==false);
        CHECK(I.presente("lagoa","teste2")==true);
        CHECK(I.presente("rio","teste2")==true);
    }

    TEST_CASE("idf(string)"){
        IndiceInvertido I("teste\\Teste");
        CHECK(fabs(I.idf("lagoa")-0.4054651081)<=0.0000001);
        CHECK(fabs(I.idf("pato")-0)<=0.0000001);
        CHECK(fabs(I.idf("carrapatoestrela")-1.098612287)<=0.0000001);
        CHECK(fabs(I.idf("rio")-0.4054651081)<=0.0000001);
        CHECK(fabs(I.idf("palito")-1.098612287)<=0.0000001);
    }

    TEST_CASE("operator=(IndiceInvertido)"){
        IndiceInvertido I1,I2("Teste");
        vector<string> u={"carrapatoestrela","lagoa","palito","pato","rio"};
        
        I1=I2;
        CHECK(Teste::tamanho(I1)==Teste::tamanho(I2));
        CHECK(Teste::docs(I1)==Teste::docs(I2));

        for(string s: u){
            auto it1=Teste::indice(I1)[s].begin();
            auto it2=Teste::indice(I2)[s].begin();
            while((it1!=Teste::indice(I1)[s].end())||(it2!=Teste::indice(I2)[s].end())){
                CHECK(**it1==**it2);
                it1++;
                it2++;
            }
        }
    }

}

TEST_SUITE("Busca.h"){
    
    TEST_CASE("Busca(string,IndiceInvertido)"){
        IndiceInvertido I("teste\\Teste");
        Busca b("Pato na lagoa",I);
        map<string,int> m;
        vector<string> u={"carrapatoestrela","lagoa","pato","palito","rio"};
        m["pato"]=1;
        m["na"]=1;
        m["lagoa"]=1;

        CHECK(Teste::frequencias(Teste::consulta(b))==m);
        CHECK(Teste::tamanho(Teste::dados(b))==Teste::tamanho(I));
        CHECK(Teste::docs(Teste::dados(b))==Teste::docs(I));
        
        for(string s: u){
            auto it1=Teste::indice(I)[s].begin();
            auto it2=Teste::indice(Teste::dados(b))[s].begin();
            while((it1!=Teste::indice(I)[s].end())||(it2!=Teste::indice(Teste::dados(b))[s].end())){
                CHECK(**it1==**it2);
                it1++;
                it2++;
            }
        }
    }

    TEST_CASE("Vetorizar(string)"){
        IndiceInvertido I("teste\\Teste");
        vector<Documento> v=I.documentos();
        Busca b("teste",I);
        
        vector<double> v1=b.Vetorizar(v[0]);
        vector<double> v2=b.Vetorizar(v[1]);
        vector<double> v3=b.Vetorizar(v[2]);

        vector<double> vc1={1.098612287,0.4054651081,0,0,0};
        vector<double> vc2={0,0.8109302162,0,0,0.4054651081};
        vector<double> vc3={0,0,2.1972245773,0,0.4054651081};

        for(int i=0;i<Teste::tamanho(Teste::dados(b));i++){
            CHECK(fabs(v1[i]-vc1[i])<=0.000001);
        }

        for(int i=0;i<Teste::tamanho(Teste::dados(b));i++){
            CHECK(fabs(v2[i]-vc2[i])<=0.000001);
        }

        
        for(int i=0;i<Teste::tamanho(Teste::dados(b));i++){
            CHECK(fabs(v3[i]-vc3[i])<=0.000001);
        }
    }

    TEST_CASE("Cosine_rank()"){
        FuncoesAuxiliares f;
        IndiceInvertido I("teste\\Teste");
        Busca b1("Pato no rio, carrapato na lagoa",I),b2("pato e palito, lagoa e rio, lagoa",I);
        multimap<double,string> v1,v2;
        vector<Documento> d=I.documentos();
        
        v1.emplace(f.cosseno_vetorial(b1.Vetorizar(d[0]),b1.Vetorizar(Teste::consulta(b1))),d[0].nome());
        v1.emplace(f.cosseno_vetorial(b1.Vetorizar(d[1]),b1.Vetorizar(Teste::consulta(b1))),d[1].nome());
        v1.emplace(f.cosseno_vetorial(b1.Vetorizar(d[2]),b1.Vetorizar(Teste::consulta(b1))),d[2].nome());
        
        v2.emplace(f.cosseno_vetorial(b2.Vetorizar(d[0]),b2.Vetorizar(Teste::consulta(b2))),d[0].nome());
        v2.emplace(f.cosseno_vetorial(b2.Vetorizar(d[1]),b2.Vetorizar(Teste::consulta(b2))),d[1].nome());
        v2.emplace(f.cosseno_vetorial(b2.Vetorizar(d[2]),b2.Vetorizar(Teste::consulta(b2))),d[2].nome());
        
        CHECK(b1.Cosine_rank()==v1);
        CHECK(b2.Cosine_rank()==v2);
    }
    
}
