  //Función que envía datos al OCB
    void enviarDatos(int magnitud){
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
        p.addParameter("\"http://localhost:1026/v2/entities/"+id+"/attrs/temperatura\"");
        p.run();
        while (p.available() > 0) {
          char c = p.read();
          Serial.print(c);
        }
        Serial.println("Terminé enviar datos");
        Serial.flush();
        p.close();
    }

        //Función que registra al sensor en el servidor
    void registrarSensor(){
        Process p;
        Serial.println("Registro de sensor");
        p.begin("curl");
        p.addParameter("-H");
        p.addParameter("\"Content-Type: application/json\"");
        p.addParameter("-X");
        p.addParameter("POST");
        p.addParameter("-d");
        //p.addParameter("{\"id\": "+id+",\"type\":\"SensorSismico\",\"temblor\":{\"value\":0},\"zona\":{\"value\":"+zona+"}}");
        p.addParameter("\"{\"id\":\"SensorTermico1\",\"type\":\"SensorTermico\",\"temperatura\":{\"value\":0},\"zona\":{\"value\":1}}\"");
        p.addParameter("-k");
        p.addParameter("\"http://localhost:1026/v2/entities\"");
        p.run();
        while (p.available() > 0) {
          char c = p.read();
          Serial.print(c);
        }
        Serial.println("Terminé regsitro");
        Serial.flush();
        p.close();
        return;
    }
