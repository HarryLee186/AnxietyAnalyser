
#include <PulseSensorPlayground.h>

volatile int BPM;
volatile boolean QS = false;
volatile int IBI = 600;
volatile int Signal;
volatile boolean Pulse = false;

int pulsePin = 0;
int blinkPin = 11;

void setup() {
Serial.begin(115200);
interruptSetup();

  }

void loop(){  
  
  if (QS == true) {  
    Serial.write(BPM);
    QS = false;
   }
  //delay(2500);
}




