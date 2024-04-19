#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;
int count = 0;
float max_ma = 0;

void setup(void) 
{
  Serial.begin(115200);
  while (!Serial) {
      // will pause Zero, Leonardo, etc until serial console opens
      delay(1);
  }
    
  //Serial.println("Hello!");
  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  //ina219.setCalibration_16V_400mA();

  //Serial.println("Measuring voltage and current with INA219 ...");
}

void loop(void) 
{
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  //power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);  

  if (max_ma > current_mA) max_ma = current_mA;

  // guide line
  Serial.print("100:");       Serial.print(100);   Serial.print("\t"); 
  Serial.print("3.3V*10:");   Serial.print(3.3*100*-1);   Serial.print("\t"); 
  Serial.print("5V*10:");     Serial.print(5*100*-1);   Serial.print("\t"); 
  Serial.print("700:");       Serial.print(-700);   Serial.print("\t");   
  
  // max current, load voltage, current
  Serial.print("max_ma:");    Serial.print(max_ma);   Serial.print("\t"); 
  Serial.print("vol*10:");    Serial.print(loadvoltage*100*-1);   Serial.print("\t"); 
  Serial.print("cur:");       Serial.println(current_mA); 
  
}
