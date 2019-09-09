#define Point * LData
#define LED_NUM
#define TRUE 1
#define FALSE 0

typedef struct _point
{
  int timeData;
  int index;
} Point;

typedef struct _ArrayList
{
  LData arr[LED_NUM];
  int numOfData;
  int curPositon;
} ArrayList;

typedef ArrayList List;

void ListInit(List* plist)
{
  (plist->numOfData) = 0;
  (plist->curPositon) = -1;
}

void LInsert(List* plist, LData data)
{
  plist->arr[plist->numOfData] = data;
  (plist->numOfData)++;
}

int LFirst(List* plist, LData* pdata)
{
  if (plist->numOfData == 0)
    return FALSE;

  (plist->curPositon) = 0;
  *pdata = plist->arr[0];
  return TRUE;
}

int LNext(List* plist, LData* pdata)
{
  if (plist->curPositon >= (plist->numOfData) - 1)
    return FALSE;

  (plist->curPositon)++;
  *pdata = plist->arr[plist->curPositon];
  return TRUE;
}

LData LRemove(List* plist)
{
  int rpos = plist->curPositon;
  int num = plist->numOfData;
  LData rdata = plist->arr[rpos];

  for (int i = rpos; i < num - 1; i++)
    plist->arr[i] = plist->arr[i + 1];

  (plist->numOfData)--;
  (plist->curPositon)--;
  return rdata;
}

//Timedata++
void PAddTime(List* plist, int index)
{
  
}

//정렬함수


void setup() {
//핀모드
  for (int i = 0; i < LED_NUM; i++) 
  {
    pinMode(i+2, OUTPUT);
  }

//리스트 초기화(EEPROM)

//정렬

}

void loop() {
//조도센서

//LED 출력(조도센서 개수에 따라)

}
