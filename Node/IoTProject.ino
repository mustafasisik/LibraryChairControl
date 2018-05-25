#define wifi_name "" // name of the network
#define wifi_password "" // network password
#define IP "184.106.153.149"    // IP of thingspeak.com
#define key "NTOI3YY8GBCA0GLU" // key of our thingspeak channel you can change it to yours.
float ldr;
float ldr2;
 
void setup()
{
  Serial.begin(115200); //Opens serial port.
                        //Baudrate of the ESP8266 is 115200
  
  Serial.println("AT"); //To test if module is connected.
  delay(3000); //3 secs delay
  analogReference(INTERNAL);
  if(Serial.find("OK")){         //If ESP is connected.
     Serial.println("AT+CWMODE=1"); // To make the ESP module be able to can connect other networks.
     delay(2000);
     String connectionCommand=String("AT+CWJAP=\"")+wifi_name+"\",\""+wifi_password+"\"";
     Serial.println(connectionCommand);
     delay(5000); // 5 secs delay.
 }
}

void loop(){
  ldr = analogRead(A0) ; 
  Serial.println(ldr);
  ldr2=analogRead(A1);
  Serial.println(ldr2);
  ldr_yolla(ldr,ldr2);
  delay(1000); // Refresh every sec.
}
 
void ldr_yolla(float ldr,float ldr2){
  Serial.println(String("AT+CIPSTART=\"TCP\",\"") + IP + "\",80");  //To connect thingspeak.
                                                                   //AT+CIPSTART request permission. 
                                                                   //TCP is the connection type.
  delay(1000);
  if(Serial.find("Error")){     //If ESP couldn't connet.
    Serial.println("AT+CIPSTART Error");
    return;
  }
  
  String sendCommand = "GET /update?key="+key+"&field1=";   // key of channel which will be use at Thingspeak 
  sendCommand += (int(ldr));                                // Assign the value to variable
                                              
  sendCommand += "&field2=";
  sendCommand +=(int(ldr2));
  sendCommand += "\r\n\r\n"; // While establishinh a conenction to ESP module we need this Enter command (/r/n).
  delay(3000);  // 3 secs delay                  
 
  Serial.print("AT+CIPSEND=");                    // to send data..
  Serial.println(sendCommand.length()+2);       // determines how many variable the data will contain.
 
  delay(1000); // refresh every sec.
 
  if(Serial.find(">")){                           // If we connected the ESP and get the data length.
                                                 
    Serial.print(sendCommand);  // Arduino sends the data.
    Serial.print("\r\n\r\n");
  }else{
    Serial.println("AT+CIPCLOSE");
  }
}
