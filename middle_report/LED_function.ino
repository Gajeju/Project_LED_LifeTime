//LED 출력
void LED_output(int step)
{
  for (int i = 0; i < step; i++)
  {
    digitalWrite(index[i] + 2, HIGH);
    time[index[i]] += 1;
  }

  for (int i = step; i < 12; i++)
  {
    digitalWrite(index[i] + 2, LOW);
  }
}

//인덱스 초기화
void LED_select(void)
{
  //배열 복사
  for (int i = 0; i < 12; i++)
  {
    temp[i] = time[i];
  }

  //오름차순 정렬
  for (int i = 0; i < 12; i++)
  {
    for (int j = 0; j < 11; j++ )
      if (temp[j] >= temp[j + 1])
      {
        int m = temp[j + 1];
        temp[j + 1] = temp[j];
        temp[j] = m;
      }
  }
  //index 초기화
  for (int i = 0; i < 12; i++)
  {
    for (int j = 0; j < 12; j++)
    {
      if (time[i] == temp[j]) index[j] = i;
    }
  }
}
