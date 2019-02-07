#include <Wire.h>
#include <SDL_Arduino_INA3221.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266Influxdb.h>

const char *INFLUXDB_HOST = "192.168.0.200";
const uint16_t INFLUXDB_PORT = 8086;
const char *DATABASE = "batteryc";
const char *DB_USER = "****";
const char *DB_PASSWORD = "***";

ESP8266WiFiMulti WiFiMulti;
Influxdb influxdb(INFLUXDB_HOST, INFLUXDB_PORT);

SDL_Arduino_INA3221 ina3221_A(0x41);
#define BATTERY1 1
#define BATTERY2 2
#define BATTERY3 3
SDL_Arduino_INA3221 ina3221_B(0x40);
#define BATTERY4 1
#define BATTERY5 2
#define BATTERY6 3
SDL_Arduino_INA3221 ina3221_C(0x42);
#define BATTERY7 1
#define BATTERY8 2
#define BATTERY9 3

void setup(void) 
{
  Serial.begin(115200);
  while (!Serial) {
      // will pause Zero, Leonardo, etc until serial console opens
      delay(1);
  }

    WiFiMulti.addAP("SSID", "password");
  while (WiFiMulti.run() != WL_CONNECTED) {
      Serial.print(". ");
          delay(100);
  }
  uint32_t currentFrequency;
  influxdb.opendb(DATABASE, DB_USER, DB_PASSWORD);  
  Serial.println("Hello!");
  
  ina3221_A.begin();
  ina3221_B.begin();
  ina3221_C.begin();
  
  Serial.println("Measuring voltage and current with INA3221 ...");
}

