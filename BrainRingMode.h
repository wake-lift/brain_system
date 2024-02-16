#pragma once
#include "GameMode.h"
#include "Constants.h"

#define BRAIN_TIMER 20                                 // время командам, чтобы дать ответ

class BrainRingMode : public GameMode {
private: 
	int setPushes;                                       // объявление счетчика нажатий кнопки "СТАРТ"
	int firstTimer;
	int seconedTimer;
	int timer;
  int timer_left;                                       // переменная оставшегося времени
  bool button_pushed = false;                           // флажок нажатой кнопки игрока
  bool falsestart_pushed = false;                       // флажок фальшстарта
	
public:
	BrainRingMode();
	~BrainRingMode();

	virtual void Set();
	virtual void Reset();
	virtual void SetTimer();
	virtual void FalseStart();
	void CheckTimeLeft(int timeLeft);
	virtual bool UserButtonPushed(int pin);
};
