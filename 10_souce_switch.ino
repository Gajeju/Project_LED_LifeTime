#include <EEPROM.h>

/*----- 전역변수 -----*/

//핀번호
int led1 = 3;
int led2 = 4;
int led3 = 5;
int led4 = 6;
int cds = A0;

//데이터 공간
int time[4] = {0, 1, 2, 3};
int temp[4];

//LED 지정
int index[4] = {0, 0, 0, 0};


/*----- 함수 -----*/

//EEPROM에서 시간데이터 로드
void EEP_load(void)
{
  for (int i = 0; i < 4; i++)
  {
    time[i] = EEPROM.read(i * 2) + (EEPROM.read((i * 2) + 1) * 256);
  }
}

//EEPROM에 저장
void EEP_store(void)
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
void LED_output(int step)
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
void LED_select(void)
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
    for (int j = 0; j < 4; j++)
    {
      if (time[i] == temp[j]) index[j] = i;
    }
  }
}

//EEPROM 초기화
void EEP_reset(void)
{
  for (int i = 0 ; i < 4 ; i++) {
    EEPROM.write(i * 2, i);
  }
  for (int i = 1; i < 8; i += 2)
  {
    EEPROM.write(i, 0);
  }
}

/*----- setup() loop() 시작 -----*/

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  //  for (int i = 0; i < 8; i++)   //시작시 EEPROM 초기화
  //  {
  //    EEPROM.write(i, 0);
  //  }

  if (EEPROM.read(0)) EEP_load();
  
  //LED 선택
  LED_select();
  
  
  Serial.begin(9600);
}

void loop() {

  int cdsValue;
  int min, max;

  cdsValue = analogRead(cds);

  //cds 값에 따른 LED 개수 설정
  if      (cdsValue > 200 && cdsValue < 400)    LED_output(4);
  else if (cdsValue > 401 && cdsValue < 600)    LED_output(3);
  else if (cdsValue > 601 && cdsValue < 800)    LED_output(2);
  else if (cdsValue > 801 && cdsValue < 1500)   LED_output(1);

  EEP_store();

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

//  Serial.println(time[0]);
//  Serial.println(time[1]);
//  Serial.println(time[2]);
//  Serial.println(time[3]);
//
//
//  Serial.println(" ");
//  Serial.println(max);
//  Serial.println(min);
//  Serial.println(" ");

  Serial.println(cdsValue);

  delay(50);  //Lamp 동작 주기 설정
}
