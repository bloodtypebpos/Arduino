// Example 3 - Receive with start- and end-markers

#define SerialTxControl 3
#define RS485Transmit HIGH
#define RS485Receive LOW

byte state = 0;

int led1 = 12;
int led2 = 11;


const byte numChars = 32;
char receivedChars[numChars];

boolean newData = false;

void setup() {
    Serial.begin (9600);
    pinMode (led1, OUTPUT); 
    pinMode (led2, OUTPUT);
    pinMode (SerialTxControl, OUTPUT); 
    digitalWrite (SerialTxControl, RS485Receive); // put the device into receiver mode
    digitalWrite (led2, HIGH);
}

void loop() {
    recvWithStartEndMarkers();
    showNewData();
}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    
 
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void showNewData() {
    if (newData == true) {
        Serial.print("This just in ... ");
        Serial.println(receivedChars);
        Serial.println(receivedChars[0]);
        if (String(receivedChars) == "ping"){
          digitalWrite(led2, state);
          state =! state;
          digitalWrite(led1, state);
        } 
        newData = false;
    }
}
