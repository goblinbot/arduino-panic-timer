
#define MINUTE (60000)
#define GAMETICK (250)
#define HALF_TICK (GAMETICK / 2)

#define NOTE_DS7 (2564)
#define NOTE_CS8 (4231)

// test rounds
const long ROUND_MINI = (MINUTE / 2);
const long ROUND_SHORT = (5 * MINUTE);
const long ROUND_REGULAR = (10 * MINUTE);
const long ROUND_LONG = (15 * MINUTE);

// breadboard config
const int NOTE_PIN = 8;
const int PIN_TEST_BUTTON = 7;
const int PIN_DEFUSE_BUTTON = 2;

// ARE WE PLAYING?
int buttonStartState = 0;
int gameIsPlaying = 0;
long gameRoundTime = ROUND_REGULAR; 
long gameTimer = 0;

const int BEEP_DELAYS[] = { 15000, 5000, 3000, 2000, 1000, GAMETICK };
const int MAX_BEEP_STATE = 5;
int beepTimingState = 0;
int beepTimer = 0;

// Beep timing ints
int beepDuration = (HALF_TICK * 0.87);


// dynamic DEFUSE states
int defuseButtonState = 0;
int defuseButtonPrevious = 0;
int defuseTimer = 0;
int requiredDefuseTime = 10000;


void resetBeepTimers() {
  beepTimingState = 0;
  beepTimer = 0;  
}

void endGame() {
  gameIsPlaying = 0;
  defuseTimer = 0;
  resetBeepTimers();
  Serial.println("END");
  tone(NOTE_PIN, 1111, beepDuration);
  delay(HALF_TICK);
  noTone(NOTE_PIN);
}

void startGame() {
  gameTimer = ROUND_REGULAR;
  gameIsPlaying = 1;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_DEFUSE_BUTTON, INPUT);
  pinMode(PIN_TEST_BUTTON, INPUT);
  Serial.begin(9600);
}

void loop() {
  handleStartButtonInput();

  if (gameIsPlaying == 1) {
    defuseButtonState = digitalRead(PIN_DEFUSE_BUTTON);
    handleDefuseButtonInput();
  
    if (defuseButtonState != HIGH) {
      beepIfNeeded();
    } else {
      tone(NOTE_PIN, 2500, beepDuration);  
    }
  }

  delay(HALF_TICK);

  stopBeepSound();
  delay(HALF_TICK);

  increaseRoundTime();
}

void handleStartButtonInput() {
  buttonStartState = digitalRead(PIN_TEST_BUTTON);
  
  if (buttonStartState == HIGH) {
    if (gameIsPlaying == 1) { 
        endGame();
    } else {
      startGame();
      Serial.println("START");
      tone(NOTE_PIN, 451, beepDuration);
      delay(HALF_TICK);
      noTone(NOTE_PIN);
    }
    delay(3000);
  }
}


void handleDefuseButtonInput() {
  defuseButtonState = digitalRead(PIN_DEFUSE_BUTTON);

  if (defuseButtonState == HIGH) {
    Serial.println("PING");

    if (defuseTimer >= requiredDefuseTime) {
      Serial.println("DONE, RESET");
      endGame();
    } else {
      defuseTimer = defuseTimer + GAMETICK;
      Serial.println(defuseTimer);
    }
    
  } else {
    if (defuseButtonPrevious == HIGH) {
      Serial.println("STOP CLOCK, RESET");
      defuseTimer = 0;
    }
  }
  defuseButtonPrevious = defuseButtonState;
}


void increaseBeepState() {
  if (beepTimingState < MAX_BEEP_STATE) {
    beepTimingState++;
  }
}

void beepIfNeeded() {
  if (beepTimer == BEEP_DELAYS[2]) {
    playBeepSound();
    beepTimer = 0;
  }
  beepTimer = beepTimer + GAMETICK;
}

void playBeepSound() {
  tone(NOTE_PIN, NOTE_CS8, beepDuration); 
  digitalWrite(LED_BUILTIN, HIGH);
}

void stopBeepSound() {
  noTone(NOTE_PIN);
  digitalWrite(LED_BUILTIN, LOW);
}

void increaseRoundTime() {
  if (gameIsPlaying == 1) {
    gameTimer = gameTimer - GAMETICK;

    if (gameTimer == 0) {
        endGame();
     }
    
  }

  Serial.println("timer");
  Serial.println(gameTimer);
}
