/*Weather monitoring system with Nodemcu
 * https://srituhobby.com
 */
 
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

DHT dht(D3, DHT11); //(sensor pin,sensor type)
BlynkTimer timer;

#define BLYNK_TEMPLATE_ID "TMPL2m6NxfVeh"
#define BLYNK_TEMPLATE_NAME "Abdalla Elbahrawy"
#define BLYNK_AUTH_TOKEN "JOZEKAI_MVid877X_JuJKOuVo3th07yh"

char auth[] = "JOZEKAI_MVid877X_JuJKOuVo3th07yh"; //Enter the Auth code which was send by Blink
char ssid[] = "Orange-9ptg";  //Enter your WIFI Name
char pass[] = "75934821Aa";  //Enter your WIFI Password


String mq135Value = "";  // Store MQ-135 gas sensor data
String rainValue = "";   // Store rain sensor data
int sensorCount = 0;     // Count of sensors for data processing
String data = "";        // Temporarily store sensor data


void weather() {
  delay(2000); // Add a delay of 2 seconds
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // int r = analogRead(A0);

  

  r = map(r, 0, 1023, 100, 0);
  if (isnan(h) || isnan(t)) {
    Serial.println(h);
    Serial.println(t);
    Serial.println("Failed to read from DHT sensor!");
    
    // return;
  }


  

  Blynk.virtualWrite(V0, t);  //V0 is for Temperature
  Blynk.virtualWrite(V1, h);  //V1 is for Humidity
  // Blynk.virtualWrite(V2, r);  //V2 is for Rainfall
  Blynk.virtualWrite(V2, rainValue);  //V2 is for Rainfall
  Blynk.virtualWrite(V3, mq135Value);  //V2 is for gas
}

void setup() {
  Serial.begin(9600); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  pinMode(D3,INPUT);
  // Setup a function to be called every second
  timer.setInterval(10L, weather);
}

void loop() {
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer

while (Serial.available() > 0)
  {
    char incomingByte = Serial.read();
    if (incomingByte == 'r')
    {
      if (sensorCount == 0)
      {
        rainValue = data.substring(0, 2);
        //lcd.print(temperature);
        // lcd.print("r=");
        // lcd.print(rainValue);
        Serial.print("r=");
        Serial.println(rainValue);
        delay(500);
      }

      data = "";
      sensorCount++;
    }else if (incomingByte == 'm'){
      if (sensorCount == 1)
      {
        mq135Value = data.substring(0, 3);
        //lcd.print(humidity);
        // lcd.print("g=");
        // lcd.print(mq135Value);
        Serial.print("g=");
        Serial.println(mq135Value);
        delay(500);
      }
    }else
    {
      data += incomingByte;
    }

    if (sensorCount == 2)
    {
      sensorCount = 0;
    }




  }
  


}