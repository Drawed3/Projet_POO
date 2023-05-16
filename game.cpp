#include "game.h"
#include <U8g2lib.h>

Game::Game(U8G2_SH1107_SEEED_128X128_1_SW_I2C& u8g2) : u8g2(u8g2), resetPressed(false), buttonPin(D8), buttonState(0), lastButtonState(1), lastButtonCheck(0), dinoX(16), dinoY(60), dinoVelocity(0), dinoWidth(24), dinoHeight(24), gravity(2), obstacleX(128), obstacleY(50), obstacleVelocity(-5), obstacleWidth(10), obstacleHeight(10), gameOver(false), lastGameOverTime(0), buttonPressed(false) {
  // constructeur qui initialise les attributs avec les valeurs données
}

void Game::setup() {
  u8g2.begin(); // initialise l'objet de type U8G2_SH1107_SEEED_128X128_1_SW_I2C
  pinMode(buttonPin, INPUT_PULLUP); // configure la broche du bouton comme une entrée avec une résistance de tirage interne
}

void Game::loop() {
  checkButton(); // vérifie l'état du bouton

  if (!gameOver) { // si le jeu n'est pas terminé
    updateDino(); // met à jour le dino
    checkCollision(); // vérifie la collision
    updateObstacle(); // met à jour l'obstacle
  } else { // si le jeu est terminé
    handleGameOver(); // gère la fin du jeu
  }

  drawGame(); // dessine le jeu

  delay(10); // fait une pause de 10 millisecondes
}

void Game::checkButton() {
  unsigned long now = millis(); // obtient le temps actuel en millisecondes
  if (now - lastButtonCheck >= 10) { // si plus de 10 millisecondes se sont écoulées depuis le dernier contrôle du bouton
    buttonState = digitalRead(buttonPin); // lit l'état actuel du bouton
    if (buttonState == LOW && lastButtonState == HIGH) { // si le bouton est passé de relâché à appuyé
      if (!gameOver) { // si le jeu n'est pas terminé
        jumpDino(); // fait sauter le dino
      } else { // si le jeu est terminé
        resetGame(); // réinitialise le jeu
      }
    }
    lastButtonState = buttonState; // met à jour l'état précédent du bouton
    lastButtonCheck = now; // met à jour le temps du dernier contrôle du bouton
  }
}

void Game::jumpDino() {
  if (dinoY == 48) { // si le dino est au sol
    dinoVelocity = -10; // lui donne une vitesse verticale négative pour le faire sauter
  }
}

void Game::updateDino() {
  dinoY += dinoVelocity; // met à jour la position verticale du dino en fonction de sa vitesse
  dinoVelocity += gravity; // met à jour la vitesse verticale du dino en fonction de la gravité
  if (dinoY > 48) { // si le dino dépasse le sol
    dinoY = 48; // le remet au sol
    dinoVelocity = 0; // annule sa vitesse verticale
  }
}


  void Game::updateObstacle() {
  obstacleX += obstacleVelocity; // met à jour la position horizontale de l'obstacle en fonction de sa vitesse
  if (obstacleX < -obstacleWidth) { // si l'obstacle sort de l'écran par la gauche
    obstacleX = 128; // le remet à droite de l'écran
    obstacleY = random(50, 50); // lui donne une position verticale aléatoire entre 50 et 50

    if (obstacleVelocity > 0 && obstacleX + obstacleWidth > dinoX && obstacleX < dinoX + dinoWidth) { // si l'obstacle se superpose au dino
      obstacleX = dinoX + dinoWidth; // le décale pour éviter la collision
    }
    
  }
}

void Game::checkCollision()   
{
 if (obstacleX < dinoX + dinoWidth - 15 && obstacleX + obstacleWidth > dinoX + 5 &&
        dinoY + dinoHeight - 5 > obstacleY && dinoY + 5 < obstacleY + obstacleHeight) { // si il y a une intersection entre les rectangles du dino et de l'obstacle
    // Collision avec l'obstacle
    gameOver = true; // met fin au jeu
    lastGameOverTime = millis(); // enregistre le temps de la fin du jeu
}
}

void Game::handleGameOver() {
  static bool buttonWasPressed = false; // variable statique qui indique si le bouton a été appuyé pendant la fin du jeu
  
  unsigned long now = millis(); // obtient le temps actuel en millisecondes
  if (now - lastGameOverTime >= 2000) { // si plus de 2 secondes se sont écoulées depuis la fin du jeu
    bool buttonIsPressed = (digitalRead(buttonPin) == LOW); // lit l'état actuel du bouton
    
    if (buttonIsPressed && !buttonWasPressed) { // si le bouton est passé de relâché à appuyé
      resetGame(); // réinitialise le jeu
    }
    
    buttonWasPressed = buttonIsPressed; // met à jour la variable statique
    lastGameOverTime = now; // met à jour le temps de la fin du jeu
  }
}

void Game::resetGame() {
  gameOver = false; // indique que le jeu n'est pas terminé
  dinoX = 10; // remet le dino à sa position initiale
  dinoY = 48;
  dinoVelocity = 0;
  obstacleX = 128; // remet l'obstacle à sa position initiale
  obstacleY = random(50, 50);
  buttonPressed = false; // indique que le bouton n'a pas été appuyé pendant le jeu
}

void Game::drawGame() {
  u8g2.firstPage(); // commence à dessiner sur la première page de l'écran
  do {
    // dessine le dino à sa position actuelle
    u8g2.drawBox(dinoX+4, dinoY+8, 6, 2);
    u8g2.drawBox(dinoX, dinoY+6, 4, 2); 
    u8g2.drawBox(dinoX+4, dinoY+4, 10, 2); 
    u8g2.drawBox(dinoX+10, dinoY+6, 4, 2); 
    u8g2.drawBox(dinoX+2, dinoY+2, 2, 2); 
 
    u8g2.drawBox(dinoX+4, dinoY+11, 2, 4);
    u8g2.drawBox(dinoX+2, dinoY+14, 2, 2);
  
    // dessine la patte droite
    u8g2.drawBox(dinoX+8, dinoY+11, 2, 4);
    u8g2.drawBox(dinoX+10, dinoY+14, 2, 2);

    // dessine l'obstacle à sa position actuelle
    u8g2.drawBox(obstacleX, obstacleY, obstacleWidth, obstacleHeight);
    

    if (gameOver) { // si le jeu est terminé
      // dessine le message de fin de jeu
      u8g2.setFont(u8g2_font_6x10_tf);
      u8g2.drawStr(36, 20, "GAME OVER");
      u8g2.drawStr(28, 40, "Press the button");
      u8g2.drawStr(28, 50, "to play again"); 
    }
  } while (u8g2.nextPage()); // passe à la page suivante et répète tant qu'il y a des pages à dessiner
}



