#include "dino.h" // inclut le fichier Dino.h

// Implémentation du constructeur de la classe Dino
Dino::Dino(U8G2_SH1107_SEEED_128X128_1_SW_I2C& u8g2) : Game(u8g2) {
  dinoColor = random(0, 255); // initialise l'attribut dinoColor avec une valeur aléatoire entre 0 et 255
}

// Implémentation de la méthode drawGame de la classe Dino
void Dino::drawGame() {  // redéfinition pour mettre la couleur
  u8g2.firstPage(); // commence à dessiner sur la première page de l'écran

  do {
    // dessine le dino à sa position actuelle avec sa couleur
    u8g2.setDrawColor(dinoColor); // change la couleur du dessin
    u8g2.drawBox(dinoX+4, dinoY+8, 6, 2); // dessine la tête
    u8g2.drawBox(dinoX, dinoY+6, 4, 2); // dessine le corps
    u8g2.drawBox(dinoX+4, dinoY+4, 10, 2); // dessine le long cou
    u8g2.drawBox(dinoX+10, dinoY+6, 4, 2); // dessine la queue
    u8g2.drawBox(dinoX+2, dinoY+2, 2, 2); // dessine l'œil

    // dessine la patte gauche
    u8g2.drawBox(dinoX+4, dinoY+11, 2, 4);
    u8g2.drawBox(dinoX+2, dinoY+14, 2, 2);
  
    // dessine la patte droite
    u8g2.drawBox(dinoX+8, dinoY+11, 2, 4);
    u8g2.drawBox(dinoX+10, dinoY+14, 2, 2);

  } while (u8g2.nextPage()); // passe à la page suivante et répète tant qu'il y a des pages à dessiner
}