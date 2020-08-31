const char* ssid = "BeerPongRobo";
const char* password = "robopong";

String website = "<h1>hi</h1>";
IPAddress Ip;
ESP8266WebServer server(80);

String ipToString(IPAddress ip){
  String s="";
  for (int i=0; i<4; i++)
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
  server.sendHeader("Access-Control-Allow-Origin","*");
  server.send(404, "text/plain", message);
}


void handleGETRoot() { //multiRGB.local/  "http://multiStarwars.local"
  // Manual Setup
  // Mode Select
  server.sendHeader("Access-Control-Allow-Origin","*");
  server.send(200, "html", website);
}

void handleGETRobot() { //multiRGB.local/  "http://multiStarwars.local"
  // Manual Setup
  // Mode Select
  server.sendHeader("type","plain");
  server.sendHeader("Access-Control-Allow-Origin","*");
  server.send(200, "html", ipToString(Ip) );
}

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
  server.on("/robot",   HTTP_GET,handleGETRobot);
   /* server.on("/green", HTTP_GET,handleGETGreen);
    server.on("/blue",  HTTP_GET,handleGETBlue);
    server.on("/mode",  HTTP_GET,handleGETMode);
    server.on("/name",  HTTP_GET,handleGETName);
    server.on("/speed",  HTTP_GET,handleGETSpeed);
    //POST
    server.on("/red",   HTTP_POST,handlePOSTRed);
    server.on("/green", HTTP_POST,handlePOSTGreen);
    server.on("/blue",  HTTP_POST,handlePOSTBlue);
    server.on("/mode",  HTTP_POST,handlePOSTMode);
    server.on("/name",  HTTP_POST,handlePOSTName);
    server.on("/speed",  HTTP_POST,handlePOSTSpeed);
    
    String completehost = "http://"+String(hostname)+".local";
    Serial.println("Start Complete");
    Serial.println(completehost + "/ , GET");
    Serial.println(completehost + "/red , GET/POST");
    Serial.println(completehost + "/green , GET/POST");
    Serial.println(completehost + "/blue , GET/POST");
    Serial.println(completehost + "/mode , GET/POST");
    Serial.println(completehost + "/name , GET/POST");
    Serial.println(completehost + "/speed , GET/POST");
  */
  Serial.println("Server Start");
  server.begin();
  Serial.println("URL: http://" + hostname + ".local/");
}

void WlanLoop() {
  server.handleClient();
  Serial.printf("Anzahl der Verbundenen Geräte= %d\n", WiFi.softAPgetStationNum());
}
