#include "Arduino.h"
#include "WwwMode.h"
#include "TimerOne.h"


void WwwMode::Set(){
  Serial.println("SET");                                     // вывод для отладки через COM-порт
	tone(SOUND_PIN, FREQUENCY, TIME);
	timer = WWW_TIMER;


}

void WwwMode::Reset(){
  Serial.println("RES");                                      // вывод для отладки через COM-порт
  tone(SOUND_PIN, FREQUENCY_RESET, TIME_RESET);
	digitalWrite(GetPin(), LOW);

}
void WwwMode::SetTimer(){                                     // звуковые сигналы за 10 секунд до конца и в конце
	timer--;
	if (timer == 0) {
		tone(SOUND_PIN, FREQUENCY_WWW_END, TIME_WWW_END);
	}
	if (timer == 9){
		tone(SOUND_PIN, FREQUENCY, TIME);
	}

}

bool WwwMode::UserButtonPushed(int pin){
	if (timer >= 59){                                         // право на досрочный ответ (в течение 1 секунды от начала отсчета)
		digitalWrite(pin, HIGH);
    Serial.println("BUT");                                  //вывод для отладки через COM-порт
		tone(SOUND_PIN, FREQUENCY_USER, TIME);		
		Timer1.stop();
		this->SetPin(pin);		
	}	
	return true;
}

void WwwMode::FalseStart(){

}

WwwMode::WwwMode(){

}

WwwMode::~WwwMode(){

}
