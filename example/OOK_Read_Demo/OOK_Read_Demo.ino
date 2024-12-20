
// Ensure rtl_433_ESP/src/options.h is set as required

#define RF_MODULE_FREQUENCY 433.92
#define JSON_MSG_BUFFER 512

#include <ArduinoJson.h>
#include <rtl_433_ESP.h>

char messageBuffer[JSON_MSG_BUFFER];

rtl_433_ESP rf;

void rtl_433_Callback(char* message) {
  JsonDocument jsonDocument;
  deserializeJson(jsonDocument,message);
  printJson(jsonDocument);
}

void printJson(JsonDocument jsondata) {
  char JSONmessageBuffer[measureJson(jsondata) + 1];
  serializeJson(jsondata, JSONmessageBuffer, measureJson(jsondata) + 1);
  Serial.print("Received message: ");
  Serial.println(JSONmessageBuffer);
}

void setup() {
  Serial.begin(115200);
  delay(10000);
  Serial.println("****** setup ******");
  rf.initReceiver(RF_MODULE_RECEIVER_GPIO, RF_MODULE_FREQUENCY);
  rf.setCallback(rtl_433_Callback, messageBuffer, JSON_MSG_BUFFER);
  rf.enableReceiver();
  Serial.println("****** setup complete ******");
  rf.getModuleStatus(); // Prints module status to Serial (optional)
}

void loop() {
  rf.loop();
}