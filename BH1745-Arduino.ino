#include <Wire.h>

#define BH1745_ADDR 0x38 // The I2C address of the sensor
#define SYSTEM_CONTROL 0x40
#define MODE_CONTROL1 0x41
#define MODE_CONTROL2 0x42
#define MODE_CONTROL3 0x44

void setup() {
    Wire.begin();
    Serial.begin(9600);

    // Reset the sensor and enable it
    writeRegister(SYSTEM_CONTROL, 0b10100000);
    delay(10);
    
    // Set measurement time to 320ms, and ADC gain to x1.
    writeRegister(MODE_CONTROL1, 0b00000001);
    
    // Enable RGB measurement.
    writeRegister(MODE_CONTROL2, 0b00010000);
    
}

void loop() {
   uint16_t red = readColorData(0x50);
   uint16_t green = readColorData(0x52);
   uint16_t blue = readColorData(0x54);

   Serial.print("Red: ");
   Serial.print(red);
   
   Serial.print(", Green: ");
   Serial.print(green);

   Serial.print(", Blue: ");
   Serial.println(blue);

   delay(500); 
}

void writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(BH1745_ADDR); 
    Wire.write(reg); 
    Wire.write(value); 
    Wire.endTransmission();  
}

uint16_t readColorData(uint8_t reg) {
     Wire.beginTransmission(BH1745_ADDR); 
     Wire.write(reg);  
     Wire.endTransmission(); 

    if (Wire.requestFrom((int)BH1745_ADDR, (int)2) == 2) {
         return (Wire.read() | (Wire.read() << 8));  
     }
     
     return -1; 
}
