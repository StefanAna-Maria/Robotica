#include <Arduino.h>

//definire pini
const int redPin = 6;
const int greenPin = 5;
const int bluePin = 4;
const int start_stopButtonPin = 3;
const int difficultyButtonPin = 2;

//declarare variabile
bool isCountingDown = false;
bool isRoundActive = false;
unsigned long roundStartTime = 0;
unsigned long wordDisplayStartMilliseconds = 0;

//dictionar de cuvinte:
const int wordsCount = 10;
const String dictionary[wordsCount] = {"arduino", "code", "project", "game", "challenge", "input", "output", "sensor", "motor", "display"};
String currentWord = "";
String userInput = "";
int correctWordsCounter = 0;

enum Difficulty {
  EASY = 0,
  MEDIUM = 1,
  HARD = 2
};

Difficulty difficulty = EASY;
int timePerWord = 5000;  //timpul initial pentru dificultatea EASY (5 secunde)

void setRgbLed(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

void setup() {
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(start_stopButtonPin, INPUT_PULLUP);
  pinMode(difficultyButtonPin, INPUT_PULLUP);

  //LED-ul in stare de repaus este alb static
  setRgbLed(255, 255, 255);
  //dificultatea default este EASY
  Serial.println("Easy mode on!");
}

void selectNewWord() {
  int index = random(wordsCount);
  currentWord = dictionary[index];
  wordDisplayStartMilliseconds = millis();
  userInput = "";  //se reseteaza inputul utilizatorului
  Serial.print("\nType this word: ");
  Serial.println(currentWord);
}

//Fct pt inceperea rundei
void startRound() {
  Serial.println("START! Type the following words:");
  correctWordsCounter = 0;  //resetez scorul la inceputul rundei
  isRoundActive = true;
  roundStartTime = millis();
  userInput = "";
  selectNewWord();
}

//Fct pt oprirea rundei
void stopRound() {
  isRoundActive = false;
  Serial.print("\n Game Over!");
  Serial.print("\n Score: ");
  Serial.println(correctWordsCounter);
  setRgbLed(255, 255, 255); //LED-ul redevine alb la final de runda
}

//Fct pt schimbarea dificultatii jocului
void changeDifficulty() {
  if (!isRoundActive) {
    difficulty = (Difficulty)(((int)difficulty + 1) % 3); //se cicleaza dificultatea
    switch (difficulty) {
      case EASY:
        Serial.println("Easy mode on!");
        timePerWord = 5000; // 5 secunde pt fiecare cuvant
        break;
      case MEDIUM:
        Serial.println("Medium mode on!");
        timePerWord = 3000; // 3 secunde pt fiecare cuvant
        break;
      case HARD:
        Serial.println("Hard mode on!");
        timePerWord = 2000; // 2 secunde pt fiecare cuvant
        break;
    }
  }
}

//Fct pt numaratoarea inversa
void handleCountdown() {
  int startGameAnimationDurationSeconds = 3; //clipirea pt numaratoarea inversa
  for (int i = startGameAnimationDurationSeconds; i >= 0; i--) {
    setRgbLed(255, 255, 255);
    delay(500);
    setRgbLed(0, 0, 0);
    delay(500);
    if (i > 0) {
      Serial.println(i);
    }
  }

  //dupa 3 clipiri, LED-ul devine verde si incepe runda
  setRgbLed(0, 255, 0);
  startRound();
}

//Fct pt verificarea input-ului jucatorului
void handleUserInput() {
  if (Serial.available() > 0) {
    char inputChar = Serial.read();

    //detectez "backspace" pt stergerea ultimului caracter introdus
    if (inputChar == '\b' && userInput.length() > 0) {
      userInput.remove(userInput.length() - 1);
      Serial.print("\b \b");  //sterg caracterul anterior de pe ecran
    } 
    else if (isPrintable(inputChar) && inputChar != '\n') {  
      userInput += inputChar;
      Serial.print(inputChar); //afisarea caracterului pe ecran
    }

    //verificarea in timp real a caracterelor introduse
    if (currentWord.startsWith(userInput)) {
      setRgbLed(0, 255, 0);  //LED-ul este verde cat timp input-ul este corect
      //verific daca intregul cuvant este corect
      if (userInput.equals(currentWord)) { 
        correctWordsCounter++;
        delay(500);
        selectNewWord(); //se trece la un cuvant nou
      }
    } else {
      setRgbLed(255, 0, 0);  //LED-ul devine Rosu cand apare o greseala
    }
  }
}

void loop() {
  //gestionarea butoanelor
  if (digitalRead(start_stopButtonPin) == LOW) {
    if (!isCountingDown && !isRoundActive) {
      isCountingDown = true;
      handleCountdown();
      isCountingDown = false;
      delay(200);
    } else if (isRoundActive) {
      stopRound();
      delay(200);
    }
  }

  if (digitalRead(difficultyButtonPin) == LOW) {
    changeDifficulty();
    delay(200);
  }

  //logica pt runda activa
  if (isRoundActive) {
    if (millis() - wordDisplayStartMilliseconds >= timePerWord) {
      selectNewWord();
    }
    handleUserInput();
    if (millis() - roundStartTime >= 30000) { //durata maxima a unei runde (30 sec)
      stopRound();
    }
  }
}
