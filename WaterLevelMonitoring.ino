#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include<HCSR04.h>
#define trig D6
#define echo D5
#define buzz D1
HCSR04 hc(trig,echo);
char auth[] = " r6lI8Q-zhb_iFY-IsVDkqL3egKsuHFXS";
char ssid[] = "Bharadwaj";
char pass[] = "12345678";
BlynkTimer timer;
void sendSensor()
{
 int c = hc.dist();
 if ( c == 0 ) {
 Serial.println("Failed to read from Ultrasonic sensor!");
 return;
 }
 Blynk.virtualWrite(V5, c);
 
 if((c<=12) and (c>=8))
 {
 Blynk.virtualWrite(V6,255);
 Blynk.virtualWrite(V7,0);
 Blynk.virtualWrite(V8,0);
 digitalWrite(buzz,LOW);
 
 }
 else if((c<=8) and (c>=5))
 {
 Blynk.virtualWrite(V7, 255);
 Blynk.virtualWrite(V6, 0);
 Blynk.virtualWrite(V8, 0);
 digitalWrite(buzz,LOW);
 }
 else
 {
 Blynk.virtualWrite(V8,255);
 Blynk.virtualWrite(V7, 0);
 Blynk.virtualWrite(V6, 0);
 digitalWrite(buzz,HIGH);
 }
}
void setup()
{
 pinMode(buzz, OUTPUT);
 // Debug console
 Serial.begin(9600);
 Blynk.begin(auth, ssid, pass);
timer.setInterval(1000L, sendSensor);
}
void loop()
{
 Blynk.run();
 timer.run();
}
