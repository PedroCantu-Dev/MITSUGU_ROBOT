int TRIG = 7;
int ECO = 6;
int LED = 13;
int DURACION;
int DISTANCIA;
int DISAUX = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(TRIG,OUTPUT);
  pinMode(ECO,INPUT);
  pinMode(LED,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIG,HIGH);
  delay(1);
  digitalWrite(TRIG,LOW);
  
  DURACION = pulseIn(ECO,HIGH);
  
  DISTANCIA = DURACION / 58.2;
  
  
    if(DISTANCIA <= 50 && DISTANCIA >= 0)
    {
     digitalWrite(LED, HIGH);
    }
    else
    {
        digitalWrite(LED, LOW);
    }
  
  Serial.println(DISTANCIA);
  //delay(200);

}
