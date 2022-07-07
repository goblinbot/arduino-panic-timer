#include "times.h"
#include "pins.h"
#include "notes.h"

const int BEEP_DELAYS[] = { 10000, 5000, 3000, 2000, 1000, 500, GAMETICK };
const int MAX_BEEP_STATE = 6;

int beepLevel = 0;
int beepTimer = 0;
int beepBreakpoint = 0;

void playDefaultBeepSound() {
  tone(NOTE_PIN, NOTE_CS8, BEEP_DURATION); 
  digitalWrite(LED_BUILTIN, HIGH);
}

void stopBeepSound() {
  noTone(NOTE_PIN);
  digitalWrite(LED_BUILTIN, LOW);
}

void resetBeepTickers() {
  beepLevel = 0;
  beepTimer = 0;
  beepBreakpoint = 0;  
}

void increaseBeepLevel() {
  if (beepLevel < MAX_BEEP_STATE) {
    beepLevel++;
    Serial.println("Beep increase!");
    Serial.println(BEEP_DELAYS[beepLevel]);
  }
}

void playEndGameBeep() {
  tone(NOTE_PIN, NOTE_A5, 180);
  delay(GAMETICK);
  noTone(NOTE_PIN);
}

void playDefuseBeep() {
  tone(NOTE_PIN, NOTE_DS7, BEEP_DURATION); 
}
