#include<iostream>
#include<set>
using namespace std;
  set<char> signos;
  char my[]={'(','['};
  set<char> abirt(my,my+2);
  char ced[]={')',']'};
  set<char> cerrados(ced,ced+2);
struct Derivar{
	string signo;
	Derivar *left,*right;
	void imprimir(){
		Derivar* prueba=this;
		imprimir(prueba);
	}
	string tostring(){
		Derivar* prueba=this;
		return tostring(prueba);
	}
	void imprimir(Derivar* & arbol){
		if(arbol->left==nullptr)
			cout<<arbol->signo;
		else{
			imprimir(arbol->left);
			cout<<arbol->signo;
			imprimir(arbol->right);
			}
	}
	string tostring(Derivar* & arbol){
		if(arbol->left==nullptr)
			return arbol->signo;
		else{
			return tostring(arbol->left)+(arbol->signo)+tostring(arbol->right);
			}
	}
	Derivar(string algo){
    cout<<"se construira\n";
		stringtotree(algo);
    cout<<"se construyo\n";
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
  void stringtotree(string palabra){
    if(palabra.size()==1){
      signo=palabra;
      left=nullptr;
      right=nullptr;
    }
    else{
      bool primersigno=true;
      char firstsign;
      int indexfirstsign;
      int corchabirt=0;
      for(size_t i=0;i<palabra.size();i++){
        cout<<palabra[i]<<endl;
        if(abirt.count(palabra[0])==1 && cerrados.count(palabra.back())==1){
          cout<<" primer y ultimo parentesis";
          stringtotree(palabra.substr(1,palabra.size()-2));
          break;
        }
        else if(abirt.count(palabra[i])==1){
          cout<<"else if(abirt.count(palabra[i])==1){"<<endl;
          corchabirt++;
          while(corchabirt!=0){
            i++;
            if(abirt.count(palabra[i])==1){
              corchabirt++;
            }
            else if(cerrados.count(palabra[i])==1){
              corchabirt--;
            }
          }
          cout<<palabra.substr(0,i)<<endl;
        }
        else if(signos.count(palabra[i])==1){
          cout<<"else if(signos.count(palabra[i])==1){";
          if(primersigno){
            primersigno=false;
            firstsign=palabra[i];
            indexfirstsign=i;
            cout<<"indexfirstsign:  "<<i<<endl;
          }
          if (palabra[i]=='-' || palabra[i]=='+'){
            cout<<"palabra[i]=='-' || palabra[i]=='+'";
            signo=palabra[i];
            left=new Derivar(palabra.substr(0,i));
            right=new Derivar(palabra.substr(i+1,palabra.size()-2));
            break;
          }
        }
        if(i==palabra.size()-1){
          cout<<"i==palabra.size()-1  "<<endl;
          signo=firstsign;
          cout<<palabra[i]<<endl;
          cout<<palabra.substr(0,indexfirstsign)<<signo<<palabra.substr(indexfirstsign+1,palabra.size()-2)<<endl;
          left=new Derivar(palabra.substr(0,indexfirstsign));
          right=new Derivar(palabra.substr(indexfirstsign+1,palabra.size()-2));
        }
      }
    }
  }
};
int main(){
  signos.insert('-');
  signos.insert('+');
  signos.insert('*');
  signos.insert('/');
  signos.insert('^');
string fx="((x^2-8x)^1/2)x/4x+5";
Derivar g(fx);
//cout<<fx[1]<<endl;
g.imprimir();
}
