#define MQ2pin 34 //pino do sensor do gás
#define GREEN 32 //pino do led verde
#define RED 33 //pino do led vermelho

float sensorValue;  //variável para armazenar o valor do sensor

void setup() {
  Serial.begin(9600); // sets the serial port to 9600
  Serial.println("MQ2 warming up!");
  delay(1000); // allow the MQ2 to warm up
  pinMode(GREEN, OUTPUT); //define o pino verde como de saída
  pinMode(RED, OUTPUT); //define o pino vermelho como de saída
}

void loop() {
  sensorValue = analogRead(MQ2pin); // obtém a leitura do pino do sensor do gás

  if(sensorValue > 1000) { //se valor > 1000  
    Serial.println("Tá detectando gás, bicho!!!");
    digitalWrite(GREEN, LOW);
    delay(1000);
    digitalWrite(RED, HIGH);
  } else {    
    digitalWrite(GREEN, HIGH);
    delay(1000);
    digitalWrite(RED, LOW);    
  }

  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  
  delay(1000); // wait 1s for next reading
}
