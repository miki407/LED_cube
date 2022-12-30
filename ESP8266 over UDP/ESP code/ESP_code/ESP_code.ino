/*
  This code was based on a example code:
  UDPSendReceive.pde:
  created 21 Aug 2010
  by Michael Margolis
  
*/


#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#ifndef STASSID
#define STASSID "SSID"
#define STAPSK  "drsstc123"
#endif

unsigned int localPort = 8888;      // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged\r\n";       // a string to send back
boolean cube[10][10][10][2];
int Data = 14;
int Clock_ = 12;
int Latch = 16;


WiFiUDP Udp;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);
  pinMode(Data, OUTPUT);
  pinMode(Clock_, OUTPUT);
  pinMode(Latch, OUTPUT);
}

void loop() {
  
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int n = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    packetBuffer[n] = 0;

    
    for (int x = 0; x < 10; x++) {
      for (int y = 0; y < 10; y++) {
        for (int z = 0; z < 10; z++) {
          for (int c = 0; c < 2; c++) {
            if (packetBuffer[x * 200 + y * 20 + z * 2 + c] == '1') {
              cube[x][y][z][c] = 1;
            }
            else {
              cube[x][y][z][c] = 0;
            }
          }
        }
      }
    }
  }
  
  output();
}




void output() {
  for (int x_ = 0 ; x_ < 10; x_++) {
    for (int c_ = 0; c_ < 2; c_++) {
      for ( int y_ = 0; y_ < 10; y_++) {

        for (int n = 0; n < 6; n++) {
          digitalWrite(Clock_, 1);
          digitalWrite(Clock_, 0);
        }

        for (int z_ = 0; z_ < 10; z_++) {
          digitalWrite(Data, cube[x_][y_][z_][c_]);
          digitalWrite(Clock_, 1);
          digitalWrite(Clock_, 0);
        }

      }
    }

    for (int n = 0; n < 6; n++) {
      digitalWrite(Clock_, 1);
      digitalWrite(Clock_, 0);
    }
    for (int n = 0; n < 10; n++) {
      if ( n == x_ ) {
        digitalWrite(Data, 1);
      }
      else {
        digitalWrite(Data, 0);
      }
      digitalWrite(Clock_, 1);
      digitalWrite(Clock_, 0);
      digitalWrite(Data, 0);
    }
    digitalWrite(Latch, 1);
    digitalWrite(Latch, 0);
  }
}
