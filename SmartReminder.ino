#include <SoftwareSerial.h> 
#include <TinyGPS.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x3F, 16, 2); // Address, columns, rows 
const int buzzerPin = 49; // Pin connected to the buzzer 
// Declare the medicine name as a string 
String medicineName = "TAKE MED:DOLO650"; // Change this to whatever medicine you 
need 
// RX, TX pins for GSM module 
char phone_no[] = "+918123943428";  // Put your phone number 
TinyGPS gps; 
// Define SoftwareSerial for SIM 7670 GSM Module 
SoftwareSerial gsm(8, 9); // TX → Pin 8, RX → Pin 9 
// Define Pins 
const int callbutton = 6; 
unsigned long lastDisplayTime = 0; // To store the last time the LCD was updated 
void setup() { 
lcd.init();          
lcd.backlight();     
// Initialize the LCD 
// Turn on the backlight 
lcd.print("Reminder medicine"); 
pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as output 
// Initialize Serial Monitor and GSM Module 
Serial.begin(9600); 
Department of CS-ICB, DSATM, Bangalore           
Page 20 
MINI PROJECT REPORT                                                                                                            2024-25 
 
Department of CS-ICB, DSATM, Bangalore           Page 21 
 
  gsm.begin(9600); 
 
  // Initialize SOS Button 
  pinMode(callbutton, INPUT_PULLUP); 
   
  // Wait for GSM Module to initialize 
  Serial.println("Initializing GSM Module..."); 
  delay(2000); // Allow module to stabilize 
  Serial.println("GSM Ready."); 
} 
 
void loop() { 
  bool newData = false; 
  unsigned long chars; 
  unsigned short sentences, failed; 
 
  // Get GPS data 
  for (unsigned long start = millis(); millis() - start < 1000;) { 
    while (Serial.available()) { 
      char c = Serial.read(); 
      Serial.print(c);  // Output GPS data to the Serial Monitor 
      if (gps.encode(c)) { 
        newData = true;  // Check if there is new GPS data 
      } 
    } 
  } 
 
  // Call displayLCD every 5 seconds (non-blocking) 
  if (millis() - lastDisplayTime > 5000) { 
    displaylcd(); 
    lastDisplayTime = millis();  // Update the time of the last display 
  } 
   
  // Debugging: Print button state to Serial Monitor 
MINI PROJECT REPORT                                                                                                            2024-25 
 
Department of CS-ICB, DSATM, Bangalore           Page 22 
 
  int buttonState = digitalRead(callbutton); 
  
  
  // Check if SOS button is pressed 
  if (buttonState == LOW) {  // Button is pressed (active LOW) 
    Serial.println("SOS Button Pressed! Making Emergency Call..."); 
    makeEmergencyCall(); 
    delay(1000); 
    sendsms();  // Send emergency SMS 
    delay(100);  // Prevent multiple calls in a short time 
  } 
} 
 
void makeEmergencyCall() { 
  gsm.println("ATD+918123943428;"); // Replace with emergency contact number 
  delay(1000); 
  Serial.println("Calling Emergency Number..."); 
} 
 
void sendsms() { 
  float flat, flon; 
  unsigned long age; 
  gps.f_get_position(&flat, &flon, &age); 
 
  gsm.print("AT+CMGF=1\r"); 
  delay(400); 
  gsm.print("AT+CMGS=\""); 
  gsm.print(phone_no); 
  gsm.println("\""); 
  gsm.println("Alert: I need help..."); 
  gsm.print("http://maps.google.com/maps?q=loc:"); 
  gsm.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6); 
  gsm.print(","); 
  gsm.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6); 
MINI PROJECT REPORT                                                                                                            
2024-25 
delay(200); 
gsm.println((char)26); 
delay(200); 
} 
void displaylcd() { 
// Display "Emergency" for 5 seconds 
lcd.clear(); 
lcd.setCursor(0, 0); 
lcd.print("Emergency"); 
delay(1000); 
// Display "Take your medicine" and the medicine name 
lcd.clear(); 
lcd.setCursor(0, 0); 
lcd.print("ATTENTION: 11 AM"); 
sumnesms(); 
delay(500); 
lcd.setCursor(0, 1); // Move to the second line 
lcd.print(medicineName); // Display the medicine name 
tone(buzzerPin, 1000);  // Play a 1 kHz tone on the buzzer 
delay(5000);  // Display for 5 seconds 
noTone(buzzerPin);  // Stop the buzzer 
// Display "Final warning" 
lcd.clear(); 
lcd.setCursor(0, 0); 
lcd.print("Final warning"); 
delay(5000);  // Display for 5 seconds 
} 
void sumnesms() 
{ 
gsm.print("AT+CMGF=1\r"); 
Department of CS-ICB, DSATM, Bangalore           
Page 23 
MINI PROJECT REPORT                                                                                                            2024-25 
 
Department of CS-ICB, DSATM, Bangalore           Page 24 
 
      delay(400); 
      gsm.print("AT+CMGS=\""); 
      gsm.print(phone_no); 
      gsm.println("\""); 
      gsm.println("Hello Uers,"); 
      gsm.println("This is a system generated EMERGENCY MESSAGE,please do not reply"); 
delay(100); 
      gsm.println((char)26); 
      delay(2000); 
}    this is the code of my iot project ( which is there in my report how to add for remsume)