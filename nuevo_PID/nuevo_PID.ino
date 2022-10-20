//#include <ESC.h>
//#define ESC_PIN 10

#define pinSeguidor  2


//#define AI      A4
//#define LED_ON  12
//#define LED     13
//#define BOTON    9
//#define GO       2
//#define GO       11

#define pwmi     9   //PWM LEFT MOTOR
#define izq1     11   //LEFT1 MOTOR
#define izq2     12   //LEFT2 MOTOR
#define pwmd     10  //PWM RIGHT MOTOR
#define der1     7  //RIGHT1 MOTOR
#define der2     8   //RIGHT2 MOTOR
//#define BOTON    2
//ESC EDF27(ESC_PIN);
//int sensores[16];
int s0    =  2;
int s1    = 3;
int s2     = 4;
int s3      =5;
int s4     = 6;
int digital[5];
//int lectura_fondo[16];
//int lectura_linea[16];
//int umbral[16];
//int umbral=750;
long int sumap, suma, pos, poslast, position;

//////COLOR DE LÍNEA SEGÚN LA BARRA//////////
//I.M BLANCA=1 NEGRA=0
//PHOENIX BLANCA=0 NEGRA=1
int linea=0;
///////////////////////////////////////////

//////BARRAS//////////
//I.M 1
//PHOENIX 0
int barra=1   ;
///////////////////////////////////////////

//////////////// pid/////////////////////
float KP=3;//0.18;//constante proporcional
float KD=8;//constante derivativa
float KI=0.002;//constante integral
int vel=180;//VELOCIDAD MÁXIMA DEL ROBOT MÁXIMA 255
int veladelante=200;//VELOCIDAD DEL FRENO DIRECCIÓN ADELANTE
int velatras=100;//VELOCIDAD DEL FRENO DIRECCIÓN ATRÁS
int veltest=1650;//VELOCIDAD DE TEST DE LA TURBINA
////////////////////////////////////////

/// datos para la integral
int error1=0;
int error2=0;
int error3=0;
int error4=0;
int error5=0;
int error6=0;
/////////////////////////

///////////variable PID///////////////
int proporcional=0;
int integral=0;
int derivativo=0;
int diferencial=0;
int last_prop;
int setpoint=200;



void setup() {
Serial.begin(9600);
//TCCR2B = TCCR2B & B11111000 | B00000001;
//set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz

//TCCR2B = TCCR2B & B11111000 | B00000010; 
//set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz

//TCCR2B = TCCR2B & B11111000 | B00000011;   
//set timer 2 divisor to    32 for PWM frequency of   980.39 Hz

//TCCR2B = TCCR2B & B11111000 | B00000100;   
//set timer 2 divisor to    64 for PWM frequency of   490.20 Hz (The DEFAULT)

//TCCR2B = TCCR2B & B11111000 | B00000101;   
//set timer 2 divisor to   128 for PWM frequency of   245.10 Hz

//TCCR2B = TCCR2B & B11111000 | B00000110;   
//set timer 2 divisor to   256 for PWM frequency of   122.55 Hz

//TCCR2B = TCCR2B & B11111000 | B00000111;   
//set timer 2 divisor to  1024 for PWM frequency of    30.64 Hz

//TCCR1B = TCCR1B & B11111000 | B00000001;    // set timer 1 divisor to     1 for PWM frequency of 31372.55 Hz
//TCCR1B = TCCR1B & B11111000 | B00000010;    // set timer 1 divisor to     8 for PWM frequency of  3921.16 Hz
TCCR1B = TCCR1B & B11111000 | B00000011;    // set timer 1 divisor to    64 for PWM frequency of   490.20 Hz (The DEFAULT)
//TCCR1B = TCCR1B & B11111000 | B00000100;    // set timer 1 divisor to   256 for PWM frequency of   122.55 Hz



pinMode(izq1,OUTPUT);
pinMode(izq2,OUTPUT);
pinMode(der1,OUTPUT);
pinMode(der2,OUTPUT);

pinMode(s0,INPUT);
pinMode(s1,INPUT);
pinMode(s2,INPUT);
pinMode(s3,INPUT);
pinMode(s3,INPUT);
/*
pinMode(LED,OUTPUT);
pinMode(LED_ON,OUTPUT);
pinMode(BOTON,INPUT);
pinMode(GO,INPUT);
EDF27.init();
digitalWrite(LED_ON,1);
digitalWrite(LED,1);
*/
delay(500);
//while(digitalRead(BOTON));
/*
for(int i=0;i<50;i++){
  fondos();
  digitalWrite(LED,0);
  delay(20);
  digitalWrite(LED,1);
  delay(20);
}*/
/*
while(digitalRead(BOTON));
for(int i=0;i<50;i++){
  lineas();
  digitalWrite(LED,0);
  delay(20);
  digitalWrite(LED,1);
  delay(20);
}
* */
//promedio();
/*while(digitalRead(BOTON));
for(int i=1000;i<=2000;i++){
  EDF27.setSpeed(i);
  delay(2);
}
EDF27.setSpeed(veltest);
while(digitalRead(BOTON));
EDF27.setSpeed(turbina);
while(!digitalRead(GO));
digitalWrite(LED,0);
*/
}


