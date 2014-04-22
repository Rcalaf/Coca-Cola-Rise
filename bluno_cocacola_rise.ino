int fsrAnalogPin = 0; // FSR is connected to analog 0
int LEDpin = 11; // connect Red LED to pin 11 (PWM pin)
const int alarmPin = 13;
int fsrReading; // the analog reading from the FSR resistor divider
int LEDbrightness;

unsigned long time = 0;
unsigned long resetTime = 0;
unsigned long sittedTime = 0;

float alarm = false;

void setup(void) {
  
Serial.begin(115200); // We'll send debugging information via the Serial monitor
//Serial.begin(9600);
pinMode(LEDpin, OUTPUT);
pinMode(alarmPin, OUTPUT); 

}

void loop(void) {

time = millis()/1000;  
  
fsrReading = analogRead(fsrAnalogPin);

// we'll need to change the range from the analog reading (0-1023) down to the range
// used by analogWrite (0-255) with map!
LEDbrightness = map(fsrReading, 0, 1023, 0, 255);
// LED gets brighter the harder you press
analogWrite(LEDpin, LEDbrightness);

if (LEDbrightness > 0) {  
    sittedTime = time;
    //Serial.println("seated time:");
    //Serial.println(time - resetTime);
    if (time - resetTime >= 30 && !alarm) {
      if(Serial.available()){
        digitalWrite(alarmPin, HIGH);
        Serial.write("ALARM");
        
      }
      alarm = true;
    }
}else {
    //Serial.println("unsitted:");
    //Serial.println(time - sittedTime);
    if(time - sittedTime >= 5 && alarm){
      resetTime = time;
      if(Serial.available()){
        Serial.write("STOP");
      }
      alarm = false;
    }
    digitalWrite(alarmPin, LOW);
}

//delay(100);
}