void loop(void) 
{
  Serial.println("BATTERY 1 BUS A DATA------------------------");
  float shuntvoltage_A0 = 0;
  float busvoltage_A0 = 0;
  float current_mA_A0 = 0;
  float loadvoltage_A0 = 0;
  float power_mW_A0 = 0;

  shuntvoltage_A0 = ina3221_A.getShuntVoltage_mV(BATTERY1);
  busvoltage_A0 = ina3221_A.getBusVoltage_V(BATTERY1);
  current_mA_A0 = -ina3221_A.getCurrent_mA(BATTERY1);
  power_mW_A0 = -ina3221_A.getCurrent_mA(BATTERY1)* ina3221_A.getBusVoltage_V(BATTERY1);
  loadvoltage_A0 = busvoltage_A0 + (shuntvoltage_A0 / 1000);
  
  Serial.print("Battery1 Bus Voltage:  "); Serial.print(busvoltage_A0)  ; Serial.println(" V");
  Serial.print("Battery1 Shunt Voltage:"); Serial.print(shuntvoltage_A0); Serial.println(" mV");
  Serial.print("Battery1 Load Voltage: "); Serial.print(loadvoltage_A0) ; Serial.println(" V");
  Serial.print("Battery1 Current:      "); Serial.print(current_mA_A0)  ; Serial.println(" mA");
  Serial.print("Battery1 Power:        "); Serial.print(power_mW_A0)    ; Serial.println(" mW");
  Serial.println("");
  FIELD dataObj("chargedata"); // Create field object with measurment name=analog_read 
  dataObj.addTag  ("bustype", "battery1");
  dataObj.addField("busvoltage", busvoltage_A0);
  dataObj.addField("shuntvoltage", shuntvoltage_A0);
  dataObj.addField("loadvoltage", loadvoltage_A0);
  dataObj.addField("current_mA", current_mA_A0);
  dataObj.addField("power_mW", power_mW_A0);
  Serial.println(influxdb.write(dataObj) == DB_SUCCESS ? "Writing Battery Bus A0" : "Writing failed");
  dataObj.empty();
  delay(500);
  Serial.println("");  
  
  Serial.println("BATTERY 2 BUS A DATA----------------------");
  float shuntvoltage_A1 = 0;
  float busvoltage_A1 = 0;
  float current_mA_A1 = 0;
  float loadvoltage_A1 = 0;
  float power_mW_A1 = 0;

  shuntvoltage_A1 = ina3221_A.getShuntVoltage_mV(BATTERY2);
  busvoltage_A1 = ina3221_A.getBusVoltage_V(BATTERY2);
  current_mA_A1 = -ina3221_A.getCurrent_mA(BATTERY2);
  power_mW_A1 = -ina3221_A.getCurrent_mA(BATTERY2)* ina3221_A.getBusVoltage_V(BATTERY2);
  loadvoltage_A1 = busvoltage_A1 + (shuntvoltage_A1 / 1000);
  
  Serial.print("Battery2 Bus Voltage "); Serial.print(busvoltage_A1)  ; Serial.println(" V");
  Serial.print("Battery2 Shunt Voltage:"); Serial.print(shuntvoltage_A1); Serial.println(" mV");
  Serial.print("Battery2 Load Voltage: "); Serial.print(loadvoltage_A1) ; Serial.println(" V");
  Serial.print("Battery2 Current:      "); Serial.print(current_mA_A1)  ; Serial.println(" mA");
  Serial.print("Battery2 Power:        "); Serial.print(power_mW_A1)    ; Serial.println(" mW");
  Serial.println("");
  dataObj.addTag  ("bustype", "battery2");
  dataObj.addField("busvoltage", busvoltage_A1);
  dataObj.addField("shuntvoltage", shuntvoltage_A1);
  dataObj.addField("loadvoltage", loadvoltage_A1);
  dataObj.addField("current_mA", current_mA_A1);
  dataObj.addField("power_mW", power_mW_A1);
  Serial.println(influxdb.write(dataObj) == DB_SUCCESS ? "Writing Battery Bus A" : "Writing failed");
  dataObj.empty();
  delay(500);
  
  Serial.println("");
  Serial.println("BATTERY 3 BUS A DATA----------------------");
  float shuntvoltage_A2 = 0;
  float busvoltage_A2 = 0;
  float current_mA_A2 = 0;
  float loadvoltage_A2 = 0;
  float power_mW_A2 = 0;

  shuntvoltage_A2 = ina3221_A.getShuntVoltage_mV(BATTERY3);
  busvoltage_A2 = ina3221_A.getBusVoltage_V(BATTERY3);
  current_mA_A2 = -ina3221_A.getCurrent_mA(BATTERY3);
  power_mW_A2 = -ina3221_A.getCurrent_mA(BATTERY3)* ina3221_A.getBusVoltage_V(BATTERY3);
  loadvoltage_A2 = busvoltage_A2 + (shuntvoltage_A2 / 1000);
  
  Serial.print("Battery3 Bus Voltage:  "); Serial.print(busvoltage_A1)  ; Serial.println(" V");
  Serial.print("Battery3 Shunt Voltage:"); Serial.print(shuntvoltage_A2); Serial.println(" mV");
  Serial.print("Battery3 Load Voltage: "); Serial.print(loadvoltage_A2) ; Serial.println(" V");
  Serial.print("Battery3 Current:      "); Serial.print(current_mA_A2)  ; Serial.println(" mA");
  Serial.print("Battery3 Power:        "); Serial.print(power_mW_A2)    ; Serial.println(" mW");
  Serial.println("");
  
  dataObj.addTag  ("bustype", "battery3");
  dataObj.addField("busvoltage", busvoltage_A2);
  dataObj.addField("shuntvoltage", shuntvoltage_A2);
  dataObj.addField("loadvoltage", loadvoltage_A2);
  dataObj.addField("current_mA", current_mA_A2);
  dataObj.addField("power_mW", power_mW_A2);
  Serial.println(influxdb.write(dataObj) == DB_SUCCESS ? "Writing Output Bus A" : "Writing failed");
  dataObj.empty();
  delay(500);
  Serial.println("");
  float current_mA_TA = 0;  
  current_mA_TA = (current_mA_A0 + current_mA_A1 + current_mA_A2)/1000;
  
  Serial.print("Total Current:      "); Serial.print(current_mA_TA)  ; Serial.println(" A");
  dataObj.addTag  ("system", "CurrentT");
  dataObj.addField("CurrenttA", current_mA_TA);
  Serial.println(influxdb.write(dataObj) == DB_SUCCESS ? "Writing Output Bus A" : "Writing failed");
  dataObj.empty();
  delay(500);
  Serial.println("");
  
//-------------------------------------------------------------------------------------------------------
  Serial.println("BATTERY 4 BUS B DATA------------------------");
  float shuntvoltage_B0 = 0;
  float busvoltage_B0 = 0;
  float current_mA_B0 = 0;
  float loadvoltage_B0 = 0;
  float power_mW_B0 = 0;

  shuntvoltage_B0 = ina3221_B.getShuntVoltage_mV(BATTERY4);
  busvoltage_B0 = ina3221_B.getBusVoltage_V(BATTERY4);
  current_mA_B0 = -ina3221_B.getCurrent_mA(BATTERY4);
  power_mW_B0 = -ina3221_B.getCurrent_mA(BATTERY4)* ina3221_B.getBusVoltage_V(BATTERY4);
  loadvoltage_B0 = busvoltage_B0 + (shuntvoltage_B0 / 1000);
  
  Serial.print("Battery4 Bus Voltage:  "); Serial.print(busvoltage_B0)  ; Serial.println(" V");
  Serial.print("Battery4 Shunt Voltage:"); Serial.print(shuntvoltage_B0); Serial.println(" mV");
  Serial.print("Battery4 Load Voltage: "); Serial.print(loadvoltage_B0) ; Serial.println(" V");
  Serial.print("Battery4 Current:      "); Serial.print(current_mA_B0)  ; Serial.println(" mA");
  Serial.print("Battery4 Power:        "); Serial.print(power_mW_B0)    ; Serial.println(" mW");
  Serial.println("");
  
//  FIELD dataObj("chargedata"); // Create field object with measurment name=analog_read 
  dataObj.addTag  ("bustype", "battery4");
  dataObj.addField("busvoltage", busvoltage_B0);
  dataObj.addField("shuntvoltage", shuntvoltage_B0);
  dataObj.addField("loadvoltage", loadvoltage_B0);
  dataObj.addField("current_mA", current_mA_B0);
  dataObj.addField("power_mW", power_mW_B0);
  Serial.println(influxdb.write(dataObj) == DB_SUCCESS ? "Writing Battery Bus B" : "Writing failed");
  dataObj.empty();
  delay(500);
  Serial.println("");  
  
  Serial.println("BATTERY 5 BUS A DATA----------------------");
  float shuntvoltage_B1 = 0;
  float busvoltage_B1 = 0;
  float current_mA_B1 = 0;
  float loadvoltage_B1 = 0;
  float power_mW_B1 = 0;

  shuntvoltage_B1 = ina3221_B.getShuntVoltage_mV(BATTERY5);
  busvoltage_B1 = ina3221_B.getBusVoltage_V(BATTERY5);
  current_mA_B1 = -ina3221_B.getCurrent_mA(BATTERY5);
  power_mW_B1 = -ina3221_B.getCurrent_mA(BATTERY5)* ina3221_B.getBusVoltage_V(BATTERY5);
  loadvoltage_B1 = busvoltage_B1 + (shuntvoltage_B1 / 1000);
  
  Serial.print("Battery5 Bus Voltage "); Serial.print(busvoltage_B1)    ; Serial.println(" V");
  Serial.print("Battery5 Shunt Voltage:"); Serial.print(shuntvoltage_B1); Serial.println(" mV");
  Serial.print("Battery5 Load Voltage: "); Serial.print(loadvoltage_B1) ; Serial.println(" V");
  Serial.print("Battery5 Current:      "); Serial.print(current_mA_B1)  ; Serial.println(" mA");
  Serial.print("Battery5 Power:        "); Serial.print(power_mW_B1)    ; Serial.println(" mW");
  Serial.println("");
  dataObj.addTag  ("bustype", "battery5");
  dataObj.addField("busvoltage", busvoltage_B1);
  dataObj.addField("shuntvoltage", shuntvoltage_B1);
  dataObj.addField("loadvoltage", loadvoltage_B1);
  dataObj.addField("current_mA", current_mA_B1);
  dataObj.addField("power_mW", power_mW_B1);
  Serial.println(influxdb.write(dataObj) == DB_SUCCESS ? "Writing Battery Bus B" : "Writing failed");
  dataObj.empty();
  delay(500);
  Serial.println("");
  
  Serial.println("BATTERY 6 BUS B DATA----------------------");
  float shuntvoltage_B2 = 0;
  float busvoltage_B2 = 0;
  float current_mA_B2 = 0;
  float loadvoltage_B2 = 0;
  float power_mW_B2 = 0;

  shuntvoltage_B2 = ina3221_B.getShuntVoltage_mV(BATTERY6);
  busvoltage_B2 = ina3221_B.getBusVoltage_V(BATTERY6);
  current_mA_B2 = -ina3221_B.getCurrent_mA(BATTERY6);
  power_mW_B2 = -ina3221_B.getCurrent_mA(BATTERY6)* ina3221_B.getBusVoltage_V(BATTERY6);
  loadvoltage_B2 = busvoltage_B2 + (shuntvoltage_B2 / 1000);
  
  Serial.print("Battery6 Bus Voltage:  "); Serial.print(busvoltage_B2)  ; Serial.println(" V");
  Serial.print("Battery6 Shunt Voltage:"); Serial.print(shuntvoltage_B2); Serial.println(" mV");
  Serial.print("Battery6 Load Voltage: "); Serial.print(loadvoltage_B2) ; Serial.println(" V");
  Serial.print("Battery6 Current:      "); Serial.print(current_mA_B2)  ; Serial.println(" mA");
  Serial.print("Battery6 Power:        "); Serial.print(power_mW_B2)    ; Serial.println(" mW");
  Serial.println("");
  
  dataObj.addTag  ("bustype", "battery6");
  dataObj.addField("busvoltage", busvoltage_B2);
  dataObj.addField("shuntvoltage", shuntvoltage_B2);
  dataObj.addField("loadvoltage", loadvoltage_B2);
  dataObj.addField("current_mA", current_mA_B2);
  dataObj.addField("power_mW", power_mW_B2);
  Serial.println(influxdb.write(dataObj) == DB_SUCCESS ? "Writing Output Bus B" : "Writing failed");
  dataObj.empty();
  
  delay(500);
  Serial.println("");
  Serial.println("");
  float current_mA_TB = 0;  
  current_mA_TB = (current_mA_B0 + current_mA_B1 + current_mA_B2)/1000;
  
  Serial.print("Total Current:      "); Serial.print(current_mA_TB)  ; Serial.println(" A");
  dataObj.addTag  ("system", "CurrentT");
  dataObj.addField("CurrenttB", current_mA_TB);
  Serial.println(influxdb.write(dataObj) == DB_SUCCESS ? "Writing Output Bus B" : "Writing failed");
  dataObj.empty();
  
    Serial.println("BATTERY 7 BUS C DATA----------------------");
  float shuntvoltage_C0 = 0;
  float busvoltage_C0 = 0;
  float current_mA_C0 = 0;
  float loadvoltage_C0 = 0;
  float power_mW_C0 = 0;

  shuntvoltage_C0 = ina3221_C.getShuntVoltage_mV(BATTERY7);
  busvoltage_C0 = ina3221_C.getBusVoltage_V(BATTERY7);
  current_mA_C0 = -ina3221_C.getCurrent_mA(BATTERY7);
  power_mW_C0 = -ina3221_C.getCurrent_mA(BATTERY7)* ina3221_C.getBusVoltage_V(BATTERY7);
  loadvoltage_C0 = busvoltage_C0 + (shuntvoltage_C0 / 1000);
  
  Serial.print("Battery7 Bus Voltage:  "); Serial.print(busvoltage_C0)  ; Serial.println(" V");
  Serial.print("Battery7 Shunt Voltage:"); Serial.print(shuntvoltage_C0); Serial.println(" mV");
  Serial.print("Battery7 Load Voltage: "); Serial.print(loadvoltage_C0) ; Serial.println(" V");
  Serial.print("Battery7 Current:      "); Serial.print(current_mA_C0)  ; Serial.println(" mA");
  Serial.print("Battery7 Power:        "); Serial.print(power_mW_C0)    ; Serial.println(" mW");
  Serial.println("");
  
  dataObj.addTag  ("bustype", "battery7");
  dataObj.addField("busvoltage", busvoltage_C0);
  dataObj.addField("shuntvoltage", shuntvoltage_C0);
  dataObj.addField("loadvoltage", loadvoltage_C0);
  dataObj.addField("current_mA", current_mA_C0);
  dataObj.addField("power_mW", power_mW_C0);
  Serial.println(influxdb.write(dataObj) == DB_SUCCESS ? "Writing Output Bus C" : "Writing failed");
  dataObj.empty();

  Serial.println("BATTERY 8 BUS C DATA----------------------");
  float shuntvoltage_C1 = 0;
  float busvoltage_C1 = 0;
  float current_mA_C1 = 0;
  float loadvoltage_C1 = 0;
  float power_mW_C1 = 0;

  shuntvoltage_C1 = ina3221_C.getShuntVoltage_mV(BATTERY8);
  busvoltage_C1 = ina3221_C.getBusVoltage_V(BATTERY8);
  current_mA_C1 = -ina3221_C.getCurrent_mA(BATTERY8);
  power_mW_C1 = -ina3221_C.getCurrent_mA(BATTERY8)* ina3221_C.getBusVoltage_V(BATTERY8);
  loadvoltage_C1 = busvoltage_C1 + (shuntvoltage_C1 / 1000);
  
  Serial.print("Battery8 Bus Voltage:  "); Serial.print(busvoltage_C1)  ; Serial.println(" V");
  Serial.print("Battery8 Shunt Voltage:"); Serial.print(shuntvoltage_C1); Serial.println(" mV");
  Serial.print("Battery8 Load Voltage: "); Serial.print(loadvoltage_C1) ; Serial.println(" V");
  Serial.print("Battery8 Current:      "); Serial.print(current_mA_C1)  ; Serial.println(" mA");
  Serial.print("Battery8 Power:        "); Serial.print(power_mW_C1)    ; Serial.println(" mW");
  Serial.println("");
  
  dataObj.addTag  ("bustype", "Battery8");
  dataObj.addField("busvoltage", busvoltage_C1);
  dataObj.addField("shuntvoltage", shuntvoltage_C1);
  dataObj.addField("loadvoltage", loadvoltage_C1);
  dataObj.addField("current_mA", current_mA_C1);
  dataObj.addField("power_mW", power_mW_C1);
  Serial.println(influxdb.write(dataObj) == DB_SUCCESS ? "Writing Output Bus C" : "Writing failed");
  dataObj.empty();

  Serial.println("BATTERY 9 BUS C DATA----------------------");
  float shuntvoltage_C2 = 0;
  float busvoltage_C2 = 0;
  float current_mA_C2 = 0;
  float loadvoltage_C2 = 0;
  float power_mW_C2 = 0;

  shuntvoltage_C2 = ina3221_C.getShuntVoltage_mV(BATTERY9);
  busvoltage_C2 = ina3221_C.getBusVoltage_V(BATTERY9);
  current_mA_C2 = -ina3221_C.getCurrent_mA(BATTERY9);
  power_mW_C2 = -ina3221_C.getCurrent_mA(BATTERY9)* ina3221_C.getBusVoltage_V(BATTERY8);
  loadvoltage_C2 = busvoltage_C2 + (shuntvoltage_C2 / 1000);
  
  Serial.print("Battery9 Bus Voltage:  "); Serial.print(busvoltage_C2)  ; Serial.println(" V");
  Serial.print("Battery9 Shunt Voltage:"); Serial.print(shuntvoltage_C2); Serial.println(" mV");
  Serial.print("Battery9 Load Voltage: "); Serial.print(loadvoltage_C2) ; Serial.println(" V");
  Serial.print("Battery9 Current:      "); Serial.print(current_mA_C2)  ; Serial.println(" mA");
  Serial.print("Battery9 Power:        "); Serial.print(power_mW_C2)    ; Serial.println(" mW");
  Serial.println("");
  
  dataObj.addTag  ("bustype", "Battery9");
  dataObj.addField("busvoltage", busvoltage_C2);
  dataObj.addField("shuntvoltage", shuntvoltage_C2);
  dataObj.addField("loadvoltage", loadvoltage_C2);
  dataObj.addField("current_mA", current_mA_C2);
  dataObj.addField("power_mW", power_mW_C2);
  Serial.println(influxdb.write(dataObj) == DB_SUCCESS ? "Writing Output Bus C" : "Writing failed");
  dataObj.empty();
  
  delay(500);
  Serial.println("");
  float current_mA_TC = 0;  
  current_mA_TC = (current_mA_C0 + current_mA_C1 + current_mA_C2)/1000;
  
  Serial.print("Total Current:      "); Serial.print(current_mA_TC)  ; Serial.println(" A");
  dataObj.addTag  ("system", "CurrentT");
  dataObj.addField("CurrenttC", current_mA_TC);
  dataObj.addField("CurrenttTotal", current_mA_TA + current_mA_TB + current_mA_TC);
  Serial.println(influxdb.write(dataObj) == DB_SUCCESS ? "Writing Output Bus B" : "Writing failed");
  dataObj.empty();
  
  delay(10000);
  Serial.println("");

}
