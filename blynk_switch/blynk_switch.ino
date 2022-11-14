#define Captivate1 D0

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";
bool Status;

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(Captivate1,INPUT);
  Status = digitalRead(Captivate1);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  bool newStatus = digitalRead(D0);
  if (Status != newStatus)
  {
    Status = newStatus;
  }
  Serial.print(Status);
  Serial.println(newStatus);
}
