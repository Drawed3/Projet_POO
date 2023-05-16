#ifndef GAME_H
#define GAME_H

#include <U8g2lib.h>

class Game {
  private:

  protected:
   U8G2_SH1107_SEEED_128X128_1_SW_I2C& u8g2; // référence à l'objet de type U8G2_SH1107_SEEED_128X128_1_SW_I2C
  public:

    // Surcharge de l'opérateur d'assignation
    Game& operator=(const Game& other) {
        if (this == &other) {
            return *this; // Vérifie si c'est la même instance, pas besoin de copier
        }

        // Copie des attributs de base
        resetPressed = other.resetPressed;
        buttonState = other.buttonState;
        lastButtonState = other.lastButtonState;
        lastButtonCheck = other.lastButtonCheck;
        dinoX = other.dinoX;
        dinoY = other.dinoY;
        dinoVelocity = other.dinoVelocity;

        // Copie des attributs spécifiques à l'objet obstacle
        obstacleX = other.obstacleX;
        obstacleY = other.obstacleY;
        obstacleVelocity = other.obstacleVelocity;

        // Copie de tout autre attribut supplémentaire si on veut en ajouter
        // ...

        return *this;
    }



    Game(U8G2_SH1107_SEEED_128X128_1_SW_I2C& u8g2); // constructeur qui prend une référence à un objet de type U8G2_SH1107_SEEED_128X128_1_SW_I2C
    void setup(); // initialise le jeu
    void loop(); // met à jour et dessine le jeu
  protected:
    bool resetPressed; // indique si le bouton de réinitialisation a été appuyé
    const int buttonPin; // le numéro de la broche du bouton
    int buttonState; // l'état actuel du bouton
    int lastButtonState; // l'état précédent du bouton
    unsigned long lastButtonCheck; // le temps du dernier contrôle du bouton

    int dinoX; // la position horizontale du dino
    int dinoY; // la position verticale du dino 
    int dinoVelocity; // la vitesse verticale du dino
    const int dinoWidth; // la largeur du dino
    const int dinoHeight; // la hauteur du dino
    const int gravity; // la gravité qui s'applique au dino

    int obstacleX; // la position horizontale de l'obstacle
    int obstacleY; // la position verticale de l'obstacle   
    int obstacleVelocity; // la vitesse horizontale de l'obstacle 
    const int obstacleWidth; // la largeur de l'obstacle
    const int obstacleHeight; // la hauteur de l'obstacle

    bool gameOver; // indique si le jeu est terminé
    unsigned long lastGameOverTime; // le temps du dernier affichage du message de fin de jeu
    bool buttonPressed; // indique si le bouton a été appuyé pendant le jeu

    void checkButton(); // vérifie l'état du bouton et appelle les fonctions appropriées
    void jumpDino(); // fait sauter le dino si il est au sol
    void updateDino(); // met à jour la position et la vitesse du dino en fonction de la gravité
    void updateObstacle(); // met à jour la position et la vitesse de l'obstacle en fonction de sa vitesse initiale
    void checkCollision();   // vérifie si il y a une collision entre le dino et l'obstacle et met fin au jeu si c'est le cas
    void handleGameOver(); // gère la fin du jeu et permet de recommencer en appuyant sur le bouton
    void resetGame(); // réinitialise le jeu en remettant les variables à leurs valeurs initiales
    void drawGame(); // dessine le jeu en utilisant les méthodes de dessin de l'objet de type U8G2_SH1107_SEEED_128X128_1_SW_I2C
};

#endif