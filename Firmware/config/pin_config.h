#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

// $[CMU]
// [CMU]$

// $[LFXO]
// LFXO LFXTAL_I on PD01
#ifndef LFXO_LFXTAL_I_PORT                      
#define LFXO_LFXTAL_I_PORT                       gpioPortD
#endif
#ifndef LFXO_LFXTAL_I_PIN                       
#define LFXO_LFXTAL_I_PIN                        1
#endif

// LFXO LFXTAL_O on PD00
#ifndef LFXO_LFXTAL_O_PORT                      
#define LFXO_LFXTAL_O_PORT                       gpioPortD
#endif
#ifndef LFXO_LFXTAL_O_PIN                       
#define LFXO_LFXTAL_O_PIN                        0
#endif

// [LFXO]$

// $[PRS.ASYNCH0]
// [PRS.ASYNCH0]$

// $[PRS.ASYNCH1]
// [PRS.ASYNCH1]$

// $[PRS.ASYNCH2]
// [PRS.ASYNCH2]$

// $[PRS.ASYNCH3]
// [PRS.ASYNCH3]$

// $[PRS.ASYNCH4]
// [PRS.ASYNCH4]$

// $[PRS.ASYNCH5]
// [PRS.ASYNCH5]$

// $[PRS.ASYNCH6]
// [PRS.ASYNCH6]$

// $[PRS.ASYNCH7]
// [PRS.ASYNCH7]$

// $[PRS.ASYNCH8]
// [PRS.ASYNCH8]$

// $[PRS.ASYNCH9]
// [PRS.ASYNCH9]$

// $[PRS.ASYNCH10]
// [PRS.ASYNCH10]$

// $[PRS.ASYNCH11]
// [PRS.ASYNCH11]$

// $[PRS.SYNCH0]
// [PRS.SYNCH0]$

// $[PRS.SYNCH1]
// [PRS.SYNCH1]$

// $[PRS.SYNCH2]
// [PRS.SYNCH2]$

// $[PRS.SYNCH3]
// [PRS.SYNCH3]$

// $[GPIO]
// [GPIO]$

// $[TIMER0]
// TIMER0 CC0 on PC06
#ifndef TIMER0_CC0_PORT                         
#define TIMER0_CC0_PORT                          gpioPortC
#endif
#ifndef TIMER0_CC0_PIN                          
#define TIMER0_CC0_PIN                           6
#endif

// TIMER0 CC1 on PC07
#ifndef TIMER0_CC1_PORT                         
#define TIMER0_CC1_PORT                          gpioPortC
#endif
#ifndef TIMER0_CC1_PIN                          
#define TIMER0_CC1_PIN                           7
#endif

// [TIMER0]$

// $[TIMER1]
// TIMER1 CC0 on PC08
#ifndef TIMER1_CC0_PORT                         
#define TIMER1_CC0_PORT                          gpioPortC
#endif
#ifndef TIMER1_CC0_PIN                          
#define TIMER1_CC0_PIN                           8
#endif

// TIMER1 CC1 on PC09
#ifndef TIMER1_CC1_PORT                         
#define TIMER1_CC1_PORT                          gpioPortC
#endif
#ifndef TIMER1_CC1_PIN                          
#define TIMER1_CC1_PIN                           9
#endif

// [TIMER1]$

// $[TIMER2]
// TIMER2 CC0 on PA08
#ifndef TIMER2_CC0_PORT                         
#define TIMER2_CC0_PORT                          gpioPortA
#endif
#ifndef TIMER2_CC0_PIN                          
#define TIMER2_CC0_PIN                           8
#endif

// TIMER2 CC1 on PA09
#ifndef TIMER2_CC1_PORT                         
#define TIMER2_CC1_PORT                          gpioPortA
#endif
#ifndef TIMER2_CC1_PIN                          
#define TIMER2_CC1_PIN                           9
#endif

// TIMER2 CC2 on PA10
#ifndef TIMER2_CC2_PORT                         
#define TIMER2_CC2_PORT                          gpioPortA
#endif
#ifndef TIMER2_CC2_PIN                          
#define TIMER2_CC2_PIN                           10
#endif

// [TIMER2]$

