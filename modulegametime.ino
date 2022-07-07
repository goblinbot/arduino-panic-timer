#include "times.h"

long gameRoundTime = ROUND_SHORT;
long gameTimer = 0;

void cleanupTimers() {
  gameIsPlaying = 0;
  defuseTimer = 0;
  gameTimer = 0;
  resetBeepTickers();
}

void startGame() {
  cleanupTimers();
  
  gameTimer = gameRoundTime;
  beepBreakpoint = (gameRoundTime / BEEP_DELAYS[beepLevel]);
  
  doom_playSong();
  gameIsPlaying = 1;
}

void endGame() {
  cleanupTimers();
  playEndGameBeep();
  Serial.println("END");
}

void runBeepTimer() {
  if (beepTimer >= BEEP_DELAYS[beepLevel]) {
    playDefaultBeepSound();
    beepTimer = 0;
  }

  beepTimer = beepTimer + GAMETICK;
}


void runGameTimer() {
  if (gameIsPlaying == 1) {
    gameTimer = gameTimer - GAMETICK;
    calculateBeepScaling();

    if (gameTimer == 0) {
        endGame();
     }
  }

}

void calculateBeepScaling() {
    if (gameIsPlaying == 1) {
      if (beepLevel == 0) {

        if ( gameTimer / BEEP_DELAYS[beepLevel] <= ( beepBreakpoint * 0.66 )) {
          increaseBeepLevel();
        }
        
      } else {
        if (gameTimer / BEEP_DELAYS[beepLevel] <= beepBreakpoint) {
          increaseBeepLevel();  
        }
      }
    } 
}