void loop() {
int go=1;
while(true){
  Serial.print("\n\n\n");
  //int go=digitalRead(GO);
  //delay(500);
  frenos();
  lectura();
  PID();
  /*if(lectura() == -1)
  {
    break;
  }*/
  //delay(2000);
  
  if(go==0){
    motores(-20,-20);
    break;
  }
}
while(true){
  motores(0,0);
  //EDF27.setSpeed(1000);
  
}
}

/*
void fondos(){
  for(int i=0;i<16;i++){
  digitalWrite(s0,i&0x01);
  digitalWrite(s1,i&0x02);
  digitalWrite(s2,i&0x04);
  digitalWrite(s3,i&0x08);
  lectura_fondo[i]=analogRead(AI);
  //Serial.print(lectura_fondo[i]);
  //Serial.print("\t");
}
//Serial.println(" ");
}
*/
/*
void lineas(){
  for(int i=0;i<16;i++){
  digitalWrite(s0,i&0x01);
  digitalWrite(s1,i&0x02);
  digitalWrite(s2,i&0x04);
  digitalWrite(s3,i&0x08);
  lectura_linea[i]=analogRead(AI);
  //Serial.print(lectura_linea[i]);
  //Serial.print("\t");
}
//Serial.println(" ");
}
*/

/*
void promedio(){
  for(int i=0;i<16;i++){
  umbral[i]=(lectura_fondo[i]+lectura_linea[i])/2;
  //Serial.print(umbral[i]);
  //Serial.print("\t");
}
//Serial.println(" ");
}
*/

