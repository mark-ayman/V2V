/*******************************************************/
/****   Author : Ibrahim Elshimy      ******************/
/****   SWC:     TIMER1_PRIVATE      ******************/
/****   Date :        5/8/2023        ******************/
/****   Version : 1.00                ******************/
/*******************************************************/
#define    NORMAL_MODE                         0
#define    PWM_PHASE_CORRECT_MODE              1
#define    CTC_MODE                            2
#define    FAST_PWM_MODE                       3

#define DISCONNECTED_OC0                       0
#define TOGGLE_0C0                             1
#define CLEAR_0C0                              2
#define SET_0C0                                3

#define NON_INVERTED_MODE                      2
#define INVERTED_MODE                          3
#define NORMAL_MODE_OC0_DISCONNECTED           0

#define    NO_CLOCK_SOURCE                     0
#define    NO_PRESCALER                        1
#define    PRESCALER_BY_8                      2
#define    PRESCALER_BY_64                     3
#define    PRESCALER_BY_256                    4
#define    PRESCALER_BY_1024                   5
#define    EXTERNAL_CLOCK_FALLING_EDGE_T1Pin   6
#define    EXTERNAL_CLOCK_RISING_EDGE_T1Pin    7

#define PRESCALER_MASKING     0b11111000
