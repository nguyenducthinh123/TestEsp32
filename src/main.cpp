#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "../include/System/System.h"
#include "../include/Firmware/Firmware.h"

// void setup() {
//   Serial.begin(9600);
//   pinMode(2, OUTPUT);
// }

// void loop() {
//   digitalWrite(2, HIGH);
//   Serial.write("on\t");
//   delay(1000);
//   digitalWrite(2, LOW);
//   Serial.write("off\t");  
//   delay(1000);
// }

// kiểm tra địa chỉ LCD
// void setup() {
//   Wire.begin();
//   Serial.begin(9600);
//   Serial.println("\nI2C Scanner");
// }
 
// void loop() {
//   byte error, address;
//   int nDevices;
//   Serial.println("Scanning...");
//   nDevices = 0;
//   for(address = 1; address < 127; address++ ) {
//     Wire.beginTransmission(address);
//     error = Wire.endTransmission();
//     if (error == 0) {
//       Serial.print("I2C device found at address 0x");
//       if (address<16) {
//         Serial.print("0");
//       }
//       Serial.println(address,HEX);
//       nDevices++;
//     }
//     else if (error==4) {
//       Serial.print("Unknow error at address 0x");
//       if (address<16) {
//         Serial.print("0");
//       }
//       Serial.println(address,HEX);
//     }    
//   }
//   if (nDevices == 0) {
//     Serial.println("No I2C devices found\n");
//   }
//   else {
//     Serial.println("done\n");
//   }
//   delay(5000);          
// }



//LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// void setup()
// {
//   lcd.init();                      // initialize the lcd 
//   lcd.backlight();
//   Serial.begin(9600);
// }

// void loop()
// {
//   // when characters arrive over the serial port...
//   if (Serial.available()) {
//     // wait a bit for the entire message to arrive
//     delay(100);
//     // clear the screen
//     lcd.clear();
//     // read all the available characters
//     while (Serial.available() > 0) {
//       // display each character to the LCD
//       lcd.write(Serial.read());
//     }
//   }
// }

// void setup() {
//   lcd.init();
//   lcd.backlight();
//   Serial.begin(9600);
// }

// void loop() {
//   lcd.clear();
//   lcd.print("LM 393");
//   lcd.setCursor(0, 1);
//   int a = analogRead(26);
//   Serial.printf("%d\t", a);
//   bool b = a < 2000; // true là sáng
//   if (b) {
//     lcd.print("day");
//   }
//   else {
//     lcd.print("night");
//   }
//   delay(1000);
// }

#define MILLIS_CYCLE    1000
System _system;
Log _log;

class LCD : public ScreenBuffer {
    LiquidCrystal_I2C screen;
public:
    LCD() : ScreenBuffer(2, 16), screen(0x27, 16, 2) {
        screen.init();
    }
    void update_device(int row, LPCHAR content) override {
        screen.setCursor(0, row);
        screen.print(content);
    }

    void Sleep() { screen.noBacklight(); }
    void WakeUp() { screen.backlight(); }
};

class SysClock : public Timer {
    int value;
public:
    SysClock() : Timer(MILLIS_CYCLE), value(0) {

    }

    void on_restart() override {
        _log << ++value << endl;
    }
} sysclock;

void setup() {
  Serial.begin(9600);
  
  _system.Reset();
  LCD lcd;
  
  lcd.GetLine(0) << "Nguyen Duc Thinh";
  lcd.GetLine(1) << "2024";
  lcd.WakeUp();
}

void loop() {
  _system.Loop();
  
}