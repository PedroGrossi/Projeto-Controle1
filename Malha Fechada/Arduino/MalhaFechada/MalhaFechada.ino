#include <HX711.h>

#define PIN_DT 3
#define PIN_SCK 2
#define pumpPin 11                    
#define wait 100
#define calibration_factor -340000

HX711 scale; 

float reading_average = 0;
float weight = 0;
float setpoint= 3.50;
float error = 0;
int controlPWM = 0;

void setup() 
{
  Serial.begin(9600);                 //init serial communication
  scale.begin (PIN_DT, PIN_SCK);      //init scale
  reading_average = scale.read_average();
  scale.tare();
  pinMode(pumpPin, OUTPUT);           //set pin as output 
}

void loop() 
{
  scale.set_scale(calibration_factor);
  if (scale.is_ready())
  
  {
    weight = scale.get_units();       //receives weight from scale
    weight += 2.50;                   //adjust the weight of the container 
    error = setpoint - weight;        //calculate the error
    Serial.print(error);              //print of error
    Serial.print(" ");
    Serial.print(weight);             //print of weight
    Serial.println();
    controlPWM = error*99+42;           //calculate the PWM value based on our scale
    analogWrite(pumpPin, controlPWM); //send PWM value
  }
  delay(wait);
}