#define SENSOR 2 // pin 2 for sensor
#define ACTION 9 // 


void setup(){
    Serial.begin(9600);
    pinMode(SENSOR, INPUT_PULLUP);
    pinMode(ACTION, OUTPvUT);

}