#include <EEPROM.h>

//전역변수 (핀번호)
int led1 = 3;
int led2 = 4;
int led3 = 5;
int led4 = 6;
int sw = 12;
int cds = A0;

//데이터 공간
int time[4] = {0, 1, 2, 3};
int temp[4];

//LED 지정
int index[4] = {0, 0, 0, 0};


//EEPROM에서 시간데이터 로드
void load(void)
{
  for (int i = 0; i < 4; i++)
  {
    time[i] = EEPROM.read(i * 2) + (EEPROM.read((i * 2) + 1) * 256);
  }
}

//EEPROM에 저장
void store(void)
{
  for (int i = 0; i < 8; i += 2)
  {
    EEPROM.write(i, time[i / 2] % 256);
  }
  for (int i = 1; i < 8; i += 2)
  {
    EEPROM.write(i, time[i / 2] / 256);
  }
}

//LED 출력
void output_LED(int step)
{
  for (int i = 0; i < step; i++)
  {
    digitalWrite(index[i] + 3, HIGH);
    time[index[i]] += 1;
  }

  for (int i = step; i < 4; i++)
  {
    digitalWrite(index[i] + 3, LOW);
  }
}

//인덱스 초기화
void select_LED(void)
{
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




void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(sw, INPUT_PULLUP);

  //  for (int i = 0; i < 8; i++)   //시작시 EEPROM 초기화
  //  {
  //    EEPROM.write(i, 0);
  //  }

  if (EEPROM.read(0))
  {
    load();
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
    if (cdsValue > 200 && cdsValue < 400)         output_LED(4);
    else if (cdsValue > 401 && cdsValue < 600)    output_LED(3);
    else if (cdsValue > 601 && cdsValue < 800)    output_LED(2);
    else if (cdsValue > 801 && cdsValue < 1500)   output_LED(1);
  }
  else                        //스위치 off
  {
    digitalWrite (led1, LOW);
    digitalWrite (led2, LOW);
    digitalWrite (led3, LOW);
    digitalWrite (led4, LOW);

    //LED 선택
    select_LED(); 
  }

  store();

  //EEPROM 초기화
  max = EEPROM.read(0) + (EEPROM.read(1) * 256);
  min = EEPROM.read(0) + (EEPROM.read(1) * 256);

  for (int i = 0; i < 4; i ++)
  {
    if ((EEPROM.read(i * 2) + (EEPROM.read((i * 2) + 1) * 256)) > max)
      max = EEPROM.read(i * 2) + (EEPROM.read((i * 2) + 1) * 256);
    if ((EEPROM.read(i * 2) + (EEPROM.read((i * 2) + 1) * 256)) < min)
      min =  EEPROM.read(i * 2) + (EEPROM.read((i * 2) + 1) * 256);
  }

  if (max > 300 && (max - min) < (max / 5) )
  {
    for (int i = 0 ; i < 4 ; i++) {
      EEPROM.write(i * 2, i);
    }
    for (int i = 1; i < 8; i += 2)
    {
      EEPROM.write(i, 0);
    }
    load();
  }
  else if (max == 60000)
  {
    for (int i = 0 ; i < 4 ; i++) {
      EEPROM.write(i * 2, i);
    }
    for (int i = 1; i < 8; i += 2)
    {
      EEPROM.write(i, 0);
    }
    load();
  }

  //  Serial.println(cdsValue);

  Serial.println(time[0]);
  Serial.println(time[1]);
  Serial.println(time[2]);
  Serial.println(time[3]);


  Serial.println(" ");
  Serial.println(max);
  Serial.println(min);
  Serial.println(" ");

  delay(50);
  //  Serial.println(" ");
}
