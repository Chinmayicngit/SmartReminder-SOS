# Smart Reminder SOS & Emergency Alert Device 🚨

A microcontroller-based system using Arduino Mega, SIM900A GSM, and NEO 6M GPS to provide:

- ⏰ Scheduled medicine reminders via LCD and buzzer.
- 🆘 SOS emergency alerts with live GPS location sent via SMS.
- 📞 Auto-call to emergency contact on SOS trigger.

## Tech Stack

- **Platform**: Arduino
- **Language**: C/C++
- **Libraries**: TinyGPS, SoftwareSerial, LiquidCrystal_I2C

## Components Used

- Arduino Mega
- SIM900A GSM Module
- NEO 6M GPS Module
- 16x2 LCD Display
- Buzzer & Push Button



## How It Works

1. Displays medicine reminder at scheduled time.
2. On SOS button press:
   - Sends location via SMS with Google Maps link.
   - Initiates emergency call.

## Author

**Chinmayi CN**  
[GitHub – ChinmayiCN](https://github.com/ChinmayiCN)
