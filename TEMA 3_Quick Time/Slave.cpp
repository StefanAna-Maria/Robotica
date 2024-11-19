#include <Arduino.h>
#include <SPI.h>

// Prototipurile funcțiilor
void startButtonChallenge(char color);
void checkButtonResponse();
void activateLED(char color);
void resetLEDs();
void playTeamSong();
void stopTeamSong();

volatile char command = '\0';
volatile bool newCommand = false;

// Pinul pentru butoanele multiplexate
const int buttonPin = A0;

// Pinul pentru buzzer
const int buzzerPin = 3;

// Pinul pentru LED-urile mici colorate (toate legate împreună)
const int smallLEDsPin = 2;

// LED-uri RGB pentru fiecare jucător
const int player1RedLEDPin = 9;
const int player1BlueLEDPin = 7;
const int player1GreenLEDPin = 8;

const int player2RedLEDPin = 6;
const int player2BlueLEDPin = 4;
const int player2GreenLEDPin = 5;

unsigned long pressStartTime = 0;
bool waitingForPress = false;
bool player1Turn = true;
bool gameInProgress = false;

void setup() {
  Serial.begin(115200);          // Pentru debugging
  SPCR |= bit(SPE);              // Activează SPI în modul slave
  pinMode(MISO, OUTPUT);         // Setează MISO ca ieșire pentru SPI
  SPI.attachInterrupt();         // Activează întreruperea SPI

  // Inițializează pinurile pentru LED-uri și buzzer
  pinMode(buzzerPin, OUTPUT);    // Pin pentru buzzer
  pinMode(smallLEDsPin, OUTPUT); // Pin pentru LED-urile mici colorate

  // LED-uri RGB pentru fiecare jucător
  pinMode(player1RedLEDPin, OUTPUT);
  pinMode(player1BlueLEDPin, OUTPUT);
  pinMode(player1GreenLEDPin, OUTPUT);
  pinMode(player2RedLEDPin, OUTPUT);
  pinMode(player2BlueLEDPin, OUTPUT);
  pinMode(player2GreenLEDPin, OUTPUT);

  // Activează LED-urile mici pe parcursul jocului
  digitalWrite(smallLEDsPin, HIGH);
  resetLEDs();  // Stinge toate LED-urile la început
}

// SPI interrupt service routine
ISR(SPI_STC_vect) {
  char receivedChar = SPDR;
  if (receivedChar != '#') {
    command = receivedChar;
    newCommand = true;
  }
}

void loop() {
  if (newCommand) {
    newCommand = false;

    if (command == 'r' || command == 'g' || command == 'b') {
      startButtonChallenge(command);  // Start a new round with color
    } else if (command == 's') {  // Command to start the game and play the song
      playTeamSong();
      gameInProgress = true;
    } else if (command == 'e') {  // Command to end the game and stop the song
      stopTeamSong();
      gameInProgress = false;
    } else {
      SPDR = '$';  // Trimite răspuns implicit pentru comenzi neidentificate
    }
  }

  if (waitingForPress) {
    checkButtonResponse();
  }
}

void startButtonChallenge(char color) {
  Serial.print("Received: ");
  Serial.print(command);
  Serial.println(player1Turn ? " for p1" : " for p2");
  pressStartTime = millis();
  waitingForPress = true;

  activateLED(color);  // Activează LED-ul corespunzător pentru jucătorul curent
  playTeamSong();      // Pornește sunetul buzzerului
}

void checkButtonResponse() {
  unsigned long elapsedTime = millis() - pressStartTime;
  int buttonValue = analogRead(buttonPin);
  Serial.print("Button value: ");  // Debugging
  Serial.println(buttonValue);

  bool buttonPressed = false;

  // Verifică valorile pentru fiecare buton în funcție de jucător și comandă
  if (player1Turn) {
    if ((command == 'r' && buttonValue >= 80 && buttonValue <= 130) ||          // Player 1 Red
        (command == 'g' && buttonValue >= 131 && buttonValue <= 190) ||        // Player 1 Green
        (command == 'b' && buttonValue >= 191 && buttonValue <= 250)) {        // Player 1 Blue
      buttonPressed = true;
    }
  } else {
    if ((command == 'r' && buttonValue >= 251 && buttonValue <= 400) ||        // Player 2 Red
        (command == 'g' && buttonValue >= 401 && buttonValue <= 900) ||        // Player 2 Green
        (command == 'b' && buttonValue >= 901 && buttonValue <= 1000)) {      // Player 2 Blue
      buttonPressed = true;
    }
  }

  if (buttonPressed) {
    waitingForPress = false;
    stopTeamSong();  // Oprește sunetul buzzerului
    char score;

    if (elapsedTime <= 300) {
      score = 'A';  // Răspuns rapid
    } else if (elapsedTime <= 600) {
      score = 'B';  // Răspuns moderat
    } else if (elapsedTime <= 1000) {
      score = 'C';  // Răspuns lent
    } else {
      score = 'F';  // Timp depășit
    }

    SPDR = score;  // Trimite scorul înapoi prin SPI
    player1Turn = !player1Turn;  // Schimbă jucătorul
  } else if (elapsedTime > 900) {  // Condiție de timeout
    waitingForPress = false;
    stopTeamSong();  // Oprește sunetul buzzerului
    SPDR = 'F';  // Trimite indicator de timeout
    player1Turn = !player1Turn;  // Schimbă jucătorul
  }
}

void activateLED(char color) {
  resetLEDs();  // Stinge toate LED-urile înainte de a aprinde unul
  int ledPin;

  if (player1Turn) {
    ledPin = (color == 'r') ? player1RedLEDPin :
             (color == 'g') ? player1GreenLEDPin :
             player1BlueLEDPin;
    Serial.print("Activating Player 1 LED: ");  // Debugging
  } else {
    ledPin = (color == 'r') ? player2RedLEDPin :
             (color == 'g') ? player2GreenLEDPin :
             player2BlueLEDPin;
    Serial.print("Activating Player 2 LED: ");  // Debugging
  }

  Serial.println(ledPin);  // Debug: Pinul care ar trebui să fie aprins
  digitalWrite(ledPin, HIGH);  // Aprinde LED-ul corespunzător pentru jucător
}

void resetLEDs() {
  digitalWrite(player1RedLEDPin, LOW);
  digitalWrite(player1BlueLEDPin, LOW);
  digitalWrite(player1GreenLEDPin, LOW);
  digitalWrite(player2RedLEDPin, LOW);
  digitalWrite(player2BlueLEDPin, LOW);
  digitalWrite(player2GreenLEDPin, LOW);
}

void playTeamSong() {
  tone(buzzerPin, 350);  // Pornește buzzerul cu o frecvență de 440 Hz (A4)
}

void stopTeamSong() {
  noTone(buzzerPin);  // Oprește sunetul buzzerului
}
