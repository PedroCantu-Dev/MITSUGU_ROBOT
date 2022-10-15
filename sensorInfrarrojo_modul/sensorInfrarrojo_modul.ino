
int input = 13;
int output = 10;

void setup() {
  // put your setup code here, to run once:
pinMode(input, INPUT);
pinMode(output, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int lectura = digitalRead(input);
  if(digitalRead(input)==HIGH)
  {
    digitalWrite(output,LOW);
    Serial.println("UP");
    
  }
  else{
     digitalWrite(output,HIGH);
    Serial.println("DOWN");
  }
}
