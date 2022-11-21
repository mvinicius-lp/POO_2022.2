/*
A atividade esta passando em todos os casos de teste.
Pedi ajuda a um colega que já havia cursado POO anteriormente (Petrúcio), assiste a playlist do YT e vi alguns conteúdos na net.
Consegui pegar bem o que a tarefa estava propondo, e aprimorei meus conhecimentos em outras bibliotecas.
Gastei em média umas 4 horas para conseguir solucionar a questão.
*/
#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>
#include <aux.hpp>

enum Cents {C10, C25, C50, C100};

class Coin {
    float value;
    int volume;
    std::string label;

public:
    Coin(Cents v) { 
        switch (v) {
            case C10: value = 0.10; volume = 1; label = "C10"; break;
            case C25: value = 0.25; volume = 2; label = "C25"; break;
            case C50: value = 0.50; volume = 3; label = "C50"; break;
            case C100: value = 1.0; volume = 4; label = "C100"; break;
        }
    }
    float getValue() const { 
        return value; 
    }
    int getVolume() const { 
        return volume; 
    }
    std::string getLabel() const { 
        return label; 
    }
};


class Item {
    std::string label;
    int volume;

public:
    Item(std::string label, int volume) {
        this->label = label;
        this->volume = volume;
    }

    int getVolume() const {
        return this->volume;
    }

    std::string getLabel() const {
        return this->label;
    }

    void setVolume(int volume) {
        this->volume = volume;
    }

    void setLabel(std::string label) {
        this->label = label;
    }

    std::string str() const {
        return this->label;
    }
};

std::ostream& operator<<(std::ostream& os, const Item& item) {
    return os << item.str();
}

class Pig {
    std::vector<std::string> itens;
    double value {0};
    int volume {0};
    int volumeMax {0};
    bool broken {false};

public:
    Pig(int volumeMax = 0) {
        this->volumeMax = volumeMax;
    }
    
    bool addCoin(Coin coin) {
        if (this->broken) {
            std::cout << "fail: the pig is broken\n";
            return false;
        }

        if (this->volume + coin.getVolume() > this->volumeMax) {
            std::cout << "fail: the pig is full\n";
            return false;
        }

        this->volume += coin.getVolume();
        this->value += coin.getValue();
        return true;
    }

    bool addItem(Item item) {
        if (this->broken) {
            std::cout << "fail: the pig is broken\n";
            return false;
        }

        if (this->volume + item.getVolume() > this->volumeMax) {
            std::cout << "fail: the pig is full\n";
            return false;
        }

        this->itens.push_back(item.getLabel());
        this->volume += item.getVolume();
        return true;
    }

    bool breakPig() {
        if (this->broken) {
            std::cout << "fail: the pig is broken\n";
            return false;
        }

        this->broken = true;
        this->volume = 0;
        return true;
    }

    double getCoins() {
        if (!this->broken) {
            std::cout << "fail: you must break the pig first\n";
            return 0.0;
        }
        
        return std::exchange(this->value, 0.0);
    }

    std::string getItems() {
        if (!this->broken) {
            std::cout << "fail: you must break the pig first\n";
            return "[]";
        }
        
        std::string out = (this->itens | aux::FMT());
        this->itens.clear();
        return out;
    }

    std::string str() const {
        std::stringstream ss;
        ss << (this->itens | aux::FMT()) << " : "
           << std::fixed << std::setprecision(2) << value << "$ : "
           << volume <<  "/" << volumeMax << " : " 
           <<  (broken ? "broken" : "unbroken");
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, const Pig& pig) {
    return os << pig.str();
}

int main() {
    aux::Chain chain;
    aux::Param par;

    Pig pig;
    
    auto toint = aux::STR2<int>();
    auto fmtdouble = aux::PIPE(LAMBDA(x, x | aux::STR("%.2f")));

    chain["addCoin"] = [&]() { 
        if      (par[1] == "10") pig.addCoin(Coin(C10));
        else if (par[1] == "25") pig.addCoin(Coin(C25));
        else if (par[1] == "50") pig.addCoin(Coin(C50));
        else if (par[1] == "100") pig.addCoin(Coin(C100));
    };
    chain["init"]     = [&]() { pig = Pig(toint(par[1])); };
    chain["addItem"]  = [&]() { pig.addItem(Item(par[1], toint(par[2]))); };
    chain["break"]    = [&]() { pig.breakPig(); };
    chain["getCoins"] = [&]() { pig.getCoins() | fmtdouble | aux::PRINT(); };
    chain["getItems"] = [&]() { pig.getItems() | aux::PRINT(); };
    chain["show"]     = [&]() { pig.str()      | aux::PRINT(); };

    aux::execute(chain, par);
}
