#include "uart.h"

double az = 0;
double elv = 0;
int stop = 0;
int go_back = 0;
int pos_recieved = 0;
int count = 0;
int ignore = 1;
uint8_t az_elv[16];


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
void recievePosition() {
	// Toggle RED LED indicating receiving of data
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);

	// Extract azimuth and elevation from the message
	sscanf((const char*)az_elv, "%lf %lf", &az, &elv);

	// Continue to receive data asynchronously
	HAL_UART_Receive_IT(&huart3, az_elv, 16);

	// Data received successfully
	pos_recieved = 1;

	// Check if the received angles indicate a request to stop tracking
	if (az == 999.999 && elv == 999.999) {
		// Toggle GPIOB Pin 7
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
		stop = 1;  // Stop both motors
		pos_recieved = 0;  // Reset the received flag
	}

	// Check if the received angles indicate a request to go back
	if (az == 888.888 && elv == 888.888) {
		// Toggle GPIOB Pin 7)
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
		go_back = 1;  // Set the goBack flag for further processing
		pos_recieved = 0;  // Reset the received flag
	}
}


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
void transmitError(const uint16_t GPIO_Pin) {

	/* Prevent unused argument(s) compilation warning */
	UNUSED(GPIO_Pin);

	if (!ignore){
		// X Motor has reached limit
		if (GPIO_Pin == xLimPin) {
			// Set stop to true to stop rotation
			//stop = 1;
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
			if (count == 0){
				// Transmit "0" to the GUI indicating Motor X has reached limit
				HAL_UART_Transmit(&huart3, (uint8_t*)"0", 1, HAL_MAX_DELAY);
				// Increment count to make sure that the message only sent once
				count = 1;
			}
		}
		// Y Motor reached limit
		else if (GPIO_Pin == yLimPin) {
			// Set stop to true to stop rotation
			//stop = 1;
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
			if (count == 0){
				// Transmit "1" to the GUI indicating Motor Y has reached limit
				HAL_UART_Transmit(&huart3, (uint8_t*)"1", 1, HAL_MAX_DELAY);
				// Increment count to make sure that the message only sent once
				count = 1;
			}
		}

		if (GPIO_Pin == GPIO_PIN_13){
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
			const uint8_t data[] = "1";
			HAL_UART_Transmit(&huart3, data, 1, HAL_MAX_DELAY);

		}
	}
}

