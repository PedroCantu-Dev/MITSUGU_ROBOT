const int sensorPin = 7;

//pines para el motor derecho
const int motDerAdelante;
const int motDerAtras;

//pines para el motor izquierdo 
const int motIzAdelante;
const int motIzqAtras;






void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(sensorPin) == HIGH)
  {
    Serial.println("yyy");
  }
  else
  {
    Serial.println("SALIO DE LA LINEA NEGRA");
  }
  delay(80);

}

void giraDerecha()
{
  
}

void giraIzquierda()
{
  
}

void adelante()
{
}

void atras()
{
}
}
