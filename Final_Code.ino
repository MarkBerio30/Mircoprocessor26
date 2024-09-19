#include <Servo.h> // Library for controlling servos
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD I2C
#include <SoftwareSerial.h> // Library for Sim800L GSM Module

// Define the pins used for the SoftwareSerial communication with the SIM800L module
#define SIM800_TX 10 // Pin 10 is used for transmitting data to the SIM800L module
#define SIM800_RX 11 // Pin 11 is used for receiving data from the SIM800L module

// Create a SoftwareSerial object to communicate with the SIM800 module using the defined pins
SoftwareSerial sim800l(SIM800_TX, SIM800_RX);

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 4); // Creates an object for the LCD and sets its address and dimensions
Servo myservo;  // create servo object to control a servo

int irsensor = 2; // Sets the pin number for the IR sensor
int pos = 0;    // variable to store the servo position
int value = A0; // Sets the pin number for the analog input

//for the wet
#define trigPin 6 // Sets the pin number for the trigger pin of the wet sensor
#define echoPin 7 // Sets the pin number for the echo pin of the wet sensor

//for the wet
#define trigPin1 4 // Sets the pin number for the trigger pin of the dry sensor
#define echoPin1 3 // Sets the pin number for the echo pin of the dry sensor

#define servos 8 // Sets the pin number for the servo

//alarm
#define buzz 5 // Sets the pin number for the buzzer

String phone_no1 = "+639613281759"; // Set phone number to send SMS to
void setup() 
{
    Serial.begin(9600); // Initializes the serial communication
    sim800l.begin(9600); // Initializes the sim800l communication
    pinMode(trigPin, OUTPUT); // Sets the trigger pin of the wet sensor as an output
    pinMode(echoPin, INPUT); // Sets the echo pin of the wet sensor as an input
    pinMode(trigPin1, OUTPUT); // Sets the trigger pin of the dry sensor as an output
    pinMode(echoPin1, INPUT); // Sets the echo pin of the dry sensor as an input
    pinMode(buzz, OUTPUT); // Sets the pin number for the buzzer as an output
  
    lcd.init(); // Initializes the LCD
    lcd.backlight(); // Turns on the backlight of the LCD
    lcd.clear(); // Clears the contents of the LCD
    lcd.setCursor(0, 0); // Sets the cursor to the first row and first column of the LCD
    lcd.print("Wet and Dry"); // Prints "Wet and Dry" on the first row of the LCD
    lcd.setCursor(0, 1); // Sets the cursor to the second row and first column of the LCD
    lcd.print("Garbage"); // Prints "Garbage" on the second row of the LCD
    
    Serial.println("Initializing...."); // Initialize GSM module
    Serial.println("AT+CMGF=1"); // Set SMS mode to text
    Serial.println("AT+CNMI=2,2,0,0,0"); // Set new message indication to the terminal
    Serial.println("Initialized Successfully"); // Successfully initialized GSM module
    delay(3000); // Delays for 3 seconds
    lcd.clear(); // Clears the contents of the LCD
    
    myservo.attach(servos);  // Attaches the servo on pin 9 to the servo object
    myservo.write(100); // Sets the initial position of the servo to 100 degrees
    
    delay(1000); // Delays for 1 second
    pinMode (irsensor, INPUT); // Sets the pin number for the IR sensor as an input
    pinMode (value, INPUT); // Sets the pin number for the analog input as an input
    
}

