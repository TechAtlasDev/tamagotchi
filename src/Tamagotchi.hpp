#ifndef TAMAGOTCHI_HPP
#define TAMAGOTCHI_HPP

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class Tamagotchi {
    protected:
        char* nombre;
        int felicidad = 50;
        int energia = 50;
        int salud = 100;
        int dinero = 0;
        
        time_t ultima_recuperacion = 0;
        time_t ultimo_evento = 0;
        
        int seed_aleatorio = 0;
        void calcular_seed();

    public:
        Tamagotchi(const char* n);
        virtual ~Tamagotchi();

        const char* getNombre() const;
        int getFelicidad() const;
        int getEnergia() const;
        int getSalud() const;
        int getDinero() const;

        virtual void comer();
        virtual void jugar();
        virtual void dormir();
        virtual void trabajar();
        
        void actualizar();
        bool estaVivo() const;
        void mostrar_estado() const;
};

#endif
