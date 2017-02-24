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
const float kv=0.05;
int p,d,u,vbase;
long i=0;
int p_old=0;
boolean on=HIGH;

void setup() {

}

void loop()
{
  qtra.read(IR); // read raw sensor values
  p = -4*IR[0]-3*IR[1]-2*IR[2]-IR[3]+IR[4]+2*IR[5]+3*IR[6]+4*IR[7];
  i=i+p;
  d=p-p_old;
  p_old=p;
  if ((p*i)<0) i=0;  // integral windup

  u=kp*p+ki*i+kd*d;
  vbase=vmin+(vmax-vmin)*exp(-kv*abs(u));
  
  digitalWrite(STBY, on); // disable standby
  drive(vbase+u,vbase-u); 
}

void drive(int L, int R) // speed for wheels Left and Right
{
  L=L+(255-L)*(L>255)+(-255-L)*(L<-255); // prevent PWM overflow
  R=R+(255-R)*(R>255)+(-255-R)*(R<-255);

  digitalWrite(AIN1, L<0); // switch < and >= if left wheel doesnt spin as expected
  digitalWrite(AIN2, L>=0);
  analogWrite(PWMA, L*(L>=0)-L*(L<0));
  
  digitalWrite(BIN1, R<0); // switch < and >= if left wheel doesnt spin as expected
  digitalWrite(BIN2, R>=0);
  analogWrite(PWMA, R*(R>=0)-R*(R<0));
}
