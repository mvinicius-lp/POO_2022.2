/* Fiz a atividade sozinho com base no material que o professor disponibilizou no YT, 
pesquisas no stack overflow, dentre outros.
Gostei bastante da atividade e o que é proposta por ela e creio que consigo replica-la.
e tempo codando. Pode melhorar minha lógica e forma de resolver os problemas.
Gastei em média umas 6 horas entre pesquisa
*/
#include <iostream>
#include <sstream>
#include <memory>
#include <aux.hpp>

class Person {
    std::string name;
    int age;

public:
    Person(std::string name = "", int age = 0) {
        this->name = name;
        this->age = age;
    }

    Person(int age) {
        this->name = "";
        this->age = age;
    }

    int getAge() {
        return this->age;
    }
    std::string getName() {
        return this->name;
    }
    std::string str() {
        std::stringstream ss;
        ss << this->name << ":" << this->age;
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, Person& p) {
    return os << p.str();
}

class Motorcycle {
    std::shared_ptr<Person> person {nullptr};
    int time {0};
    int power {1};

public:
    Motorcycle(int power = 1) {
        this->power = power;
    }

    bool insertPerson(std::shared_ptr<Person> p) {
        if (this->person != nullptr) {
            std::cout << "fail: busy motorcycle\n";
            return false;
        }

        this->person = p;
        return true;
    }

    std::string honk() {
        std::stringstream ss;
        ss << "P";
        for (int i = 0; i < this->power; i++)
            ss << "e";
        ss << "m";

        return ss.str();
    }

    std::shared_ptr<Person> remove() {
        if (this->person == nullptr) {
            std::cout << "fail: empty motorcycle\n";
        }
        
        return std::exchange(this->person, nullptr);
    }

    void buyTime(int time) {
        this->time += time;
    }

    void drive(int time) {
        if (this->time == 0) {
            std::cout << "fail: buy time first\n";
            return;
        }

        if (this->person == nullptr) {
            std::cout << "fail: empty motorcycle\n";
            return;
        }

        if (this->person->getAge() <= 10) {
            this->time -= time;

            if (this->time < 0) {
                std::cout << "fail: time finished after " << (-1 * this->time) << " minutes\n";
                this->time = 0;
            }
        } else {
            std::cout << "fail: too old to drive\n";
        }
    }

    std::string str() {
        std::ostringstream os;
        os << "power:" << power << ", time:" << time;
        os << ", person:(" << (person == nullptr ? "empty" : person->str()) << ")";
        return os.str();
    }
};

std::ostream& operator<<(std::ostream& os, Motorcycle m) {
    return os << m.str();
}


int main() {
    aux::Chain chain;
    aux::Param param;

    Motorcycle m(1);

    auto INT = aux::to<int>;

    chain["show"]  = [&]() { m | aux::PRINT(); };
    chain["leave"] = [&]() { 
        auto person = m.remove(); 
        if (person != nullptr) {
            *person | aux::PRINT();
        }
    };
    chain["honk"]  = [&]() { m.honk()  | aux::PRINT(); };
    chain["init"]  = [&]() { m = Motorcycle(INT(param.at(1)));};
    chain["enter"] = [&]() { m.insertPerson(std::make_shared<Person>(param.at(1), INT(param.at(2)))); };
    chain["buy"]   = [&]() { m.buyTime(INT(param.at(1))); };
    chain["drive"] = [&]() { m.drive  (INT(param.at(1))); };

    aux::execute(chain, param);
}

