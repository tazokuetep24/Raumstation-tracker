#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"
#include "rotate.h"
#include <stdio.h>

extern double az;
extern double elv;
extern int stop;
extern int go_back;
extern int pos_recieved;
extern int count;
extern int ignore;
extern uint8_t az_elv[16];
extern UART_HandleTypeDef huart3;

/**
  * @brief Receive and process position information from UART.
  *
  * This function is designed to receive position information from UART and process
  * the received data. The expected message format is "azimuth_angle elevation_angle\n".
  * The function extracts azimuth (az) and elevation (elv) angles from the received message
  * and takes appropriate actions based on the received values.
  *
  * @param huart UART handle for communication.
  *
  * @note If az = elv = 999.999, it indicates a request to stop tracking,
  *       and both X and Y motors will be stopped.
  * @note If az = elv = 888.888, it indicates a request to return X and Y motors
  *       to their initial positions.
  */
void recievePosition();

/**
  * @brief Transmit an error signal over UART based on the GPIO_Pin.
  *
  * This function is designed to transmit an error signal over UART when a specific
  * GPIO pin triggers an external interrupt. The error signal indicates that either
  * the X motor or the Y motor has reached its limit. The error signal is sent as a
  * single character ('0' for X motor, '1' for Y motor) to notify the receiving end
  * about the error condition.
  *
  * @param GPIO_Pin The GPIO pin that triggered the external interrupt.
  * @param uart UART handle for communication.
  *
  */
void transmitError(const uint16_t GPIO_Pin);


#endif /* INC_UART_H_ */
