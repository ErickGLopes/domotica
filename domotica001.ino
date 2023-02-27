#include <WiFi.h>

#define sala 5
#define quarto 18
#define cozinha 19
int estado_sala = 0;
int estado_quarto = 0;
int estado_cozinha = 0;
const char *ssid = "Ez";
const char *password = "12345678";

WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  pinMode(sala, OUTPUT);
  pinMode(quarto, OUTPUT);
  pinMode(cozinha, OUTPUT);

  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Conectando em: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
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

void loop()
{
  WiFiClient client = server.available();

  if (client)
  {                                  
    Serial.println("Novo cliente."); 
    String currentLine = "";         
    while (client.connected())
    { 
      if (client.available())
      {                         
        char c = client.read(); 
        Serial.write(c);        
        if (c == '\n')
        { 
          if (currentLine.length() == 0)
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

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
            client.println();
            break;
          }
          else
          { 
            currentLine = "";
          }
        }
        else if (c != '\r')
        {                  
          currentLine += c;
        }

        if (currentLine.endsWith("GET /SALA"))
        {
          estado_sala = !estado_sala;
        }
        if (currentLine.endsWith("GET /QUARTO"))
        {
          estado_quarto = !estado_quarto;
        }
        if (currentLine.endsWith("GET /COZINHA"))
        {
          estado_cozinha = !estado_cozinha;
        }

        digitalWrite(sala, estado_sala);
        digitalWrite(quarto, estado_quarto);
        digitalWrite(cozinha, estado_cozinha);
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
