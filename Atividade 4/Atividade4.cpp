#include <iostream>
#include <string>

using namespace std;

class AtivoCampo {
// private: Protege o estado critico (tag inalteravel e bloqueio controlado).
private:
    string tag;
    bool bloqueado;

// protected: Permite o reuso de 'area' apenas pelas classes derivadas.
protected:
    string area;

    void redefinirArea(string novaArea) {
        area = novaArea;
    }

// public: Interface de uso externo e seguro do objeto.
public:
    AtivoCampo(string novaTag, string novaArea)
        : tag(novaTag), bloqueado(false), area(novaArea) {}

    string getTag() const {
        return tag;
    }

    bool estaBloqueado() const {
        return bloqueado;
    }

    void bloquear() {
        bloqueado = true;
    }

    void liberar() {
        bloqueado = false;
    }
};

class SensorNivel : public AtivoCampo {
// private: Oculta detalhes internos do sensor, forçando o uso de metodos validadores.
private:
    double nivelAtual;
    double limiteAlto;

public:
    SensorNivel(string novaTag, string novaArea, double novoLimiteAlto)
        : AtivoCampo(novaTag, novaArea), nivelAtual(0.0), limiteAlto(novoLimiteAlto) {}

    void atualizarNivel(double novoNivel) {
        if (estaBloqueado()) {
            return;
        }

        if (novoNivel < 0.0) {
            novoNivel = 0.0; // Satura em 0 (nao aceita negativo)
        }

        nivelAtual = novoNivel;
    }

    void exibirResumo() const {
        cout << "[SensorNivel] " << getTag()
             << " | area: " << area // Acesso direto permitido pelo protected da base
             << " | nivel: " << nivelAtual
             << " | limite alto: " << limiteAlto << "\n";
    }

    // friend: Permite que uma funcao externa acesse atributos private para inspecao tecnica.
    friend void inspecionarSensor(const SensorNivel& sensor);
};

void inspecionarSensor(const SensorNivel& sensor) {
    cout << "[Inspecao] " << sensor.getTag()
         << " | nivel interno: " << sensor.nivelAtual
         << " | limite interno: " << sensor.limiteAlto << "\n";
}

class BombaDosadora : public AtivoCampo {
// private: Protege o setpoint da vazao, garantindo que fique entre 0 e 100 via metodos.
private:
    double vazaoPercentual;

public:
    BombaDosadora(string novaTag, string novaArea)
        : AtivoCampo(novaTag, novaArea), vazaoPercentual(0.0) {}

    void ajustarVazao(double novaVazao) {
        if (estaBloqueado()) {
            return;
        }

        if (novaVazao < 0.0) {
            novaVazao = 0.0;
        }

        if (novaVazao > 100.0) {
            novaVazao = 100.0;
        }

        vazaoPercentual = novaVazao;
    }

    void moverParaArea(string novaArea) {
        redefinirArea(novaArea); // Reuso do metodo protected da base
    }

    void exibirResumo() const {
        cout << "[BombaDosadora] " << getTag()
             << " | area: " << area
             << " | vazao: " << vazaoPercentual << "%\n";
    }
};

int main() {
    // Valores alterados aqui na criacao dos objetos
    SensorNivel sensor("SN-102", "Tanque de Decantacao", 95.0);
    BombaDosadora bomba("BD-005", "Tratamento Quimico");

    // Passando novos valores para teste
    sensor.atualizarNivel(78.4);
    bomba.ajustarVazao(82.5);
    bomba.moverParaArea("Setor de Manutencao");

    sensor.exibirResumo();
    bomba.exibirResumo();
    inspecionarSensor(sensor);

    return 0;
}