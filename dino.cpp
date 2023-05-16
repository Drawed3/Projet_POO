#include "dino.h"

// Implémentation du constructeur de la classe Dino
Dino::Dino(U8G2_SH1107_SEEED_128X128_1_SW_I2C& u8g2) : Game(u8g2) {
  dinoColor = random(0, 255); // initialise l'attribut dinoColor avec une valeur aléatoire entre 0 et 255
}
