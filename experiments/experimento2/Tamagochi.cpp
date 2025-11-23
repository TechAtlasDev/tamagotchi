// Tamagochi.cpp
#include "Tamagochi.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

// Constructor
Tamagotchi::Tamagotchi(const char* nombre)
{
    Nombre = nombre;

    Hambre = 100;
    Felicidad = 100;
    Energia = 100;
    Salud = 100;
    Dinero = 0;
    Estado = 0;

    int base = calcularBaseNombre(nombre);

    // Modificadores de atributos
    modHambre    = 1 + (base % 3); 
    modEnergia   = 1 + (base % 2); 
    modFelicidad = 1 + (base % 4); 
    DanoPerCritico = 10 + (base % 5); 

    // Tiempos base
    tiempoBaseHambre    = 40;
    tiempoBaseFelicidad = 45;
    tiempoBaseEnergia   = 50;

    // Inicializar timers
    lastHambreUpdate    = time(NULL);
    lastFelicidadUpdate = time(NULL);
    lastEnergiaUpdate   = time(NULL);
    lastEnergiaRecuperacion = time(NULL);
    lastEventoUpdate    = time(NULL);

    // Generar tiempos iniciales aleatorios
    tiempoHambre    = generarTiempoAleatorio(tiempoBaseHambre, base % 20 + 1);
    tiempoFelicidad = generarTiempoAleatorio(tiempoBaseFelicidad, base % 10 + 1);
    tiempoEnergia   = generarTiempoAleatorio(tiempoBaseEnergia, base % 15 + 1);
    tiempoProximoEvento = generarTiempoAleatorio(60, 240); 
    eventoActivo = true;
}

// Funcion para calcular la "base" del nombre sumando los códigos ASCII
int Tamagotchi::calcularBaseNombre(const char* nombre) {
    int base = 0;
    for (int i = 0; nombre[i] != '\0'; i++)
        base += (int)nombre[i];
    return base;
}

// Funcion para generar un tiempo aleatorio entre base y base + maxExtra
int Tamagotchi::generarTiempoAleatorio(int base, int maxExtra) {
    return base + (rand() % maxExtra);
}

// Método para alimentar la mascota
void Tamagotchi::alimentar()
{
    if (Hambre >= 100) {
        cout << "La mascota no necesita comer por ahora.\n";
        return;
    }

    Hambre += 20;
    if (Hambre > 100) Hambre = 100;

    // Recuperar salud al alimentarla
    if (Salud < 100) {
        Salud += 10;
        if (Salud > 100) Salud = 100;
        cout << Nombre << " ha recuperado salud al comer!\n";
    }

    // Reiniciar temporizador de hambre
    tiempoHambre = generarTiempoAleatorio(tiempoBaseHambre, 20);
    lastHambreUpdate = time(NULL);

    cout << "Has alimentado a " << Nombre << ". Tiempo hasta próxima hambre: " << tiempoHambre << "s\n";
}

// Metodo para jugar con la mascota :D
void Tamagotchi::jugar()
{
    if (Felicidad >= 100) {
        cout << "La mascota no necesita jugar por ahora.\n";
        return;
    }

    Felicidad += 20;
    if (Felicidad > 100) Felicidad = 100;

    Energia -= 10;
    if (Energia < 0) Energia = 0;

    // Reiniciar los tiempos 
    tiempoFelicidad = generarTiempoAleatorio(tiempoBaseFelicidad, 10);
    lastFelicidadUpdate = time(NULL);
    tiempoEnergia = generarTiempoAleatorio(tiempoBaseEnergia, 15);
    lastEnergiaUpdate = time(NULL);

    cout << Nombre << " ha jugado. Tiempo hasta próxima felicidad: " << tiempoFelicidad 
         << "s, tiempo hasta próxima energía: " << tiempoEnergia << "s\n";
}

// Recuperacion pasiva de energía cada 60 segundos
void Tamagotchi::recuperarEnergia()
{
    time_t ahora = time(NULL);
    if (difftime(ahora, lastEnergiaRecuperacion) >= 60) {
        Energia += 5;
        if (Energia > 100) Energia = 100;
        lastEnergiaRecuperacion = ahora;
    }
}

// Calcular daño proporcional según atributo
int Tamagotchi::calcularDanoProporcional(int valor)
{
    if (valor == 0) return DanoPerCritico;
    else if (valor <= 20) return 20;
    else if (valor <= 50) return 15;
    else if (valor <= 80) return 10;
    else return 5;
}

// Eventos aleatorios
void Tamagotchi::eventoAleatorio()
{
    if (!eventoActivo) return;

    int tipoEvento = rand() % 4; // 0 a 3
    switch(tipoEvento) {
        case 0:
            Felicidad += 10;
            if (Felicidad > 100) Felicidad = 100;
            cout << Nombre << " encontró un juguete! Felicidad +10\n";
            break;
        case 1:
            Energia -= 5;
            if (Energia < 0) Energia = 0;
            cout << Nombre << " se cansó jugando solo. Energia -5\n";
            break;
        case 2:
            Salud -= 5;
            if (Salud < 0) Salud = 0;
            cout << Nombre << " se resfrió! Salud -5\n";
            break;
        case 3:
            Hambre -= 5;
            if (Hambre < 0) Hambre = 0;
            cout << Nombre << " tiene hambre repentina! Hambre -5\n";
            break;
    }

    tiempoProximoEvento = generarTiempoAleatorio(60, 240); // 1-5 min
    eventoActivo = false;
}

// Metodo principal que aplica ticks y modificaciones
void Tamagotchi::aplicarModAndTik()
{
    time_t ahora = time(NULL);

    // Revisar temporizadores de atributos
    if (difftime(ahora, lastHambreUpdate) >= tiempoHambre) {
        Hambre -= modHambre;
        if (Hambre < 0) Hambre = 0;
        lastHambreUpdate = ahora;
    }

    if (difftime(ahora, lastFelicidadUpdate) >= tiempoFelicidad) {
        Felicidad -= modFelicidad;
        if (Felicidad < 0) Felicidad = 0;
        lastFelicidadUpdate = ahora;
    }

    if (difftime(ahora, lastEnergiaUpdate) >= tiempoEnergia) {
        Energia -= modEnergia;
        if (Energia < 0) Energia = 0;
        lastEnergiaUpdate = ahora;
    }

    // Recuperacion pasiva de energia
    recuperarEnergia();

    // Muerte instantanea si hambre o felicidad llegan a 0
    if (Hambre == 0 || Felicidad == 0) {
        Salud = 0;
    } else {
        // Daño proporcional por atributos
        int dano = 0;
        dano += calcularDanoProporcional(Hambre);
        dano += calcularDanoProporcional(Felicidad);
        dano += calcularDanoProporcional(Energia);
        Salud -= dano;
        if (Salud < 0) Salud = 0;
    }

    // Revisar eventos
    if (difftime(ahora, lastEventoUpdate) >= tiempoProximoEvento) {
        eventoActivo = true;
        lastEventoUpdate = ahora;
        eventoAleatorio();
    }
}

// Accesores simples
Inventario* Tamagotchi::getInventario() { 
    return &inventario; 
}
bool Tamagotchi::estaVivo() { 
    return Salud > 0; 
}
void Tamagotchi::EstadoAnimacion() {
    // Encargate Giovany de esto XD
}
