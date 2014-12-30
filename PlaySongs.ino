/*
Plays "The Entertainer"
 
circuit:
  8-ohm speaker on digital pin 8

Based Upon: http://arduino.cc/en/Tutorial/Tone

Created by: Nick Ubben, Gregg Ubben, Roger Ubben

*/
#include "Melody.h"
#include "Entertainer.h"
#include "Joy.h"
#include "Clocks.h"
#include "ISUFight.h"

const int ledPin = 13;
const int speakerPin = 8;
  

void setup() {
  // Setup serial input so the song can be selected.
  Serial.begin(9600);
  
  // Need the speaker pin to defined as OUTPUT
  pinMode(speakerPin, OUTPUT);

  // Using the LED to identify when the song is being played.
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin,LOW);
  printInstructions();
}

void loop() {

  if(Serial.available())  // Check to see if at least one
                          // character is available
  {
    char tune = Serial.read();
    Serial.print("Playing ");
    switch(tune)
    {
      case '1':
         Serial.println("Entertainer");
         playMusic(speakerPin, entertainer);
         break;
      case '2':
         Serial.println("Joy");
         playMusic(speakerPin, joy);
         break;
      case '3':
         Serial.println("Clocks");
         playMusic(speakerPin, clocks);
         break;
      case '4':
         Serial.println("ISU Fight Song");
         playMusic(speakerPin, isu_fight);
         break;
      default :
         Serial.print(tune);
         Serial.println("  was received but not expected");
      break;
    }
    Serial.println("");
    printInstructions();    
  }
}

/*
 * Print the instructions
 */
void printInstructions () {
    Serial.println("1  is The Entertainer");
    Serial.println("2  is Joy");
    Serial.println("3  is Clocks");
    Serial.println("4  is ISU Fight Song");
}  


void playMusic(int speakerPin, Note music[]) {
    digitalWrite(ledPin,HIGH);
    
    // iterate over the notes of the melody:
    int thisNote=0;
    while (music[thisNote].note != END_NOTES) {
    
      int dur = music[thisNote].duration;
      
      // to calculate the note duration, take one second 
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000/music[thisNote].duration;
      tone(speakerPin, music[thisNote].note, noteDuration);
    
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      noTone(speakerPin);
      thisNote++;
    }
    digitalWrite(ledPin,LOW);
}

