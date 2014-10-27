////
//
// General code from http://www.pushingbox.com for Arduino Yun v1.0
// adapted from the original code for the WiFi shield
// created 21 October 2014
// by Simon Schvartzman
//
////

#include <Bridge.h>
#include <HttpClient.h>
 
  /////////////////
 // MODIFY HERE //
/////////////////
char DEVID1[] = "Your_DevID_Here";        //Scenario : "The mailbox is open"

//Numeric Pin where you connect your switch
uint8_t pinDevid1 = 3; // Example : the mailbox switch is connect to the Pin 3

// Debug mode
boolean DEBUG = true;
  //////////////
 //   End    //
//////////////


char serverName[] = "api.pushingbox.com";
boolean pinDevid1State = false;                // Save the last state of the Pin for DEVID1
boolean lastConnected = false;  

void setup() 
{
  // initialize serial:
  Serial.begin(9600);

  while (!Serial); // wait for a serial connection

  pinMode(pinDevid1, INPUT);

  Bridge.begin();
}
 
void loop() 
{
   ////
   // Listening for the pinDevid1 state
   ////
  if (digitalRead(pinDevid1) == HIGH && pinDevid1State == false) // switch on pinDevid1 is ON
  {
    if(DEBUG){Serial.println("pinDevid1 is HIGH");}
    pinDevid1State = true;
    //Sending request to PushingBox when the pin is HIGH
    sendToPushingBox(DEVID1);
  }
   if (digitalRead(pinDevid1) == LOW && pinDevid1State == true) // switch on pinDevid1 is OFF
  {
    if(DEBUG){Serial.println("pinDevid1 is LOW");}
    pinDevid1State = false;
  }
 
}


//Function for sending the request to PushingBox
void sendToPushingBox(char devid[])
{
  String APIRequest;
  
  Serial.println("Connecting to PushingBox ...");
  HttpClient client; 
  Serial.println("connected");
  Serial.println("sending request");
  
  //build API request
  APIRequest = String(serverName) + "/pushingbox?devid=" + String(devid);
  
  client.get (APIRequest);
    //DEBUG part
    // this write the response from PushingBox Server.
    // You should see a "200 OK"
    if (client.available()) 
    {
      char c = client.read();
      if(DEBUG){Serial.print(c);}
    }  

}

