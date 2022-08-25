#include <iostream>

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

int posicao_primeiro_homem(int vet[], int tam){
    int pos = 0;
    for(int i = 0; i < tam; i++){
        if(vet[i] > 0){
            pos = i;
            break;
        }
    }
    return pos;
}

int posicao_menor_valor(int vet[], int tam){
    int aux = vet[0];
    int pos = 0;
    for(int i = 0; i < tam; i++){
        if(aux > vet[i]){
            aux = vet[i];
            pos = i;
        }
    }
    return pos;
}

int homem_mais_calmo(int vet[], int tam){
    int aux = vet[0], pos {};
    for(int i = 0; i < tam ; i++){
        if(vet[i] > 0 && vet[i] < aux){
            aux = vet[i];
            pos = i;
        }
    }
    return pos;
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

int mediaStress(int vet[], int tam){
    int soma = 0;
    for(int i = 0; i < tam; i++){
        soma = soma + vet[i];
    }
    return soma/tam;
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
        cout << "empate" << endl;
    }else if(primeira > segunda){
        cout << "primeira" << endl;
    }else{
        cout << "segunda" << endl;
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
        cout << "existe a mesma quantidade de homens e melheres\n";
    }else if(contM > contH){
        cout << "existe mais mulheres\n";
    }else{
        cout << "existe mais homens\n";
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
        cout << "estresse medio iguais\n";
    }else if(mediaM_absoluto > mediaH){
        cout << "em media mulheres mais estressadas\n";
    }else{
        cout << "em media homens mais estressados\n";
    }
}

int main (){
    int tam;
    int x;
    cout << "digite o tamanho: ";
    cin >> tam;
    int vet[tam];

    cout << "preencha o vetor" << endl;
    for(int i = 0; i < tam; i++){
        cin >> vet[i];
    }
    cout << "digite um elemento: ";
    cin >> x;

    //verifica se existe x
   if(existe(vet, tam, x) == true){
        cout << "existe" << endl;
   }else{
    cout << x << " nao existe" << endl;
   }

    //verifica qual posição
    if(posicao(vet, tam, x) > 0){
        cout << "aparece na posicao: " << posicao(vet, tam, x) << endl;
    }

    //posicao do primeiro homem da fila
    cout << "o primeiro homem aparece na posicao: " << posicao_primeiro_homem(vet, tam) << endl;

    //posicao do menor valor
    cout << "o menor valor ta na posicao: " << posicao_menor_valor(vet, tam) << endl;

    //verifica homem mais calmo
    cout << "o homem mais calmo ta na posicao: " << homem_mais_calmo(vet, tam) << endl;

    //quantas vezes X aparece na fila
    cout << "X aparece " << quantosX(vet, tam, 3) << " vezes na fila\n";

    //estress medio
    cout << "o stress medio e: " << mediaStress(vet, tam) << endl;

    //qual metade é mais estressada
    metade_mais_estressada(vet, tam);

    //mais homems ou mulheres
    mais_homem_ou_mulher(vet, tam);

    //media mais estressada
    media_mais_estressada(vet, tam);
}