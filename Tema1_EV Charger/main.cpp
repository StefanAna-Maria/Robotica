//Definire pini 
const int led1 = 10;
const int led2 = 9;
const int led3 = 8;
const int led4 = 7;
const int ledRGB_R = 6;
const int ledRGB_B = 5;
const int ledRGB_G = 4;
const int buttonStart = 3;
const int buttonStop = 2;

//Variabile pt. stare
unsigned long lastUpdate = 0;
unsigned long buttonPressTime = 0;
bool stopButtonPressed = false;
bool stopButtonHeld = false;
const unsigned long interval = 3000;
int batteryLevel = 0;
bool charging = false;
bool stationFree = true;
bool finalBlinking = false;
int blinkCount = 0;

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(ledRGB_R, OUTPUT);
  pinMode(ledRGB_G, OUTPUT);
  pinMode(buttonStart, INPUT_PULLUP);
  pinMode(buttonStop, INPUT_PULLUP);

  setStationFree();
}

void loop()
{
  //verific daca butonul de start a fost apasat si statia este libera
  if (digitalRead(buttonStart) == LOW && stationFree) 
  {
    delay(100);//debounce
    startCharging();
  }

  //verific daca butonul de stop a fost apasat si incarcarea este activa
  if (digitalRead(buttonStop) == LOW && !stopButtonPressed && charging)
  {
    //se inregistreaza timpul la care am apasat butonul
    buttonPressTime = millis();
    stopButtonPressed = true;
    stopButtonHeld = false;
  }

  //gestionarea pt apasarea lunga pe butonul de stop
  if (stopButtonPressed)
  {
    if (digitalRead(buttonStop) == HIGH)
    {
      //butonul a fost eliberat
      unsigned long pressDuration = millis() - buttonPressTime;
      stopButtonPressed = false;

      //daca butonul a fost apasat timp de minim 1 sec -> oprim incarcarea si pornim clipirea led-urilor
      if (pressDuration >= 1000 && charging){
        stopChargingAndBlink(); // Oprire imediată și clipire simultană a LED-urilor
      } else if (charging && !stopButtonHeld) {
        //daca butonul s-a apasat scurt si incarcarea este activa -> oprim statia
        stopCharging();
      }
    } 
    else if (millis() - buttonPressTime >= 1000 && !stopButtonHeld && charging)
    {
      stopButtonHeld = true;
      stopChargingAndBlink();
    }
  }

  //incarcarea progresiva
  if (charging && !finalBlinking) 
  {
    unsigned long currentMillis = millis();
    if (currentMillis - lastUpdate >= interval)
    {
      updateBatteryLevel();
      lastUpdate = currentMillis;
    }
  }

  if (finalBlinking) {
    blinkAllLedsFinal();
  }
}

//fct start incarcare
void startCharging() 
{
  charging = true;
  stationFree = false;
  setRGBColor(255, 0, 0);//ocupat
  batteryLevel = 0;
  updateBatteryLevel();
}

//fct oprire incarcare si clipire
void stopChargingAndBlink()
{
  charging = false;
  finalBlinking = true;
  blinkCount = 0;
  lastUpdate = millis();
}

//fct oprire nefortata a incarcarii
void stopCharging() 
{
  charging = false;
  setStationFree();
}

//fct incarcare baterie
void updateBatteryLevel() 
{
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  
//aprinderea progresiva a led-urilor
  if (batteryLevel == 0){
    blinkLED(led1);
  } else if (batteryLevel == 1) {
    digitalWrite(led1, HIGH);
    blinkLED(led2);
  } else if (batteryLevel == 2) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH); 
    blinkLED(led3);
  } else if (batteryLevel == 3) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    blinkLED(led4);
  }

  batteryLevel++;

  if (batteryLevel > 3){
  delay(500);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
    delay(500);
    batteryLevel = 0;
    startFinalBlinking();
  }
}

//fct blink pt LED
void blinkLED(int ledPin) 
{
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
}

//fct pt setarea led-ului RGB
void setRGBColor(int red, int green, int blue) 
{
  analogWrite(ledRGB_R, red);
  analogWrite(ledRGB_G, green);
  analogWrite(ledRGB_B, blue);
}

//fct pt resetarea statiei
void setStationFree() 
{
  stationFree = true;
  charging = false;
  finalBlinking = false;
  setRGBColor(0, 255, 0);// verde
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
}

//fct pt inceperea secventei de clipire finala
void startFinalBlinking() 
{
  charging = false;
  finalBlinking = true;
  blinkCount = 0;
  lastUpdate = millis();
}

//fct pentru clipirea finala a celor 4 led-uri
void blinkAllLedsFinal()
{
  unsigned long currentMillis = millis();
  if (currentMillis - lastUpdate >= 500) 
  {
    lastUpdate = currentMillis;
    
    bool state = blinkCount % 2 == 0;
    digitalWrite(led1, state);
    digitalWrite(led2, state);
    digitalWrite(led3, state);
    digitalWrite(led4, state);
    
    blinkCount++;
    if (blinkCount >= 6)
    {
      finalBlinking = false;
      setStationFree();
    }
  }
}
