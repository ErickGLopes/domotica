/*
 WiFi Web Server LED Blink
 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 5.
 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off
 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.
 Circuit:
 * WiFi shield attached
 * LED attached to pin 5
 created for arduino 25 Nov 2012
 by Tom Igoe
ported for sparkfun esp32 
31.01.2017 by Jan Hendrik Berlin
 
 */

#include <WiFi.h>

#define sala 5
#define quarto 18
#define cozinha 19
int estado_sala = 0;
int estado_quarto = 0;
int estado_cozinha = 0;
const char* ssid     = "Ez";
const char* password = "12345678";


WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    pinMode(sala, OUTPUT);      // set the LED pin mode
    pinMode(quarto, OUTPUT);
    pinMode(cozinha, OUTPUT);

    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Conectando em: ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    IPAddress ip(192, 168, 0, 199);
    IPAddress gateway(192, 168, 0, 1);
    IPAddress subnet(255, 255, 255, 0);

    Serial.println("");
    Serial.println("WiFi Conectado.");
    Serial.println("Endereço IP: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

int value = 0;

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("Novo cliente.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.println("<!DOCTYPE html>");
            client.println("<head>");
            client.println("<title>Witcher Automations</title>");
            client.println("<style>");
            client.println("a {");
            client.println("margin-top: 50px;");
            client.println("}");
            client.println("body {");
            client.println("font-family: Arial;");
            client.println("background-color: #90EE90;");
            client.println("}");
            client.println("button {");
            client.println("width: 150px;");
            client.println("height: 70px;");
            client.println("margin: 10px;");
            client.println("background-color: green;");
            client.println("align-items: center;");
            client.println("font-size: 16px;");
            client.println("padding: 10px 20px;");
            client.println("border: none;");
            client.println("border-radius: 4px;");
            client.println("cursor: pointer;");
            client.println("}");
            client.println("p {");
            client.println("font-size: 20px;");
            client.println("align-items: center;");
            client.println("}");
            client.println("section {");
            client.println("width: 200px;");
            client.println("height: 300px;");
            client.println("background-color: #F0F0F0;");
            client.println("padding: 20px;");
            client.println("border-radius: 10px;");
            client.println("border: 1px solid #CCCCCC;");
            client.println("}");
            client.println("</style>");
            client.println("</head>");
            client.println("<body>");
            client.println("<center>");
            client.println("<section>");
            client.println("<div><a href=\"/SALA\"\><button><strong><p>Sala</p></strong></button></a>");
            client.println("</div>");
            client.println("<div>");
            client.println("<a href=\"/QUARTO\"\><button><strong><p>Quarto</p></strong></button></a>");
            client.println("<div>");
            client.println("<a href=\"/COZINHA\"\><button><strong><p>Cozinha</p></strong></button></a>");
            client.println("</div>");
            client.println("</section>");
            client.println("</center>");
            client.println("</body>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

       
        if (currentLine.endsWith("GET /SALA")) {
          estado_sala = ! estado_sala;                         
        }
        if (currentLine.endsWith("GET /QUARTO")) {
          estado_quarto = ! estado_quarto;
        }
        if (currentLine.endsWith("GET /COZINHA")) {
          estado_cozinha = ! estado_cozinha;
        }

        digitalWrite(sala, estado_sala);
        digitalWrite(quarto, estado_quarto);  
        digitalWrite(cozinha, estado_cozinha);
        
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
