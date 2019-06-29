//Pin Number

int state = 0;
 
void setup() {

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  //int state = analogRead(A0);
  
  if (state ==0)
  {
    digitalWrite(2,HIGH);
    delay(200);
  }
  else if (state >= 51 && state <= 100)
  {
    digitalWrite(2,HIGH);
    digitalWrite(3,HIGH);
    delay(200);
  }
  else if (state >= 101 && state <= 150)
  {
    digitalWrite(2,HIGH);
    digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);
    delay(200);
  }  
}
