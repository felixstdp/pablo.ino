#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#define xshut1 5
#define xshut2 7
#define xshut3 8
#define xshut4 16

int lox[4];

void setup() {
  
  pinMode(xshut1,OUTPUT);
  pinMode(xshut2,OUTPUT);
  pinMode(xshut3,OUTPUT);
  pinMode(xshut4,OUTPUT);

  i2cconfig();

  lox.begin(0x30)

  Serial.begin(9600);
}

void loop() {

  lox[0]=lox.read(0x30);
  lox[1]=lox.read(0x31);
  lox[2]=lox.read(0x32);
  lox[3]=lox.read(0x33);

  for (int i=0; i<4; i++); {
    Serial.print(lox[i]); Serial.print(" , ");
  }

  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }

  Serial.println();
  
}

void i2cconfig() {

  digitalWrite(xshut1,LOW);
  digitalWrite(xshut2,LOW);
  digitalWrite(xshut3,LOW);
  digitalWrite(xshut4,LOW);

  delay(10);

  digitalWrite(xshut1,HIGH);
  digitalWrite(xshut2,HIGH);
  digitalWrite(xshut3,HIGH);
  digitalWrite(xshut4,HIGH);
  
  digitalWrite(xshut1,HIGH);
  digitalWrite(xshut2,LOW);
  digitalWrite(xshut3,LOW);
  digitalWrite(xshut4,LOW);
  lox.setAddress(0x30);
  
  digitalWrite(xshut1,HIGH);
  digitalWrite(xshut2,HIGH);
  digitalWrite(xshut3,LOW);
  digitalWrite(xshut4,LOW);
  lox.setAddress(0x31);
  
  digitalWrite(xshut1,HIGH);
  digitalWrite(xshut2,HIGH);
  digitalWrite(xshut3,HIGH);
  digitalWrite(xshut4,LOW);
  lox.setAddress(0x32);
  
  digitalWrite(xshut1,HIGH);
  digitalWrite(xshut2,HIGH);
  digitalWrite(xshut3,HIGH);
  digitalWrite(xshut4,HIGH);
  lox.setAddress(0x33);
  
}
