#ifndef DINO_H
#define DINO_H

#include "game.h"

// Déclaration de la classe Dino qui hérite de la classe Game (sinon on peut pas setup et loop dans le main)
class Dino : public Game {
  public:
    Dino(U8G2_SH1107_SEEED_128X128_1_SW_I2C& u8g2); // constructeur qui prend une référence à un objet de type U8G2_SH1107_SEEED_128X128_1_SW_I2C
  private:
    int dinoColor; 
};

#endif