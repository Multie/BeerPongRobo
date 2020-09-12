

#define MotorSpeed 111 // mm/s = n * u = n * 2*pi*r = 212/60 [1/s] * 2*pi*5mm 
#define WheelbaseRadius 33.2 //mm = messuard in Fusion
double MotorStep = 0.1; //s Timesteps for the MotorPulses

int MotorMode = 1;
double RobotSpeed = 10; // mm/s
double Mode1Forward = 20; // mm
double Mode2Rotate = 0; // degree

double Mode6Forward = 100;
double Mode6Rotate = 10;
bool RobotMove(double speed, double distance) {
  bool forward = distance >= 0;
long long endtime = 0;
  double time = distance / speed; // Total time R
  double timesteps = time / MotorStep; // Steps of Timesteps
  double OnTime = speed / MotorSpeed * MotorStep * 1000; // ms
  double OffTime = (1-speed / MotorSpeed) * MotorStep * 1000; //ms
  Debug("time",String(time));
  Debug("timesteps",String(timesteps));
   Debug("OnTime",String(OnTime));
    Debug("OffTime",String(OffTime));
  for (int a = 0; a < timesteps; a++) {
    endtime = millis() + OnTime;
    while (millis() < endtime) {
      //Debug("Wait",String((forward && (SensorStateFR || SensorStateFL)) || (!forward && (SensorStateBR || SensorStateBL))));
      if ((forward && (SensorStateFR || SensorStateFL)) || (!forward && (SensorStateBR || SensorStateBL))) {
        // Sees Obstacle => Break
        MotorStop(true, true);
        //ClearSensor();
        return false;
      }
      else {
        MotorMove(forward, forward);
      }
      Unblock();
    }
    MotorStop(true, true);
    endtime = millis() + OffTime;
    while (millis() < endtime) {
      Unblock();
    }
  }

}

bool RobotRotate(double speed, double degree) {
  double roationDistance = degree / 720 * WheelbaseRadius; // mm Per Wheel
  bool rightway = roationDistance >= 0;
  long long endtime = 0;
  double time = roationDistance / speed; // Total time R
  double timesteps = time / MotorStep; // Steps of Timesteps
  double OnTime = speed / MotorSpeed * MotorStep * 1000;
  double OffTime = (1-speed / MotorSpeed) * MotorStep * 1000;
  for (int a = 0; a < timesteps; a++) {
    MotorMove(!rightway, rightway);
    endtime = millis() + OnTime;
    while (millis() < endtime) {
      if ((rightway && (SensorStateBR || SensorStateFL) || !rightway && (SensorStateFR || SensorStateBL))) {
        // Sees Obstacle => Break
        MotorStop(true, true);
        ClearSensor();
        return false;
      }
      else {
         MotorMove(!rightway, rightway);
      }
      Unblock();
    }
    MotorStop(true, true);
    endtime = millis() + OffTime;
    while (millis() < endtime) {
      Unblock();
    }
  }
}

void MotorMove(bool dirR, bool dirL) { // true = forward
  digitalWrite(MotorPinRDir, dirR);
  digitalWrite(MotorPinRSpeed, !dirR);

  digitalWrite(MotorPinLDir, !dirL);
  digitalWrite(MotorPinLSpeed, dirL);
}

void MotorStop(bool r, bool l) {
  if (r) {
    digitalWrite(MotorPinRDir, 0);
    digitalWrite(MotorPinRSpeed, 0);
  }
  if (l) {
    digitalWrite(MotorPinLDir, 0);
    digitalWrite(MotorPinLSpeed, 0);
  }
}

void MotorSetup() {
  pinMode(MotorPinLDir, OUTPUT);
  pinMode(MotorPinLSpeed, OUTPUT);
  pinMode(MotorPinRDir, OUTPUT);
  pinMode(MotorPinRSpeed, OUTPUT);
}

void MotorLoop() {
  Debug("Motor Mode",String(MotorMode));
  switch (MotorMode) {
    case 0:
      MotorStop(true, true);
      MotorMode = -1;
      break;
    case 1: // Manuel Forward
      if (!RobotMove(RobotSpeed, Mode1Forward)) {
        MotorMode = 0;
      }
      break;
    case 2: // Manuel Rotate
      if (!RobotRotate(RobotSpeed, Mode2Rotate)) {
        MotorMode = 0;
      }
      break;
    case 3: // Random Drive
      if (!RobotMove(RobotSpeed, 1000)) {
        RobotRotate(RobotSpeed, random(1) * 360 - 180); // Rotate any
      }
      break;
    case 4: // Edge Follow
      if (!RobotMove(RobotSpeed, 1000)) {
        if (SensorStateFR) {
          RobotRotate(RobotSpeed, -5);
        }
        else if (SensorStateFL) {
          RobotRotate(RobotSpeed, 5);
        }
      }
      break;
    case 5: // Edge Follow
      if (!RobotMove(RobotSpeed, 1000)) {
        if (SensorStateFR) {
          RobotRotate(RobotSpeed, -5);
        }
        else if (SensorStateFL) {
          RobotRotate(RobotSpeed, 5);
        }
      }
      break;
    case 6: // Random Circle
      RobotMove(RobotSpeed, Mode6Forward);
      RobotRotate(RobotSpeed, Mode6Rotate);
      break;
  }
}
