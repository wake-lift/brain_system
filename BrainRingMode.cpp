#include "BrainRingMode.h"
#include "Arduino.h"
#include "TimerOne.h"
                                                                      // отработка мигания светодиодом при фальшстарте:
int falsestart_player_button = -1;                                    // объявление переменной, определяющее мигание при фальшстарте светодиода конкретного игрока
int ledState = LOW;                                                   // переменная, устанавливающая состояние мигающего при фальшстарте светодиода
long previousMillis = 0;                                              // храним время последнего переключения светодиода
long interval = 300;                                                  // интервал между включение/выключением светодиода (1 секунда)


BrainRingMode::BrainRingMode() {
	 setPushes = 0;                                                     // счетчик нажатий кнопки "СТАРТ"
}

BrainRingMode::~BrainRingMode() {	
	
}

                                                                       //отработка нажатий кнопки "SET" при неправильных ответах игроков или фальшстартах
void BrainRingMode::Set() {                   
	if (setPushes == 0) {
  Serial.println("SET_0");                                             //вывод для отладки через COM-порт
		tone(SOUND_PIN, FREQUENCY, TIME);
    digitalWrite(LED_START_SIGNAL, HIGH);
		timer = BRAIN_TIMER;
		for (int i = 0; i < ARRAY_SIZE(ARRAY_LED); i++){                   // гасит все светодиоды игроков (на случай если было несколько фальшстартов)
    digitalWrite(ARRAY_LED[i], LOW);
		}
   }
	
	
	else if (setPushes == 1) {
    Serial.println("SET_1");                                           //вывод для отладки через COM-порт
		tone(SOUND_PIN, FREQUENCY, TIME);
    digitalWrite(LED_START_SIGNAL, HIGH);
		digitalWrite(GetPin(), LOW);
		timer = timer_left;
    for (int i = 0; i < ARRAY_SIZE(ARRAY_LED); i++){                   // гасит все светодиоды игроков (на случай если было несколько фальшстартов)
    digitalWrite(ARRAY_LED[i], LOW);
   }
 
	}
  else if (setPushes == 2) {
    Serial.println("SET_2");                                           //вывод для отладки через COM-порт
    tone(SOUND_PIN, FREQUENCY, TIME);
    digitalWrite(LED_START_SIGNAL, HIGH);
    digitalWrite(GetPin(), LOW);
    timer = timer_left;
    for (int i = 0; i < ARRAY_SIZE(ARRAY_LED); i++){                    // гасит все светодиоды игроков (на случай если было несколько фальшстартов)
    digitalWrite(ARRAY_LED[i], LOW);
    }
   
  }
  else if (setPushes == 3) {
    Serial.println("SET_3");                                            //вывод для отладки через COM-порт
    tone(SOUND_PIN, FREQUENCY, TIME);
    digitalWrite(LED_START_SIGNAL, HIGH);
    digitalWrite(GetPin(), LOW);
    timer = timer_left;
    for (int i = 0; i < ARRAY_SIZE(ARRAY_LED); i++){                    // гасит все светодиоды игроков (на случай если было несколько фальшстартов)
    digitalWrite(ARRAY_LED[i], LOW);
    }
    
  }
	setPushes++;
}

void BrainRingMode::SetTimer() {
	timer--;
  if (timer == 5) {                                                     // звуковые сигналы за 5 секунд до истечения времени
    tone(SOUND_PIN, FREQUENCY, TIME_BRAIN_ENDING_SOON);
  }
  if (timer == 4) {
    tone(SOUND_PIN, FREQUENCY, TIME_BRAIN_ENDING_SOON);
  }
  if (timer == 3) {
    tone(SOUND_PIN, FREQUENCY, TIME_BRAIN_ENDING_SOON);
  }
  if (timer == 2) {
    tone(SOUND_PIN, FREQUENCY, TIME_BRAIN_ENDING_SOON);
  }
  if (timer == 1) {
    tone(SOUND_PIN, FREQUENCY, TIME_BRAIN_ENDING_SOON);
  }
	if (timer == 0) {                                                     //звуковой сигнал окончания времени на ответ
    pinMode(ADMIN_BUTTON_SET, OUTPUT);                                  // отключает пин кнопки ведущего "SET", чтобы не стартовать сразу
     for (int i = 0; i < ARRAY_SIZE(ARRAY_USER_BUTTON); i++){           // отключает пины кнопок игроков, чтобы не реагировало на нажатия
      pinMode(ARRAY_USER_BUTTON[i], OUTPUT);  
    }
		tone(SOUND_PIN, FREQUENCY_BRAIN_END, TIME);
    digitalWrite(LED_START_SIGNAL, LOW);
		this->SetFalseStart(true);

	}
}

