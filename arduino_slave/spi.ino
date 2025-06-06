#include <SPI.h>

// SCK  -> pin 13
// MOSI -> pin 12
// MISO -> pin 11
// SS   -> pin 10
char buff [50];
volatile byte indx;
volatile boolean process;


void setup (void) {
   Serial.begin (115200);
   pinMode(MISO, OUTPUT); // have to send on master in so it set as output

   // Configure SPI
   SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE1));

   indx = 0; // buffer empty
   process = false;
   SPI.attachInterrupt(); // turn on interrupt
}

ISR (SPI_STC_vect) // SPI interrupt routine 
{
   byte c = SPDR; // read byte from SPI Data Register
   
   if (indx < sizeof( buff)) {
      buff [indx++] = c; // save data in the next index in the array buff
      if (c == '\r' || c == '\0' || c == '\n') {
         buff[indx] = '\0'; // null terminate the string!
         process = true;
      }
   }
}

void loop (void) {

   if (process) {
      process = false; //reset the process
      Serial.println (buff); //print the array on serial monitor
      indx= 0; //reset button to zero
   }
}
