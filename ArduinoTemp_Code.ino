  #include <SPI.h>
  #include <Ethernet.h>
  #include <EthernetUdp.h>
  EthernetUDP Udp;
 
  int lm35Pin = 0;
  char  buffer[7];      //
  unsigned int port = 6000;
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  IPAddress ip(192, 168, 1, 9);
 
 
 float getTemperatureC(int pin)
 {
    int valueIn = analogRead(pin);  
    float temperature = (valueIn * 5.0 *100) /1024.0;
    return temperature;
 }

void setup() {
      
      Serial.begin(9600);
      Serial.println("Serial ready");
      Ethernet.begin(mac,ip);
      Udp.begin(port);
   
    }

  
 void loop() {
     
     float temperatureC;
     temperatureC = getTemperatureC(lm35Pin);
     Serial.println(temperatureC);
     
     dtostrf(temperatureC, 6, 2, buffer);
     
     Udp.beginPacket(IPAddress(192, 168, 1, 3), port);
     Udp.write(buffer);
     Udp.endPacket();
     delay(1000);
  }
 
 
