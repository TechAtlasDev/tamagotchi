#include <ctime>
#include <cstdlib>
#include "Game.hpp"

int main() {
    srand(time(nullptr));
    Game juego(100, 100);
    juego.play();
    return 0;
}