#include<WiFi.h>
#include<AWS_IOT.h>

#define WIFI_SSID "duckietown" // SSID of your WIFI
#define WIFI_PASSWD "quackquack" //your wifi password

#define CLIENT_ID "temp_sensor"// thing unique ID, this id should be unique among all things associated with your AWS account.
#define MQTT_TOPIC "$aws/things/esp32_lm35_temp_sensor/shadow/update" //topic for the MQTT data
#define AWS_HOST "****************amazonaws.com" // your host for uploading data to AWS,

AWS_IOT aws;

const int sensor=A0;
float tempc; 
float tempf;
float vout;

void setup(){
  pinMode(sensor,INPUT);
  Serial.begin(9600);
  Serial.print("\nInitializing thing \n");

  Serial.print("\n  Initializing WIFI: Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  Serial.print("  ");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println("\n  Connected.\n  Done");


  Serial.println("\n  Initializing connetction to AWS....");
  if(aws.connect(AWS_HOST, CLIENT_ID) == 0){ // connects to host and returns 0 upon success
    Serial.println("  Connected to AWS\n  Done.");
  }
  else {
    Serial.println("  Connection failed!\n make sure your subscription to MQTT in the test page");
  }
  Serial.println("  Done.\n\nDone.\n");
}

void loop(){
  // read temperature
  vout=analogRead(sensor); //Reading the value from sensor
  vout=(vout*500)/1023;
  tempc=vout*0.01; // Storing value in Degree Celsius
  tempf=(tempc*1.8)+32;
 
  //create string payload for publishing
  String temp_humidity = "Temperature in Celcius: ";
  temp_humidity += String(tempc);
  
  
  char payload[80];
  temp.toCharArray(payload, 80);
  Serial.println("Publishing ......... ");
  Serial.println(payload);
  if(aws.publish(MQTT_TOPIC, payload) == 0){// publishes payload and returns 0 upon success
      Serial.println("Successfully Published\n");
    }
  else{
      Serial.println("Publishing Failed!\n");
    }
  delay(5000);
}
