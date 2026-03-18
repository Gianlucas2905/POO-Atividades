#include <iostream>
#include <string>
using namespace std;

class Car {
  private:
    float velocidade_instantanea = 0;

  public:
    string marca = "VOLKSWAGEN";
    string modelo = "GOL G5";
    int ano = 2011;

    void acelerar(float taxa_de_aceleracao) {
        velocidade_instantanea += taxa_de_aceleracao;
    }

    float getVelocidade() {
        return velocidade_instantanea;
    }
};

int main() {
  Car meuCarro;

  cout << "Veiculo: " << meuCarro.marca << " " << meuCarro.modelo << " (" << meuCarro.ano << ")\n";
  cout << "Velocidade instantanea: " << meuCarro.getVelocidade() << " km/h\n";
  meuCarro.acelerar(20.5);
  cout << "Velocidade instantanea: " << meuCarro.getVelocidade() << " km/h\n";
  meuCarro.acelerar(15.0); 
  cout << "Velocidade instantanea: " << meuCarro.getVelocidade() << " km/h\n";
  meuCarro.acelerar(4.5);  
  cout << "Velocidade instantanea: " << meuCarro.getVelocidade() << " km/h\n";
  
  return 0;
}