// $[TIMER3]
// [TIMER3]$

// $[TIMER4]
// [TIMER4]$

// $[USART0]
// USART0 RX on PA04
#ifndef USART0_RX_PORT                          
#define USART0_RX_PORT                           gpioPortA
#endif
#ifndef USART0_RX_PIN                           
#define USART0_RX_PIN                            4
#endif

// USART0 TX on PA05
#ifndef USART0_TX_PORT                          
#define USART0_TX_PORT                           gpioPortA
#endif
#ifndef USART0_TX_PIN                           
#define USART0_TX_PIN                            5
#endif

// [USART0]$

// $[I2C1]
// [I2C1]$

// $[EUSART1]
// [EUSART1]$

// $[EUSART2]
// [EUSART2]$

// $[LCD]
// [LCD]$

// $[KEYSCAN]
// [KEYSCAN]$

// $[LETIMER0]
// [LETIMER0]$

// $[IADC0]
// [IADC0]$

// $[ACMP0]
// [ACMP0]$

// $[ACMP1]
// [ACMP1]$

// $[VDAC0]
// [VDAC0]$

// $[PCNT0]
// [PCNT0]$

// $[LESENSE]
// [LESENSE]$

// $[I2C0]
// [I2C0]$

// $[EUSART0]
// [EUSART0]$

// $[PTI]
// [PTI]$

// $[MODEM]
// [MODEM]$

// $[CUSTOM_PIN_NAME]
#ifndef _PORT                                   
#define _PORT                                    gpioPortA
#endif
#ifndef _PIN                                    
#define _PIN                                     0
#endif

#ifndef UART_CLI_RX_PORT                        
#define UART_CLI_RX_PORT                         gpioPortA
#endif
#ifndef UART_CLI_RX_PIN                         
#define UART_CLI_RX_PIN                          4
#endif

#ifndef UART_CLI_TX_PORT                        
#define UART_CLI_TX_PORT                         gpioPortA
#endif
#ifndef UART_CLI_TX_PIN                         
#define UART_CLI_TX_PIN                          5
#endif

#ifndef LED_RED_PORT                            
#define LED_RED_PORT                             gpioPortA
#endif
#ifndef LED_RED_PIN                             
#define LED_RED_PIN                              8
#endif

#ifndef LED_GREEN_PORT                          
#define LED_GREEN_PORT                           gpioPortA
#endif
#ifndef LED_GREEN_PIN                           
#define LED_GREEN_PIN                            9
#endif

#ifndef LED_BLUE_PORT                           
#define LED_BLUE_PORT                            gpioPortA
#endif
#ifndef LED_BLUE_PIN                            
#define LED_BLUE_PIN                             10
#endif

#ifndef MOTOR_UP_LEFT_PORT                      
#define MOTOR_UP_LEFT_PORT                       gpioPortC
#endif
#ifndef MOTOR_UP_LEFT_PIN                       
#define MOTOR_UP_LEFT_PIN                        6
#endif

#ifndef MOTOR_DOWN_LEFT_PORT                    
#define MOTOR_DOWN_LEFT_PORT                     gpioPortC
#endif
#ifndef MOTOR_DOWN_LEFT_PIN                     
#define MOTOR_DOWN_LEFT_PIN                      7
#endif

#ifndef MOTOR_DOWN_RIGHT_PORT                   
#define MOTOR_DOWN_RIGHT_PORT                    gpioPortC
#endif
#ifndef MOTOR_DOWN_RIGHT_PIN                    
#define MOTOR_DOWN_RIGHT_PIN                     8
#endif

#ifndef MOTOR_UP_RIGHT_PORT                     
#define MOTOR_UP_RIGHT_PORT                      gpioPortC
#endif
#ifndef MOTOR_UP_RIGHT_PIN                      
#define MOTOR_UP_RIGHT_PIN                       9
#endif

#ifndef VBATT_DIV2_PORT                         
#define VBATT_DIV2_PORT                          gpioPortD
#endif
#ifndef VBATT_DIV2_PIN                          
#define VBATT_DIV2_PIN                           2
#endif

// [CUSTOM_PIN_NAME]$

#endif // PIN_CONFIG_H

