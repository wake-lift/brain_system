#include "Arduino.h"
#include "QuartetMode.h"
#include "TimerOne.h"

QuartetMode::QuartetMode(){
setPushes = 0;                                                    // число нажатий кнопки "СТАРТ"
}
                                                                  // отработка нажатий кнопки "SET" при неправильных ответах игроков
void QuartetMode::Set(){
	if (setPushes == 0) {
  Serial.println("SET_0");                                        // вывод для отладки через COM-порт
   digitalWrite(GetPin(), LOW);
   for (int i = 0; i < ARRAY_SIZE(ARRAY_USER_BUTTON); i++){       // отключает пин кнопки игрока, давшего неверный ответ
      if (GetPin() == ARRAY_LED[i]){
      pinMode(ARRAY_USER_BUTTON[i], OUTPUT);
      }    
    }
	}
  else if (setPushes == 1) {
    Serial.println("SET_1");                                      //вывод для отладки через COM-порт
    digitalWrite(GetPin(), LOW);
   for (int i = 0; i < ARRAY_SIZE(ARRAY_USER_BUTTON); i++){       // отключает пин кнопки игрока, давшего неверный ответ
      if (GetPin() == ARRAY_LED[i]){
      pinMode(ARRAY_USER_BUTTON[i], OUTPUT);
      }    
    }
  }
  else if (setPushes == 2) {
   Serial.println("SET_2");                                        //вывод для отладки через COM-порт
    digitalWrite(GetPin(), LOW);
    for (int i = 0; i < ARRAY_SIZE(ARRAY_USER_BUTTON); i++){       // отключает пин кнопки игрока, давшего неверный ответ
      if (GetPin() == ARRAY_LED[i]){
      pinMode(ARRAY_USER_BUTTON[i], OUTPUT);
      }
    }   
  }
  else if (setPushes == 3) {
    Serial.println("SET_3");                                        //вывод для отладки через COM-порт
    digitalWrite(GetPin(), LOW);
    for (int i = 0; i < ARRAY_SIZE(ARRAY_USER_BUTTON); i++){       // отключает пин кнопки игрока, давшего неверный ответ
      if (GetPin() == ARRAY_LED[i]){
      pinMode(ARRAY_USER_BUTTON[i], OUTPUT);
      }
    }   
  }
  setPushes++;    
}

void QuartetMode::Reset(){
    tone(SOUND_PIN, FREQUENCY_RESET, TIME_RESET);
	  setPushes = 0;                                                    // обнуляет счетчик нажатий кнопки "СТАРТ"
    Serial.println("RES");                                            // вывод для отладки через COM-порт
    for (int i = 0; i < ARRAY_SIZE(ARRAY_USER_BUTTON); i++) {         // вновь назначает пины кнопок игроков
    pinMode(ARRAY_USER_BUTTON[i], INPUT);
  }
  for (int i = 0; i < ARRAY_SIZE(ARRAY_LED); i++){                    // гасит все светодиоды
    digitalWrite(ARRAY_LED[i], LOW);
  }
}
void QuartetMode::SetTimer(){
	
}

void QuartetMode::FalseStart(){	

}

QuartetMode::~QuartetMode(){

}

bool QuartetMode::UserButtonPushed(int pin){
 digitalWrite(pin, HIGH);
 pinMode(ADMIN_BUTTON_SET, INPUT);                                 // включает пин кнопки ведущего "SET"
 Serial.println("BUT");                                               // вывод для отладки через COM-порт
 this->SetPin(pin);
    tone(SOUND_PIN, FREQUENCY_USER, TIME);
    return true;    
}
