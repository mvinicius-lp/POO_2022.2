/*
Fiz a atividade sozinho, com base na atividade passada realizei a estruturação dessa
e pude resolve-la. Com essa atividade tive a oportunidade de aprender a utilizar a biblioteca iomanip, 
mais precisamente o setprecision, aprimorar a lógica de resolução bem como toda a parte algébrica do problema
e a manipulação dos tipos de variáveis. Gastei em média umas 4 horas desde o entendimento, pesquisa e implementação
do código em si.
*/
#include <iostream>
#include <iomanip>

using namespace std;

struct Calculadora{
    int bateria = 0;
    float display = 0;
    int bateriaMax = 0;

    void soma(){
        int val1 = 0, val2 = 0;
            cin >> val1;
            cin >> val2;
        if(this->bateria == 0){
          cout << "$sum " << val1 << " " << val2 << endl;
          cout << "fail: bateria insuficiente\n";
        }else{
            this->display = val1 + val2;
            cout << "$sum " << val1 << " " << val2 << endl;
            this->bateria -= 1;
        }
    }

    void div(){
      int val1 = 0, val2 = 0;
      float div = 0;
      cin >> val1;
      cin >> val2;
      
      if(this->bateria == 0){
          cout << "$div " << val1 << " " << val2 << endl;
          cout << "fail: bateria insuficiente\n";
      }
      else if(val2 == 0){
        cout << "$div " << val1 << " " << val2 << endl;
        cout <<"fail: divisao por zero\n";
        this->bateria -= 1;
      }else{
        cout << "$div " << val1 << " " << val2 << endl;
        div = (float)val1/val2;
        this->display = div;
        this->bateria -= 1;
      }
    }
    void init(){
      this->bateria = 0;
      int val = 0;
      cin >> val;
      this->bateriaMax = val;
      cout << "$init " << val << endl;
    }
    
    void charge(){
        int val = 0;
        cin >> val;
        
        if(val >= this->bateriaMax){
            this->bateria = this->bateriaMax;
            cout << "$charge " << val << endl;
        }
        else if((this->bateria + val) >= this->bateriaMax){
            this->bateria = this->bateriaMax;
            cout << "$charge " << val << endl;
        }
        else{
            this->bateria += val;
            cout << "$charge " << val << endl;
        }
    }
    void show(){
        cout << "$show\n";
        cout << fixed << setprecision(2) << "display = " << this->display;
        cout << ", battery = " << this->bateria << endl;
    }
};


int main(){

    Calculadora * calculadora= new Calculadora();

    while (true){
      string cmd;
      cin >> cmd;

      if(cmd == "end"){
        delete calculadora;
        cout << "$end\n";
        break;
      }
      else if(cmd == "sum"){
        calculadora->soma();
      }
      else if(cmd == "show"){
        calculadora->show();
      }
      else if(cmd == "div"){
        calculadora->div();
      }
      else if(cmd == "init"){
        calculadora->init();
      }
      else if(cmd == "charge"){
        calculadora->charge();
      }
    }
}