int lectura(void){
  
/*digitalWrite(s0,0);digitalWrite(s1,0);digitalWrite(s2,0);digitalWrite(s3,0);sensores[0]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,0);digitalWrite(s2,0);digitalWrite(s3,0);sensores[1]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,1);digitalWrite(s2,0);digitalWrite(s3,0);sensores[2]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,1);digitalWrite(s2,0);digitalWrite(s3,0);sensores[3]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,0);digitalWrite(s2,1);digitalWrite(s3,0);sensores[4]=analogRead(AI);
dilkjlkjoiugitalWrite(s0,1);digitalWrite(s1,0);digitalWrite(s2,1);digitalWrite(s3,0);sensores[5]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,1);digitalWrite(s2,1);digitalWrite(s3,0);sensores[6]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,1);digitalWrite(s2,1);digitalWrite(s3,0);sensores[7]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,0);digitalWrite(s2,0);digitalWrite(s3,1);sensores[8]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,0);digitalWrite(s2,0);digitalWrite(s3,1);sensores[9]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,1);digitalWrite(s2,0);digitalWrite(s3,1);sensores[10]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,1);digitalWrite(s2,0);digitalWrite(s3,1);sensores[11]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,0);digitalWrite(s2,1);digitalWrite(s3,1);sensores[12]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,0);digitalWrite(s2,1);digitalWrite(s3,1);sensores[13]=analogRead(AI);
digitalWrite(s0,0);digitalWrite(s1,1);digitalWrite(s2,1);digitalWrite(s3,1);sensores[14]=analogRead(AI);
digitalWrite(s0,1);digitalWrite(s1,1);digitalWrite(s2,1);digitalWrite(s3,1);sensores[15]=analogRead(AI);*/
/*for(int i=0;i<16;i++){
  if(sensores[i]<=umbral){
    sensores[i]=0;
  }
  Serial.print(sensores[i]);
  Serial.print("\t");
}
Serial.println(" ");*/
/*for(int i=0;i<16;i++){
  digitalWrite(s0,i&0x01);
  digitalWrite(s1,i&0x02);
  digitalWrite(s2,i&0x04);
  digitalWrite(s3,i&0x08);
  sensores[i]=analogRead(AI);
  if(linea==0){if(sensores[i]<=umbral[i]){digital[i]=0;}else{digital[i]=1;}}
  if(linea==1){if(sensores[i]<=umbral[i]){digital[i]=1;}else{digital[i]=0;}}
  //Serial.print(digital[i]);
  //Serial.print("\t");
}
*/
/*
for(int i=0;i<5;i++){
  int lecturaSeguidor =digitalRead(pinSeguidor+i);
    digital[i]=lecturaSeguidor;
    Serial.print(digital[i]);
    Serial.print("\t");
  }*/

  digital[i]=digitalRead(0);
  digital[i]=digitalRead(1);
  digital[i]=digitalRead(2);
  digital[i]=digitalRead(13);
  digital[i]=digitalRead(A3);

  
Serial.println(" ");
if(barra==0){sumap=(400*digital[0]+300*digital[1]+200*digital[2]+100*digital[3]+0*digital[4]);}

if(barra==1){sumap=(400*digital[4]+300*digital[3]+200*digital[2]+100*digital[1]+0*digital[0]);}
Serial.println("sumap: "+ String(sumap));
suma=(digital[0]+digital[1]+digital[2]+digital[3]+digital[4]);
Serial.println("suma: " + String(suma));
if(suma == 5){
  return -1;
}
pos=(sumap/suma);
Serial.println("rawPos: " + String(pos));

if(poslast>=350 && pos==-1){
  pos=400;
}
else if(poslast<=100 && pos==-1){
  pos=0;
}

poslast=pos;
Serial.println("posPos: " + String(pos));
return pos;
}

void PID(){
  proporcional=pos-setpoint;
  derivativo=proporcional-last_prop;
  integral=error1+error2+error3+error4+error5+error6;
  last_prop=proporcional;
  error6=error5;
  error5=error4;
  error4=error3;
  error3=error2;
  error2=error1;
  error1=proporcional;
  int diferencial=(proporcional*KP) + (derivativo*KD) + (integral*KI);
  Serial.println(String ("PID{ ")+String("D: ")+String(diferencial)+ String(" P: ") +  String(proporcional) +String("} "));
  
  //"String(diferencial)"  + "P: " + "String(proporcional)"+"} "+"\n"+ "Posision: " +  "String(pos)");
  if(diferencial > vel) diferencial=vel;
  else if(diferencial < -vel) diferencial=-vel;
  (diferencial < 0)?
  //motores(vel-diferencial, vel): motores(vel, vel+diferencial);
  motores(vel, vel+diferencial):motores(vel-diferencial, vel);
}

void frenos(){
  Serial.println("frenos:" + String(pos));
   if(pos>=350){
    motores(-velatras, veladelante);
     //motores(veladelante, -velatras);
    
  }
  if(pos<=100){
    motores(veladelante, -velatras);
     //motores(-velatras, veladelante);
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
