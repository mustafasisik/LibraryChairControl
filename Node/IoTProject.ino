#define ag_ismi "" // bağlanılacak ağın adı
#define ag_sifresi "" // bağlanılacak ağın şifresi
#define IP "184.106.153.149"    //thingspeak.com IP adresi
 
float ldr;
float ldr2;
 
void setup()
{
  Serial.begin(115200); //Seriport'u açýyoruz. Güncellediðimiz 
                        //ESP modülünün baudRate deðeri 115200 olduðu için bizde Seriport'u 115200 þeklinde seçiyoruz
  
  Serial.println("AT"); //ESP modülümüz ile baðlantý kurulup kurulmadýðýný kontrol ediyoruz.
  
  delay(3000); //ESP ile iletiþim için 3 saniye bekliyoruz.
 analogReference(INTERNAL);
  if(Serial.find("OK")){         //esp modülü ile baðlantýyý kurabilmiþsek modül "AT" komutuna "OK" komutu ile geri dönüþ yapýyor.
     Serial.println("AT+CWMODE=1"); //esp modülümüzün WiFi modunu STA þekline getiriyoruz. Bu mod ile modülümüz baþka aðlara baðlanabilecek.
     delay(2000);
     String baglantiKomutu=String("AT+CWJAP=\"")+ag_ismi+"\",\""+ag_sifresi+"\"";
    Serial.println(baglantiKomutu);
    
     delay(5000);
 }
}
 
void loop(){
  ldr = analogRead(A0) ; 
 Serial.println(ldr);
  ldr2=analogRead(A1);
  Serial.println(ldr2);
 ldr_yolla(ldr,ldr2);
 // dakikada 1 güncellenmesi için 1 dakika bekle
 delay(1000);
}
 
 
void ldr_yolla(float ldr,float ldr2){
 Serial.println(String("AT+CIPSTART=\"TCP\",\"") + IP + "\",80");  //thingspeak sunucusuna baðlanmak için bu kodu kullanýyoruz. 
                                                                   //AT+CIPSTART komutu ile sunucuya baðlanmak için sunucudan izin istiyoruz. 
                                                                   //TCP burada yapacaðýmýz baðlantý çeþidini gösteriyor. 80 ise baðlanacaðýmýz portu gösteriyor
 delay(1000);
  if(Serial.find("Error")){     //sunucuya baðlanamazsak ESP modülü bize "Error" komutu ile dönüyor.
   Serial.println("AT+CIPSTART Error");
    return;
  }
  
 String yollanacakkomut = "GET /update?key=NTOI3YY8GBCA0GLU&field1=";   // Burada NTOI3YY8GBCA0GLU yazan kýsým bizim API Key den aldýðýmýz Key. Siz buraya kendi keyinizi yazacaksýnýz.
 yollanacakkomut += (int(ldr));                                      // Burada ise sýcaklýðýmýzý float deðiþkenine atayarak yollanacakkomut deðiþkenine ekliyoruz.
                                              // ESP modülümüz ile seri iletiþim kurarken yazdýðýmýz komutlarýn modüle iletilebilmesi için Enter komutu yani
 yollanacakkomut += "&field2=";
 yollanacakkomut +=(int(ldr2));
 yollanacakkomut += "\r\n\r\n";
  delay(3000);                                                                                // /r/n komutu kullanmamýz gerekiyor.
 
 Serial.print("AT+CIPSEND=");                    //veri yollayacaðýmýz zaman bu komutu kullanýyoruz. Bu komut ile önce kaç tane karakter yollayacaðýmýzý söylememiz gerekiyor.
 Serial.println(yollanacakkomut.length()+2);       //yollanacakkomut deðiþkeninin kaç karakterden oluþtuðunu .length() ile bulup yazýrýyoruz.
 
 delay(1000);
 
 if(Serial.find(">")){                           //eðer sunucu ile iletiþim saðlayýp komut uzunluðunu gönderebilmiþsek ESP modülü bize ">" iþareti ile geri dönüyor.
                                                 // arduino da ">" iþaretini gördüðü anda sýcaklýk verisini esp modülü ile thingspeak sunucusuna yolluyor.
 Serial.print(yollanacakkomut);
 Serial.print("\r\n\r\n");
 }
 else{
 Serial.println("AT+CIPCLOSE");
 }
}
