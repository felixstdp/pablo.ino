// followline PID algorithm for Bricolabs Raptor robot
// Arduino Pro Micro, TB6612 driver, Pololu QTR-8 sensor

// TB6612 driver pinout
const int STBY = 15; // standby
const int PWMA = 5; // speed and direction control motor A (left)
const int AIN1 = 2;
const int AIN2 = 3;
const int PWMB = 10; // speed and direction control motor B (right)
const int BIN1 = 14;
const int BIN2 = 16;

// Pololu QTR-8A analog array readout
#include <QTRSensors.h>
QTRSensorsAnalog qtra((unsigned char[]) {6, 7, 8, 9, 0, 1, 2, 3 }, 8);
unsigned int IR[8];

// parameters and variables for non linear PID
const int vmin=60;
const int vmax=120;
const float kp=.016;
const float ki=0.001;
const float kd=0.01;
const float kv=0.1;
int p,d,u,vbase;
int i=0;
int p_old=0;


void setup() {
  digitalWrite(STBY, HIGH); // disable standby
  // Serial.begin(9600); 
}

void loop()
{
  qtra.read(IR); // read raw sensor values

  /* uncomment to show sensor values via serial monitor
  for (int i=0 ; i<8; i++)
  {
    Serial.print(IR[i]);
    Serial.print(" ");
  }
  Serial.println();
  */
  
  p = -4*IR[0]-3*IR[1]-2*IR[2]-IR[3]+IR[4]+2*IR[5]+3*IR[6]+4*IR[7];

  i=i+p;
  d=p-p_old;
  p_old=p;
  if ((p*i)<0) i=0;  // integral windup

  u=kp*p+ki*i+kd*d;
  vbase=vmin+(vmax-vmin)*exp(-kv*u);
  drive(vbase+u,vbase-u);
 
}

void drive(int L, int R)
{
  L=L+(255-L)*(L>255)+(-255-L)*(L<-255); // avoid PWM overflow
  R=R+(255-R)*(R>255)+(-255-R)*(R<-255);

  if (L>0)
  {
    digitalWrite(AIN1, LOW); // switch high for low if left wheel doesnt spin forward
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, L);
  } else {
    digitalWrite(AIN1, HIGH); // switch high for low if left wheel doesnt spin backward
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, -L);
  }  

if (R>0)
  {
    digitalWrite(BIN1, LOW); // switch high for low if right wheel doesnt spin forward
    digitalWrite(BIN2, HIGH);
    analogWrite(PWMB, R);
  } else {
    digitalWrite(BIN1, HIGH); // switch high for low if right wheel doesnt spin backward
    digitalWrite(BIN2, LOW);
    analogWrite(PWMB, -R);
  }  
}
