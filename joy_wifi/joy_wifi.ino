
#include <WiFi.h>

const int x = 34;
const int y = 35;

const char* ssid = "iPod touch";
char* password = "tomakomaigm";
String m5camera_ipaddr = "172.20.10.2";

WiFiClient client;


void setup() { 

  WiFi.begin(ssid, password);  // Wi-Fiネットワークに接続する
  while (WiFi.status() != WL_CONNECTED) {  // 接続したか調べる
      delay(500);
      Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.begin(115200);
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  
}



void send_req(String cmd) {
    String url = "/control?var=pantilt&val=";
    Serial.println(url + cmd);

    if (!client.connect(m5camera_ipaddr.c_str(), 80)) {
        Serial.println("connection faile");
        return;
    }
    client.print(String("GET ") + url + cmd + " HTTP/1.1\r\n" +
                        "Host: " + m5camera_ipaddr + "\r\n" + 
                        "Connection: close\r\n\r\n");

    while(client.available()){
        String line = client.readStringUntil('\r');
    }
}

void loop() {
  String cmd = "p";
  int a = analogRead(x), b = analogRead(y), X, Y;
  X = a * 0.04395604;
  Y = b * 0.04395604;
  Serial.print("x=");

  Serial.println(X);
  Serial.print("y=");
  Serial.println(Y);


  if(X > 175){
      cmd += "+";
  }

  else if(X < 65){
        cmd += "-";
  }
  else cmd += "0";
  
  if(Y > 175){
      cmd += "t+";
  }

  else if(Y < 67){
    
      cmd += "t-";
    
  }
  else cmd += "t0";
  send_req(cmd);
  delay(150);
}
