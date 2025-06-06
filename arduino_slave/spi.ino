#include <SPI.h>
char buff [50];
volatile byte indx;
volatile boolean process;


void setup (void) {
   Serial.begin (115200);
   pinMode(MISO, OUTPUT); // have to send on master in so it set as output

   SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE1)); // example mode1, adjust as needed
   //SPCR |= _BV(SPE); // turn on SPI in slave mode
   indx = 0; // buffer empty
   process = false;
   SPI.attachInterrupt(); // turn on interrupt
}

ISR (SPI_STC_vect) // SPI interrupt routine 
{
   //cli();
   byte c = SPDR; // read byte from SPI Data Register

//   Serial.print("Received: ");
//   Serial.println((char)c);  // Print received byte in HEX
   if (indx < sizeof( buff)) {
      buff [indx++] = c; // save data in the next index in the array buff
      if (c == '\r') {
         buff[indx] = '\0'; // null terminate the string!
         process = true;
      }
   }
   //sei();
}

void loop (void) {
//  int state = digitalRead(13);
//  Serial.println(state == HIGH ? "HIGH" : "LOW");

   if (process) {
      process = false; //reset the process
      Serial.println (buff); //print the array on serial monitor
      indx= 0; //reset button to zero
   }
}
