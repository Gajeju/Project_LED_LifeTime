#include <stdio.h>
#include <stdlib.h>
#include <EEPROM.h>
#include <Wire.h>
#include <BH1750.h>

#define TRUE  1
#define FALSE 0
#define LED_NUM 12

//데어터 저장공간
typedef struct _Lifetime
{
  int index;
  short timeData;
} Data;

typedef Data* LData;

/*---------------------------------------------------------*/

//리스트 구현

typedef struct __ArrayList
{
  LData arr[LED_NUM];
  int numOfData;
  int curPosition;
} ArrayList;

typedef ArrayList List;

void ListInit(List* plist)
{
  (plist->numOfData) = 0;
  (plist->curPosition) = -1;
}

void LInsert(List* plist, LData data)
{
  if (plist->numOfData >= LED_NUM)
  {
    return;
  }
  plist->arr[plist->numOfData] = data;
  (plist->numOfData)++;
}

int LFirst(List* plist, LData* pdata)
{
  if (plist->numOfData == 0)
    return FALSE;

  (plist->curPosition) = 0;
  *pdata = plist->arr[0];
  return TRUE;
}

int LNext(List* plist, LData* pdata)
{
  if (plist->curPosition >= (plist->numOfData) - 1)
    return FALSE;

  (plist->curPosition)++;
  *pdata = plist->arr[plist->curPosition];
  return TRUE;
}

//데이터 정렬
void LBubble(List* plist)
{
  Data* comp;

  for (int i = 0; i < LED_NUM; i++)
  {
    for (int j = 0; j < LED_NUM - 1; j++)
    {
      if (plist->arr[i]->timeData < plist->arr[j]->timeData)
      {
        comp = plist->arr[i];
        plist->arr[i] = plist->arr[j];
        plist->arr[j] = comp;
      }
    }
  }
}

/*---------------------------------------------------------*/
//구조체 접근 함수

//데이터 초가화
void SetTimeData(Data* plife, int rindex, short rtimeData)
{
  plife->index = rindex;
  plife->timeData = rtimeData;
}

//데이터 증가
void countTimeData(Data* plife)
{
  plife->timeData++;
}

//LED 출력
void outTimeData(List* plist, int ledStep)
{
  for (int i = 0; i < ledStep; i++)
  {
    digitalWrite(plist->arr[i]->index, HIGH);
    countTimeData(plist->arr[i]);
  }

  for (int i = ledStep; i < LED_NUM; i++)
  {
    digitalWrite(plist->arr[i]->index, LOW);
  }
}
/*---------------------------------------------------------*/
//EEPROM

typedef struct For_divide_struct
{
  byte front;
  byte back;
} SBox;

typedef union For_divide_union
{
  short timedata;
  SBox box;
} BBox;

void EEP_load(List* plist)
{
  BBox load;
  
  for (int i = 0; i < LED_NUM; i++)
  {
    load.box.front = EEPROM.read(i * 2);
    load.box.back = EEPROM.read((i * 2) + 1);
    plist->arr[i]->timeData = load.timedata;
  }
}


void EEP_store(List* plist)
{
  BBox save;
  
  for (int i = 0; i < LED_NUM; i++)
  {
    save.timedata = plist->arr[i]->timeData;

    EEPROM.write((i * 2), save.box.front);
    EEPROM.write(((i * 2) + 1), save.box.back);
  }
}

void EEP_reset(List* plist)
{
  int min, max;
  BBox save;

  save.box.front = EEPROM.read(0);
  save.box.back  = EEPROM.read(1);

  max = save.timedata;
  min = save.timedata;

  for (int i = 0; i < LED_NUM; i ++)
  {
    save.box.front = EEPROM.read(i * 2);
    save.box.back  = EEPROM.read((i * 2) + 1);

    if (save.timedata > max)
      max = save.timedata;
    if (save.timedata < min)
      min =  save.timedata;
  }

  if (max > 300 && (max - min) < (max / 5) )
  {
    EEP_delete();
    EEP_load(plist);
  }
  else if (max == 60000)
  {
    EEP_delete();
    EEP_load(plist);
  }
}

////EEPROM 초기화
void EEP_delete(void)
{
  for (int i = 0 ; i < LED_NUM ; i++) {
    EEPROM.write(i * 2, i);
  }
  for (int i = 1; i < (LED_NUM * 2); i += 2)
  {
    EEPROM.write(i, 0);
  }
}

/*---------------------------------------------------------*/
List list;
Data* plife;
BH1750 lightMeter;

void setup()
{
  for (int i = 0; i < LED_NUM; i++)
  {
    pinMode(i + 2, OUTPUT);
  }

  ListInit(&list);

  for (int i = 0; i < LED_NUM; i++)
  {
    plife = (Data*)malloc(sizeof(Data));
    SetTimeData(plife, i + 2, i);
    LInsert(&list, plife);
  }
    
  if (EEPROM.read(0))
  {
    EEP_load(&list);
  }

  LBubble(&list);

  Wire.begin();
  lightMeter.begin(0x23);

  pinMode(A0, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  int sw = digitalRead(A0);
  //uint16_t cdsValue = lightMeter.readLightLevel();
  uint16_t cdsValue  = 2500;

  if      (cdsValue >= 0 && cdsValue < 300)      outTimeData(&list, 12);
  else if (cdsValue >= 300 && cdsValue < 600 )    outTimeData(&list, 11);
  else if (cdsValue >= 600 && cdsValue < 900)   outTimeData(&list, 10);
  else if (cdsValue >= 900 && cdsValue < 1200)   outTimeData(&list, 9);
  else if (cdsValue >= 1200 && cdsValue < 1500)   outTimeData(&list, 8);
  else if (cdsValue >= 1500 && cdsValue < 1800)   outTimeData(&list, 7);
  else if (cdsValue >= 1800 && cdsValue < 2100)   outTimeData(&list, 6);
  else if (cdsValue >= 2100 && cdsValue < 2400)   outTimeData(&list, 5);
  else if (cdsValue >= 2400 && cdsValue < 2700)   outTimeData(&list, 4);
  else if (cdsValue >= 2700 && cdsValue < 3000)   outTimeData(&list, 3);
  else if (cdsValue >= 3000 && cdsValue < 3300)   outTimeData(&list, 2);
  else outTimeData(&list, 1);

  EEP_store(&list);
  EEP_reset(&list);

  if (sw == 0)
  {
    EEP_delete();
    EEP_load(&list);
  }
  /*---------------------------------------------------------*/

  //Serial.println(cdsValue);

    if (LFirst(&list, &plife))
    {
      Serial.println(plife->index);
      Serial.println(plife->timeData);
      Serial.println("");
  
      while (LNext(&list, &plife))
      {
        Serial.println(plife->index);
        Serial.println(plife->timeData);
        Serial.println("");
      }
    }

//  for (int i = 0; i < LED_NUM; i++)
//  {
//    Serial.println(EEPROM.read(i * 2));
//    Serial.println(EEPROM.read((i * 2)+1));
//  }

  Serial.println("");
  delay(500);
}
