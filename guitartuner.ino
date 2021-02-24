
#define SEG_C 11
#define SEG_E 9
#define SEG_D 10
#define SEG_B 8
#define SEG_G 5
#define SEG_A 7
#define SEG_F 6
#define SEG_DP 12

#define LED_low 4
#define LED_high 13
#define LED_ok 3

//frequency and notes arrays
const float freq_lib[] = {65.4, 69.3, 73.4, 77.8, 82.4, 87.3, 92.5, 98.0, 103.8,
                          110.0, 116.5, 123.5, 130.8, 138.6, 146.8, 155.6, 164.8,
                          174.6, 185.0, 196.0, 207.7, 220.0, 233.1, 246.9, 261.6,
                          277.2, 293.7, 311.1, 329.6, 349.2, 370.0, 392.0};
const char note_lib[] = {'c', 'C', 'd', 'D', 'e', 'f', 'F', 'g', 'G', 'a', 'A',
                         'b', 'c', 'C', 'd', 'D', 'e', 'f', 'F', 'g', 'G', 'a',
                         'A', 'b', 'c', 'C', 'd', 'D', 'e', 'f', 'F', 'g'};

int sample_counter;
int length = 200;
float freq;
unsigned long time1, time2, end_time, sseg_time;
float data[200]; //length

char letter;
int test_time = 100;
int led_off_time = 3000;



void setup()
{  
  pinMode(2,INPUT_PULLUP);
  attachInterrupt(0, frequency, FALLING);
  
  ssegInit(test_time); //check each diode of display

}

void loop(){
  
 //turn off display
  sseg_time = millis();
  if(sseg_time-end_time > led_off_time)
  {
    sseg('o');
    LED('o');
  } 


}

void frequency()
{
  time1 = micros();
  freq = 1000000.0/(time1-time2);
  
  if (sample_counter < length) {
    sample_counter++;
    data[sample_counter] = freq;
  }
  else{
    freq = getPopularElement(data); //choose most frequent data
    sample_counter = 0;

  }
  
  findfreq(freq);

    
  time2 = time1;
  end_time = millis();
  

}

float getPopularElement(float a[])
{
  int count = 1; 
  int tempCount;
  float popular = a[0];
  float temp;
  for (int i = 0; i < (length - 1); i++)
  {
    temp = a[i];
    tempCount = 0;
    for (int j = 1; j < length; j++)
    {
      if (temp == a[j])
        tempCount++;
    }
    if (tempCount > count)
    {
      popular = temp;
      count = tempCount;
    }
  }
  
  if(popular > 60) return popular;
}

void findfreq(float freq)
{
  float er = 0.8; //frequency error
  
  // find the closest frequency
  
  for(int i=0; i< 31; i++)
  {
    if(freq <= freq_lib[i])
    {
      if(abs(freq-freq_lib[i]) < abs(freq-freq_lib[i-1]))
      {
        sseg(note_lib[i]);
        
        if(abs(freq-freq_lib[i]) < er) LED('k');
 
        else if(freq >= (freq_lib[i] + er)) LED('h');
        
        else if(freq <= (freq_lib[i] - er)) LED('l');
      }
      
      else if(abs(freq-freq_lib[i]) >= abs(freq-freq_lib[i-1]))
      {
        sseg(note_lib[i-1]);
        
        if(abs(freq-freq_lib[i-1]) < er) LED('k');
 
        else if(freq >= (freq_lib[i-1] + er)) LED('h');
        
        else if(freq <= (freq_lib[i-1] - er)) LED('l');
        
      }
      break;
    }
  }
 
  
}

//display functions below


void ssegInit(int time){
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);
  pinMode(SEG_DP, OUTPUT);
  
  pinMode(LED_low, OUTPUT);
  pinMode(LED_high, OUTPUT);
  pinMode(LED_ok, OUTPUT);
 
  delay(time);
  digitalWrite(SEG_G,HIGH);
  delay(time);
  digitalWrite(SEG_F,HIGH);
  delay(time);
  digitalWrite(SEG_A,HIGH);
  delay(time);
  digitalWrite(SEG_B,HIGH);
  delay(time);
  digitalWrite(SEG_C,HIGH);
  delay(time);
  digitalWrite(SEG_D,HIGH);
  delay(time);
  digitalWrite(SEG_E,HIGH);
  delay(time);
  digitalWrite(SEG_DP,HIGH);
  
}

void LED(char letter){
    
    switch (letter) {
    case 'h':
        digitalWrite(LED_low,LOW);
        digitalWrite(LED_ok,LOW);
        digitalWrite(LED_high,HIGH);
    break;
    
    case 'k':
        digitalWrite(LED_low,LOW);
        digitalWrite(LED_high,LOW);
        digitalWrite(LED_ok,HIGH);
    break;
    
    case 'l':
        digitalWrite(LED_high,LOW);
        digitalWrite(LED_ok,LOW);
        digitalWrite(LED_low,HIGH);
    break;
    
    case 'o':
        digitalWrite(LED_low, LOW);
        digitalWrite(LED_high, LOW);
        digitalWrite(LED_ok, LOW);
    break;
    }
    
}

void sseg(char letter){
    
    switch (letter) {
    case 'a':
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, LOW);
        digitalWrite(SEG_C, LOW);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, LOW);
        digitalWrite(SEG_DP,HIGH);
    break;
    
    case 'A':
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, LOW);
        digitalWrite(SEG_C, LOW);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, LOW);
        digitalWrite(SEG_DP,LOW);
    break; 
    
    case 'b':
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, LOW);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, LOW);
        digitalWrite(SEG_DP,HIGH);
    break; 
    
    case 'c':
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, HIGH);
        digitalWrite(SEG_DP,HIGH);
    break;
    
    case 'C':
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, HIGH);
        digitalWrite(SEG_DP,LOW);
    break; 
    
    case 'd':
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, LOW);
        digitalWrite(SEG_C, LOW);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, HIGH);
        digitalWrite(SEG_G, LOW);
        digitalWrite(SEG_DP,HIGH);
    break;
    
    case 'D':
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, LOW);
        digitalWrite(SEG_C, LOW);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, HIGH);
        digitalWrite(SEG_G, LOW);
        digitalWrite(SEG_DP,LOW);
    break; 
    
    case 'e':
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, LOW);
        digitalWrite(SEG_DP,HIGH);
    break; 
    
    case 'f':
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, LOW);
        digitalWrite(SEG_DP,HIGH);
    break;
    
    case 'F':
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, LOW);
        digitalWrite(SEG_DP,LOW);
    break; 
    
    case 'g':
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, LOW);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, LOW);
        digitalWrite(SEG_DP,HIGH);
    break;
    
    case 'G':
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, LOW);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, LOW);
        digitalWrite(SEG_DP,LOW);
    break;
    
    case 'o':
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, HIGH);
        digitalWrite(SEG_F, HIGH);
        digitalWrite(SEG_G, HIGH);
        digitalWrite(SEG_DP,HIGH);
    break;
  }
}
  
  
