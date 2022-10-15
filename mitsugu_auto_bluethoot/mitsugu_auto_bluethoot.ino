#include <SoftwareSerial.h>

SoftwareSerial miBT(12,13);

//definiendo los sensores
//veamos
int izqA = 4; 
int izqR = 2;  
int derA = 7; 
int derR = 5; 

int vel = 255; // Velocidad de los motores (0-255)
String estadoLatch = "neutral"; // inicia detenido


// NEUTRAL Y PARO TOTAL
String NEUTRAL = "neutral"; //0000
int neutral[4] = {0,0,0,0};
String STOP = "stop";//1111
int stoped[4] = {1,1,1,1};

//AVANCE Y RETROCESO
String FORWARD = "forward";
int forward[4] = {1,0,1,0};
String REVERSE = "reverse";
int reverse[4] = {0,1,0,1};

//MODOS NORAMALES DE VUELTA
String RIGTH_LOW = "r_low";
int r_low[4] = {1,0,0,0};
String LEFT_LOW = "l_low";
int l_low[4] =  {0,0,1,0}; 

//MODOS DE VUELTA CON LLANTA OPUESTA DETENIDA
String RIGTH_LOW_STUCK = "r_low_stuck";
int r_low_stuck[4] = {1,0,1,1};
String LEFT_LOW_STUCK = "l_low_stuck";
int l_low_stuck[4] = {1,1,1,0};

//VUELTA DE PRECISION con circulo
String RIGTH_CIRCLE;
int r_circle[4] = {1,0,0,1};
String LEFT_CIRCLE;
int l_circle[4] = {0,1,1,0};

//VUELTAS EN REVERSA
String RIGTH_REVERSE = "r_rev";
int r_rev[4] = {0,0,0,1};
String RIGTH_REVERSE_STUCK  = "r_rev_stuck";
int r_rev_stuck[4] = {1,1,0,1};
String LEFT_REVERSE = "l_rev";
int l_rev[4] = {0,1,0,0};
String LEFT_REVERSE_STUCK =  "l_rev_stuck";
int l_rev_stuck[4] = {0,1,1,1};

String controlModeLatch = "cm_normal"; //can be normal, xtra and reversed

void setup() { 
Serial.begin(9600); // inicia el puerto serial para comunicacion con el Bluetooth
pinMode(derA, OUTPUT);
pinMode(derR, OUTPUT);
pinMode(izqA, OUTPUT);
pinMode(izqR, OUTPUT);
miBT.begin(38400);
} 

