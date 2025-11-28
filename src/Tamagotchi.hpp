#ifndef TAMAGOTCHI_HPP
#define TAMAGOTCHI_HPP

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class Tamagotchi {
    protected:
        char* nombre;
        int felicidad = 100;
        int energia = 100;
        int salud = 100;
        int dinero = 0;
        int hambre = 100;
        int estado = 0;
        
        time_t ultimo_hambre = 0;
        time_t ultima_felicidad = 0;
        time_t ultima_energia = 0;
        time_t ultima_recuperacion_energia = 0;
        time_t ultimo_evento = 0;

        int mod_hambre = 1;
        int mod_energia = 1;
        int mod_felicidad = 1;
        int dano_critico = 10;

        int tiempo_base_hambre = 40;
        int tiempo_base_felicidad = 45;
        int tiempo_base_energia = 50;

        int tiempo_hambre = 40;
        int tiempo_felicidad = 45;
        int tiempo_energia = 50;
        int tiempo_proximo_evento = 60;
        bool evento_activo = true;
        
        int seed_aleatorio = 0;
        void calcular_seed();
        int calcular_base_nombre(const char* nombre_base);
        int generar_tiempo_aleatorio(int base, int max_extra);
        int calcular_dano_proporcional(int valor);
        void recuperar_energia();
        void evento_aleatorio();

    public:
        Tamagotchi(const char* n);
        virtual ~Tamagotchi();

        const char* getNombre() const;
        int getFelicidad() const;
        int getEnergia() const;
        int getSalud() const;
        int getDinero() const;
        int getHambre() const;

        virtual void comer();
        virtual void jugar();
        virtual void dormir();
        virtual void trabajar();
        
        void aplicarModAndTik();
        void actualizar();
        bool estaVivo() const;
        void mostrar_estado() const;
};

#endif
