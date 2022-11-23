#define MODE_MANUAL 0
#define MODE_AUTO   1	

int ledPinGreen = 32;
int ledPinRed = 33;
int ledChannel = 0;
int ledValue = 10;
int ledMode = MODE_MANUAL;

int mq2Pin = 34;
int mq2Max = 10000;

int thresholdValue = 3000;

void setup() {
    Serial.begin(9600);

    pinMode(LED_BUILTIN, OUTPUT);
    for (int i=9; i>=0; i--) {
        digitalWrite(LED_BUILTIN, i % 2 ? HIGH : LOW);
        delay(50);
    }

    ledcSetup(1, 5000, 8);
    ledcAttachPin(LED_BUILTIN, 1); // Led Builtin aceita PWM no ESP32
    
    pinMode(ledPinGreen, OUTPUT);
    // ledcSetup(ledChannel, 5000, 8);
    // ledcAttachPin(ledPinGreen, ledChannel);
    
    pinMode(ledPinRed, OUTPUT);
    // ledcSetup(ledChannel, 5000, 8);
    // ledcAttachPin(ledPinGreen, ledChannel);
    
    Serial.printf("DBG SmartGas Initialized.\n");
}

 
void loop() {
    String serialCommand;

    while (Serial.available() > 0) {
        char serialChar = Serial.read();
        serialCommand += serialChar; 

        if (serialChar == '\n') {
            processCommand(serialCommand);
            serialCommand = "";
        }
    }

    ledUpdate();
    delay(100);
}


void processCommand(String command) {
    command.trim();
    command.toUpperCase();

    // Serial.println("DBG Received command: " + command);

    // if (command.startsWith("SET_LED ")) {
    //     int ledTmp = command.substring(8).toInt();
    //     if (ledTmp >= 0 && ledTmp <= 100) {
    //         ledValue = ledTmp;
    //         ledMode  = MODE_MANUAL;
    //         ledUpdate();
    //         Serial.printf("RES SET_LED 1\n");
    //     }
    //     else {
    //         Serial.printf("RES SET_LED -1\n");
    //     }
    // }
    // else 
    if (command.startsWith("SET_THRESHOLD ")) {
        int thresholdTmp = command.substring(14).toInt();
        if (thresholdTmp >= 300 && thresholdTmp <= 10000) {
            thresholdValue = thresholdTmp;
            ledMode = MODE_AUTO;
            ledUpdate();
            Serial.printf("RES SET_THRESHOLD 1\n");
        }
        else {
            Serial.printf("RES SET_THRESHOLD -1\n");
        }
    }

    else if (command == "GET_MQ2")
      Serial.printf("RES GET_MQ2 %d\n", mq2GetValue());

    // else if (command == "GET_LED")
    //   Serial.printf("RES GET_LED %d\n", ledValue);
    
    else if (command == "GET_THRESHOLD")
      Serial.printf("RES GET_THRESHOLD %d\n", thresholdValue);
    
    else
      Serial.println("ERR Unknown command.");
      
}

void ledUpdate() {
    if (
        // ledMode == MODE_MANUAL || (ledMode == MODE_AUTO && 
        mq2GetValue() > thresholdValue
        // )
        ) {
        // ledcWrite(ledChannel, 255.0*(ledValue/100.0));
        // ledcWrite(1, 255.0*(ledValue/100.0));
        Serial.println("Tá detectando gás, bicho!!!");
        digitalWrite(ledPinGreen, LOW);
        delay(1000);
        digitalWrite(ledPinRed, HIGH);
    }
    else {
        // ledcWrite(ledChannel, 0);
        // ledcWrite(1, 0);
        digitalWrite(ledPinGreen, HIGH);
        delay(1000);
        digitalWrite(ledPinRed, LOW);  
    }
}

int mq2GetValue() {
    int mq2Analog = analogRead(mq2Pin);
    // int mq2Value = 100*mq2Analog/mq2Max;

    // Serial.printf("DBG MQ2_MAX=%d, MQ2_ANALOG=%d, MQ2_VALUE=%d\n", mq2Max, mq2Analog, mq2Value);

    return mq2Analog;
    // return mq2Value > 100 ? 100 : mq2Value;
}
