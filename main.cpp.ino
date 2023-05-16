#include <U8g2lib.h> 
#include "dino.h" 

U8G2_SH1107_SEEED_128X128_1_SW_I2C u8g2(U8G2_R0, SCL,SDA,U8X8_PIN_NONE); // crée un objet de type U8G2_SH1107_SEEED_128X128_1_SW_I2C
Dino game(u8g2); // crée un objet de type Dino en lui passant une référence à l'objet de type U8G2_SH1107_SEEED_128X128_1_SW_I2C

void setup() {
  game.setup(); // initialise le jeu
}

void loop() {
  game.loop(); // met à jour et dessine le jeu
}