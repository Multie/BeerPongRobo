const char* ssid = "BeerPongRobo";
const char* password = "robopong";


IPAddress Ip;
ESP8266WebServer server(80);
bool WifiIsHost=false;
String ipToString(IPAddress ip) {
  String s = "";
  for (int i = 0; i < 4; i++)
    s += i  ? "." + String(ip[i]) : String(ip[i]);
  return s;
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(404, "text/plain", message);
}
/*
Getter/Setter
Sensor:
  TrackWhite
Motor:
  MotorMode
  MotorStep
  RobotSpeed
  Mode1Forward
  Mode2Rotate
Led:
  LedMode
  LedR
  LedG
  LedB
Wifi:
  WifiIp(Robot)
  WifiIsHost
*/

// GET //////////////
void handleGETRoot() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  String json = "{\"ip\": \"ipVal\",\"TrackWhite\": \"TrackWhiteVal\",\"MotorMode\": \"MotorModeVal\",\"MotorStep\": \"MotorStepVal\",\"RobotSpeed\": \"RobotSpeedVal\",\"Mode1Forward\": \"Mode1ForwardVal\",\"Mode2Rotate\": \"Mode2RotateVal\",\"LedMode\": \"LedModeVal\",\"LedR\": \"LedRVal\",\"LedG\": \"LedGVal\",\"LedB\": \"LedBVal\",\"WifiIsHost\": \"WifiIsHostVal\"}";
  json.replace("TrackWhiteVal",String(TrackWhite));
  json.replace("MotorModeVal",String(MotorMode));
  json.replace("MotorStepVal",String(MotorStep));
  json.replace("RobotSpeedVal",String(RobotSpeed));
  json.replace("Mode1ForwardVal",String(Mode1Forward));
  json.replace("Mode2RotateVal",String(Mode2Rotate));
  json.replace("LedModeVal",String(LedMode));
  json.replace("LedRVal",String(LedR));
  json.replace("LedGVal",String(LedG));
  json.replace("LedBVal",String(LedB));
  json.replace("WifiIsHostVal",String(WifiIsHost));
  json.replace("ipVal",String(ipToString(Ip)));
  server.send(200, "text/plain", json);
}
void handleGETRobot() {
  // Manual Setup
  // Mode Select
  server.sendHeader("type", "plain");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", ipToString(Ip) );
}
// POST /////////////
void handlePOSTTrackWhite() {
  String text = server.arg("plain");
  TrackWhite = text=="1";
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", String(TrackWhite));
}
void handlePOSTMotorMode() {
  String text = server.arg("plain");
  MotorMode = text.toInt();
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", String(MotorMode));
}
void handlePOSTRobotSpeed() {
  String text = server.arg("plain");
  RobotSpeed = text.toDouble();
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", String(RobotSpeed));
}
void handlePOSTMode1Forward() {
  String text = server.arg("plain");
  Mode1Forward = text.toDouble();
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", String(Mode1Forward));
}
void handlePOSTMode2Rotate() {
  String text = server.arg("plain");
  Mode2Rotate = text.toDouble();
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", String(Mode2Rotate));
}
void handlePOSTLedMode() {
  String text = server.arg("plain");
  Mode1Forward = text.toInt();
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", String(Mode1Forward));
}
void handlePOSTLedR() {
  String text = server.arg("plain");
  LedR = text.toInt();
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", String(LedR));
}
void handlePOSTLedG() {
  String text = server.arg("plain");
  LedG = text.toInt();
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", String(LedG));
}
void handlePOSTLedB() {
  String text = server.arg("plain");
  LedB = text.toInt();
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", String(LedB));
}
// Connect /////////////
bool ConnectWifi() {
  Serial.print("Connecting to Wifi ");
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
  int timeout = 5;
  while (WiFi.status() != WL_CONNECTED && timeout > 0) {
    timeout--;
    SetColor(255, 0, 0);
    delay(500);
    SetColor(0, 0, 0);
    delay(500);
    Serial.print(".");
  }
  if (timeout <= 0) {
    Serial.println(" Not Connected");
    return false;
  }
  else {
    Serial.println(" Connected");
    Serial.print("IP:");
    Ip = WiFi.localIP();
    Serial.println(Ip);
   SetColor(0, 255, 0);
   delay(1000);
    return true;
  }
}

bool StartACPWifi() {
  Serial.println("Start Acsess Point");
  WiFi.mode(WIFI_AP);
  boolean result = WiFi.softAP(ssid, password);
  if (result) {
    Serial.println("Srarted Acsess Point");
    Serial.print("IP:");
    Ip = WiFi.softAPIP();
    Serial.println(Ip);
    SetColor(0, 0, 255);
    delay(1000);
    WifiIsHost = true;
    return true;
  }
  else {
    Serial.println("Not Srarted Acsess Point");
    while (true) {
      SetColor(0, 0, 255);
      delay(50);
      SetColor(255, 0, 0);
      delay(100);
    }
    return false;
  }
}

void WlanSetup() {
  Serial.println("Wifi Start");

  if (!ConnectWifi()) {
    StartACPWifi();
  }
  // GET
  server.onNotFound(handleNotFound);
  server.on("/",      HTTP_GET, handleGETRoot);
  server.on("/robot",   HTTP_GET, handleGETRobot);
  /* server.on("/green", HTTP_GET,handleGETGreen);

    server.on("/speed",  HTTP_GET,handleGETSpeed);
    //POST*/
  server.on("/TrackWhite",   HTTP_POST,handlePOSTTrackWhite );
  server.on("/MotorMode",   HTTP_POST, handlePOSTMotorMode);
  server.on("/RobotSpeed",   HTTP_POST,handlePOSTRobotSpeed );
  server.on("/Mode1Forward",   HTTP_POST,handlePOSTMode1Forward );
  server.on("/Mode2Rotate",   HTTP_POST, handlePOSTMode2Rotate);
  server.on("/LedMode",   HTTP_POST,handlePOSTLedMode );
  server.on("/LedR",   HTTP_POST, handlePOSTLedR);
  server.on("/LedG",   HTTP_POST,handlePOSTLedG );
  server.on("/LedB",   HTTP_POST, handlePOSTLedB);
  
  //server.on("/name",  HTTP_POST,handlePOSTName);
  //server.on("/speed",  HTTP_POST,handlePOSTSpeed);



  server.begin();
 #ifdef WIFIDEBUG
  Serial.println("Server Start");

  #endif
}

void WlanLoop() {
  server.handleClient();
  #ifdef WIFIDEBUG
    Debug("AnzahlderVerbundenen",String(WiFi.softAPgetStationNum()));
  #endif
}
