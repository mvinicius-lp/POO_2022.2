/*
Assisti uma video aula no YT e em seguida fiz a atividade com base na explicação
do video, fiz usando minha lógica e a maneira que achei mais interessante para
resolver os problemas.
Realizei a atividade sozinho e pude melhorar minha forma de pensar e resolver os 
problemas, gastei em torno de 4 horas resolvendo essa atividade. 
*/

#include <iostream>

using namespace std;

struct Carro{
    int pessoas = 0;
    int maxPessoas = 2;
    float gasolina = 0;
    float maxgasolina = 100;
    int km = 0;

    bool enter(){
        cout << "$enter\n";
        if(this->pessoas >= this->maxPessoas){
            cout << "fail: limite de pessoas atingido\n";
            return false;
        }else if(this->pessoas < this->maxPessoas){
            this->pessoas += 1;
            return true;
        }
    }
    void leave(){
        cout << "$leave\n";
        if(this->pessoas <= 0){
            cout << "fail: nao ha ninguem no carro\n";
        }else if(this->pessoas > 0){
            this->pessoas -= 1;
        }
    }
    int show(){
        cout << "$show\n";
        cout << "pass: " << this->pessoas << ", gas: " << this->gasolina << ", km: "<< this->km << endl;
    }
    bool fuel(int qtd){
        if(this->gasolina < this->maxgasolina){
            if((this->gasolina + qtd) > 100){
                this->gasolina = 100;
                cout << "$fuel " << qtd << endl;
                return true;
            }else{
                this->gasolina = this->gasolina + qtd;
                cout << "$fuel " << qtd << endl;
                return true;
            }
        }
    }
    bool drive(int percorrer){
        cout << "$drive " << percorrer << endl;
        if(this->gasolina == 0){
            cout << "fail: tanque vazio\n";
            return false;
        }else if(this->pessoas == 0){
            cout << "fail: nao ha ninguem no carro\n";
            return false;
        }else if(this->pessoas > 0 && this->gasolina > 0){
                if(this->gasolina < percorrer){
                    cout << "fail: tanque vazio apos andar " << this->gasolina << " km\n";
                    this->km += this->gasolina;
                    this->gasolina = 0;
                }else{
                    this->gasolina = this->gasolina - percorrer;
                    this->km = percorrer;
            }
        }
    }
};

int main(){
    //Carro carro = Carro();
    Carro * carro= new Carro();
    
   while (true){
    string cmd;
    cin >> cmd;

     if(cmd == "end"){
            delete carro;
            cout << "$end\n";
            break;
        }
    else if(cmd == "enter"){
        carro->enter();
    }
    else if(cmd == "drive"){
        int dr = 0;
        cin >> dr;
        carro->drive(dr);
    }
    else if(cmd == "show"){
        carro->show();
    }
    else if(cmd == "fuel"){
        int fu = 0;
        cin >> fu;
        carro->fuel(fu);
    }
    else if(cmd == "leave"){
        carro->leave();
    }
   }   
   return 0;
};