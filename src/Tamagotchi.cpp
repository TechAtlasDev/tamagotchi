#include "Tamagotchi.hpp"

// Función helper para obtener longitud de string
int get_strlen(const char* s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

// Función helper para copiar string
void copy_string(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

Tamagotchi::Tamagotchi(const char* n) {
    nombre = new char[get_strlen(n) + 1];
    copy_string(nombre, n);
    
    calcular_seed();
    ultima_recuperacion = time(nullptr);
    ultimo_evento = time(nullptr);
}

Tamagotchi::~Tamagotchi() {
    delete[] nombre;
}

void Tamagotchi::calcular_seed() {
    int suma = 0;
    for (int i = 0; nombre[i] != '\0'; i++) {
        suma += (int)nombre[i];
    }
    seed_aleatorio = suma;
    srand(seed_aleatorio);
}

const char* Tamagotchi::getNombre() const {
    return nombre;
}

int Tamagotchi::getFelicidad() const {
    return felicidad;
}

int Tamagotchi::getEnergia() const {
    return energia;
}

int Tamagotchi::getSalud() const {
    return salud;
}

int Tamagotchi::getDinero() const {
    return dinero;
}

void Tamagotchi::comer() {
    if (energia < 10) {
        energia += 5;
    } else {
        energia += 10;
    }
    
    if (energia > 100) {
        energia = 100;
    }
    
    if (salud < 100) {
        salud += 5;
    }
    if (salud > 100) {
        salud = 100;
    }
    
    dinero -= 5;
}

void Tamagotchi::jugar() {
    if (energia < 20) {
        energia -= 5;
        felicidad += 5;
    } else {
        energia -= 15;
        felicidad += 20;
    }
    
    if (felicidad > 100) {
        felicidad = 100;
    }
    if (energia < 0) {
        energia = 0;
    }
}

void Tamagotchi::dormir() {
    energia = 100;
    salud += 10;
    if (salud > 100) {
        salud = 100;
    }
    felicidad -= 5;
    if (felicidad < 0) {
        felicidad = 0;
    }
}

void Tamagotchi::trabajar() {
    energia -= 20;
    if (energia < 0) {
        energia = 0;
    }
    dinero += 25;
    felicidad -= 10;
    if (felicidad < 0) {
        felicidad = 0;
    }
}

void Tamagotchi::actualizar() {
    time_t ahora = time(nullptr);
    
    // Recuperación pasiva cada 60 segundos
    if (difftime(ahora, ultima_recuperacion) >= 60) {
        if (energia < 100) {
            energia += 5;
        }
        if (salud < 100) {
            salud += 2;
        }
        ultima_recuperacion = ahora;
    }
    
    // Eventos aleatorios cada 1-5 minutos (simular rápido: cada 5-10 segundos)
    if (difftime(ahora, ultimo_evento) >= (5 + rand() % 5)) {
        int evento = rand() % 3;
        
        if (evento == 0) {
            // Evento hambre
            energia -= 10;
            felicidad -= 5;
        } else if (evento == 1) {
            // Evento aburrimiento
            felicidad -= 15;
        } else {
            // Evento enfermedad
            salud -= 10;
        }
        
        ultimo_evento = ahora;
    }
    
    // Cálculo de daño por hambre/felicidad
    int daño_total = 0;
    
    if (energia == 0) {
        daño_total += 10;
    } else if (energia >= 1 && energia <= 20) {
        daño_total += 20;
    }
    
    if (felicidad == 0) {
        daño_total += 10;
    } else if (felicidad >= 1 && felicidad <= 20) {
        daño_total += 20;
    }
    
    salud -= daño_total;
    if (salud < 0) {
        salud = 0;
    }
}

bool Tamagotchi::estaVivo() const {
    return salud > 0;
}

void Tamagotchi::mostrar_estado() const {
    cout << "\n=== Estado de " << nombre << " ===" << endl;
    cout << "Felicidad: " << felicidad << "/100" << endl;
    cout << "Energia:   " << energia << "/100" << endl;
    cout << "Salud:     " << salud << "/100" << endl;
    cout << "Dinero:    $" << dinero << endl;
    cout << "=====================\n" << endl;
}
