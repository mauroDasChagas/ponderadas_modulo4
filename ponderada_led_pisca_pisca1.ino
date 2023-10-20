// C++ code

// Usando o #define ao invés de variáveis pela otimização;
#define LED_RED 13
#define LED_GREEN 12
#define LED_BLUE 8
#define TIME 300


void setup() {
  // Definindo os pinos como de saída;
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void loop() {
  // Ligando os leds e desligando repetidamente;
  // assim simulando um pisca pisca;
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  delay(TIME);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
  delay(TIME);
}