#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#include "Tamagotchi.hpp"

class Pou : public Tamagotchi {
    private:
        int necesidad_dormir = 0;

    public:
        Pou(const char* nombre);
        virtual ~Pou();
};

class Gato : public Tamagotchi {
    private:
        int limpieza_arenero = 0;

    public:
        Gato(const char* nombre);
        virtual ~Gato();
        void aplicar_adicional_TK();
};

#endif
