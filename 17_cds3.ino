#include <Wire.h>  
#include <BH1750.h>  
  
BH1750 lightMeter;  
  
void setup(){  
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin(0x23);  
  Serial.println(F("BH1750 Test"));  
}  
  
  
void loop() {  
  uint16_t lux = lightMeter.readLightLevel();
  Serial.print("Light: ");  
  Serial.print(lux);  
  Serial.println(" lx");  
  delay(1000);  
}  