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

        static map<string,set<string>> indice(const IndiceInvertido& i){
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
       CHECK(fabs(f.cosseno_vetorial(v5,v6)-(-0.0761373365))<=0.000001); 
    }
    
    TEST_CASE("obter_diretorio_atual()"){
        FuncoesAuxiliares f;
        string diretorio=f.obter_diretorio_atual()+"/teste/Teste/teste1.txt";
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
        vector<string> arquivos=f.obter_arquivos_em(f.obter_diretorio_atual()+"/teste/Teste");
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
        FuncoesAuxiliares a;
        Documento d("documento2",a.obter_diretorio_atual()+"/teste/Teste/teste2.txt");
        map<string,int> f;
        f["lagoa"]=2;
        f["pato"]=1;
        f["rio"]=1;
        CHECK(Teste::nome(d)=="documento2");
        REQUIRE(Teste::frequencias(d).size()==3);
        for(auto it=f.begin();it!=f.end();it++){
            CHECK(Teste::frequencias(d).find(it->first)!=Teste::frequencias(d).end());
            CHECK(Teste::frequencias(d)[it->first]==it->second);
        }
    }

    TEST_CASE("nome()"){
        FuncoesAuxiliares a;
        Documento d1,d2("Documento1"),d3("Documento2",a.obter_diretorio_atual()+"/teste/Teste/teste2.txt");
        CHECK(d1.nome()=="");
        CHECK(d2.nome()=="Documento1");
        CHECK(d3.nome()=="Documento2");
    }

    TEST_CASE("quantas(string)"){
        FuncoesAuxiliares a;
        Documento d1("d1",a.obter_diretorio_atual()+"/teste/Teste/teste1.txt"),d2("d2",a.obter_diretorio_atual()+"/teste/Teste/teste2.txt");
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
        FuncoesAuxiliares a;
        Documento d3("d3",a.obter_diretorio_atual()+"/teste/Teste/teste3.txt");
        vector<string> v={"palito","pato","rio"};
        CHECK(d3.conteudo().size()==3);
        CHECK(d3.conteudo()==v);
    }

    TEST_CASE("operator==(Documento)"){
        FuncoesAuxiliares a;
        Documento d1("d1",a.obter_diretorio_atual()+"/teste/Teste/teste1.txt"), d2("d2",a.obter_diretorio_atual()+"/teste/Teste/teste2.txt"),d3,d4;
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
        FuncoesAuxiliares a;
        Documento d1("d1",a.obter_diretorio_atual()+"/teste/Teste/teste1.txt"), d2("d2",a.obter_diretorio_atual()+"/teste/Teste/teste2.txt"),d3,d4;
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
        FuncoesAuxiliares a;
        Documento d1("teste1",a.obter_diretorio_atual()+"/teste/Teste/teste1.txt"),d2;
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
        FuncoesAuxiliares a;
        IndiceInvertido I(a.obter_diretorio_atual()+"/teste/Teste");
        Documento teste1("teste1.txt",a.obter_diretorio_atual()+"/teste/Teste/teste1.txt");
        Documento teste2("teste2.txt",a.obter_diretorio_atual()+"/teste/Teste/teste2.txt");
        Documento teste3("teste3.txt",a.obter_diretorio_atual()+"/teste/Teste/teste3.txt");
        Documento d[]={teste1,teste2,teste3};
        vector<Documento> v(d,d+3);
        string s[]={"carrapatoestrela","lagoa","palito","pato","rio"};
        vector<string> u(s,s+5);
        map<string,set<Documento*>> m;

        CHECK(Teste::tamanho(I)==5);
        CHECK(Teste::docs(I)==v);

        string dp1[]={"teste1"};
        set<string> valores1(dp1,dp1+1);
        m.emplace("carrapatoestrela",valores1);
        
        string dp2[]={"teste1","teste2"};
        set<string> valores2(dp2,dp2+2);
        m.emplace("lagoa",valores2);
        
        string dp3[]={"teste1","teste2","teste3"};
        set<string> valores3(dp3,dp3+3);
        m.emplace("pato",valores3);
        
        string dp4[]={"teste2","teste3"};
        set<string> valores4(dp4,dp4+2);
        m.emplace("rio",valores4);
        
        string dp5[]={"teste3"};
        set<string> valores5(dp5,dp5+1);
        m.emplace("palito",valores5);
        
        for(string& k: u){
            CHECK(m[k]==Teste::indice(I)[k]);
        }
    }

    TEST_CASE("tamanho()"){
        FuncoesAuxiliares a;
        IndiceInvertido I(a.obter_diretorio_atual()+"/teste/Teste");
        CHECK(I.tamanho()==5);
    }

    TEST_CASE("documentos()"){
        FuncoesAuxiliares a;
        IndiceInvertido I(a.obter_diretorio_atual()+"/teste/Teste");
        Documento d1("teste1.txt",a.obter_diretorio_atual()+"/teste/Teste/teste1.txt");
        Documento d2("teste2.txt",a.obter_diretorio_atual()+"/teste/Teste/teste2.txt");
        Documento d[]={d1,d2};
        vector<Documento> v(d,d+2);
        CHECK(I.documentos()[0]==v[0]);
        CHECK(I.documentos()[1]==v[1]);
    }

    TEST_CASE("presente(string,string)"){
        FuncoesAuxiliares a;
        IndiceInvertido I(a.obter_diretorio_atual()+"/teste/Teste");
        CHECK(I.presente("","teste1.txt")==false);
        CHECK(I.presente("rio","teste1.txt")==false);
        CHECK(I.presente("lagoa","teste1.txt")==true);
        CHECK(I.presente("pato","teste1.txt")==true);
        CHECK(I.presente("","teste2.txt")==false);
        CHECK(I.presente("carrapatoestrela","teste2.txt")==false);
        CHECK(I.presente("lagoa","teste2.txt")==true);
        CHECK(I.presente("rio","teste2.txt")==true);
    }

    TEST_CASE("idf(string)"){
        FuncoesAuxiliares a;
        IndiceInvertido I(a.obter_diretorio_atual()+"/teste/Teste");
        CHECK(fabs(I.idf("lagoa")-0.4054651081)<=0.0000001);
        CHECK(fabs(I.idf("pato")-0)<=0.0000001);
        CHECK(fabs(I.idf("carrapatoestrela")-1.098612287)<=0.0000001);
        CHECK(fabs(I.idf("rio")-0.4054651081)<=0.0000001);
        CHECK(fabs(I.idf("palito")-1.098612287)<=0.0000001);
    }

    TEST_CASE("operator=(IndiceInvertido)"){
        FuncoesAuxiliares a;
        IndiceInvertido I1,I2(a.obter_diretorio_atual()+"/teste/Teste");
        vector<string> u={"carrapatoestrela","lagoa","palito","pato","rio"};
        
        I1=I2;
        CHECK(Teste::tamanho(I1)==Teste::tamanho(I2));
        
        REQUIRE(Teste::docs(I1).size()==Teste::docs(I2).size());
        for(int i=0;i<(int)Teste::docs(I2).size();i++){
            CHECK(Teste::docs(I1)[i]==Teste::docs(I2)[i]);
        }

        for(string& k: u){
            CHECK(Teste::indice(I1)[k]==Teste::indice(I2)[k]);
            
        }
    }

}

