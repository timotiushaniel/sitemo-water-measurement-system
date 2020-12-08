#include <LiquidCrystal_I2C.h>
#include <CTBot.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
CTBot myBot;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xxxxxxxxxxxxxxxxxxxxxx";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "yyyyyyyyy";
char pass[] = "zzzzzzzzzzzz";
String token = "xyz";
const int id = 1234567890;

// defines pins numbers
const int trigPin = 2;  //D4
const int echoPin = 0;  //D3
const int redLed = 16;  //D0
const int greenLed = 12;//D6
const int blueLed = 14; //D5
const int speakerPin = 13; //D7

// defines variables
long duration;
int distance;
String ledStatus;
String lcdDisplay;
String lcdLowerLayer;
String botMessage;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(redLed, OUTPUT); // Sets the ledPin as an Output
  pinMode(greenLed, OUTPUT); // Sets the ledPin as an Output
  pinMode(blueLed, OUTPUT); // Sets the ledPin as an Output
  Serial.begin(9600); // Starts the serial communication

  pinMode(speakerPin, OUTPUT); // Sets the speakerPin as an Output

  // Initialize LCD as the Output
  lcd.begin(16,2);
  lcd.init();

  Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8080);
  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);

  // Checking WiFi Connection
  if (myBot.testConnection()) {
    Serial.println("Connection Successful");
  } else {
    Serial.println("Connection Failed");
  }
}

void loop() {
  // Ultrasonic Data Calculation
  ultraSonicDistance();
  // Condition Data for the Physical Output
  conditionData();
  // Serial Monitor Data for serial monitor output
  serialMonitorDisplay();
  Blynk.run();
}

// Serial Monitor Output Function
int serialMonitorDisplay(){
  // Ultrasonic Sensor Data
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" Cm");

  // LED Data
  Serial.print("LED: ");
  Serial.println(ledStatus);

  // LCD Display Data
  Serial.print("LCD Display: ");
  Serial.println(lcdDisplay);
  Serial.println(" ");
  delay(2000);
}

int ultraSonicDistance(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;  
}

int conditionData(){
  // LCD & LED Output Indicator
  lcd.clear();
  if(distance<=10){
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    digitalWrite(blueLed, LOW);
    ledStatus = "Red LED";
    
    lcdDisplay = "BAHAYA!!";
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print(lcdDisplay);
    lcd.setCursor(0, 1);      
    lcdLowerLayer = String(distance);
    lcd.print("Jarak: "+lcdLowerLayer+" Cm");
    Blynk.virtualWrite(V0, lcdDisplay); 
    Blynk.virtualWrite(V1, distance); 
    digitalWrite(speakerPin, HIGH);
    delay(150);
    digitalWrite(speakerPin, LOW);
    delay(150);

    botMessage = "Status: BAHAYA!!";
    myBot.sendMessage(id, botMessage);
  }
  else if(distance>=11 && distance<=16){
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(blueLed, HIGH);
    digitalWrite(speakerPin, LOW);    
    ledStatus = "Blue LED";
    
    lcdDisplay = "SIAGA";
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print(lcdDisplay);
    lcd.setCursor(0, 1);      
    lcdLowerLayer = String(distance);
    lcd.print("Jarak: "+lcdLowerLayer+" Cm");
    Blynk.virtualWrite(V0, lcdDisplay);
    Blynk.virtualWrite(V1, distance);  
  }
  else{
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    digitalWrite(blueLed, LOW);    
    digitalWrite(speakerPin, LOW);
    ledStatus = "Green LED";
    
    lcdDisplay = "AMAN";
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print(lcdDisplay);
    lcd.setCursor(0, 1);      
    lcdLowerLayer = String(distance);
    lcd.print("Jarak: "+lcdLowerLayer+" Cm");
    Blynk.virtualWrite(V0, lcdDisplay);
    Blynk.virtualWrite(V1, distance); 
  }
}
