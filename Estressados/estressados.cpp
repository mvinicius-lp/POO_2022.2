#include <iostream>
#include <iomanip>

using namespace std;

bool existe(int vet[], int tam, int x){
    int aux = false;
    for(int i = 0; i < tam; i++){
        if(vet[i] == x){
            aux = true;
        }
    }
    return aux;
}

int posicao(int vet[], int tam, int x){
    int pos = -1;
    for(int i = 0; i < tam; i++){
        if(vet[i] == x){
            pos = i;
        }
    }
    return pos;
}

void posicao_primeiro_homem(int vet[], int tam){
    int pos = 0;
    for(int i = 0; i < tam; i++){
        if(vet[i] > 0){
            pos = i;
            break;
        }
    }
    cout << pos << endl;
}

void posicao_menor_valor(int vet[], int tam){
    int aux = vet[0];
    int pos = 0;
    for(int i = 0; i < tam; i++){
        if(aux > vet[i]){
            aux = vet[i];
            pos = i;
        }
    }
    cout << pos << endl;
}

void homem_mais_calmo(int vet[], int tam){
    int aux = vet[0], pos {};
    for(int i = 0; i < tam ; i++){
        if(vet[i] > 0 && vet[i] < aux){
            aux = vet[i];
            pos = i;
        }
    }
    cout << pos << endl;
}

int quantosX(int vet[], int tam, int x){
    int cont = 0;
    for(int i = 0; i < tam; i++){
        if(vet[i] == x){
            cont += 1;
        }
    }
    return cont;
}

void mediaStress(int vet[], int tam){
    int soma1 = 0, soma2 = 0;
    float result = 0;
    for(int i = 0; i < tam; i++){
        if(vet[i] < 0){
            soma1 = soma1 + vet[i];
        }else{
            soma2 = soma2 + vet[i];
        }
    }
    soma1 * -1;
    int soma = soma1 + soma2;
    result  = (float)soma/tam;
    if(result < 0){
        cout << fixed << setprecision(2) << result * -1 << endl;
    }else{
        cout << fixed << setprecision(2) << result << endl;
    }
}

void metade_mais_estressada(int vet[], int tam){
    int metade = tam/2, primeira = 0, segunda = 0;
    for(int i = 0; i < metade; i++){
        primeira += vet[i];
    }
    for(int i = metade; i < tam; i++){
        segunda += vet[i];
    }
    if(primeira == segunda){
        cout << "draw" << endl;
    }else if(primeira > segunda){
        cout << "first" << endl;
    }else{
        cout << "second" << endl;
    }
}

void mais_homem_ou_mulher(int vet[], int tam){
    int contM = 0, contH = 0;
    for(int i = 0; i < tam; i++){
        if(vet[i] < 0){
            contM += 1;
        }else{
            contH += 1;
        }
    }
    if(contM == contH){
        cout << "draw\n";
    }else if(contM > contH){
        cout << "women\n";
    }else{
        cout << "men\n";
    }
}

void media_mais_estressada(int vet[], int tam){
    int mediaM = 0, mediaH = 0, mediaM_absoluto;
    for(int i = 0; i < tam; i++){
        if(vet[i] < 0){
            mediaM += vet[i];
        }else{
            mediaH += vet[i];
        }
    }
    mediaM_absoluto = mediaM * -1;
    if(mediaM_absoluto == mediaH){
        cout << "draw\n";
    }else if(mediaM_absoluto > mediaH){
        cout << "women\n";
    }else{
        cout << "men\n";
    }
}

void show(int vet[], int tam, int x, string cmd){
    cout << "$" << cmd << " " << "[";
    for(int i = 0; i < tam; i++){
        if(i != (tam - 1)){
            cout << vet[i] << ", ";
        }else{
            cout << vet[i];
        }
    }
    cout << "] " << x << endl;
}

void _show(int vet[], int tam, string cmd){
    cout << "$" << cmd << " " << "[";
    for(int i = 0; i < tam; i++){
        if(i != (tam - 1)){
            cout << vet[i] << ", ";
        }else{
            cout << vet[i];
        }
    }
    cout << "] " << endl;
}

void preenche(int vet[], int tam){
    for(int i = 0; i < tam; i++){
        cin >> vet[i];
    }
}

int main (){

    while (true){
        string cmd;
        cin >> cmd;

        if(cmd == "in"){
            int tam {};
            cin >> tam;
            int vet[tam];
            preenche(vet, tam);
            int el {};
            cin >> el;
            show(vet, tam, el, cmd);
            if(existe(vet, tam, el) == true){
                cout << true << endl;
            }else{
                cout << false << endl;
            }
        }
        else if(cmd == "index_of"){
            int tam {};
            cin >> tam;
            int vet[tam];
            preenche(vet, tam);
            int el {};
            cin >> el;
            show(vet, tam, el, cmd);
            if(posicao(vet, tam, el) > 0){
              cout << posicao(vet, tam, el) << endl;
            }
        }
        else if(cmd == "find_if"){
            int tam {};
            cin >> tam;
            int vet[tam];
            preenche(vet, tam);
            _show(vet, tam, cmd);
            posicao_primeiro_homem(vet, tam);
        }
        else if(cmd == "min_element"){
            int tam {};
            cin >> tam;
            int vet[tam];
            preenche(vet, tam);
            _show(vet, tam, cmd);
            posicao_menor_valor(vet, tam);
        }
        else if(cmd == "find_min_if"){
            int tam {};
            cin >> tam;
            int vet[tam];
            preenche(vet, tam);
            _show(vet, tam, cmd);
            homem_mais_calmo(vet, tam);
        }
        else if(cmd == "count"){
            int tam {};
            cin >> tam;
            int vet[tam];
            preenche(vet, tam);
            int el {};
            cin >> el;
            show(vet, tam, el, cmd);
            cout << quantosX(vet, tam, el) << endl;
        }
        else if(cmd == "average"){
            int tam {};
            cin >> tam;
            int vet[tam];
            preenche(vet, tam);
            _show(vet, tam, cmd);
            mediaStress(vet, tam);
        }
        else if(cmd == "half_compares"){
            int tam {};
            cin >> tam;
            int vet[tam];
            preenche(vet, tam);
            _show(vet, tam, cmd);
            metade_mais_estressada(vet, tam);
        }
        else if(cmd == "more_men"){
            int tam {};
            cin >> tam;
            int vet[tam];
            preenche(vet, tam);
            _show(vet, tam, cmd);
            mais_homem_ou_mulher(vet, tam);
        }
        else if(cmd == "sex_battle"){
            int tam {};
            cin >> tam;
            int vet[tam];
            preenche(vet, tam);
            _show(vet, tam, cmd);
            media_mais_estressada(vet, tam);
        }
        else if(cmd == "end"){
            break;
        }
    }
}