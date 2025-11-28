#include "Tamagotchi.hpp"

int get_strlen(const char* s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

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

    hambre = 100;
    felicidad = 100;
    energia = 100;
    salud = 100;
    dinero = 0;
    estado = 0;

    time_t ahora = time(nullptr);
    ultimo_hambre = ahora;
    ultima_felicidad = ahora;
    ultima_energia = ahora;
    ultima_recuperacion_energia = ahora;
    ultimo_evento = ahora;

    int base = calcular_base_nombre(nombre);
    mod_hambre = 1 + (base % 3);
    mod_energia = 1 + (base % 2);
    mod_felicidad = 1 + (base % 4);
    dano_critico = 10 + (base % 5);

    tiempo_base_hambre = 40;
    tiempo_base_felicidad = 45;
    tiempo_base_energia = 50;

    tiempo_hambre = generar_tiempo_aleatorio(tiempo_base_hambre, 20);
    tiempo_felicidad = generar_tiempo_aleatorio(tiempo_base_felicidad, 10);
    tiempo_energia = generar_tiempo_aleatorio(tiempo_base_energia, 15);
    tiempo_proximo_evento = generar_tiempo_aleatorio(60, 240);
    evento_activo = true;
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

int Tamagotchi::calcular_base_nombre(const char* nombre_base) {
    int base = 0;
    for (int i = 0; nombre_base[i] != '\0'; i++) {
        base += (int)nombre_base[i];
    }
    return base;
}

int Tamagotchi::generar_tiempo_aleatorio(int base, int max_extra) {
    if (max_extra <= 0) {
        return base;
    }
    return base + (rand() % max_extra);
}

int Tamagotchi::calcular_dano_proporcional(int valor) {
    if (valor == 0) {
        return dano_critico;
    }
    if (valor <= 20) {
        return 20;
    }
    if (valor <= 50) {
        return 15;
    }
    if (valor <= 80) {
        return 10;
    }
    return 5;
}

void Tamagotchi::recuperar_energia() {
    time_t ahora = time(nullptr);
    if (difftime(ahora, ultima_recuperacion_energia) >= 60) {
        energia += 5;
        if (energia > 100) {
            energia = 100;
        }
        ultima_recuperacion_energia = ahora;
    }
}

void Tamagotchi::evento_aleatorio() {
    if (!evento_activo) {
        return;
    }

    int tipo = rand() % 4;
    if (tipo == 0) {
        felicidad += 10;
        if (felicidad > 100) {
            felicidad = 100;
        }
    } else if (tipo == 1) {
        energia -= 5;
        if (energia < 0) {
            energia = 0;
        }
    } else if (tipo == 2) {
        salud -= 5;
        if (salud < 0) {
            salud = 0;
        }
    } else {
        hambre -= 5;
        if (hambre < 0) {
            hambre = 0;
        }
    }

    tiempo_proximo_evento = generar_tiempo_aleatorio(60, 240);
    evento_activo = false;
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

int Tamagotchi::getHambre() const {
    return hambre;
}

void Tamagotchi::comer() {
    if (hambre >= 100) {
        return;
    }

    hambre += 20;
    if (hambre > 100) {
        hambre = 100;
    }

    if (salud < 100) {
        salud += 10;
        if (salud > 100) {
            salud = 100;
        }
    }

    if (dinero >= 5) {
        dinero -= 5;
    }

    tiempo_hambre = generar_tiempo_aleatorio(tiempo_base_hambre, 20);
    ultimo_hambre = time(nullptr);
}

void Tamagotchi::jugar() {
    if (felicidad >= 100) {
        return;
    }

    felicidad += 20;
    if (felicidad > 100) {
        felicidad = 100;
    }

    energia -= 10;
    if (energia < 0) {
        energia = 0;
    }

    tiempo_felicidad = generar_tiempo_aleatorio(tiempo_base_felicidad, 10);
    ultima_felicidad = time(nullptr);
    tiempo_energia = generar_tiempo_aleatorio(tiempo_base_energia, 15);
    ultima_energia = time(nullptr);
}

void Tamagotchi::dormir() {
    energia = 100;
    ultima_energia = time(nullptr);
    tiempo_energia = generar_tiempo_aleatorio(tiempo_base_energia, 15);

    felicidad -= 5;
    if (felicidad < 0) {
        felicidad = 0;
    }

    hambre -= 10;
    if (hambre < 0) {
        hambre = 0;
    }
}

void Tamagotchi::trabajar() {
    dinero += 25;
    energia -= 15;
    felicidad -= 10;
    hambre -= 5;

    if (energia < 0) {
        energia = 0;
    }
    if (felicidad < 0) {
        felicidad = 0;
    }
    if (hambre < 0) {
        hambre = 0;
    }
}

void Tamagotchi::aplicarModAndTik() {
    time_t ahora = time(nullptr);

    if (difftime(ahora, ultimo_hambre) >= tiempo_hambre) {
        hambre -= mod_hambre;
        if (hambre < 0) {
            hambre = 0;
        }
        ultimo_hambre = ahora;
    }

    if (difftime(ahora, ultima_felicidad) >= tiempo_felicidad) {
        felicidad -= mod_felicidad;
        if (felicidad < 0) {
            felicidad = 0;
        }
        ultima_felicidad = ahora;
    }

    if (difftime(ahora, ultima_energia) >= tiempo_energia) {
        energia -= mod_energia;
        if (energia < 0) {
            energia = 0;
        }
        ultima_energia = ahora;
    }

    recuperar_energia();

    if (hambre == 0 || felicidad == 0) {
        salud = 0;
    } else {
        int dano = 0;
        dano += calcular_dano_proporcional(hambre);
        dano += calcular_dano_proporcional(felicidad);
        dano += calcular_dano_proporcional(energia);
        salud -= dano;
        if (salud < 0) {
            salud = 0;
        }
    }

    if (difftime(ahora, ultimo_evento) >= tiempo_proximo_evento) {
        evento_activo = true;
        ultimo_evento = ahora;
        evento_aleatorio();
    }
}

void Tamagotchi::actualizar() {
    aplicarModAndTik();
}

bool Tamagotchi::estaVivo() const {
    return salud > 0;
}

void Tamagotchi::mostrar_estado() const {
    cout << "\n=== Estado de " << nombre << " ===" << endl;
    cout << "Hambre:    " << hambre << "/100" << endl;
    cout << "Felicidad: " << felicidad << "/100" << endl;
    cout << "Energia:   " << energia << "/100" << endl;
    cout << "Salud:     " << salud << "/100" << endl;
    cout << "Dinero:    $" << dinero << endl;
    cout << "=====================\n" << endl;
}
