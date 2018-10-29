#include<iostream>
using namespace std;
struct Derivar{
	string signo;
	Derivar *left,*right;
	void imprimir(){
		Derivar* prueba=this;
		imprimir(prueba);
	}
	void imprimir(Derivar* & arbol){
		if(arbol->left==nullptr && arbol->right==nullptr)
			cout<<arbol->signo;
		else{
			imprimir(arbol->left);
			cout<<arbol->signo;
			imprimir(arbol->right);
			}
	}
	Derivar(string algo){
		signo=algo;
		left=nullptr;
		right=nullptr;
	}
	Derivar(string antes,string algo,string despues){
		signo=algo;
		left=new Derivar(antes);
		right=new Derivar(despues);
	}
	Derivar(Derivar & antes,string algo,Derivar & despues){
		signo=algo;
		left=&antes;
		right=&despues;
	}
	Derivar(Derivar & antes,string algo,string despues){
		signo=algo;
		left=&antes;
		right=new Derivar(despues);
	}
	Derivar(string antes,string algo,Derivar& despues){
		signo=algo;
		left=new Derivar(antes);
		right=&despues;
	}
};
int main(){
Derivar g("*");
Derivar x("x");
Derivar h("2");
Derivar j(h,"*",x);
Derivar k(j,"^",h);
k.imprimir();
}
