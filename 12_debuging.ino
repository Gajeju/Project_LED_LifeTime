#include <EEPROM.h>

/*----- 전역변수 -----*/

#define LED_NUM 12

//2~13 핀 모두 LED로 사용
int cds = A0;

//데이터 공간
int time[LED_NUM] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int temp[LED_NUM];

//LED 지정
int index[LED_NUM] = {0,};

/*----- 함수 -----*/

//EEPROM에서 시간데이터 로드
void EEP_load(void)
{
  for (int i = 0; i < LED_NUM; i++)
  {
    time[i] = EEPROM.read(i * 2) + (EEPROM.read((i * 2) + 1) * 256);
  }
}

//EEPROM에 저장
void EEP_store(void)
{
  for (int i = 0; i < (LED_NUM * 2); i += 2)
  {
    EEPROM.write(i, time[i / 2] % 256);
  }
  for (int i = 1; i < (LED_NUM * 2); i += 2)
  {
    EEPROM.write(i, time[i / 2] / 256);
  }
}

//LED 출력
void LED_output(int step)
{
  for (int i = 0; i < step; i++)
  {
    digitalWrite(index[i] + 2, HIGH);
    time[index[i]] += 1;
  }

  for (int i = step; i < LED_NUM; i++)
  {
    digitalWrite(index[i] + 2, LOW);
  }
}

//인덱스 초기화
void LED_select(void)
{
  //배열 복사
  for (int i = 0; i < LED_NUM; i++)
  {
    temp[i] = time[i];
  }

  //오름차순 정렬
  for (int i = 0; i < LED_NUM; i++)
  {
    for (int j = 0; j < (LED_NUM - 1); j++ )
      if (temp[j] >= temp[j + 1])
      {
        int m = temp[j + 1];
        temp[j + 1] = temp[j];
        temp[j] = m;
      }
  }
  //index 초기화
  for (int i = 0; i < LED_NUM; i++)
  {
    for (int j = 0; j < LED_NUM; j++)
    {
      if (time[i] == temp[j]) index[j] = i;
    }
  }
}

//EEPROM 초기화
void EEP_reset(void)
{
  for (int i = 0 ; i < LED_NUM ; i++) {
    EEPROM.write(i * 2, i);
  }
  for (int i = 1; i < (LED_NUM * 2); i += 2)
  {
    EEPROM.write(i, 0);
  }
}

/*----- setup() loop() 시작 -----*/

void setup() {
  
  for (int i = 0; i < LED_NUM; i++)
  {
    pinMode(i + 2, OUTPUT);
  }

  //  for (int i = 0; i < 8; i++)   //시작시 EEPROM 초기화
  //  {
  //    EEPROM.write(i, 0);
  //  }

  if (EEPROM.read(0))
  {
    EEP_load();
  }

  //LED 선택
  LED_select();
  
  Serial.begin(9600);
}

void loop() {

  int cdsValue;
  int min, max;
  
  cdsValue = analogRead(cds);

  //cds 값에 따른 LED 개수 설정
  if      (cdsValue > 0 && cdsValue < 90)      LED_output(12);
  else if (cdsValue > 91 && cdsValue < 180)    LED_output(11);
  else if (cdsValue > 181 && cdsValue < 270)   LED_output(10);
  else if (cdsValue > 271 && cdsValue < 360)   LED_output(9);
  else if (cdsValue > 361 && cdsValue < 450)   LED_output(8);
  else if (cdsValue > 451 && cdsValue < 540)   LED_output(7);
  else if (cdsValue > 541 && cdsValue < 630)   LED_output(6);
  else if (cdsValue > 631 && cdsValue < 720)   LED_output(5);
  else if (cdsValue > 721 && cdsValue < 810)   LED_output(4);
  else if (cdsValue > 811 && cdsValue < 900)   LED_output(3);
  else if (cdsValue > 901 && cdsValue < 990)   LED_output(2);
  else if (cdsValue > 991 && cdsValue < 1024)  LED_output(1);

  EEP_store();

  //EEPROM 초기화
  max = EEPROM.read(0) + (EEPROM.read(1) * 256);
  min = EEPROM.read(0) + (EEPROM.read(1) * 256);

  for (int i = 0; i < LED_NUM; i ++)
  {
    if ((EEPROM.read(i * 2) + (EEPROM.read((i * 2) + 1) * 256)) > max)
      max = EEPROM.read(i * 2) + (EEPROM.read((i * 2) + 1) * 256);
    if ((EEPROM.read(i * 2) + (EEPROM.read((i * 2) + 1) * 256)) < min)
      min =  EEPROM.read(i * 2) + (EEPROM.read((i * 2) + 1) * 256);
  }

  if (max > 300 && (max - min) < (max / 5) )
  {
    EEP_reset();
    EEP_load();
  }
  else if (max == 60000)
  {
    EEP_reset();
    EEP_load();
  }

  //시리얼 통신을 이용하여 변수 체크

  //  Serial.println(cdsValue);

  for (int i = 0; i < LED_NUM; i++)
  {
    Serial.println(time[i]);
  }


  Serial.println(" ");
//  Serial.println(max);
//  Serial.println(min);
//  Serial.println(" ");

  delay(10);  //Lamp 동작 주기 설정
}
