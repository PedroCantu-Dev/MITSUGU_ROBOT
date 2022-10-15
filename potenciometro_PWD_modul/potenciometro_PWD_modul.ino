int avance = 8;
int retroceso = 9 ;
int enableMotor = 10;
int speedMotor = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(avance, HIGH);
  digitalWrite(avance,LOW);
  speedMotor = analogRead(A0);
  speedMotor = speedMotor * (255/1023); 
  analogWrite(enableMotor , speedMotor);
}

/*1023 = 255
x = x*255/1023
*/
