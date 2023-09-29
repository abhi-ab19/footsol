#include<ESP8266WiFi.h>
#include<WiFiClientSecure.h>
#include<UniversalTelegramBot.h>
#include<ArduinoJson.h>

int pen=0,book=0,pencil=0,eraser=0,scale=0;
const char* ssid = "store123";
const char* password ="123456789";

#define BOTtoken "6312573312:AAFzp5IDdvi-Q6lwSUGK1kZ8DQprdmXFjII"  // your Bot Token (Get from Botfather)
#define CHAT_ID "1783281809"
//#define BOTtoken "5848384584:AAHoyE3u5Yx5NuFjbtIoS2GZz52O4uYdQyY" 
//#define CHAT_ID "5224603882"

#define SS_PIN D4  //D2
#define RST_PIN D3 //D1

#include <SPI.h>
#include <MFRC522.h>

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() 
{
    
    Serial.begin(9600);
    SPI.begin();      // Initiate  SPI bus
    mfrc522.PCD_Init();   // Initiate MFRC522
    Serial.println("Starting TelegramBot...");
    configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
    client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org

    Serial.print("Connecting Wifi: ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
    }
  
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    
    bot.sendMessage(CHAT_ID, "system started");
   
    
}
void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  if (content.substring(1) == "CC 05 8B 81") 
  {
    pen++;
    Serial.println("laptop number="+String(pen));
    bot.sendMessage(CHAT_ID, "laptop number="+String(pen));
    delay(1000);
    statuss = 1;
  }
 else if (content.substring(1) == "D3 DE 79 A5") 
  {
    book++;
    Serial.println("mobile phone number="+String(book));
    bot.sendMessage(CHAT_ID, "mobile phone number="+String(book));
    delay(1000);
    statuss = 1;
  }
  else if (content.substring(1) == "43 9E 43 95") 
  {
    pencil++;
    Serial.println("TV number="+String(pencil));
    bot.sendMessage(CHAT_ID,"TV number="+String(pencil));
    delay(1000);
    statuss = 1;
  }
  else if (content.substring(1) == "BA DB A2 EE") 
  {
    eraser++;
    Serial.println("washing machine number="+String(eraser));
    bot.sendMessage(CHAT_ID,"washing machine number="+String(eraser));
    delay(1000);
    statuss = 1;
  }
  else if (content.substring(1) == "DA 81 9B EE") 
  {
    scale++;
    Serial.println("fridge number="+String(scale));
    bot.sendMessage(CHAT_ID,"fridge number="+String(scale));
    delay(1000);
    statuss = 1;
  }
     
}

int motorPin = 9;  // Define the pin connected to the base of the transistor

void setup() {
  pinMode(motorPin, OUTPUT);
}

void loop() {
  digitalWrite(motorPin, HIGH);  // Turn on the motor
  delay(1000);  // Run the motor for 1 second
  digitalWrite(motorPin, LOW);   // Turn off the motor
  delay(1000);  // Wait for 1 second
}


//code for motors

#include <Wire.h>

#define SENSOR_ADDRESS 0x5C // Replace with the actual I2C address of your sensor

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(SENSOR_ADDRESS);
  Wire.write(0x??); // Replace with the register address for pressure reading
  Wire.endTransmission();

  delay(100); // Wait for sensor to provide data (adjust as per datasheet)

  Wire.requestFrom(SENSOR_ADDRESS, 2);
  if (Wire.available() == 2) {
    byte msb = Wire.read();
    byte lsb = Wire.read();
    int pressure_raw = (msb << 8) | lsb;

    // Convert raw data to pressure value (refer to datasheet)
    float pressure_in_pascals = ...; // Use the formula from the datasheet

    Serial.print("Pressure (Pa): ");
    Serial.println(pressure_in_pascals);

    delay(1000); // Delay before the next reading
  }
}
