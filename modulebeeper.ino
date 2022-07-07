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

void playExplosionVictory() {
  digitalWrite(LED_BUILTIN, HIGH);

  tone(NOTE_PIN, 250);
  delay(200);

  tone(NOTE_PIN, 150);
  delay(200);

  tone(NOTE_PIN, 50, 200);
  delay(500);

  for (int j = 0; j <= 150; j++){
    var1 = random(150, 500);
    var2 = random(150, 500);
    tone(NOTE_PIN, var1);
    delay(4);
    tone(NOTE_PIN, var2);
    delay(4);
  }
  noTone(NOTE_PIN);

  digitalWrite(LED_BUILTIN, LOW);

  tone(NOTE_PIN, NOTE_D8);
  delay(3000);
  noTone(NOTE_PIN);
}

void playDefuseVictory() {
  tone(NOTE_PIN,500);
  delay(200);
  tone(NOTE_PIN,500);
  delay(200);
  tone(NOTE_PIN,500);
  delay(200);
  tone(NOTE_PIN,800);
  delay(150);
  tone(NOTE_PIN,500);
  delay(500);
  tone(NOTE_PIN,600);
  delay(1000);
  noTone(NOTE_PIN);
  delay(2000);
}

void playEarlyGameEnd() {
  tone(NOTE_PIN, NOTE_A5, 400);
  delay(500);
  tone(NOTE_PIN, NOTE_D5, 300);
  delay(400);
  tone(NOTE_PIN, NOTE_B3, 500);
  delay(500);
  noTone(NOTE_PIN);
}
