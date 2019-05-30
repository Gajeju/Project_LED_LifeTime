#include <EEPROM.h>

int led1 = 3;
int led2 = 4;
int led3 = 5;
int sw = 12;

int time[3] = {0, 1, 2};

int temp[3];
int index1;
int index2;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(sw, INPUT_PULLUP);

  Serial.begin(9600);

  if (EEPROM.read(0))
  {
    time[0] = EEPROM.read(0);
    time[1] = EEPROM.read(1);
    time[2] = EEPROM.read(2);
  }
}

void loop() {

  if (digitalRead(sw) == LOW)   //스위치 on
  {
    digitalWrite (index1 + 3, HIGH);
    time[index1] += 1;
    digitalWrite (index2 + 3, HIGH);
    time[index2] += 1;
    delay(100);
  }
  else                        //스위치 off
  {
    digitalWrite (led1, LOW);
    digitalWrite (led2, LOW);
    digitalWrite (led3, LOW);

    //배열 복사
    for (int i = 0; i < 3; i++)
    {
      temp[i] = time[i];
    }

    //오름차순 정렬
    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 3 - (i + 1); j++)
        if (temp[j] >= temp[j + 1])
        {
          int m = temp[j + 1];
          temp[j + 1] = temp[j];
          temp[j] = m;
        }
    }

    //index 초기화
    for (int i = 0; i < 3; i++)
    {
      if (time[i] == temp[0]) index1 = i;
      if (time[i] == temp[1]) index2 = i;
    }
  }

  Serial.println(temp[0]);
  Serial.println(temp[1]);
  Serial.println(temp[2]);
  Serial.println(" ");

  EEPROM.write(0, time[0]);
  EEPROM.write(1, time[1]);
  EEPROM.write(2, time[2]);

  if (EEPROM.read(0) > 200)
  {
    for (int i = 0 ; i < EEPROM.length() ; i++) {
      EEPROM.write(i, 0);
    }
  }
}
