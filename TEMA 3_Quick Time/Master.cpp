#include <Arduino.h>
#include <SPI.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <Wire.h>

// Inițializează LCD-ul cu pinii corecți: RS, E, D4, D5, D6, D7
const int rs = 9;
const int e = 8;
const int d4 = 6;
const int d5 = 5;
const int d6 = 4;
const int d7 = 3;

LiquidCrystal lcd(rs, e, d4, d5, d6, d7);
Servo gameTimerServo;

// Prototipurile funcțiilor
void displayWinner();
void resetGame();
void sendColorCommand();
char sendCommand(char command);
void updateScore(char rating);

const int buttonPin = 2;
const int servoPin = 7;
const int servoMaxAngle = 180;
const unsigned long gameDuration = 30000;  // Total game time (30 seconds)

char colors[] = {'r', 'g', 'b'};
unsigned long gameStartTime = 0;
unsigned long lastRoundTime = 0;
unsigned long roundInterval = 3000;  // 1 second per round
bool gameStarted = false;
bool awaitingResponse = false;
char response;

String player1, player2;
int player1Score = 0;
int player2Score = 0;
int roundCounter = 0;
bool isPlayer1Turn = true;

void setup() {
  Serial.begin(115200);
  SPI.begin();
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH);
  pinMode(buttonPin, INPUT_PULLUP);

  lcd.begin(16, 2);
  gameTimerServo.attach(servoPin);

  // Mesaj de bun venit
  lcd.print("Welcome!");
  lcd.setCursor(0, 1);
  lcd.print("Prepare To Fight!");
  delay(3000);  // Afișează mesajul pentru 3 secunde
  
  lcd.clear();
  lcd.print("Press to Start!");
}

void loop() {
  if (!gameStarted && digitalRead(buttonPin) == LOW) {
    delay(200);
    gameStarted = true;
    lcd.clear();
    lcd.print("Enter Player 1:");
    Serial.println("Enter Player 1 Name:");
    while (Serial.available() == 0) {}
    player1 = Serial.readStringUntil('\n'); 

    lcd.clear();
    lcd.print("Enter Player 2:");
    
    Serial.println("\nEnter Player 2 Name:");
    while (Serial.available() == 0) {}
    player2 = Serial.readStringUntil('\n');

    // Afișează numele jucătorilor într-un format "Player1 vs Player2"
    lcd.clear();
    lcd.print(player1 + " vs " + player2);
    delay(3000);  // Afișează mesajul timp de 3 secunde

    gameStartTime = millis();
    lcd.clear();
    lcd.print("Game Starting!");
    delay(1000);
    lcd.clear();
  }

  if (gameStarted) {
    unsigned long currentMillis = millis();

    // End the game if 30 seconds have elapsed
    if (currentMillis - gameStartTime >= gameDuration) {
      gameStarted = false;
      displayWinner();
      resetGame();
      return;
    }

    // Rotate servo based on time elapsed
    int angle = map(currentMillis - gameStartTime, 0, gameDuration, 0, servoMaxAngle);
    gameTimerServo.write(angle);

    // Alternate rounds every 1 second between players
    if (currentMillis - lastRoundTime >= roundInterval) {
      if (roundCounter < 30) {  // 15 rounds per player
        if (isPlayer1Turn) {
          lcd.clear();
          lcd.print(player1 + " Round");
        } else {
          lcd.clear();
          lcd.print(player2 + " Round");
        }
        sendColorCommand();
        delay(1000);
        awaitingResponse = true;
        lastRoundTime = currentMillis;
        isPlayer1Turn = !isPlayer1Turn;
        roundCounter++;
      }
    }

    // Receive and process score response from slave
    if (awaitingResponse) {
      response = sendCommand('#');  // Dummy command to get response
      Serial.println((isPlayer1Turn ? player2 : player1) + " Received score: ");
      Serial.println(response);

      updateScore(response);
      awaitingResponse = false;
    }
  }
}

// Function to send color command over SPI
void sendColorCommand() {
  char colorCommand = colors[random(0, 3)];
  sendCommand(colorCommand);
  delay(50);  // Adaugă o întârziere pentru a ajuta la sincronizare
  Serial.print("Sent color: ");
  Serial.println(colorCommand);
}

// Update player scores based on response
void updateScore(char rating) {
  int points = 0;
  switch (rating) {
    case 'A': points = 50; break;
    case 'B': points = 25; break;
    case 'C': points = 10; break;
    case 'F': points = 0; break;
  }

  if (!isPlayer1Turn) {
    player1Score += points;
  } else {
    player2Score += points;
  }

  // Actualizează afișajul cu scorurile curente
  lcd.clear();
  lcd.print(player1 + ": " + String(player1Score));
  lcd.setCursor(0, 1);
  lcd.print(player2 + ": " + String(player2Score));
}

// Send command over SPI and receive response
char sendCommand(char command) {
  digitalWrite(SS, LOW);
  char response = SPI.transfer(command);
  digitalWrite(SS, HIGH);
  delay(50);  // Întârziere pentru a ajuta la sincronizare
  return response;
}

// Display final scores and winner after game ends
void displayWinner() {
  lcd.clear();
  lcd.print(player1 + " score:");
  lcd.setCursor(0, 1);
  lcd.print(player1Score);
  delay(5000);

  lcd.clear();
  lcd.print(player2 + " score:");
  lcd.setCursor(0, 1);
  lcd.print(player2Score);
  delay(5000);

  lcd.clear();
  if (player1Score > player2Score) {
    lcd.print("Winner: " + player1);
  } else if (player2Score > player1Score) {
    lcd.print("Winner: " + player2);
  } else {
    lcd.print("It's a Draw!");
  }
  delay(2000);
}

// Reset game to initial state
void resetGame() {
  player1Score = 0;
  player2Score = 0;
  roundCounter = 0;
  isPlayer1Turn = true;
  lcd.clear();
  lcd.print("Press to Start!");
}
