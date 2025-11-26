#include "Inventario.hpp"

Pou::Pou(const char* nombre) : Tamagotchi(nombre) {
    necesidad_dormir = 30;
}

Pou::~Pou() {
}

Gato::Gato(const char* nombre) : Tamagotchi(nombre) {
    limpieza_arenero = 50;
}

Gato::~Gato() {
}

void Gato::aplicar_adicional_TK() {
}
