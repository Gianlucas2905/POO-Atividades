#include <iostream>
#include <string>
using namespace std;

class SensorNivel {
private:
    string tag;
    double minimo;
    double maximo;
    double valorAtual;

public:
    // Construtor mínimo 
    SensorNivel(string tagSensor)
        : tag(tagSensor), minimo(0.0), maximo(100.0), valorAtual(0.0) {}

    // Construtor completo
    SensorNivel(string tagSensor, double min, double max, double valorInic)
        : tag(tagSensor), minimo(min), maximo(max), valorAtual(valorInic) {
        // Evita estado absurdo: garante que o valor inicial não exceda os limites
        if (valorInic < min){
            valorAtual = min;
        } 
        else if (valorInic > max){
            valorAtual = max;
        }
        else {
            valorAtual = valorInic;
        }
    }

    void exibirResumo() const {
        cout << "[SensorNivel] " << tag
             << " | faixa: " << minimo << " a " << maximo
             << " | valor atual: " << valorAtual << "\n";
    }
};

class Bomba {
private:
    string tag;
    double velocidade;

public:
    // Construtor mínimo
    Bomba(string tagBomba)
        : tag(tagBomba), velocidade(0.0) {}

    // Construtor completo
    Bomba(string tagBomba, double velInicial)
        : tag(tagBomba), velocidade(velInicial) {
        // Evita estado absurdo: velocidade não pode ser negativa
        if(velocidade < 0.0) {
            velocidade = 0.0;
        }
    }

    void exibirResumo() const {
        cout << "[Bomba] " << tag
             << " | velocidade: " << velocidade << "%\n";
    }
};

class ControladorTanque {
private:
    string tag;
    double setpoint;
    double kp;

public:
    // Construtor mínimo
    ControladorTanque(string tagControlador)
        : tag(tagControlador), setpoint(50.0), kp(1.0) {}

    // Construtor completo
    ControladorTanque(string tagControlador, double sp, double ganhoProporcional)
        : tag(tagControlador), setpoint(sp), kp(ganhoProporcional) {}

    void exibirResumo() const {
        cout << "[ControladorTanque] " << tag
             << " | SP=" << setpoint
             << " | Kp=" << kp << "\n";
    }
};

int main() {
    cout << "--- Inicializando Gemeos Digitais ---\n\n";

    // Criando objetos usando o construtor mínimo
    SensorNivel sn1("LT-401"); 
    Bomba b1("P-101A");  
    ControladorTanque ct1("LIC-401"); 

    // Criando objetos usando o construtor completo
    SensorNivel sn2("LT-402", 0.0, 5000.0, 2780.0); 
    Bomba b2("P-101B", 60.5); 
    ControladorTanque ct2("LIC-402", 2500.0, 2.5);

    cout << "----------Sensores de Nivel----------\n";
    sn1.exibirResumo();
    sn2.exibirResumo();
    cout << "-------------------------------------\n";
    
    cout << "--------------Bomba------------------\n";
    b1.exibirResumo();
    b2.exibirResumo();
    cout << "-------------------------------------\n";
    
    cout << "-------Controladores de Tanque-------\n";
    ct1.exibirResumo();
    ct2.exibirResumo();
    cout << "-------------------------------------\n";

    return 0;
}