TEST_SUITE("Busca.h"){
    
    TEST_CASE("Busca(string,IndiceInvertido)"){
        FuncoesAuxiliares a;
        IndiceInvertido I(a.obter_diretorio_atual()+"/teste/Teste");
        Busca b("Pato na lagoa",I);
        map<string,int> m;
        string s[]={"carrapatoestrela","lagoa","pato","palito","rio"};
        vector<string> u(s,s+5);
        m["pato"]=1;
        m["na"]=1;
        m["lagoa"]=1;

        CHECK(Teste::frequencias(Teste::consulta(b))==m);
        CHECK(Teste::tamanho(Teste::dados(b))==Teste::tamanho(I));
        
        REQUIRE(Teste::docs(I).size()==Teste::docs(Teste::dados(b)).size());
        for(int i=0;i<(int)Teste::docs(I).size();i++){
            CHECK(Teste::docs(Teste::dados(b))[i]==Teste::docs(I)[i]);
        }

        bool encontrardoc=false;

        for(string & k: u){
            CHECK(Teste::indice(I)[k]==Teste::indice(Teste::dados(b))[k]);
        }
    }
    
    TEST_CASE("Vetorizar(string)"){
        FuncoesAuxiliares a;
        IndiceInvertido I(a.obter_diretorio_atual()+"/teste/Teste");
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
        IndiceInvertido I(f.obter_diretorio_atual()+"/teste/Teste");
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
