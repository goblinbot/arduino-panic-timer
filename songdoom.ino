#include "pins.h"
#include "notes.h"

// !! song credit to robsoncouto/arduino-songs on github!

const int doom_tempo = 200;
const int doom_melody[] = {
  NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //1
  NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
  NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
  NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 2
};

int doom_notes = sizeof(doom_melody) / sizeof(doom_melody[0]) / 2;
int doom_wholenote = (60000 * 4) / doom_tempo;
int doom_divider = 0, doom_noteDuration = 0;

void doom_playSong() {
  
  for (int thisNote = 0; thisNote < doom_notes * 2; thisNote = thisNote + 2) {    
    doom_divider = doom_melody[thisNote + 1];

    if (doom_divider > 0) {
      doom_noteDuration = (doom_wholenote) / doom_divider;
      
    } else if (doom_divider < 0) {
      doom_noteDuration = (doom_wholenote) / abs(doom_divider);
      doom_noteDuration *= 1.5; // increases the duration in half for dotted notes
    }
  
    tone(NOTE_PIN, doom_melody[thisNote], doom_noteDuration * 0.9);
  
    delay(doom_noteDuration);
    noTone(NOTE_PIN);
  }

  delay(GAMETICK);
}
