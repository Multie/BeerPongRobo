const char* ssid = "BeerPongRobo";
const char* password = "robopong";

String website = "<h1>hi</h1>";
IPAddress Ip;
ESP8266WebServer server(80);

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



void handleGETRoot() { //multiRGB.local/  "http://multiStarwars.local"
  // Manual Setup
  // Mode Select
  server.sendHeader("Access-Control-Allow-Origin", "*");
  String json = "{\"ip\": \"" + ipToString(Ip) + "\",\"mode\":" + String(MotorMode) + ",\"power\":" + String(Power) + ",\"ledMode\":" + String(LedMode) + ",\"trackwhite\":" + String(TrackWhite) + "}";
  server.send(200, "text/plain", json);
}

void handleGETRobot() { //multiRGB.local/  "http://multiStarwars.local"
  // Manual Setup
  // Mode Select
  server.sendHeader("type", "plain");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", ipToString(Ip) );
}

void handlePOSTMode() {
  String text = server.arg("plain");
  MotorMode = text.toInt();
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", String(MotorMode));
}
void handlePOSTPower() {
  String text = server.arg("plain");
  Power = text.toInt();
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", String(Power));
}
void handlePOSTLedMode() {
  String text = server.arg("plain");
  LedMode = text.toInt();
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", String(LedMode));
}
void handlePOSTTrackwhite() {
  String text = server.arg("plain");
  TrackWhite = text.toInt();
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", String(TrackWhite));
}
/*
  ip:string;
  red:number;
  green:number;
  blue:number;
  mode:number;
  power:boolean;
  ledMode:number;
  trackwhite:number;
*/


bool ConnectWifi() {
  Serial.print("Connecting to Wifi ");
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
  int timeout = 20;
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
    return true;
  }
  else {
    Serial.println("Not Srarted Acsess Point");
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
    server.on("/blue",  HTTP_GET,handleGETBlue);
    server.on("/mode",  HTTP_GET,handleGETMode);
    server.on("/name",  HTTP_GET,handleGETName);
    server.on("/speed",  HTTP_GET,handleGETSpeed);
    //POST*/
  server.on("/mode",   HTTP_POST, handlePOSTMode);
  server.on("/power", HTTP_POST, handlePOSTPower);
  server.on("/ledmode",  HTTP_POST, handlePOSTLedMode);
  server.on("/trackwhite",  HTTP_POST, handlePOSTTrackwhite);
  //server.on("/name",  HTTP_POST,handlePOSTName);
  //server.on("/speed",  HTTP_POST,handlePOSTSpeed);


  String completehost = "http://" + String(hostname) + ".local";


  Serial.println("Server Start");
  server.begin();
  Serial.println("URL: http://" + hostname + ".local/");
}

void WlanLoop() {
  server.handleClient();
  Serial.printf("Anzahl der Verbundenen Geräte= %d\n", WiFi.softAPgetStationNum());
}