void BrainRingMode::Reset(){
  Serial.println("RES");                                                  // вывод для отладки через COM-порт
  //tone(SOUND_PIN, FREQUENCY_RESET, TIME_RESET);                         // короткий звук нажатия кнопки "RESET"
  if (falsestart_pushed == false && button_pushed == false) {             // вариант, когда нужен сброс для новой игры
   for (int i = 0; i < ARRAY_SIZE(ARRAY_USER_BUTTON); i++) {              // вновь назначает пины кнопок игроков
    pinMode(ARRAY_USER_BUTTON[i], INPUT); 
  }
  digitalWrite(LED_START_SIGNAL, LOW);
  pinMode(ADMIN_BUTTON_SET, INPUT);                                       // включает пин кнопки ведущего "SET"
	setPushes = 0;
	for (int i = 0; i < ARRAY_SIZE(ARRAY_LED); i++){                        // гасит все светодиоды
		digitalWrite(ARRAY_LED[i], LOW);
	}
}
else if (falsestart_pushed == true && button_pushed == false) {           // вариант, когда нужен сброс при фальшстарте
  falsestart_pushed = false;                                              // опускается флажок фальшстарта
  pinMode(ADMIN_BUTTON_SET, INPUT);                                       // включает пин кнопки ведущего "SET" (сброс фальшстарта)
  digitalWrite(LED_START_SIGNAL, LOW);                                    // гасит светодиод ведущего
  for (int i = 0; i < ARRAY_SIZE(ARRAY_LED); i++){                        // гасит все светодиоды
    digitalWrite(ARRAY_LED[i], LOW);
  }
}
else if (falsestart_pushed == false && button_pushed == true){            // вариант, когда нужен сброс при неправильном ответе игрока
  button_pushed = false;                                                  // опускается флажок нажатой кнопки
  pinMode(ADMIN_BUTTON_SET, INPUT);                                       // включает пин кнопки ведущего "SET" (сброс нажатия кнопки игрока)
  for (int i = 0; i < ARRAY_SIZE(ARRAY_LED); i++){                        // гасит все светодиоды
    digitalWrite(ARRAY_LED[i], LOW);
  }
}
falsestart_player_button = -1;                                            // останавливает мигание светодиода при фальшстарте
}


void BrainRingMode::FalseStart() {
  falsestart_pushed = true;                                             // поднимается флажок фальшстарта
  pinMode(ADMIN_BUTTON_SET, OUTPUT);                                    // отключает пин кнопки ведущего "SET", чтобы сразу не сбросить фальшстарт
	tone(SOUND_PIN, FREQUENCY_FALSESTART, TIME_FALSESTART);
}

bool BrainRingMode::UserButtonPushed(int pin){
	digitalWrite(pin, HIGH);                                              // зажигает соответствующий светодиод игрока
	this->SetPin(pin);
	if (this->GetFalseStart()){
		this->FalseStart();
   Serial.println("BUT_FALSESTART");                                    // вывод для отладки через COM-порт
   for (int i = 0; i < ARRAY_SIZE(ARRAY_USER_BUTTON); i++){             //отключает пин кнопки игрока, сделавшего фальшстарт
      if (GetPin() == ARRAY_LED[i]){                                
      pinMode(ARRAY_USER_BUTTON[i], OUTPUT);                        
      falsestart_player_button = GetPin();                              // записывает номер кнопки игрока, сделавшего фальшстарт, для начала мигания светодиода
      } 
   }
		return true;                                                        // поменять на "false", чтобы в игре могло быть несколько фальшстартов одновременно
  }
  
	else{
    button_pushed = true;                                               // поднимается флажок нажатой кнопки
    pinMode(ADMIN_BUTTON_SET, OUTPUT);                                  // отключает пин кнопки ведущего "SET", чтобы не стартовать сразу
    Serial.println("BUT");                                              // вывод для отладки через COM-порт
		tone(SOUND_PIN, FREQUENCY_USER, TIME);
    digitalWrite(LED_START_SIGNAL, LOW);                                // гасит светодиод ведущего
    timer_left = timer;
		Timer1.stop();
     for (int i = 0; i < ARRAY_SIZE(ARRAY_USER_BUTTON); i++){           // отключает пин кнопки игрока, давшего неверный ответ
      if (GetPin() == ARRAY_LED[i]){
      pinMode(ARRAY_USER_BUTTON[i], OUTPUT);
      }    
    }
		return true;		
	}

}

void loop() {        
    while(falsestart_player_button != -1){                               // отработка мигания светодиода игрока, допустившего фальшстарт 
      unsigned long currentMillis = millis();
      if(currentMillis - previousMillis > interval) {
        previousMillis = currentMillis; 
      if (ledState == LOW)
        ledState = HIGH;
      else
      ledState = LOW;
    digitalWrite(falsestart_player_button, ledState);
      }
    } 
  
}