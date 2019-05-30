int cds = A0;
int led1 = 3;
int led2 = 4;
int led3 = 5;
 
void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int cdsValue = analogRead(cds);

 Serial.println(cdsValue);
 
  if (cdsValue > 0 && cdsValue < 300)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }
  else if (cdsValue > 301 && cdsValue < 600)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
  }
  else if (cdsValue > 601 && cdsValue < 800)
  {
  digitalWrite(led1, HIGH);
  }
  else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  delay(200);
}
