const int sensorPin = 4;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 //pinMode(sensorPin, INPUT);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(sensorPin) == HIGH){
    Serial.println("1");
 
  }
  else{
    Serial.println("0");
  }
 /*

int valorAnalogico = analogRead(3);

if(valorAnalogico > 79)
{
  Serial.print("en la linea: ");
  Serial.println(valorAnalogico);
}
else
{
  Serial.print("Fuera de la linea:  ");
  Serial.println(valorAnalogico);
}*/
}