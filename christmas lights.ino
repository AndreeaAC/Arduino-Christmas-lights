
#include <IRremote.h>

const int receiver = 5; 
IRrecv irrecv(receiver);
decode_results results;

const byte releuPin = 6;
const byte releuPin1 = 5;
volatile byte stat = 1;
byte ok=0;
volatile int intarziere = 0;
volatile int ceva = 0;
const int buzzerPin = 4;


volatile byte mod = 0; // 0 - stop, 1 - play, 2 - pauza

const byte length = 64;

const char * notes = { "ggdgadbabCbaggsesgabsedd DCbCbabgasedggsgagdbbabCbabCbagsgCbagg " };
                     
const byte beats[] = {2,4,2,2,4,4,2,2,2,2,4,2,2,4,2,2,2,2,2,2,4,3,1,6,2,4,2,2,4,4,2,2,2,2,3,1,2,2,2,2,2,2,4,2,2,2,2,2,2,4,2,2,2,2,2,2,4,2,2,4,3,1,6,8};

const int tempo = 150;

void playNote(char note, int duration) 
{
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D', 'E', 'F', 'G', 'A', 'B' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956, 851, 758, 716, 636, 568, 506 };  

  for (int i = 0; i < 12; i++) 
  {
    if (names[i] == note) playTone(tones[i], duration);
  }
}


void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(tone);
  }
}


void setup()

{
  irrecv.enableIRIn();
  pinMode(releuPin, OUTPUT);  
  pinMode(releuPin1, OUTPUT);  
  pinMode(buzzerPin, OUTPUT);
//  Serial.begin(9600);
}

void loop() {
if(ceva==0) {delay(5000);
ceva = 1;}

 
    for (int n = 0; n < length; n++) 
    {
     

    if ( ok==0)
    {
      digitalWrite(releuPin,LOW);
      digitalWrite(releuPin1,HIGH);
      
       ok=1;
      // delay(200);
     }
     else
       {
         ok=0;
       digitalWrite(releuPin,HIGH);
       digitalWrite(releuPin1,LOW);
         //delay(200);
       }
      
      if (notes[n] == ' ') delay(beats[n] * tempo); 
      else playNote(notes[n], beats[n] * tempo);
      delay(tempo / 2);
    if (results.value==0x807FA05F) mod=!mod;
    
    if (n==length-24) {delay(3500);
    intarziere=1;}
    
    }


  
  
  
  if (irrecv.decode(&results)) 
  {
    
    if(results.value==0xFF30CF) {stat=!stat;
   
    }
    else playTone(2000,500);
   if (results.value==0x807FA05F) mod=!mod;

    irrecv.resume(); 
  }

}




