#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySerial(4, 3); // TX, RX. 
DFRobotDFPlayerMini myDFPlayer;

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
    "womb.mp3"

}

const int totalSongs = sizeof(songNames) / sizeof(songNames[0]);
int currentSongIndex = 0;
int volume =  10;

void setup() {
    Serial.begin(9600);
    mySerial.begin(9600);
    
    if(!myDFPlayer.begin(mySerial)) {
        Serial.println("DFPlayer Mini NOT FOUND!11!!")
        while(true);
    }

    myDFPlayer.volume(volume);
}

void loop() {
    // just checkin' for functionality tbh. should use the BUSY pin. 
    // but who has time for that?

    myDFPlayer.play(currentSongIndex + 1); // apparently the tf-mp3-16p has its index start with 1. who does that?


}
