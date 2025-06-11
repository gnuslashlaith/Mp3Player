#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySerial(4, 3); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

// song arrays

const char* songNames
