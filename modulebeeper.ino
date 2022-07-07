#include "times.h"
#include "pins.h"
#include "notes.h"

const int BEEP_DELAYS[] = { 10000, 5000, 3000, 2000, 1000, 500, GAMETICK };
const int MAX_BEEP_STATE = 6;

int beepLevel = 0;
int beepTimer = 0;
int beepBreakpoint = 0;

int var1;
int var2;

void playDefaultBeepSound() {
  tone(PIN_NOTE, NOTE_CS8, BEEP_DURATION); 
  digitalWrite(PIN_LED, HIGH);
}

void stopBeepSound() {
  noTone(PIN_NOTE);
  digitalWrite(PIN_LED, LOW);
}

void resetBeepTickers() {
  beepLevel = 0;
  beepTimer = 0;
  beepBreakpoint = 0;  
}

void increaseBeepLevel() {
  if (beepLevel < MAX_BEEP_STATE) {
    beepLevel++;
  }
}

void playEndGameBeep() {
  tone(PIN_NOTE, NOTE_C1, 150);
  delay(GAMETICK);
  noTone(PIN_NOTE);
}

void playDefuseBeep() {
  tone(PIN_NOTE, NOTE_DS7, BEEP_DURATION); 
}

void playExplosionVictory() {
  digitalWrite(PIN_LED, HIGH);

  tone(PIN_NOTE, NOTE_AS4, 600);
  delay(660);
  digitalWrite(PIN_LED, LOW);

  tone(PIN_NOTE, NOTE_B3);
  delay(525);
  digitalWrite(PIN_LED, HIGH);

  tone(PIN_NOTE, NOTE_GS1, 300);
  delay(800);
  digitalWrite(PIN_LED, LOW);

  for (int j = 0; j <= 150; j++){
    var1 = random(150, 500);
    var2 = random(150, 500);
    tone(PIN_NOTE, var1);
    delay(4);
    tone(PIN_NOTE, var2);
    delay(4);
  }
  noTone(PIN_NOTE);
  digitalWrite(PIN_LED, HIGH);

  tone(PIN_NOTE, NOTE_D8);
  delay(4000);
  digitalWrite(PIN_LED, LOW);
  noTone(PIN_NOTE);
}

void playDefuseVictory() {
  digitalWrite(PIN_LED, HIGH);

  int xNotes[] = { NOTE_B4, NOTE_B4, NOTE_B4, NOTE_G5, NOTE_B4, NOTE_D5 };
  int yPauses[] = { 200, 200, 200, 150, 500, 1000 };

  for (int i = 0; i < 6; i++) {
    tone(PIN_NOTE, xNotes[i], (yPauses[i] * 0.95));
    delay(yPauses[i]);
  }

  noTone(PIN_NOTE);
  digitalWrite(PIN_LED, LOW);
  delay(GAMETICK);
}

void playGameToggleSound(int x) {
  int y[] = { NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5 };
  int z[] = { 400, 200, 200, 600 };
  
  digitalWrite(PIN_LED, HIGH);

  for (int i = 0; i < x; i++) {
    tone(PIN_NOTE, y[i], (z[i] * 0.9));
    delay(z[i]);
    noTone(PIN_NOTE);
  }

  delay(GAMETICK);
  digitalWrite(PIN_LED, LOW);
}

void playEarlyGameEnd() {
  int y[] = { NOTE_A5, NOTE_D5, NOTE_B3 };
  int z[] = { 400, 300, 600 };
  
  for (int i = 0; i < 3; i++) {
    tone(PIN_NOTE, y[i], (z[i] * 0.8));
    delay(z[i]);
  }

  noTone(PIN_NOTE);
}
