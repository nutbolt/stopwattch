volatile int flag = HIGH;
unsigned long now = 0;
unsigned long previous = 0;
unsigned long timer = 0;
unsigned int watt = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(PUSH2, INPUT_PULLUP);
  attachInterrupt(PUSH2, pulse, FALLING);
  
  previous = millis();
}

void loop() { // Try to keep execution time under 1ms, otherwise the millis()-based time scheduler won't work
  
  if(flag) {
    now = millis();
    watt = 360000/(now - previous);
    previous = now;
    flag = LOW;
  }
  
  if(millis() % 1000 == 0) {
    Serial.print("w:");
    Serial.println(watt);
    delay(4); // Dirty hack to send stuff only once
  }
  
}

void pulse() {
  flag = HIGH;
}
