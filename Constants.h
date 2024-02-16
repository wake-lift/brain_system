#pragma once
#define USER_BUTTON_1 5                                            // пин кнопки игрока (красный) (порт 5 цифровой)
#define USER_BUTTON_2 4                                            // пин кнопки игрока (зеленый) (порт 4 цифровой)
#define USER_BUTTON_3 3                                            // пин кнопки игрока (синий) (порт 3 цифровой)
#define USER_BUTTON_4 2                                            // пин кнопки игрока (желтый) (порт 2 цифровой)

const int  ARRAY_USER_BUTTON[] = { 5, 4, 3, 2 };
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

const int  ARRAY_LED[] = { 19, 18, 17, 16 };                            // пины светодиодов игроков (соотв. красный(A5), зеленый(A4), синий(A3), желтый(A2))

#define LED_START_SIGNAL 15                                         // пин светодиода ведущего (белый(A1)) 

#define ADMIN_BUTTON_SET 9                                          // пин кнопки ведущего ("СТАРТ") 
#define ADMIN_BUTTON_RESET 8                                        // пин кнопки ведущего ("СБРОС") 

#define SOUND_PIN 10                                                 // пин буззера
#define FREQUENCY 2000                                              // частота основного сигнала ("СТАРТ") 

#define FREQUENCY_USER 1500                                         // частота сигнала ответа игрока 
#define FREQUENCY_FALSESTART 200                                    // частота сигнала фальшстарта
#define FREQUENCY_BRAIN_END 2100                                    // частота сигнала окончания времени на ответ (брейн-ринг)
#define TIME 500                                                    // продолжительность основного сигнала ("СТАРТ")
#define TIME_FALSESTART 3000                                        // продолжительность сигнала фальшстарта
#define TIME_BRAIN_ENDING_SOON 100                                  // продолжительность сигналов за 5 секунд до окончания времени на ответ (брейн-ринг)
#define TIME_WWW_END 1000                                           // продолжительность сигнала "прошла минута, время вышло" (ЧГК)
#define TIME_RESET 25                                               // продолжительность сигнала кнопки ведушего "СБРОС"
#define FREQUENCY_RESET 500                                        // частота сигнала кнопки ведушего "СБРОС"
#define FREQUENCY_WWW_END 1500                                      // частота сигнала окончания времени на ответ (ЧГК)

#define BRAIN_RING_MODE	11                                          // пин выбора режима игры (брейн-ринг) 
#define	QUARTET_MODE	12                                            // пин выбора режима игры (квартет)  
