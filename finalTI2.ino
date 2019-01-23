#include <SPI.h>
#include <bitBangedSPI.h>
#include "RF24.h"
#include <MAX7219.h>


int prev = 0;
int prev2 = 0;
int selectChar = 0;
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
RF24 radio (10, 9);
char characters[8] = {'H','E','L','L','O','P','P','L'};
MAX7219 display (1 , 1, 2, 0); 

void setup() {
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  // put your setup code here, to run once:
  //Serial.begin(115200);
  //Serial.println ("RF24 TI Testing Monitor!");
  //radio stuff
  radioInit();
  //end of tadio stuff
  display.begin();
  display.sendString("Starting");
  delay(1000);
  display.sendString(characters);
}

void radioInit() {
  radio.begin();
  radio.setRetries(15,15);
 // radio.setPayloadSize(8);
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  radio.startListening();
  //radio.printDetails();  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(radio.available()) {
     display.sendString("Recieving");
     while(radio.available()) {
      
           radio.read(&characters,strlen(characters));
    }
      for(int x = 0;x<8;x++) {
            if(selectChar == x) {
              display.sendChar(x, characters[x], true); 
            }
            else {
            display.sendChar(x, characters[x], false); 
            }
        }
  }
  digitalWrite(7,LOW);
  digitalWrite(6,HIGH);
  if(digitalRead(3) == LOW) {
    if(prev2 != 1) {
          if(characters[selectChar] == 90) {
              characters[selectChar] = 0;
          }          
          else if(characters[selectChar] == 0) {
              characters[selectChar] = 65;
          }
          else {
              characters[selectChar]++;
          }
          display.sendChar(selectChar, characters[selectChar], true); 
    }
    prev2 = 1;
  }
  
  else if(digitalRead(5) == LOW) {
     if(prev2 != 1) {
         display.sendChar(selectChar, characters[selectChar], false); 
         if( selectChar > 0) {
          selectChar--;
         }
         else {
          selectChar = 0;
         }
         display.sendChar(selectChar, characters[selectChar], true); 
        }
        prev2 = 1;
  }
  else if(digitalRead(4) == LOW) {

     if(prev2 != 1) {
      display.sendChar(selectChar, characters[selectChar], false); 
     if( selectChar < 7) {
      selectChar++;
     }
     else {
      selectChar = 0;
     }
     display.sendChar(selectChar, characters[selectChar],true); 
    }
    prev2 = 1;
    
   
  }
  else {
   prev2 = 0; 
  }
  delay(10);
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  if(digitalRead(3) == LOW) {
      if(prev != 1) {
       if(characters[selectChar] == 65) {
              characters[selectChar] = 0;
          }          
          else if(characters[selectChar] == 0) {
              characters[selectChar] = 90;
          }
          else {
              characters[selectChar]--;
          }
          display.sendChar(selectChar, characters[selectChar], true); 
    }
    prev = 1;
  }
  else if(digitalRead(5) == LOW) {
    if(prev != 2) {
        for(int x = 0;x<8;x++) {
            characters[x] = 0;
            if(selectChar == x) {
              display.sendChar(x, characters[x], true); 
            }
            else {
            display.sendChar(x, characters[x], false); 
            }
        }
    }
    prev = 2;
  }
  else if(digitalRead(4) == LOW) {
    if(prev != 2) {
      display.sendString("Sending");
      radio.stopListening();
       radio.write(&characters, strlen(characters));
       radio.startListening();
        for(int x = 0;x<8;x++) {
            if(selectChar == x) {
              display.sendChar(x, characters[x], true); 
            }
            else {
            display.sendChar(x, characters[x], false); 
            }
        }
    }
    prev = 2;
  }
  else {
   prev = 0; 
  }
  
  delay(10);
}
