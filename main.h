#ifndef MAIN_H_
#define MAIN_H_

#define PLANT_NO                        3
#define SENSOR_MAX                      2400u

/* TIME */
#define SECOND                          1000
#define MINUTE                          (60 * SECOND)
#define HOUR                            (60 * MINUTE)
#define WATERING_INTERVAL               (10 * SECOND)
#define SLEEP_INTERVAL                  (6 * HOUR)

/* PLANT WATERING THRESHOLDS */
#define PLANT1_THRESHOLD                0.2         
#define PLANT2_THRESHOLD                0.5
#define PLANT3_THRESHOLD                0.6

/* PIN VALUES */
#define INTERNAL_TEMP_PIN_NO            4
#define LED_PIN_NO                      25

#define RELAY_IN0_PIN_NO                12
#define RELAY_IN1_PIN_NO                13
#define RELAY_IN2_PIN_NO                14
#define RELAY_IN3_PIN_NO                15

#define ADC0_PIN_NO                     26
#define ADC1_PIN_NO                     27
#define ADC2_PIN_NO                     28
#define ADC3_PIN_NO                     29

#define ADC0_CHANNEL_INPUT              0
#define ADC1_CHANNEL_INPUT              1
#define ADC2_CHANNEL_INPUT              2
#define ADC3_CHANNEL_INPUT              3

#define ADC0_IRQ_FIFO                   22

/* MISC. VALUES */
#define GPIO_ON                         1
#define GPIO_OFF                        0
#define ADC_ERROR_RET                   0xFFFFFFFF

#endif