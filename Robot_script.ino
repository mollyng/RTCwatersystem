
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;

int RELAY = 4; //for each relay, give it a pin slot
int RELAY2 = 6;
int RELAY3 = 8;
char daysOfTheWeek[7][12] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
//days of the week is from 0-6
void setup () {

  Serial.begin(9600);
  Wire.begin();
  RTC.begin();

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__)); //when you plug it in and gives you an error, try to take out the battery, hit the restart button, and then check if it gives you the right time and date
  }
  pinMode(RELAY, OUTPUT); //defining output
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  //digitalWrite(8, HIGH); //8 is where the relay is plugged in
}
void loop () {
  DateTime now = RTC.now();

  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(" ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(1000); //ms

  //now.dayOfTheWeek()==5, "5" is friday
  //this is where you can configure the time and length of watering

  if (now.dayOfTheWeek() == 2 && now.hour() == 12 && now.minute() == 10 && now.second() == 10) {
    //3 sets of on & off for different water regimes ~ our system has 3 pumps, one for each shelf. Each relay is in charge of a different shelf. 
    digitalWrite(RELAY, HIGH); //turn it "on"
    delay(120000); //for x long
    digitalWrite(RELAY, LOW); //turn it "off"
    delay(5000); 
   
    digitalWrite(RELAY2, HIGH);
    delay(120000);
    digitalWrite(RELAY2, LOW);
    delay(5000);
 
    digitalWrite(RELAY3, HIGH);
    delay(120000);
    digitalWrite(RELAY3, LOW);
    delay(5000);
  }
  if (now.dayOfTheWeek() == 4 && now.hour() == 12 && now.minute() == 10 && now.second() == 10) {
    //this is top shelf
    digitalWrite(RELAY, HIGH);
    delay(120000);
    digitalWrite(RELAY, LOW);
    delay(5000);
    //this is the second shelf
    digitalWrite(RELAY2, HIGH);
    delay(120000);
    digitalWrite(RELAY2, LOW);
    delay(5000);
    //this is the bottom shelf
    digitalWrite(RELAY3, HIGH);
    delay(120000);
    digitalWrite(RELAY3, LOW);
    delay(5000);
  }
}



