#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <GyverOLED.h>

SoftwareSerial mySerial(8, 7); // TX, RX. 
GyverOLED<SSH1106_128x64> oled(0x3C);

DFRobotDFPlayerMini myDFPlayer;

int lastVolume = -1;
// song arrays

const char* songNames[] = { 
    "constellations.mp3",
    "dull.mp3",
    "fine.mp3",
    "hand-comes-down.mp3",
    "kiss-a-girl-in-black.mp3",
    "Painfully.mp3",
    "pennies.mp3",
    "pitseleh.mp3",
    "resonance.mp3",
    "weirdo-summer-hug.mp3",
    "womb.mp3",

};

const int totalSongs = sizeof(songNames) / sizeof(songNames[0]);
int currentSongIndex = 0;
int volume =  15;

//buttons
const int nextButtonPin = 13;
const int prevButtonPin = 14;
const int toggle = 15;

bool nextPressed = false;
bool prevPressed = false;
bool togglePressed = false;

bool isPlaying = true;

void setup() {
    Serial.begin(9600);
    mySerial.begin(9600);
    
    if(!myDFPlayer.begin(mySerial)) {
        Serial.println("DFPlayer Mini NOT FOUND!11!!");
        while(true);
    }

    myDFPlayer.volume(volume);
    myDFPlayer.play(currentSongIndex + 1);

    pinMode(nextButtonPin, INPUT_PULLUP);
    pinMode(prevButtonPin, INPUT_PULLUP);
    pinMode(toggle, INPUT_PULLUP);

    oled.init();
    oled.clear();
    oled.update();
}

void loop() {

  int potValue = analogRead(A0);
  int newVolume = map(potValue, 0, 1023, 0, 30);
    // just checkin' for functionality tbh. should use the BUSY pin. 
    // but who has time for that?

  if(digitalRead(nextButtonPin) == LOW && !nextPressed) {
    nextPressed = true;
    currentSongIndex = (currentSongIndex + 1) % totalSongs;
    myDFPlayer.play(currentSongIndex + 1);
    oled.setCursorXY(28,28);
    oled.print("Now playing: ");
    oled.print(currentSongIndex + 1);
    oled.update();

    isPlaying = true;
    delay(200);
  } else if (digitalRead(nextButtonPin) == HIGH) {
    nextPressed = false;
  }
  
  if (digitalRead(prevButtonPin) == LOW && !prevPressed) {
        prevPressed = true;
        currentSongIndex = (currentSongIndex - 1 + totalSongs) % totalSongs;
        myDFPlayer.play(currentSongIndex + 1);
        oled.setCursorXY(28,28);
        oled.print("Now playing: ");
        oled.print(currentSongIndex+1);
        oled.update();
        isPlaying = true;
        
        delay(200);
    } else if (digitalRead(prevButtonPin) == HIGH) {
        prevPressed = false;
    }

    if (digitalRead(toggle) == LOW && !togglePressed) {
        togglePressed = true;

        if (isPlaying) {
            myDFPlayer.pause();
            oled.setCursorXY(28,15);
            oled.print("paused");
            oled.update();
            isPlaying = false;
        } else {
            myDFPlayer.start(); 
            isPlaying = true;
        }

        delay(200);
    } else if (digitalRead(toggle) == HIGH) {
        togglePressed = false;
        oled.setCursorXY(28,15);
        oled.print("MP3 Player");
        oled.update();
    }


  if(newVolume != lastVolume) {
    myDFPlayer.volume(newVolume);
    lastVolume = newVolume;
  }

  oled.setCursorXY(28, 50);
  oled.print("Volume: ");
  oled.print(newVolume);
  oled.update();



}
