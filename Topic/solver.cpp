/*
Fiz a atividade com base nas explicações das aulas e com o conhecimento que eu já tinha de ED.
Estava tendo algumas dificuldades, mas fiz algumas adptaçoes para passar nos casos de teste e utilizei 
minha lógica e a maneira que achei mais fácil para resolver os problemas da questão.
Realizei a atividade sozinho com base em um material do YT e pude melhorar minha forma de pensar e resolver os 
problemas, gastei em torno de 5 horas resolvendo essa atividade.
Consegui passar em todos os casos de teste.
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <utility>
#include <aux.hpp>

class Pass {
    std::string id;
    int idade;

public:
    Pass(std::string id = "", int idade = 0  ){
        this->id = id;
        this->idade = idade;
    }

    bool isPref() {
        return idade >= 65;
    }

    std::string getId() {
        return id;
    }

    int getIdade() {
        return idade;
    }

    std::string str() {
        std::stringstream ss;
        ss << id << ":" << idade;
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, Pass p) {
    return os << p.str();
}

class Topic {
    std::vector<std::shared_ptr<Pass>> preferenciais;
    std::vector<std::shared_ptr<Pass>> normais;
    int qtdPref;

    static int procurarPorNome(std::string id, std::vector<std::shared_ptr<Pass>> &cadeiras) {
        for (int i = 0; i < cadeiras.size(); i++) {
            if (cadeiras[i] != nullptr && cadeiras[i]->getId() == id) {
                return i;
            }
        }

        return -1;
    }

    static int procurarVaga(std::vector<std::shared_ptr<Pass>> &cadeiras) {
        for (int i = 0; i < cadeiras.size(); i++) {
            if (cadeiras[i] == nullptr) {
                return i;
            }
        }

        return -1;
    }

    static int sentar(std::shared_ptr<Pass> pass, std::vector<std::shared_ptr<Pass>> &cadeiras) {
        int cadeira = Topic::procurarVaga(cadeiras);
        if (cadeira != -1) {
            cadeiras[cadeira] = pass;
        }

        return cadeira;
    }

    static std::shared_ptr<Pass> descer(std::string id, std::vector<std::shared_ptr<Pass>> &cadeiras) {
        int pessoa = Topic::procurarPorNome(id, cadeiras);
        if (pessoa != -1) {
            return std::exchange(cadeiras[pessoa], nullptr);
        }

        return nullptr;
    }
    
public:

    Topic(int lotacao = 0, int qtdPref = 0) {
        this->preferenciais = std::vector<std::shared_ptr<Pass>>(qtdPref, nullptr);
        this->normais = std::vector<std::shared_ptr<Pass>>(lotacao - qtdPref, nullptr);
    }

    bool subir(std::shared_ptr<Pass> pass) {
        if (Topic::procurarPorNome(pass->getId(), this->preferenciais) != -1 || Topic::procurarPorNome(pass->getId(), this->normais) != -1) {
            std::cout << "fail: " << pass->getId() << " ja esta na topic\n";
            return false;
        }

        if (pass->isPref()) {
            if (Topic::sentar(pass, this->preferenciais) != -1) {
                return true;
            }
        }

        if (Topic::sentar(pass, this->normais) != -1) {
            return true;
        } else if (!pass->isPref()) {
            if (Topic::sentar(pass, this->preferenciais) != -1) {
                return true;
            }
        }
        
        std::cout << "fail: topic lotada\n";
        return false;
    }

    std::shared_ptr<Pass> descer(std::string id) {
        auto pessoa = Topic::descer(id, this->preferenciais);
        if (pessoa != nullptr) {
            return pessoa;
        } else if ((pessoa = Topic::descer(id, this->normais)) != nullptr) {
            return pessoa;
        } else {
            std::cout << "fail: " << id << " nao esta na topic\n";
            return nullptr;
        }
    }

    std::string str() {
        std::stringstream ss;
        ss << "[";
        for (auto cadeira : this->preferenciais) {
            ss << "@" << (cadeira != nullptr ? cadeira->str() : "") << " ";
        }

        for (int i = 0; i < this->normais.size(); i++) {
            auto cadeira = this->normais[i];
            ss << "=" << (cadeira != nullptr ? cadeira->str() : "") << (i == this->normais.size() - 1 ? "" : " ");
        }
        ss << "]";

        return ss.str();
    }
};

int main(){
    aux::Chain chain;
    aux::Param param;
    Topic topic;

    chain["init"] = [&](){
        topic = Topic(aux::to<int>(param[1]), aux::to<int>(param[2]));
    };
    chain["show"] = [&](){
        std::cout << topic.str() << std::endl;
    };
    chain["in"] = [&](){
        topic.subir(std::make_shared<Pass>(param[1], aux::to<int>(param[2])));
    };
    chain["out"] = [&](){
        topic.descer(param[1]);
    };
    aux::execute(chain, param);
}
