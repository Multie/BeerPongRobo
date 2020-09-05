
#define MovementSpeed 0.222; //mm/ms

#define Mode1ForwardBackward 100
#define Mode1Rotate 10

long long MotorRTime = 0;
long long MotorLTime = 0;
bool MotorROn = false;
bool MotorLOn = false;
bool MotorRDirection = false;
bool MotorLDirection = false;
int MotorMovement = 0; // 0 = Off, 1=forward 2=backward 3=turnRight 4=turnLeft

void MoveForward(double distance) { // mm
  bool dir = distance >= 0;
  MotorMovement = 1;
  if (distance < 0) {
    distance = distance * (-1);
    MotorMovement = 2;
  }
  double duration = distance / MovementSpeed;
  MotorMove(dir, duration, dir, duration);
}

void MoveRotate(double degree) { // mm
  bool dir = degree >= 0;
  MotorMovement = 3;
  if (degree < 0) {
    degree = degree * (-1);
    MotorMovement = 4;
  }
  double drivelength = degree * 0.62831; // mm per wheel
  double duration = drivelength / MovementSpeed;
  MotorMove(dir, duration, !dir, duration);
}

void MotorMove(bool dirR, double msR, bool dirL, double msL) {
  digitalWrite(MotorPinLDir, dirL);
  digitalWrite(MotorPinRDir, dirR);
  digitalWrite(MotorPinLSpeed, 1);
  digitalWrite(MotorPinRSpeed, 1);
  long long start = millis();
  MotorRTime = start + msR;
  MotorLTime = start + msL;
  MotorROn = true;
  MotorLOn = true;
}

void MotorStop(bool r, bool l) {
  if (r) {
    MotorRTime = 0;
    digitalWrite(MotorPinRDir, 0);
    digitalWrite(MotorPinRSpeed, 0);
  }
  MotorRTime = 0;
  MotorLTime = 0;
  digitalWrite(MotorPinLDir, 0);
  digitalWrite(MotorPinLSpeed, 0);

  MotorROn = false;
  MotorLOn = false;
}

void MotorEvent() {
  if (MotorMode == 1) {
    switch (MotorMovement) {
      case 1: // Forward
        if (SensorStateFR) {
          // Turn Left
          MotorStop(true, true);
          MoveRotate(Mode1Rotate*-1);
        }
        else if (SensorStateFL) {
          // Turn Right
          MotorStop(true, true);
           MoveRotate(Mode1Rotate);
        }
        break;
      case 2: // backward
        if (SensorStateBR) {
          // Turn Right
          MotorStop(true, true);
          MoveRotate(Mode1Rotate);
        }
        else if (SensorStateBL) {
          // Turn Left
          MotorStop(true, true);
          MoveRotate(Mode1Rotate*-1);
        }
        break;
      case 3: // Turn Right
        if (SensorStateFR) {
          // Go Back
          MotorStop(true, true);
          MoveForward(Mode1ForwardBackward*-1);
        }
        else if (SensorStateBL) {
          // Go Front
          MotorStop(true, true);
          MoveForward(Mode1ForwardBackward);
        }
        break;
      case 4: // Turn Left
        if (SensorStateFL) {
          // Go Back
          MotorStop(true, true);
          MoveForward(Mode1ForwardBackward*-1);
        }
        else if (SensorStateBR) {
          // Go Front
          MotorStop(true, true);
          MoveForward(Mode1ForwardBackward);
        }
        break;
    }
  }
}

void MotorSetup() {
  pinMode(MotorPinLDir, OUTPUT);
  pinMode(MotorPinLSpeed, OUTPUT);
  pinMode(MotorPinRDir, OUTPUT);
  pinMode(MotorPinRSpeed, OUTPUT);
}

void MotorLoop() {
  if (millis() > MotorRTime && MotorROn) {
    MotorROn = false;
    // Turn Off R
    MotorStop(true, false);
  }
  if (millis() > MotorLTime && MotorLOn) {
    MotorLOn = false;
    // Turn Off L
    MotorStop(false, true);
  }
  if (!MotorROn && !MotorLOn) { // NomalDrive never enters
    // Finished Booth Actions
    MotorMovement = 0;
  }
}
