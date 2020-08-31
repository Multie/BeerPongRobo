

volatile bool SensorStateFR = false;
volatile bool SensorStateFL = false;
volatile bool SensorStateBR = false;
volatile bool SensorStateBL = false;

void ICACHE_RAM_ATTR IntSensorFR() {
  SensorStateFR = digitalRead(IRSensorPinFR);
}
void ICACHE_RAM_ATTR IntSensorFL() {
  SensorStateFL = digitalRead(IRSensorPinFL);
}
void ICACHE_RAM_ATTR IntSensorBR() {
  SensorStateBR = digitalRead(IRSensorPinBR);
}
void ICACHE_RAM_ATTR IntSensorBL() {
  SensorStateBL = digitalRead(IRSensorPinBL);
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
  attachInterrupt(digitalPinToInterrupt(IRSensorPinBL), IntSensorBL, CHANGE);
  Serial.println("SensorSetup End");
}

void SensorLoop() {
  Debug("SensorFR",String(SensorStateFR));
  Debug("SensorFL",String(SensorStateFL));
  Debug("SensorBR",String(SensorStateBR));
  Debug("SensorBL",String(SensorStateBL));
}
