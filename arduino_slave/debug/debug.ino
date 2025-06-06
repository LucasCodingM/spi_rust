
int _SCK = 13;
int _MOSI = 12;
int _MISO = 11;
int _SS = 10;

int lastSCK = -1;
int lastMOSI = -1;
int lastMISO = -1;
int lastSS = -1;

void setup() {
  Serial.begin(115200);

  pinMode(_SCK, INPUT); // SPI SCK pin on Arduino Uno is digital pin 13
  pinMode(_MOSI, INPUT); // MOSI − This is the master output / slave input driven by the master
  pinMode(_MISO, INPUT); // MISO − This is the master input / slave output driven by the master
  pinMode(_SS, INPUT); // SS − This is the slave-selection wire

}

void loop() {
  checkPinChange(_SCK, &lastSCK, "SCK");
  checkPinChange(_MOSI, &lastMOSI, "MOSI");
  checkPinChange(_MISO, &lastMISO, "MISO");
  checkPinChange(_SS, &lastSS, "SS");
}

void checkPinChange(int pin, int* lastState, const char* label) {
  int currentState = digitalRead(pin);
  if (currentState != *lastState) {
    *lastState = currentState;
    Serial.print(label);
    Serial.print(" changed to ");
    Serial.println(currentState == HIGH ? "HIGH" : "LOW");
  }
}
