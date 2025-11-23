// Tamagochi.hpp
#ifndef TAMAGOTCHI_HPP
#define TAMAGOTCHI_HPP

#include <ctime>
#include "inventario.hpp"

class Tamagotchi {
protected:
    const char* Nombre;

    // Atributos de la mascota
    int Hambre;
    int Felicidad;
    int Energia;
    int Salud;
    int Dinero;
    int Estado;

    // Modificadores derivados del nombre
    int modHambre;
    int modEnergia;
    int modFelicidad;
    int DanoPerCritico;

    // Temporizadores independientes para cada necesidad
    time_t lastHambreUpdate;
    time_t lastFelicidadUpdate;
    time_t lastEnergiaUpdate;
    time_t lastEnergiaRecuperacion;

    // Temporizador para eventos aleatorios
    time_t lastEventoUpdate;
    int tiempoProximoEvento;
    bool eventoActivo;

    // Tiempo base y tiempo actual con aleatoriedad
    int tiempoBaseHambre;
    int tiempoBaseFelicidad;
    int tiempoBaseEnergia;

    int tiempoHambre;
    int tiempoFelicidad;
    int tiempoEnergia;

    Inventario inventario;

    // Funciones internas
    int calcularBaseNombre(const char* nombre);
    int generarTiempoAleatorio(int base, int maxExtra);
    int calcularDanoProporcional(int valor);
    void recuperarEnergia();
    void eventoAleatorio();

public:
    Tamagotchi(const char* nombre);
    
    void alimentar();
    void jugar();
    void dormir();  

    Inventario* getInventario();

    bool estaVivo() const;

    void aplicarModAndTik();

    void EstadoAnimacion();
};

#endif

