// C++ code
//
int LedR=7;
int LedV=8;
int Gaz=A0;
int Buz=6;
int Max = 60;
int G;
void setup()
{
  Serial.begin(9600);
  pinMode(LedR, OUTPUT);
  pinMode(LedV, OUTPUT);
  pinMode(Gaz, INPUT);
  pinMode(Buz, OUTPUT);
}

void loop()
{
   G = analogRead(Gaz);
  Serial.println(G);
  
  if (G>Max){ 
  digitalWrite(LedR, HIGH); 
  tone (Buz,40); // digitalWrite(Buz, HIGH);
  digitalWrite(LedV, LOW);
  }
  
  
  else {
    digitalWrite(LedV,HIGH);
    digitalWrite(LedR,LOW);
    noTone (Buz); //digitalWrite(Buz, LOW);
  }  
        
}
