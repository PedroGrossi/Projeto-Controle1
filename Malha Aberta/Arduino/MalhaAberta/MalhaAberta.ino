#include <HX711.h>                            //scale library

#define PIN_DT 3                             //config the pins to module HX711
#define PIN_SCK 2
#define wait 100                              //variable of waiting
#define calibration_factor -340000            //definition of calibration factor
                                              //calibration_factor = -340000 -> container with 5L
                                              //calibration_factor = -354000 -> container with 2,5L
HX711 scale;                                  //object scale from HX711 library

float reading_average = 0;                    //variable to average the reading values
float weight = 0;                             //variable to weight

void setup ()
{
  Serial.begin(9600);                         //init serial communication
  scale.begin (PIN_DT, PIN_SCK);              //init and define the DT and SCK pins on the object scale
  reading_average = scale.read_average();     //average reading values without weight
  scale.tare();                               //zero the scale
}

void loop ()
{
  scale.set_scale(calibration_factor);        //adjust the scale to calibration factor
  if (scale.is_ready())                       //make sure the module is ready to take readings
  {
    weight = scale.get_units();               //weight measured
    Serial.print(weight);                     //return the weight measured in Kg with 2 decimal places
    Serial.println();
  }
  delay(wait);                                 //delay
}