#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

#define INCLUDE_TERMINAL_MODULE
#include <Dabble.h>

//Right motor
int enable_R_Motor=6; 

//Left motor
int enable_L_Motor=3;

//pines de motores
//motor pins
int izqA = 4; 
int izqR = 2;  
int derA = 7; 
int derR = 5; 

String lastPressed = "NEUTRAL";

String controlModes[5] = {"cm_normal","cm_normal_stuck", "cm_circle", "cm_reverse", "cm_reverse_stuck"};

String controlMode = "cm_normal";

// NEUTRAL Y PARO TOTAL
int neutral[4] = {0,0,0,0};
int stoped[4] = {1,1,1,1};

//AVANCE Y RETROCESO
int forward[4] = {1,0,1,0};
int reverse[4] = {0,1,0,1};

//MODOS NORAMALES DE VUELTA
int r_low[4] = {1,0,0,0};
int l_low[4] =  {0,0,1,0}; 

//MODOS DE VUELTA CON LLANTA OPUESTA DETENIDA
int r_low_stuck[4] = {1,0,1,1};
int l_low_stuck[4] = {1,1,1,0};

//VUELTA DE PRECISION con circulo
int r_circle[4] = {1,0,0,1};
int l_circle[4] = {0,1,1,0};

//VUELTAS EN REVERSA
int r_rev[4] = {0,0,0,1};
int l_rev[4] = {0,1,0,0};

//VUELTAS EN REVERSA CON LLANTA OPUESTA DETENIDA
int r_rev_stuck[4] = {1,1,0,1};
int l_rev_stuck[4] = {0,1,1,1};

int countModeSelect = 0;


int backSensor = 2;
int frontSensor = 13;

void setup()
{
  countModeSelect = 0;
  lastPressed = "NEUTRAL";
  
  //salidas de motor
  pinMode(derA, OUTPUT);
  pinMode(derR, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqR, OUTPUT);

  //front sensor  
  pinMode(frontSensor, INPUT);

  //back sensor
  pinMode(backSensor, INPUT);

  //iniciando el motor sin movimiento
  rotateMotor(neutral);   
  Dabble.begin(38400, 9, 10);
  //Serial.begin(9600);
}

void loop()
{
  int R_MotorSpeed=0;
  int L_MotorSpeed=0;
  Dabble.processInput();
  //para cambiar los modos del robot desde la terminal del celular
  if(Terminal.available()){
     controlMode = Terminal.readString();
  }
  //los movimientos
  if (GamePad.isUpPressed())
  {
    //Serial.println("UP");
    rotateMotor(forward);
  }
  else if (GamePad.isDownPressed())
  {
    //Serial.println("DOWN");
    if(digitalRead(backSensor) == HIGH){
      rotateMotor(reverse);
    }
    
  }
  else if (GamePad.isLeftPressed())
  {
    //Serial.println("LEFT");
    makeTurn("left");
  }
  else if (GamePad.isRightPressed())
  {
    //Serial.println("RIGHT");
    makeTurn("right");
  }
  else {
    //Serial.println("NEUTRAL");
    rotateMotor(neutral);
  }

  //el cambio de modos rapido
  if (GamePad.isTrianglePressed())
  {
    //Serial.println("TRIANGLE");
    controlMode = "cm_normal";
    lastPressed = "TRIANGLE";
  }
  else if (GamePad.isCirclePressed())
  {
    //Serial.println("CIRCLE");
     if(lastPressed != "CIRCLE"){
        if(controlMode == "cm_circle"){
          controlMode = "cm_normal";
        }
        else
        {
          controlMode = "cm_circle";
        }
    }
    lastPressed = "CIRCLE";
  }
  else if (GamePad.isCrossPressed())
  {
    //Serial.println("CROSS");
     if(lastPressed != "CROSS"){
        if(controlMode == "cm_reverse"){
          controlMode = "cm_normal";
        }
        else
        {
          controlMode = "cm_reverse";
        }
    }
    lastPressed = "CROSS";
  }
  else if (GamePad.isSquarePressed())
  {
    //Serial.println("STOP");
    rotateMotor(stoped);
    lastPressed = "SQUARE";
  }
  else if (GamePad.isStartPressed())
  {
    //cambia el modo
    //Serial.println("START");
     if(lastPressed == "START"){
      
    }
    else{
      
    }
    lastPressed = "START";
  }
  else if (GamePad.isSelectPressed())
  {
      //select
      if(lastPressed != "SELECT"){
           if(controlMode == controlModes[countModeSelect])
           {
               countModeSelect++;
              if(countModeSelect>=5){
                countModeSelect = 0;
              }
            
             controlMode  = controlModes[countModeSelect];
           }
           else{
              controlMode = controlModes[countModeSelect];
           }
       }
      lastPressed = "SELECT";
  }
  else
  {
    lastPressed = "NEUTRAL";
  }

  //delay(3000);
  //Serial.println("LastPresed:::: "+lastPressed);
  //Serial.println("MODO: "+controlMode);
}




void rotateMotor(int *mov)
{
    digitalWrite(izqA,  mov[0]); 
    digitalWrite(izqR,  mov[1]); 
    digitalWrite(derA,  mov[2]); 
    digitalWrite(derR,  mov[3]); 
}

void makeTurn(String dir)
{
   if(controlMode == "cm_circle"){
        if(dir == "right"){
          rotateMotor(r_circle);
        }
        else{
          rotateMotor(l_circle);
          }
   }
    else if(controlMode == "cm_normal_stuck"){
        if(dir == "right"){
          rotateMotor(r_low_stuck);
        }
        else{
          rotateMotor(l_low_stuck);
          }
     }
   else if(controlMode == "cm_reverse"){
      if(dir == "right"){
          rotateMotor(r_rev);
        }
        else{
          rotateMotor(l_rev);
          }
     }
   else if(controlMode == "cm_reverse_stuck"){
       if(dir == "right"){
          rotateMotor(r_rev_stuck);
        }
        else{
          rotateMotor(l_rev_stuck);
          }
      
     }
   else {
    if(dir == "right"){
          rotateMotor(r_low);
        }
        else{
          rotateMotor(l_low);
          } 
     }
}


/*Terminal.available(): This function tells if there is new data present in the terminal queue or not. It returns 0 if there is not data, and 1 if there is data present.
Terminal.read(): This function returns the first byte available in the terminal queue. This function returns one character at a time.
Terminal.readString(); This function returns the whole string of data available on the Terminal.
Terminal.compareString(String text): This function takes a string in the argument and compares whether the string available in the Terminal is same or not. If the string matches, it returns 1, otherwise returns 0.*/
