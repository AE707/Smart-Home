#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
int ledV=8;
int ledR=7;
int ledJ=4; // C++ code
int alarme= 6;
int gaz=A0;
int mouvement=5;
int photoresistor=A1;
int moteur=2;

int pos = 0;

Servo servo_9;
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


//
void setup()
{
 
  pinMode(ledV, OUTPUT);
   pinMode(ledR, OUTPUT);
  pinMode(ledJ, OUTPUT);
  pinMode(alarme,OUTPUT) ;
  pinMode (gaz, INPUT);
   pinMode(mouvement, INPUT);
  pinMode(photoresistor, INPUT);
   pinMode(moteur, OUTPUT);
  Serial.begin(9600);// Initiate a serial communication
   servo_9.attach(3);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Put your card to the reader...");
  Serial.println();

   
}

void loop()
{  
  Serial.println(analogRead(A0));
  if (analogRead(gaz)>=100) {
    digitalWrite(ledV, LOW);
    digitalWrite(ledR, HIGH);
    digitalWrite(alarme, HIGH);
    digitalWrite(moteur, HIGH);
  
    delay(1000);
    
   
  }
  
  
 else { 
      digitalWrite(ledV, HIGH);
      digitalWrite(ledR, LOW);
      digitalWrite(alarme,LOW );
  
    
   digitalWrite(moteur, LOW);
  delay(1000);
   
 }
  Serial.println(photoresistor);
  if (analogRead(photoresistor) <=15)
  { 
    if (digitalRead (mouvement)==1)
    {digitalWrite(ledJ, HIGH);
     delay(1000);}
    else
    {digitalWrite(ledJ, LOW);
     delay(1000);}
  }
  else
  {
     {digitalWrite(ledJ, LOW);
       delay(1000);}
    
  }
    // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "73 60 49 13") 
  {
    for (pos = 90; pos >= 0; pos -= 1) {
    // tell servo to go to position in variable 'pos'
    servo_9.write(pos);
    delay(15); // Wait for 15 millisecond(s)
  };
  delay(3000);
    for (pos = 0; pos <= 90; pos += 1) {
    // tell servo to go to position in variable 'pos'
    servo_9.write(pos);
    delay(15); // Wait for 15 millisecond(s)
  };
  delay(500);
    Serial.println("Authorized access");
    Serial.println();
    
    delay(400);
  }
 
 else   {
    Serial.println(" Access denied");
  }
  
  
  }
