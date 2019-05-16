int cds = A0;
int led1 = 3;
int led2 = 5;
int led3 = 6;
 
void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  int cdsValue = analogRead(cds);
 
 
  if (cdsValue > 300 && cdsValue < 500)
  {
    digitalWrite(led1, HIGH);
  }
  else if (cdsValue > 501 && cdsValue < 600)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
  }
  else if (cdsValue > 601 && cdsValue < 1000)
  {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  }
  else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  delay(200);
}
