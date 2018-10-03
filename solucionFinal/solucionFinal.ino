#include <DHT.h>
#include<Process.h>
// Definimos el pin digital donde se conecta el sensor 
#define DHTPIN 2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11
// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

  //Inicializamos variables.
String id = "SensorTermico1";
String json;
float hum,tem;

void setup() {
  // Inicializamos comunicación serie.
  Serial.begin(9600);
  // Comenzamos el sensor DHT.
  dht.begin(); 

  //Registramos sensor.
  registrarSensor();
 }

 
void loop() {
  // Esperamos 5 segundos entre medidas
  delay(5000);
  // Leemos la humedad relativa
  hum = leerHumedad();
  // Leemos la temperatura en grados centígrados 
  tem = leerTemperatura();
  //Enviamos datos
  enviarDatos(hum,1);
  enviarDatos(tem,0);

  
}




float leerTemperatura(){
  float t = dht.readTemperature();
  Serial.print("Temperatura: "); 
  Serial.print(t);
  Serial.println(" *C "); 
  return t;
}

float leerHumedad(){
  float h = dht.readHumidity();
  Serial.print("Humedad: "); +
  Serial.println(h);
  return h;
}

    void registrarSensor(){
        Process p;
        Serial.println("Registro de sensor");
        /*
        p.begin("curl");
        p.addParameter("-H");
        p.addParameter("\"Content-Type: application/json\"");
        p.addParameter("-X");
        p.addParameter("POST");
        p.addParameter("-d");
        p.addParameter("\"{\"id\":\"SensorTermico1\",\"type\":\"SensorTermico\",\"temperatura\":{\"value\":0},\"humedad\":{\"value\":0}}\"");
        p.addParameter("-k");
        p.addParameter("\"http://148.205.176.167:1026/v2/entities\"");
        p.run();*/
        p.runShellCommand("curl -H \"Content-Type: application/json\" -X POST -d \"{\"id\":\"SensorTermico1\",\"type\":\"SensorTermico\",\"temperatura\":{\"value\":0},\"humedad\":{\"value\":0}}\" -k \"http://148.205.176.167:1026/v2/entities\"");
        while (p.available()) {
          char c = p.read();
          Serial.print(c);
        }
        Serial.flush();
        Serial.println("Terminé regsitro");
        p.close();
        return;
    }

       void enviarDatos(int magnitud, int tipo){
        Process p;
        p.begin("curl");
        p.addParameter("-H");
        p.addParameter("\"Content-Type: application/json\"");
        p.addParameter("-X");
        p.addParameter("PUT");
        p.addParameter("-d");
        json = "\"{\"value\":"+(String)magnitud+"}\"";
        Serial.println(json);
        p.addParameter(json);
        p.addParameter("-k");
        // Si es temperatura
        if(tipo == 0){
          p.addParameter("\"http://148.205.176.167:1026/v2/entities/"+id+"/attrs/temperatura\"");
        }else{
          // Si es humedad
          p.addParameter("\"http://148.205.176.167:1026/v2/entities/"+id+"/attrs/humedad\"");
        }
        
        p.run();
        /*
        while (p.available() > 0) {
          char c = p.read();
          Serial.print(c);
        }
        */
        Serial.println("Terminé enviar datos");
        Serial.flush();
        p.close();
    }

