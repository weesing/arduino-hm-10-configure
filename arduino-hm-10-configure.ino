#include <SoftwareSerial.h>

SoftwareSerial BTSerial(3, 4); // RX | TX

void sendCommand(const char* command) {
  Serial.print("Sending command: >");
  Serial.println(command);
  
  BTSerial.println(command);
  delay(500);
  if (BTSerial.available())
  {
    char reply[100];
    int i = 0;
    while (BTSerial.available())
    {
      reply[i] = BTSerial.read();
      i += 1;
    }
    reply[i] = '\0';
    Serial.print(reply);
  }
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  delay(100);
  BTSerial.println("U,9600,N");
  BTSerial.begin(9600);  // HC-05 default speed in AT command more
}

void loop()
{
  // sendCommand("AT+GETSTAT");
  if (BTSerial.available())
  {
    char reply[100];
    int i = 0;
    while (BTSerial.available())
    {
      reply[i] = BTSerial.read();
      i += 1;
    }
    reply[i] = '\0';
    Serial.print(reply);
  }
  if (Serial.available()) {
    char command[100];
    int i = 0;
    while(Serial.available()) {
      char c = Serial.read();
      if (c != 10 && c != 13) {
        command[i] = c;
        Serial.print(c);
        delay(10);
        i += 1; 
      }
    }
    command[i] = "\0";
    Serial.println("");
    Serial.print("Command read: >");
    Serial.println(command);
    delay(500);
    sendCommand(command);
    delay(1000);
  }
}