void loop() 
{
  
     // Read analog input value from pin A0 and store it in the "value" variable
    int value = analogRead(A0);
    
    // If the IR sensor detects an object and the analog input value is greater than 950
    if (digitalRead(2) == LOW && value > 950)
    {
      // Set servo position to 30 degrees
      myservo.write(30);
      delay(1000); // Delay for 1 second
      // Set servo position to 100 degrees
      myservo.write(100);
      delay(1000); // Delay for 1 second
    
      // Display "DRY DETECTED" on the LCD
      lcd.setCursor(0, 0); // Set cursor to the first row and first column of the LCD
      lcd.print("DRY"); // Print "DRY" on the first row of the LCD
      lcd.setCursor(0, 1); // Set cursor to the second row and first column of the LCD
      lcd.print("DETECTED"); // Print "DETECTED" on the second row of the LCD
    
      delay(1000); // Delay for 1 second
    }
    else
    {
      // If the condition is not met, do nothing
    }
    
    // Clear the contents of the LCD
    lcd.clear();
    
    // Read the analog input value from pin A0 and store it in the "value" variable
    value = analogRead(A0);
    
    // If the analog input value is less than 900
    if (value < 900)
    {
      Serial.println(value); // Print the value to the serial monitor
      // Set servo position to 150 degrees
      myservo.write(150);
      delay(1000); // Delay for 1 second
      // Set servo position to 100 degrees
      myservo.write(100);
      delay(1000); // Delay for 1 second
    
      // Display "WET DETECTED" on the LCD
      lcd.setCursor(0, 0); // Set cursor to the first row and first column of the LCD
      lcd.print("WET"); // Print "WET" on the first row of the LCD
      lcd.setCursor(0, 1); // Set cursor to the second row and first column of the LCD
      lcd.print("DETECTED"); // Print "DETECTED" on the second row of the LCD
    
      delay(1000); // Delay for 1 second
    }
    else
    {
      // If the condition is not met, do nothing
    }

    // Clear the contents of the LCD
    lcd.clear();

      //for the ultrasonic wet
      long duration, inches, cm;

      // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
      // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
      digitalWrite(trigPin, LOW); // set trigPin to LOW
      delayMicroseconds(2); // wait for 2 microseconds
      digitalWrite(trigPin, HIGH); // set trigPin to HIGH
      delayMicroseconds(5); // wait for 5 microseconds
      digitalWrite(trigPin, LOW); // set trigPin to LOW

      // Take reading on echo pin
      duration = pulseIn(echoPin, HIGH); // measure the time taken for the echo to return

      // convert the time into a distance
      inches = microsecondsToInches(duration); // convert the duration to inches
      cm = microsecondsToCentimeters(duration); // convert the duration to centimeters

      Serial.print(inches); // print the distance in inches
      Serial.print("in, ");
      Serial.print(cm); // print the distance in centimeters
      Serial.print("cm");
      Serial.println();

     
      // Declare variables for the ultrasonic sensor readings
      long duration1, inches1, cm1;

      // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
      // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
      digitalWrite(trigPin1, LOW); // Set trigger pin to LOW
      delayMicroseconds(2); // Wait for 2 microseconds
      digitalWrite(trigPin1, HIGH); // Set trigger pin to HIGH
      delayMicroseconds(5); // Wait for 5 microseconds
      digitalWrite(trigPin1, LOW); // Set trigger pin to LOW

      // Take reading on echo pin
      duration1 = pulseIn(echoPin1, HIGH); // Read the pulse duration on echo pin

      // Convert the time into a distance in inches and centimeters
      inches1 = microsecondsToInches(duration1);
      cm1 = microsecondsToCentimeters(duration1);

      // Print the distance in inches and centimeters
      Serial.print(inches1);
      Serial.print("in, ");
      Serial.print(cm1);
      Serial.print("cm");
      Serial.println();

     // Check if both dry and wet garbage are full
    if (inches < 1 && inches1 < 3) {
        Serial.println("BOTH GARBAGE BINS ARE FULL"); // Print message to indicate both bins are full
        digitalWrite(buzz, HIGH); // Turn on buzzer
       
        delay(500); // Wait for 500 milliseconds
        sendSMS(phone_no1, "BOTH GARBAGE BINS ARE FULL"); // Send SMS message to user
    } else { // Otherwise, check each bin separately
        // Check if wet garbage is full
        if (inches < 2) {
          Serial.println("WET GARBAGE FULL"); // Print message to indicate dry garbage is full
          digitalWrite(buzz, HIGH); // Turn on buzzer
         
          delay(500); // Wait for 500 milliseconds
          sendSMS(phone_no1, "DRY GARBAGE BIN IS FULL"); // Send SMS message to user
    } else {
          Serial.println("WET GARBAGE EMPTY"); // Print message to indicate dry garbage is empty
          digitalWrite(buzz, LOW); // Turn off buzzer
          
          delay(500); // Wait for 500 milliseconds
    }
      // Check if dry garbage is full
      if (inches1 < 2) {
        Serial.println("DRY GARBAGE FULL"); // Print message to indicate wet garbage is full
        digitalWrite(buzz, HIGH); // Turn on buzzer
       
        delay(500); // Wait for 500 milliseconds
        sendSMS( phone_no1, "DRY GARBAGE BIN IS FULL"); // Send SMS message to user
      } else {
        Serial.println("DRY GARBAGE EMPTY"); // Print message to indicate wet garbage is empty
        digitalWrite(buzz, LOW); // Turn off buzzer
        
      
        delay(500); // Wait for 500 milliseconds
  }
}
      delay(100); // Wait for 100 milliseconds before starting again
      
}

//Function to send an SMS message
void sendSMS(String number, String msg)
{
  sim800l.print("AT+CMGS=\""); 
  sim800l.print(number); 
  sim800l.println("\"\r\n");
  delay(500);
  sim800l.println(msg);
  delay(500);
  sim800l.write(byte(26));
  delay(5000);
}


// Function to convert microseto convert microseconds to inches
long microsecondsToInches(long microseconds)
{
  // The speed of soundconds to centimeters
  // Function  is 1130 feet per second or 1 foot per 29 microseconds.
  // The ping travels out and back, so to find the distance of the object
  // in inches, we take half of the distance travelled and divide by 74.
  return microseconds / 74 / 2;
}
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 343 meters per second or 1 meter per 29 microseconds.
  // The ping travels out and back, so to find the distance of the object
  // in centimeters, we take half of the distance travelled and divide by 29.
  return microseconds / 29 / 2;
}
