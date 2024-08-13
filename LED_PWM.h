volatile char *outf=0x31;
  
volatile char check = 1;
volatile char counts_for_Ton[] = {35,104,173,243,312};   // precentage of ton
volatile char counts_for_Toff[] = {312,243,173,104,35};  // precentage of toff
volatile long count,Ton_count,Toff_count;


void timer1_init(void);
void port_intialization();
void increasing(void);
void decresing(void);

void port_intialization(){
  volatile char *dirf=0x30;
  *dirf=0x01;
}
void timer1_init(void){
  volatile char *TCCR1_A = 0x80;  // FOR SELECTING MODE
  volatile char *TCCR1_B = 0X81;  // FOR ANY PRESCALER
  volatile short *TCNT1_L  = 0X84;  // FOR STORING COUNTING VALUE
  volatile short *OCR1A_L  = 0X88;  // COMPARED VALUE STORED HERE
  volatile char *TIMSK_1 = 0X6f;  // FOR ENABLING THE INTRRUPT
  // FOR CTC MODE AND PRESCALER=256
  *TCCR1_A  = 0X00;
  *TCCR1_B  = 0X0c;  // presacler 256
  *TCNT1_L  = 0x00;  // COUNTING VALUE STARTS FROM 0
  *OCR1A_L  = 3500;  // GIVING COMPARED VALUE
  *TIMSK_1  = 0X02;  // Output Compare A Match Interrupt Enable
}
void increasing(){
  volatile char index = 0;
  for(index=0;index<5;index++){
    *outf = 0x01;  // Turn on LED
    for (Ton_count = 0; Ton_count < counts_for_Ton[index]; Ton_count++);  // Simulate Ton
    *outf = 0x00;  // Turn off LED
    for (Toff_count = 0; Toff_count < counts_for_Toff[index]; Toff_count++);  // Simulate Toff
  } 
}
void decresing(){
  volatile char index = 4;
  for(index=4;index<=0;index--){
    *outf = 0x01;  // Turn on LED
    for (Ton_count = 0; Ton_count < counts_for_Ton[index]; Ton_count--);  // Simulate Ton
    *outf = 0x00;  // Turn off LED
    for (Toff_count = 0; Toff_count < counts_for_Toff[index]; Toff_count--);  // Simulate Toff
  }
}
ISR(TIMER1_COMPA_vect) {
  
  if(check == 1){
    check = check ^ 0x01;
    increasing();
  }
  else{
    check = check ^ 0x01;
    decresing();
  }
}

 
