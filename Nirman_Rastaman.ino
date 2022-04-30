#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define ADC_ref 5 // ADC reference Voltage
#define zero_x 1.799
#define zero_y 1.799
#define zero_z 1.799
//LDR
#define light A3
//buzzer
#define buzz 13
//blinking led
#define led 12
//Sonar
#define echoPin 2
#define trigPin 3
#define echoPin2 9
#define trigPin2 8
#define selectSwitch 1
#define sensitivity_x 0.4
#define sensitivity_y 0.4
#define sensitivity_z 0.4
unsigned int value_x;
unsigned int value_y;
unsigned int value_z;
float xv;
float yv;
float zv;
float angle;
LiquidCrystal_I2C lcd(0x27,16,2);
void setup()
{
analogReference(ADC_ref);
pinMode(selectSwitch,INPUT);
pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);
pinMode(trigPin2,OUTPUT);
pinMode(echoPin2,INPUT);
pinMode(led, OUTPUT);
//Serial.begin(9600);

lcd.init();                      // initialize the lcd 
lcd.init();
  // Print a message to the LCD.
lcd.backlight();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Tilt & Distance");
lcd.setCursor(0,1);
lcd.print(" Measurement ");
delay(3000);
lcd.clear();

}
void loop()
{
int distance,duration,duration2,distance2;//distance= side distance, distance2= front //duration= side duration //duration2= front duration
value_x = analogRead(A0);
value_y = analogRead(A1);
value_z = analogRead(A2);
xv=(value_x/1024.0*ADC_ref-zero_x)/sensitivity_x;
yv=(value_y/1024.0*ADC_ref-zero_y)/sensitivity_y;
zv=(value_z/1024.0*ADC_ref-zero_z)/sensitivity_z;
angle =atan2(-yv,-zv)*57.2957795+180;
float output_angle=angle;
if(digitalRead(selectSwitch)==HIGH)
{
lcd.setCursor(0,0);
lcd.print("T:");
lcd.print(output_angle);
//lcd.print(" deg");
//////Side
digitalWrite(trigPin, HIGH);
delayMicroseconds(1000);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
//////Front
digitalWrite(trigPin2, HIGH);
delayMicroseconds(1000);
digitalWrite(trigPin2, LOW);
duration2 = pulseIn(echoPin2, HIGH);
distance2 = (duration2/2) / 29.1;
lcd.setCursor(9,1);
lcd.print("FD:");
lcd.print(distance2);
if (distance >= 400 || distance <= 0)
{
lcd.setCursor(0,1);
lcd.print("Out of Range           ");
}
else
{
lcd.setCursor(0,1);
lcd.print("SD:");
lcd.print(distance);
lcd.print("");
}
delay(1000);
lcd.clear();
}
/*else
{
lcd.setCursor(0,0);
lcd.print("X=");
lcd.print(xv);
lcd.print(" Y=");
lcd.print(yv);
lcd.setCursor(0,1);
lcd.print(" Z= ");
lcd.print(zv);
delay(1000);
}*/
int light_Reading_input = analogRead(light);
int light_Reading_output=1100-light_Reading_input;
lcd.setCursor(9,0);
lcd.print("I:");
lcd.print(light_Reading_output);
if(distance<=10 || distance2<=10)
{
  //digitalWrite(led, HIGH);
 tone(buzz, 1000);
  }
else
{
  //digitalWrite(led, LOW);
  noTone(buzz);

 }

 if (light_Reading_output>=500)
 {
  for(int j=0; j<3; j++)
  {
for(int i=0; i<10000; i++)
{
  digitalWrite(led, HIGH);
  }
  digitalWrite(led, LOW);
  
  }
 }
  else
  {
    digitalWrite(led, LOW);
    }
 //int light_reading = analogRead(light);
 //Serial.println(light);

}
