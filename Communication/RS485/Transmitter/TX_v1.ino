        
#define SerialTxControl 3 // contact # 3 will switch receiver / transmitter mode
#define RS485Transmit HIGH
#define RS485Receive LOW

// output protocol...   < [aux1 stp/fwd/rev] [aux2 stp/fwd/rev] [aux3 stp/fwd/rev] > 
// output values.....   < [      0,  1,   2] [      0,  1,   2] [      0,  1,   2] > 

char output[8];
const char defStr[6] = "<000>";
/*
int decimal = 10;
int hex = 0xA;
int octal = 012;
*/

enum MOTOR_CMD {
    STOP  = 0x0,
    FORWARD = 0x1,
    REVERSE = 0x2,
    INVALID = 0x3
};

// HEXADECIMAL
// 0-9, A - F (A == 10, F == 15)
// 0x is the prefix that says 'anything to the right is hexadecimal'


enum CMD_POSITION {
    POS_LT = 0,
    POS_CMD1,
    POS_CMD2,
    POS_CMD3,
    POS_GT,
    NUM_POS
};

void setup (void) {
    Serial.begin (9600); // set the serial port to 9600baud speed
    pinMode (SerialTxControl, OUTPUT);
    for (int i = 4; i < 10; i++){
      pinMode (i, INPUT);
    }
    digitalWrite (SerialTxControl, RS485Transmit); // put the device into transmitter mode
}


 
void loop (void) {
    memset(output, 0, sizeof(output));
    strcpy(output, defStr);
    
    // bit shift the first value to the left 1 place
    // and bitwise OR with the second value
    //    int CMD_1_PINS =  pinCheck(5) << 1 | pinCheck(4);
    //    00 NOTHING PRESSED
    //    10 PIN-5 PRESSED
    //    11 BOTH
    //    01 PIN-4 PRESSED  
       
    int CMD_1_PINS =  pinCheck(5) << 1 | pinCheck(4);
    int CMD_2_PINS =  pinCheck(7) << 1 | pinCheck(6);
    int CMD_3_PINS =  pinCheck(9) << 1 | pinCheck(8);
    
    setOutput(CMD_1_PINS, POS_CMD1);
    setOutput(CMD_2_PINS, POS_CMD2);
    setOutput(CMD_3_PINS, POS_CMD3);
    Serial.println(output);
    delay(100);
}


bool pinCheck(int inputPin){
    return digitalRead(inputPin) == HIGH;
}

void setOutput(int command, int position) {
    switch(command) {
        case FORWARD:
            output[position] = '1';
            break;
        case REVERSE:
            output[position] = '2';
            break;
        case STOP:
        case INVALID:
        default:
            output[position] = '0';
    }
}
