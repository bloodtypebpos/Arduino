        
#define SerialTxControl 3 // contact # 3 will switch receiver / transmitter mode
#define RS485Transmit HIGH
#define RS485Receive LOW

String output;


void setup (void) {
    Serial.begin (9600); // set the serial port to 9600baud speed
    pinMode (SerialTxControl, OUTPUT);
    digitalWrite (SerialTxControl, RS485Transmit); // put the device into transmitter mode
}
 
void loop (void) {
    Serial.print ("<ping>"); // send text
    delay (1000);
}


