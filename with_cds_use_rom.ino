#include <EEPROM.h>

int led1 = 3;
int led2 = 4;
int led3 = 5;
int led4 = 6;

int sw = 12;
int cds = A0;

int time[4] = {0, 1, 2, 3};
int temp[4];

int index[4] = {0, 0, 0, 0};

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(sw, INPUT_PULLUP);

  if (EEPROM.read(0))
  {
    time[0] = EEPROM.read(0);
    time[1] = EEPROM.read(1);
    time[2] = EEPROM.read(2);
    time[3] = EEPROM.read(3);
  }
  Serial.begin(9600);
}

void loop() {

  int cdsValue;
  int min, max;

  if (digitalRead(sw) == LOW)   //스위치 on
  {
    cdsValue = analogRead(cds);

    //cds 값에 따른 LED 개수 설정
    if (cdsValue > 200 && cdsValue < 400)
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
    }
    else if (cdsValue > 401 && cdsValue < 600)
    {
      digitalWrite(index[0] + 3, HIGH);
      time[index[0]] += 1;
      digitalWrite(index[1] + 3, HIGH);
      time[index[1]] += 1;
      digitalWrite(index[2] + 3, HIGH);
      time[index[2]] += 1;

      digitalWrite(index[3] + 3, LOW);
    }
    else if (cdsValue > 601 && cdsValue < 800)
    {
      digitalWrite(index[0] + 3, HIGH);
      time[index[0]] += 1;
      digitalWrite(index[1] + 3, HIGH);
      time[index[1]] += 1;

      digitalWrite(index[2] + 3, LOW);
      digitalWrite(index[3] + 3, LOW);
    }
    else if (cdsValue > 801 && cdsValue < 1500)
    {
      digitalWrite(index[0] + 3, HIGH);
      time[index[0]] += 1;

      digitalWrite(index[1] + 3, LOW);
      digitalWrite(index[2] + 3, LOW);
      digitalWrite(index[3] + 3, LOW);
    }
  }

  else                        //스위치 off
  {
    digitalWrite (led1, LOW);
    digitalWrite (led2, LOW);
    digitalWrite (led3, LOW);
    digitalWrite (led4, LOW);

    //배열 복사
    for (int i = 0; i < 4; i++)
    {
      temp[i] = time[i];
    }

    //오름차순 정렬
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 3; j++ )
        if (temp[j] >= temp[j + 1])
        {
          int m = temp[j + 1];
          temp[j + 1] = temp[j];
          temp[j] = m;
        }
    }
    //index 초기화
    for (int i = 0; i < 4; i++)
    {
      if (time[i] == temp[0]) index[0] = i;
      if (time[i] == temp[1]) index[1] = i;
      if (time[i] == temp[2]) index[2] = i;
      if (time[i] == temp[3]) index[3] = i;
    }
  }
  EEPROM.write(0, time[0]);
  EEPROM.write(1, time[1]);
  EEPROM.write(2, time[2]);
  EEPROM.write(3, time[3]);

  max = EEPROM.read(0);
  min = EEPROM.read(0);

  for (int i = 0; i < 4; i++)
  {
    if (EEPROM.read(i) > max)  max = EEPROM.read(i);
    if (EEPROM.read(i) < min)  min = EEPROM.read(i);

    if (max > 150 && (max - (max / 10)) < min)
    {
      for (int j = 0 ; j < 4 ; j++) {
        EEPROM.write(j, j);
      }
      time[0] = EEPROM.read(0);
      time[1] = EEPROM.read(1);
      time[2] = EEPROM.read(2);
      time[3] = EEPROM.read(3);
    }
  }


  //    if (EEPROM.read(0) > 200)
  //    {
  //      for (int i = 0 ; i < EEPROM.length() ; i++) {
  //        EEPROM.write(i, 0);
  //      }
  //    }

  //  Serial.println(cdsValue);

  Serial.println(time[0]);
  Serial.println(time[1]);
  Serial.println(time[2]);
  Serial.println(time[3]);

  delay(50);
  Serial.println(" ");
  //  Serial.println(max);
  //  Serial.println(min);
  //  Serial.println(" ");


}