void loop() { 

String estado="";
  while (!miBT.available()) {delay (500);}
    if (miBT.available() > 0)
    {
      while (miBT.available())
    {
      char reading = miBT.read();
      estado += reading;
      delay (1);
    }
      estado += '\0';
      
     if(estado == ""){
        } 
     else if(estado==estadoLatch){
      estadoLatch = "neutral";
      //Serial.println( "desasig: " + estadoLatch);
     }
     else if(estado == "cm_normal" || estado == "cm_xtra" || estado == "cm_reversed"){
        controlModeLatch = estado;
        Serial.println(controlModeLatch);
        Serial.println(estadoLatch);
       }
     else if(estado == controlModeLatch){
      controlModeLatch = "cm_normal";
     }
     else {
       estadoLatch =  estado;
       //can be normal, xtra and reversed
     }
       estado = "";
       //Serial.println( "asig: " + estadoLatch);
       
     }
     if(strcmp(estadoLatch.c_str() , NEUTRAL.c_str())==0 )
     { // neutral
        Serial.println("neutral");
        digitalWrite(izqA,  neutral[0]); 
        digitalWrite(izqR,  neutral[1]); 
        digitalWrite(derA,  neutral[2]); 
        digitalWrite(derR,  neutral[3]); 
      
      }
      if(strcmp(estadoLatch.c_str() , STOP.c_str())== 0)
      { // stop
          Serial.println("stop");
          digitalWrite(izqA,  stoped[0]); 
          digitalWrite(izqR,  stoped[1]); 
          digitalWrite(derA,  stoped[2]); 
          digitalWrite(derR,  stoped[3]); 
       }

     if(strcmp(estadoLatch.c_str() , FORWARD.c_str())==0)
      { // Forward
          Serial.println(" forward");
          digitalWrite(izqA, forward[0]); 
          digitalWrite(izqR, forward[1]); 
          digitalWrite(derA, forward[2]); 
          digitalWrite(derR, forward[3]); 
       }
      if(strcmp(estadoLatch.c_str() , REVERSE.c_str())==0)
      { // Reverse
          Serial.println(" reverse");
          digitalWrite(izqA, reverse[0]); 
          digitalWrite(izqR, reverse[1]); 
          digitalWrite(derA, reverse[2]); 
          digitalWrite(derR, reverse[3]); 
       }
       if(strcmp(estadoLatch.c_str() , RIGTH_LOW.c_str())==0)
      { // Rigth low
          if(strcmp(controlModeLatch.c_str(), "cm_xtra")==0){
             Serial.println("rigth circle");
              digitalWrite(izqA, r_circle[0]); 
              digitalWrite(izqR, r_circle[1]); 
              digitalWrite(derA, r_circle[2]); 
              digitalWrite(derR, r_circle[3]); 
            }
           else if(strcmp(controlModeLatch.c_str(), "cm_reversed" )==0){
                     Serial.println("rigth rev");
                digitalWrite(izqA, r_rev[0]); 
                digitalWrite(izqR, r_rev[1]); 
                digitalWrite(derA, r_rev[2]); 
                digitalWrite(derR, r_rev[3]); 
                  }
           else if(strcmp(controlModeLatch.c_str(), "cm_normal" )==0){
                  Serial.println("rigth normal");
                digitalWrite(izqA, r_low[0]); 
                digitalWrite(izqR, r_low[1]); 
                digitalWrite(derA, r_low[2]); 
                digitalWrite(derR, r_low[3]); 
                }          
       }
        if(strcmp(estadoLatch.c_str() , RIGTH_REVERSE.c_str())==0)
      { // Rigth
          Serial.println("rigth_rev");
          digitalWrite(izqA, r_rev[0]); 
          digitalWrite(izqR, r_rev[1]); 
          digitalWrite(derA, r_rev[2]); 
          digitalWrite(derR, r_rev[3]); 
       }
       if(strcmp(estadoLatch.c_str() , RIGTH_CIRCLE.c_str())==0)
      { // Rigth circle
          Serial.println("rigth_rev");
          digitalWrite(izqA, r_circle[0]); 
          digitalWrite(izqR, r_circle[1]); 
          digitalWrite(derA, r_circle[2]); 
          digitalWrite(derR, r_circle[3]); 
       }
        if(strcmp(estadoLatch.c_str() , LEFT_LOW.c_str())==0)
      { // Left low
              if(strcmp(controlModeLatch.c_str(), "cm_xtra" )==0){
                Serial.println("left circle");
                  digitalWrite(izqA, l_circle[0]); 
                  digitalWrite(izqR, l_circle[1]); 
                  digitalWrite(derA, l_circle[2]); 
                  digitalWrite(derR, l_circle[3]); 
                }
              else if(strcmp(controlModeLatch.c_str(), "cm_reversed" )==0){
                   Serial.println("left rev");
                    digitalWrite(izqA, l_rev[0]); 
                    digitalWrite(izqR, l_rev[1]); 
                    digitalWrite(derA, l_rev[2]); 
                    digitalWrite(derR, l_rev[3]); 
                }
              else if(strcmp(controlModeLatch.c_str(), "cm_normal" )==0){
                  Serial.println("left normal");
                    digitalWrite(izqA, l_low[0]); 
                    digitalWrite(izqR, l_low[1]); 
                    digitalWrite(derA, l_low[2]); 
                    digitalWrite(derR, l_low[3]); 
                }
       }
       if(strcmp(estadoLatch.c_str() , LEFT_REVERSE.c_str())==0)
      { // Left reverse
          Serial.println("left_rev");
          digitalWrite(izqA, l_rev[0]); 
          digitalWrite(izqR, l_rev[1]); 
          digitalWrite(derA, l_rev[2]); 
          digitalWrite(derR, l_rev[3]); 
       }
       if(strcmp(estadoLatch.c_str() , LEFT_CIRCLE.c_str())==0)
      { // Left circle
          Serial.println("rigth_rev");
          digitalWrite(izqA, r_circle[0]); 
          digitalWrite(izqR, r_circle[1]); 
          digitalWrite(derA, r_circle[2]); 
          digitalWrite(derR, r_circle[3]); 
       }
       
      
  }
