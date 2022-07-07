#include "times.h"

const long ROUND_TYPES[] = { ROUND_SHORT, ROUND_REGULAR, ROUND_LONG, ROUND_XL };
const int ROUND_TYPES_MAX = 3;

int currentRoundType = 1;
long gameRoundTime = ROUND_TYPES[currentRoundType];
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
  
  Serial.println("Starting round, game time:");
  Serial.println(gameRoundTime);
  doom_playSong();
  gameIsPlaying = 1;
}

void endGame() {
  cleanupTimers();
  playEndGameBeep();
  Serial.println("END GAME");
}

void runBeepTimer() {
  if (beepTimer >= BEEP_DELAYS[beepLevel]) {
    playDefaultBeepSound();
    beepTimer = 0;
  }

  beepTimer = beepTimer + GAMETICK;
}

void toggleRoundTimes() {
  if (currentRoundType < ROUND_TYPES_MAX) {
    currentRoundType++;
  } else {
    currentRoundType = 0;
  }

  Serial.println("RoundType switch, New Type:");
  Serial.println(currentRoundType);

  gameRoundTime = ROUND_TYPES[currentRoundType];
  
  playGameToggleSound(currentRoundType + 1);
  delay(GAMETICK);
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
