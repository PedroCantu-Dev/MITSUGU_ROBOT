#define pwmi     9   //PWM LEFT MOTOR
#define izq1     11   //LEFT1 MOTOR
#define izq2     12   //LEFT2 MOTOR
#define pwmd     10  //PWM RIGHT MOTOR
#define der1     7  //RIGHT1 MOTOR
#define der2     8   //RIGHT2 MOTOR

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  String estado="";
  int izqVel= 0;
  int derVel = 0;
  // put your main code here, to run repeatedly:
    while (!Serial.available()) {delay (500);}
    if (Serial.available() > 0)
    {
      while (Serial.available())
    {
      char reading = Serial.read();
      estado += reading;
      delay (1);
    }
      estado += '\0';
          
         if(estado == ""){
          Serial.println("nada");
            } 
         else {
          Serial.println("estado : " + estado);
           if(estado.indexOf("l") >-1){
            Serial.println("estado L : " +String( estado.indexOf("l")));
              int izqIndex = estado.indexOf("l")+1;
              izqVel = String(estado.substring(izqIndex) ).toInt();
           }
          else if(estado.indexOf("r") >0){
            int derIndex = estado.indexOf("r")+1;
            derVel = String(estado.substring(derIndex) ).toInt();
          }
           motores(izqVel, derVel);
         }

        
     }
}


void motores(int izq, int der){//0 hasta 255    0 hasta -255
  ////////////////motor LEFT "IZQUIERDO" ////////////////////////
  Serial.println("L:" + String(izq)+ "R:"+String(der));
  if(izq>=0){
    digitalWrite(izq1,HIGH);
    digitalWrite(izq2,LOW);
  }
  else{
    digitalWrite(izq1,LOW);
    digitalWrite(izq2,HIGH);
    izq=izq*(-1);
  }
  analogWrite(pwmi,izq);
  
  ////////////////motor RIGHT "DERECHO" ////////////////////////
  if(der>=0){
    digitalWrite(der1,HIGH);
    digitalWrite(der2,LOW);
  }
  else{
    digitalWrite(der1,LOW);
    digitalWrite(der2,HIGH);
    der=der*(-1);
  }
  analogWrite(pwmd,der);
  //int convertido = String(c).toInt();
  String L = String(der);
}
