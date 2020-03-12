/*
   Copyright (c) 2015, Majenko Technologies
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

 * * Redistributions in binary form must reproduce the above copyright notice, this
     list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.

 * * Neither the name of Majenko Technologies nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "ikka";
const char *password = "tsanking";

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void ledcon()
{String message;

String req=server.arg("CONTROL");
message="val=";
message+=req;
server.send(200,"text/plain",message);
int y= req.toInt();
if(y>255)
y=255;
else
y=0;
analogWrite(D2,y);

  }
void handleRoot() {
  String message;
  String req = server.arg("parameter1");
  String req1 = server.arg("parameter2");
  message = "You are connected";
  message += "\n";
  message += "FIRST PARAMETER=";
  message += req;
  message += "\n";
  message += "SECOND PARAMETER=";
  message += req1;
  server.send(200, "text/plain", message );
  Serial.println(req);
  Serial.println(req1);
  int x1= req.toInt();
  if(x1>255);
  else if(x1<0)
  x1=0;
  for(int i=0;i<255;i++)
  {
  analogWrite(D2,i);
  delay(100);
  }
  int x2=req1.toInt();
  digitalWrite(D5,x2);
  digitalWrite(D6,x2);
  
}
void ledon()
{digitalWrite(D2,1);
server.send(200,"text/plain","LED is on");
  }
  void ledoff()
  {digitalWrite(D2,0);
server.send(200,"text/plain","LED is off");
    }
  

void func()
{
  server.send(200, "text/html", "<!DOCTYPE html><html><head><title>Page Title</title></head><body><h1>This is a Heading</h1><p>This is a paragraph.</p></body></html>");
}

void handleNotFound()
{
   server.send(200, "text/plain","SORRY" );
}
void ldr()
{ server.send(200, "text/plain",String(analogRead(A0)) );
  }
void setup() {
  delay(1000);
  pinMode(D2,OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/hello", handleRoot);
   server.on("/LEDON", ledon);
   server.on("/LEDOFF",ledoff);
   server.on("/LEDCONTROL",ledcon);
   server.on("/LDR",ldr);
 
  server.on("/sample", func);
   server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
  
}

void loop()
{
  server.handleClient();
  delay(500);
}
