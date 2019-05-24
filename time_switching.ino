int led1 = 3;
int led2 = 4;
int led3 = 5;

int time[3] = {0,0,0};

int index1 = 3;
int index2 = 4;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  
  digitalWrite (index1, HIGH);
  time[index1 - 3] += 1;
  digitalWrite (index2, HIGH);
  time[index2 - 2] += 1;
  delay(1000);
  
  if (time[index1 - 3] == 3)
  {
      digitalWrite (index1, LOW);
      digitalWrite (index2, LOW);
      index1++;
      index2++;
      if (index1 == 6) index1 = 3;
      if (index2 == 6) index2 = 3;
      time[index1 - 3] = 0;
  }

//  if (time[0] == time[1] && time[1] == time[2])
//  {
//    time[0] == 0;
//    time[1] == 0;
//    time[2] == 0;
//  }
}

