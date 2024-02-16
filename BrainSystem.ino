#include "Constants.h"
#include "BrainRingMode.h"
#include "GameMode.h"
#include "TimerOne.h"
#include "WwwMode.h"
#include "QuartetMode.h"
bool isPushed = false;                                                                   // переменная, отвечающая за блокировку кнопок остальных игроков после нажатия одного из игроков
GameMode *gameMode;


void setup() { 
  Serial.begin(9600);                                                                    // инициализация COM-порта (для режима отладки)
  for (int i = 0; i < ARRAY_SIZE(ARRAY_USER_BUTTON); i++) {                              // назначение пинов кнопок игроков
    pinMode(ARRAY_USER_BUTTON[i], INPUT);                   
    pciSetup(ARRAY_USER_BUTTON[i]);
  }
  for (int i = 0; i < ARRAY_SIZE(ARRAY_LED); i++) {                                      // назначение пинов светодиодов игроков
    pinMode(ARRAY_LED[i], OUTPUT);
  }

  pinMode(ADMIN_BUTTON_RESET, INPUT);                                                     // назначение пина кнопки ведущего "СБРОС"
  pinMode(ADMIN_BUTTON_SET, INPUT);                                                       // назначение пина кнопки ведущего "СТАРТ"
  pinMode(BRAIN_RING_MODE, INPUT);                                                        // назначение пина выбора режима игры (брейн-ринг)
  pinMode(QUARTET_MODE, INPUT);                                                           // назначение пина выбора режима игры (квартет)
  pinMode(SOUND_PIN, OUTPUT);                                                             // назначение пина буззера
  pinMode(LED_START_SIGNAL, OUTPUT);                                                      // назначение пина светодиода ведущего (белый)
  pciSetup(ADMIN_BUTTON_RESET);
  pciSetup(ADMIN_BUTTON_SET);

                                                                                          
  if (digitalRead(BRAIN_RING_MODE) == HIGH && digitalRead(QUARTET_MODE) == LOW) {         // определение режима игры (три позиции тумблера ON-OFF-ON)
    gameMode = new BrainRingMode();
  }
  else if (digitalRead(QUARTET_MODE) == HIGH && digitalRead(BRAIN_RING_MODE) == LOW) {
    gameMode = new QuartetMode();   
  }
  else {                                                                                  // тумблер в среднем положении
    gameMode = new WwwMode();  
  }
  Timer1.initialize(1000000);
  Timer1.stop();

}



void pciSetup(byte pin) {
  *digitalPinToPCMSK(pin) |= bit(digitalPinToPCMSKbit(pin));                              // enable pin 
  PCIFR |= bit(digitalPinToPCICRbit(pin));                                                // clear any outstanding interrupt 
  PCICR |= bit(digitalPinToPCICRbit(pin));                                                // enable interrupt for the group 
}

                                                                                      
ISR(PCINT0_vect) {                                                                        // назначение прерываний на кнопки ведущего
  noInterrupts();
  isPushed = false;
  if (digitalRead(ADMIN_BUTTON_SET) == HIGH ) {
    pinMode(ADMIN_BUTTON_SET, OUTPUT);                                                    // отключает пин кнопки ведущего "SET" для исключения ложных повторных нажатий
    gameMode->Set();
    Timer1.attachInterrupt(TimerInterrupt);
    gameMode->SetFalseStart(false);
  }
  if (digitalRead(ADMIN_BUTTON_RESET) == HIGH) {
    pinMode(ADMIN_BUTTON_SET, INPUT);                                                     // включает пин кнопки ведущего "SET"
    Timer1.stop();
    gameMode->Reset();
    gameMode->SetFalseStart(true);
  }
  interrupts();
}

                                                                                          
ISR(PCINT2_vect){                                                                         // назначение прерываний на кнопки игроков
  noInterrupts(); 
  if (isPushed == false){
    for (int i = 0; i < ARRAY_SIZE(ARRAY_USER_BUTTON); i++){
      if (digitalRead(ARRAY_USER_BUTTON[i]) == HIGH){
        isPushed = gameMode->UserButtonPushed(ARRAY_LED[i]);
      }
    }   
  } 
  interrupts();
}

void TimerInterrupt() {
  gameMode->SetTimer();
}
