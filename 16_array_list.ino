#include <stdio.h>
#include <stdlib.h>
#include <EEPROM.h>

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

void LBubble(List* plist)
{

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

//데이터 정렬
void alignTimeData(Data* plifeFront,Data* plifeBack)
{
  Data* comp;
  
  if(plifeFront->timeData > plifeBack->timeData)
  {
    comp = plifeFront;
    plifeFront = plifeBack;
    plifeFront = comp;
  }
}

/*---------------------------------------------------------*/
void setup()
    {
  
}

void loop()
{
  
}
