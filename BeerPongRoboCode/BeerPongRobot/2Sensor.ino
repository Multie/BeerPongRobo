

volatile bool SensorStateFR = false;
volatile bool SensorStateFL = false;
volatile bool SensorStateBR = false;
volatile bool SensorStateBL = false;
volatile bool TrackWhite = true;
void ICACHE_RAM_ATTR IntSensorFR() {
  if (digitalRead(IRSensorPinFR) == TrackWhite) {
    SensorStateFR = true;
  }
}
void ICACHE_RAM_ATTR IntSensorFL() {
   if (digitalRead(IRSensorPinFL) == TrackWhite) {
    SensorStateFL = true;
   }
}
void ICACHE_RAM_ATTR IntSensorBR() {
  if (digitalRead(IRSensorPinBR) == TrackWhite) {
    SensorStateBR = true;
   }
}
void ICACHE_RAM_ATTR IntSensorBL() {
  if (digitalRead(IRSensorPinBL) == TrackWhite) {
    SensorStateBL = true;
   }
}

void ClearSensor() {
  SensorStateFR = false;
  SensorStateFL = false;
  SensorStateBR = false;
  SensorStateBL = false;
}

void SensorSetup() {
  Serial.print("SensorSetup Start");
  pinMode(IRSensorPinFR,INPUT);
  pinMode(IRSensorPinFL,INPUT);
  pinMode(IRSensorPinBR,INPUT);
  pinMode(IRSensorPinBL,INPUT);

  attachInterrupt(digitalPinToInterrupt(IRSensorPinFR), IntSensorFR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(IRSensorPinFL), IntSensorFL, CHANGE);
  attachInterrupt(digitalPinToInterrupt(IRSensorPinBR), IntSensorBR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), IntSensorBL, CHANGE);
  Serial.println("SensorSetup End");
}


void SensorLoop() {
  #ifdef SENSORDEBUG
  Debug("SensorFR",String(SensorStateFR));
  Debug("SensorFL",String(SensorStateFL));
  Debug("SensorBR",String(SensorStateBR));
  Debug("SensorBL",String(SensorStateBL));

  Debug("SensorFRPin",String(digitalRead(IRSensorPinFR)));
  Debug("SensorFLPin",String(digitalRead(IRSensorPinFL)));
  Debug("SensorBRPin",String(digitalRead(IRSensorPinBR)));
  Debug("SensorBLPin",String(digitalRead(IRSensorPinBL)));
  #endif
}
