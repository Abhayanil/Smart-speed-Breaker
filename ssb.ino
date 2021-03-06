#include <Servo.h>
#include <LiquidCrystal.h>

Servo myservo;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define trigPin1 13
#define echoPin1 10
#define trigPin2 7
#define echoPin2 6
#define led 0
#define led2 1

int blinking;                       // condition for blinking - timer is timing
int frameRate = 100;                // the frame rate (frames per second) at which the stopwatch runs - Change to suit
long interval = (1000/frameRate);   // blink interval =10
long startTime ;                    // start time for stop watch
long elapsedTime ;                  // elapsed time for stop watch
int fractional;                     // variable used to store fractional part of Frames
int fractionalSecs;                 // variable used to store fractional part of Seconds
int elapsedFrames;                  // elapsed frames for stop watch
int elapsedSeconds;                 // elapsed seconds for stop watch

float carspeedf;
float cstemp;
int cstempi;
int carspeed;
int carspeedd;

char buf[10];                       // string buffer for itoa function
    
long duration1;
long distance1;
long switch1;
long switch2;
long duration2;
long distance2;

void setup()
{
  
  myservo.attach(9);
  myservo.write(45);
  
  lcd.begin(16, 2);                // intialise the LCD.

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led,LOW); 
  digitalWrite(led2,LOW);
 
  
  lcd.setCursor(0,0);
  lcd.print("  SMART SPEED  ");
  lcd.setCursor(0,1);
  lcd.print("    BREAKER    ");

}


void loop()
{


  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);   //amount of sound pulses
  digitalWrite(trigPin1, LOW); 


  duration1 = pulseIn(echoPin1, HIGH, 1000);  //makes it high 10ms after trigger and waits for it become low and stores that time
  distance1 = (duration1/2) / 29.1;

  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);   //amount of sound pulses
  digitalWrite(trigPin2, LOW);


  duration2 = pulseIn(echoPin2, HIGH, 1000);  //makes it high 10ms after trigger and waits for it become low and stores that time
  distance2 = (duration2/2) / 29.1;

  if (distance2 > 0) 
  {  
    digitalWrite(led,HIGH);  //1 is on
    switch1=1;
  }

  if (distance1 > 0) 
  {
    digitalWrite(led2,HIGH);
    switch2=1;
  }


   if ( switch1 == 1  )
   {
      startTime = millis();                               // store the start time
      switch1=0;                                
      delay(10);                                         
   }

   
   else if ( switch2 == 1 )// check for a high to low transition if true then found a new button press while clock is running - stop the clock and report
   {
   
   switch2=0;
   elapsedTime =   millis() - startTime;                // store elapsed time
   elapsedSeconds = (elapsedTime / 1000L);              // divide by 1000 to convert to seconds - then cast to an int to print
   elapsedFrames = (elapsedTime / interval);            // divide by 100 to convert to 1/100 of a second - then cast to an int to print
   
   fractional = (int)(elapsedFrames % frameRate);       // use modulo operator to get fractional part of 100 Seconds
   fractionalSecs = (int)(elapsedSeconds % 60L);        // use modulo operator to get fractional part of 60 Seconds

   carspeedf = (792 / elapsedTime);
   cstemp = (carspeedf * 100);
   cstempi = (int)(cstemp);
   
   carspeed = (int)(carspeedf);
   carspeedd = (int)(cstempi % 100);
     
   lcd.clear();                                         // clear the LDC
   lcd.print("SPEED : ");
   lcd.print(itoa(carspeed, buf, 10));   // convert the int to a string and print a fractional part of 60 Seconds to the LCD
   lcd.print(".");
   lcd.print(itoa(carspeedd, buf, 10));
   lcd.print(" KM/H");
         
         if(elapsedTime > 119)
         {
         lcd.setCursor(0,1);
         lcd.print("LEVELING BREAKER"); 
         delay(50);
         myservo.write(90);
         }  
   
   delay(2000);
   digitalWrite(led,LOW); 
   digitalWrite(led2,LOW);
   lcd.clear();                                         // clear the LDC
   lcd.print("SPEED : ");
   myservo.write(45); 
   
   }

   
   else
   {
   switch1=0 ;
   switch2=0 ;                     
   }

   
}
