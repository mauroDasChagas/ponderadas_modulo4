#include <vector> // Biblioteca para facilitar o trabalho com vetores;

// definindo pinos dos LEDs;
#define LED_YELLOW 14
#define LED_GREEN 27
#define LED_BLUE 26
#define LED_RED 25

const int leds[] = {LED_YELLOW, LED_GREEN, LED_BLUE, LED_RED};

// definindo pinos dos botões;
#define BUTTON_YELLOW 2
#define BUTTON_GREEN 4
#define BUTTON_BLUE 16
#define BUTTON_RED 17
#define BUTTON_RESET 21

const int buttons[] = {BUTTON_YELLOW, BUTTON_GREEN, BUTTON_BLUE, BUTTON_RED};

// valores padrão para o delay;
#define TIME_PLAYER 400
#define TIME_SIMON 400

// FUNÇÃO AUXILIAR PARA VISUALIZAR AS SEQUÊNCIAS // 
void printSequence(std::vector<int> seq) {
    for (int i = 0; i < seq.size(); i++) {
        Serial.print(seq[i]);
        Serial.print(" ");
    }
    Serial.println();
}

// MÁQUINAS DE ESTADO //
int lengthSequencePlayer = 0;

int lengthSequenceSimon = 0;

bool simonTurn = true;

bool areYouWinningSon = true;

void loseSimonGame() {
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_RED, HIGH);
  delay(100);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_RED, LOW);
  delay(100);
}

bool verifySequencesLength() {
  return lengthSequenceSimon == lengthSequencePlayer;
}

bool compareSequences(std::vector<int> seq1, std::vector<int> seq2) {
  for (int i = 0; i < seq1.size(); i++) {
    if (seq1[i] != seq2[i]) {
      return false;
    }
  }

  return true;
}

// SEQUÊNCIAS //

std::vector<int> playerSequence {};

std::vector<int> simonSequence {};

// FUNÇÕES DO SIMON //

void simonSequenceFunc() {
  lengthSequencePlayer = 0;
  playerSequence.clear();

  int ledToBlink = leds[random(4)];
  simonSequence.push_back(ledToBlink);

  for(int led: simonSequence) {
    digitalWrite(led, HIGH);
    delay(TIME_SIMON);
    digitalWrite(led, LOW);
    delay(TIME_SIMON);
  }

  lengthSequenceSimon++;
  simonTurn = verifySequencesLength();

  // Serial.println("Simon Sequence:");
  // printSequence(simonSequence);
}


// FUNÇÕES DO JOGADOR //

void clickButton(int BUTTON, int LED) {
  if (digitalRead(BUTTON) == LOW) {
    digitalWrite(LED, HIGH);
    delay(TIME_PLAYER);
    digitalWrite(LED, LOW);

    playerSequence.push_back(LED);

    lengthSequencePlayer++;
    simonTurn = verifySequencesLength();

    if (compareSequences(playerSequence, simonSequence)) {
      areYouWinningSon = true;
    } else {
      areYouWinningSon = false;
    }

    // Serial.println("Player Sequence:");
    // printSequence(playerSequence);
  }
}

void buttonsToPress() {
  clickButton(BUTTON_YELLOW, LED_YELLOW);
  clickButton(BUTTON_GREEN, LED_GREEN);
  clickButton(BUTTON_BLUE, LED_BLUE);
  clickButton(BUTTON_RED, LED_RED);
}


// Funções setup() e loop();
void setup() {
  Serial.begin(9600); // apenas para debugar;

  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(buttons[i], INPUT_PULLUP);
  }

  pinMode(BUTTON_RESET, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(BUTTON_RESET) == LOW) {
    ESP.restart();
  }

  if (areYouWinningSon) {
    if (simonTurn) {
      simonSequenceFunc();
    } else {
      buttonsToPress();
    }
  } else {
    loseSimonGame();
  }
}
