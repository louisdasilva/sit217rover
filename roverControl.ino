// include libraries
#include <AFMotor.h> // Adafruit Motor Shield v1
#include <SoftwareSerial.h> // Allows serial communication on digital pins of Arduino Board

// define bluetooth comms pins
SoftwareSerial bluetoothSerial(9,10); // RX, TX

// define each motor
AF_DCMotor frontLeft(2);
AF_DCMotor frontRight(1);
AF_DCMotor rearLeft(3);
AF_DCMotor rearRight(4);

// define motor array
AF_DCMotor motors[] = {frontLeft, frontRight, rearRight, rearLeft}; // start front left, move clockwise

// define variable for receiving bluetooth instruction
char instruction;

// define max speed
int MAX = 255;

void setup() {
  // set baud rate for bluetooth comms
  bluetoothSerial.begin(9600);
}

void loop() { 
  // get current instruction
  if (bluetoothSerial.available() > 0)
  {
    instruction = bluetoothSerial.read();
  }
  // initialise stop
  Stop();
  
  // identify instruction function and execute
  switch(instruction){
    case 'F':
      Forward();
      break;
    case 'B':
      Back();
      break;
    case 'L':
      Left();
      break;
    case 'R':
      Right();
      break;
    default:
      Stop();
      break;
  } 
}

void Stop(){
  SetAll(0, RELEASE);
}

void Forward(){
 SetAll(MAX, FORWARD); 
}

void Back(){
  SetAll(MAX, BACKWARD);
}

void Left(){
  SetSpeedAll(MAX);
  SetLeft(BACKWARD);
  SetRight(FORWARD);
}

void Right(){
  SetSpeedAll(MAX);
  SetLeft(FORWARD);
  SetRight(BACKWARD);
}

void SetLeft(int direction){
  frontLeft.run(direction);
  rearLeft.run(direction);
}

void SetRight(int direction){
  frontRight.run(direction);
  rearRight.run(direction);
}

void SetAll(int speed, int direction){
  for(int i = 0; i < 4; i++){
    motors[i].setSpeed(speed);
    motors[i].run(direction);
  }
}

void SetSpeedAll(int speed){
  for(int i = 0; i < 4; i++){
    motors[i].setSpeed(speed);
  }
}

/*
void testAllMotors(){
  testMotor(frontLeft);
  testMotor(frontRight);
  testMotor(rearLeft);
  testMotor(rearRight);
}

void testMotor(AF_DCMotor motor){
  motor.setSpeed(200);
  motor.run(FORWARD);
  delay(2000);
  motor.run(RELEASE);
  delay(1000);
  motor.run(BACKWARD);
  delay(2000);
  motor.run(RELEASE);
}
*/
