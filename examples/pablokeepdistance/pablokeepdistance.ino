#define limit 15

#include <Pablo.h>
Pablo robot;

#include <NewPing.h>
NewPing sonar(10,10,50);

void setup() {}

void loop()
{
  delay(30);
  int dist = sonar.ping_cm();
  if (dist==0) {dist=50;}

  if (dist<limit) {robot.reverse(120,120,0);
  if (dist>limit) {robot.forward(120,120,0);
  if (dist==limit) {robot.brake(0)};
}
