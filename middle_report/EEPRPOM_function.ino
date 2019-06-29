//EEPROM에서 시간데이터 로드
void EEP_load(void)
{
  for (int i = 0; i < 12; i++)
  {
    time[i] = EEPROM.read(i * 2) + (EEPROM.read((i * 2) + 1) * 256);
  }
}

//EEPROM에 저장
void EEP_store(void)
{
  for (int i = 0; i < 24; i += 2)
  {
    EEPROM.write(i, time[i / 2] % 256);
  }
  for (int i = 1; i < 24; i += 2)
  {
    EEPROM.write(i, time[i / 2] / 256);
  }
}

//EEPROM 초기화
void EEP_reset(void)
{
  for (int i = 0 ; i < 12 ; i++) {
    EEPROM.write(i * 2, i);
  }
  for (int i = 1; i < 24; i += 2)
  {
    EEPROM.write(i, 0);
  }
}
