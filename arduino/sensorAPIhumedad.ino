#include <WiFi.h>
#include <HTTPClient.h>
#include "DHTesp.h"

//declaramosla variable que almacena el pin a conectar el DHT11
int pinDHT =15;
//variables string para almacenar la temperatura la humedad desde el sensor
String temperatura, humedad;

//Instanciamos el DHT
DHTesp dht;
const char* ssid = "POCO X5 Pro hugo";
const char* password =  "Nuevaera2024@";
const char* serverName = "http://192.168.17.157:3000/sensor";


int cont = 300;
String ip;

//Your Domain name with URL path or IP address with path


// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

void setup() {
  
  //pinMode(pot, INPUT);
  Serial.begin(115200);
   //Inicializamos el dht11
  dht.setup(pinDHT,DHTesp::DHT11);

  analogReadResolution(10);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  //Send an HTTP POST request every 10 minutes

  
  if ((millis() - lastTime) > timerDelay) {
     int sensor = analogReadMilliVolts(2);
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      TempAndHumidity data = dht.getTempAndHumidity();
      temperatura=String(data.temperature,2) + " °C";
      humedad=String(data.humidity,1)+" %";
      cont--;

      Serial.println(sensor);
      

      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      //String ip = WiFi.localIP();
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
      
      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&value1=24.25&value2=49.54&value3=1005.14";           
      // Send HTTP POST request
      //int httpResponseCode = http.POST(httpRequestData);
      Serial.print(cont);
     
      
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"nombreCompleto\":\"Hugo chenal\",\"correo\":\"hchenala@miumg.edu.gt\",\"numCarne\":\"0902-12-3918\",\"latitud\":\"15.472378\",\"longitud\":\"-90.369280\",\"humedad\":\"" + humedad + "\",\"temperatura\":\"" + temperatura + "\"}");

  
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}