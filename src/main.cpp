#include "main.h"

#define DEBUG               true  // Debug mode
#define ATARI_JOYSTICK_IR   false // Turns the IR Joystick on/off
#define IR_RECV_PIN         34    // IR receiver pin
#define IR_RECV_DELAY       250   // IR reading time in ms
#define WAITING_DELAY       1000  // WiFi waiting time in ms

AsyncWebServer server(80);        // Set the Web server port
String fileList;                  // JSON List of ROMs "http://<smartConfig_IP>/roms"

ESP32IR IRAtariJoystick;          // IR Joystick receiver

unsigned int IRdata[1000];        // IR receiver stack data in 1/10 ms
unsigned int delayRead = 0;       // IR receiver read timer

void setup() {
  #if DEBUG
  Serial.begin(115200);           // Enable serial port
  #endif

  #if ATARI_JOYSTICK_IR
  initIRJoystick();               // Initializes the IR joystick receiver
  #endif

  // Checks initialization of the SPIFFS file system
  if (!SPIFFS.begin()) {
    #if DEBUG
    Serial.println("An error occurred while mounting SPIFFS.");
    #endif
    return;
  }

  initWiFi();                     // Initializes the SmartConfig and WiFi
  mountPageIndexEmulator();       // Mount root page of Atari emulator
  mountROMsFileRoute();           // Mount ROMs file route and listing
  mountNotFoundRoute();           // Mount Not Found route (404)

  server.begin();                 // Initializes the Web server
}

void initWiFi() {
  // Force disconnect from WiFi network
  WiFi.disconnect();

  // Set ESP32 WiFi to Station mode
  WiFi.mode(WIFI_STA);

  // Start smart config
  WiFi.beginSmartConfig();

  #if DEBUG
  Serial.println("Waiting for SmartConfig.");
  #endif

  // Waiting for SmartConfig
  while (!WiFi.smartConfigDone()) {
    // Delay in milliseconds (1000ms by default)
    delay(WAITING_DELAY);
    #if DEBUG
    Serial.print(".");
    #endif
  }

  #if DEBUG
  Serial.println("");
  Serial.println("SmartConfig Done.");
  Serial.println("Waiting for WiFi to connect.");
  #endif

  // Waiting for WiFi connected
  while (WiFi.status() != WL_CONNECTED) {
    // Delay in milliseconds (1000ms by default)
    delay(WAITING_DELAY);
    #if DEBUG
    Serial.print(".");
    #endif
  }

  #if DEBUG
  Serial.println("WiFi Connected.");
  Serial.print("Your IP: ");
  Serial.println(WiFi.localIP());
  #endif
}

void initIRJoystick() {
  #if DEBUG
  Serial.println("Initializing IR...");
  #endif

  // Channel 0, so you can use full channel memory
  IRAtariJoystick.recvPIN(IR_RECV_PIN, 0);
  IRAtariJoystick.initReceive(); // Initialize the IR receiver

  #if DEBUG
  Serial.println("IR Ok.");
  #endif
}

void mountPageIndexEmulator() {
  // Root route of index.html
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  // Favicon route assembly
  server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/favicon.ico", "image/x-icon");
  });

  // Mount Javatari.js embedded of the developer: Paulo Peccin @ppeccin
  server.on("/javatari.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/javatari.js", "application/javascript");
  });

  // Mount the background image (Atari logo)
  server.on("/logo.jpg", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/logo.jpg", "image/jpeg");
  });
}

void mountROMsFileRoute() {
  // Set the ROMs directory
  File root = SPIFFS.open("/roms");
  File file;

  // Add brackets to open JSON list
  fileList = "[";

  // Scroll through all files in the ROMs directory
  while (file = root.openNextFile()) {
    // Checks the separator of the list JSON
    if (fileList != "[") {
      fileList += ','; // Add file list separator
    }

    // Add file ROM information (type, name, size)
    fileList += "{\"type\":\"";
    fileList += (file.isDirectory()) ? "dir" : "file";
    fileList += "\",\"name\":\"";
    fileList += String(file.name()).substring(1);
    fileList += "\",\"size\":\"";
    fileList += String(file.size());
    fileList += "\"}";

    // ROMs image route montage
    server.on(file.name(), HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(SPIFFS, request->url(), "application/octet-stream");
    });
  }

  // Add brackets to close JSON list
  fileList += "]";

  // Mount route list of the ROMs in JSON
  server.on("/roms", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/json", fileList);
  });
}

void mountNotFoundRoute() {
  // Not found montage route (404)
  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/plain; charset=utf-8",
      "The content you requested cannot be found!.");
  });
}

void readJoystickIRReceive() {
  // Return the IR receiver reading
  IRAtariJoystick.readIR(IRdata, sizeof(IRdata));
  // Checks the IR receiver reading time
  if ((millis() - delayRead) >= IR_RECV_DELAY) {
    // Reset timer reading
    delayRead = millis();
    // Stop the RMT channel so it can be reused for receiving IR
    IRAtariJoystick.stopIR();
    // Channel 0 so it can use the full memory of the channels
    IRAtariJoystick.recvPIN(IR_RECV_PIN, 0);
    // Setup the ESP32 to Receive IR code
    IRAtariJoystick.initReceive();
  }
}

void loop() {
  #if ATARI_JOYSTICK_IR
  readJoystickIRReceptor();
  #endif
}
