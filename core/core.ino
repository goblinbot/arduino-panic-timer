#include "times.h"
#include "pins.h"

// ARE WE PLAYING?
int buttonStartState = 0;
int buttonConfigState = 0;
int gameIsPlaying = 0;

// dynamic DEFUSE states
int defuseButtonState = 0;
int defuseButtonPrevious = 0;
int defuseTimer = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_DEFUSE_BUTTON, INPUT);
  pinMode(PIN_START_BUTTON, INPUT);
  Serial.begin(9600);
  Serial.println("Setup done");
}

void loop() {
  handleGameConfigButtonInput();
  handleStartButtonInput();

  if (gameIsPlaying == 1) {
    defuseButtonState = digitalRead(PIN_DEFUSE_BUTTON);
    handleDefuseButtonInput();
  
    if (defuseButtonState == HIGH) {
      digitalWrite(PIN_LED, HIGH);
      playDefuseBeep();
    } else {
      runBeepTimer();
    }
  }

  delay(HALF_TICK);
  stopBeepSound();
  
  delay(HALF_TICK);
  runGameTimer();
}

void handleGameConfigButtonInput() {
  if (gameIsPlaying == 0) {
    buttonConfigState = digitalRead(PIN_CONFIG_BUTTON);

    if (buttonConfigState == HIGH) {
      toggleRoundTimes();  
    }
  }
}

void handleStartButtonInput() {
  buttonStartState = digitalRead(PIN_START_BUTTON);
  
  if (buttonStartState == HIGH) {
    if (gameIsPlaying == 1) { 
      endGame();
      playEarlyGameEnd();
    } else {
      startGame();
      Serial.println("START");
    }
  }
}

void handleDefuseButtonInput() {
  defuseButtonState = digitalRead(PIN_DEFUSE_BUTTON);

  if (defuseButtonState == HIGH) {
    Serial.println("PING");

    if (defuseTimer >= REQUIRED_DEFUSE_TIME) {
      Serial.println("DONE, RESET");
      endGame();
      playDefuseVictory();
    } else {
      defuseTimer = defuseTimer + GAMETICK;
      Serial.println(defuseTimer);
    }
    
  } else {
    if (defuseButtonPrevious == HIGH) {
      Serial.println("STOP DEFUSE CLOCK, RESET");
      defuseTimer = 0;
    }
  }
  defuseButtonPrevious = defuseButtonState;
}
