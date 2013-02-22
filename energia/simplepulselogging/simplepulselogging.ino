/*
 Logging pulses from meter to be picked up by Python over a serial connection.
 Bart Nijssen 2013-02-15
 
 Simplyfied version where python handles more data & calculations
 */

// setting constants

int incomingByte = 0;   // for incoming serial data

int verbruik_deler = 100;                    // deelwaardes van de opbrengstmeter  (10000 pulses per 1kWh
unsigned long teller_verbruik = 0;           // De tellers als LONG (unsigned), dan kunnen de tellers eventueel 2^32 als (positieve) waarde hebben
unsigned long dagteller_verbruik = 0;
int resolutie = 10;
int resolutie_count = 0;
float dagverbruik;
unsigned int verstreken = 0;
int teller_controle_kw=0;
unsigned int valverbruik_nu = 0;
unsigned long time = 0;


// setting for fakepulse
long randNumber;
int ledPin = RED_LED;
int nepPin = 0;

// arduino setup for pins etc.
void setup() {
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  Serial.begin(9600);           // opens serial port, sets data rate to 9600 bps
  time = millis();              // start registering time
}

// hoofdlus
void loop() {
  fakePulse();                  // fakePulse inladen zodat we kunnen simuleren
  
  if(nepPin==0){                // Als pulse is HIGH begint de actie
   //   teller_controle_kw = teller_verbruik;
  //    teller_verbruik = (teller_verbruik +1);
      resolutie_count = resolutie_count + 1;
   //   incomingByte = Serial.read();

    //  if ( (teller_verbruik - teller_controle_kw) >1) {     // Waarom deze controle erin zit is nog niet helemaal duidelijk.
    //     teller_verbruik=teller_controle_kw + 1;    
    //    }
      
    //  dagteller_verbruik = (dagteller_verbruik +1);
    //  dagverbruik = ((float)dagteller_verbruik / verbruik_deler);  
    
      if (resolutie_count == resolutie) {
        
        //  Serial.print(dagverbruik);
        //  Serial.print(", ");
          reset_tellers();
          Serial.println(valverbruik_nu);
          
        }
     // if (incomingByte==49) {
     //   dagteller_verbruik = 0;
     // }
  }
}

void fakePulse() {                // functie voor om de nepPulse te generen
  randNumber = random(340,380);  // 360 milliseconde tussen de puls
  digitalWrite(ledPin, HIGH);   
  nepPin = 1;
  delay(100);                
  digitalWrite(ledPin, LOW);    
  nepPin = 0;
  delay(randNumber-100);  
}

void reset_tellers()            // bereken opgenomen vermogen in de afgelopen tijdseenheid
{     
      verstreken = (millis() - time);// / 100;          // misschien moet die 100 hier toch in, maar resolutie?
      valverbruik_nu = (((float)(10 * 1000) / verstreken) * 360); // teller / tijdseenheid tussen resets, uitkomst * 3600 sec/h
      time = millis(); 
      teller_verbruik = 0;
      resolutie_count = 0;
}

