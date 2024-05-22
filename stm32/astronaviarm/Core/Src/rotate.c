// Includes
#include "rotate.h"
#include <stdlib.h>
#include <math.h>


extern int stop;


/*
 * @brief Rotate the X motor to a specified azimuth angle.
 *
 * This function controls the rotation of the X motor to achieve a desired azimuth angle.
 * If the azimuth angle is greater than 0, the rotation will be in a clockwise direction;
 * otherwise, it will be in a counterclockwise direction.
 *
 * @param azimuth The desired azimuth angle in degrees.
 */
void rotateX(const double azimuth) {
    // Set direction based on azimuth sign
    if (azimuth > 0) {
        HAL_GPIO_WritePin(xDirPort, xDirPin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(xDirPort, xDirPin, GPIO_PIN_RESET);
    }

    // Calculate the number of steps required for the rotation
    int steps = round((abs(azimuth) / 1.8) * 4);

    // Iterate through the steps and control the motor
    for (int step = 0; step < steps; step++) {
        if (stop) {
            break;  // Break out of the loop if the motor should stop
        }
        HAL_GPIO_WritePin(xStepPort, xStepPin, GPIO_PIN_SET);
        HAL_Delay(1);
        HAL_GPIO_WritePin(xStepPort, xStepPin, GPIO_PIN_RESET);
        HAL_Delay(1);
    }
}
/*
 * @brief Rotate the Y motor to a specified elevation angle.
 *
 * This function controls the rotation of the Y motor to achieve a desired elevation angle.
 * If the elevation angle is greater than 0, the rotation will be upward;
 * otherwise, it will be downward.
 *
 * @param elevation The desired elevation angle in degrees.
 */
void rotateY(const double elevation) {
    // Set direction based on elevation sign
    if (elevation > 0) {
        HAL_GPIO_WritePin(yDirPort, yDirPin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(yDirPort, yDirPin, GPIO_PIN_RESET);
    }

    // Calculate the number of steps required for the rotation
    int steps = round((abs(elevation) / 1.8) * 3.8);

    // Iterate through the steps and control the motor
    for (int step = 0; step < steps; step++) {
        if (stop) {
            break;  // Break out of the loop if the motor should stop
        }
        HAL_GPIO_WritePin(yStepPort, yStepPin, GPIO_PIN_SET);
        HAL_Delay(1);
        HAL_GPIO_WritePin(yStepPort, yStepPin, GPIO_PIN_RESET);
        HAL_Delay(1);
    }
}
/*
 * @brief Simultaneously rotate the X and Y motors based on azimuth and elevation angles.
 *
 * This function controls the combined rotation of the X and Y motors to achieve a desired
 * orientation. Azimuth angle specifies horizontal rotation (clockwise if > 0, counterclockwise if <= 0),
 * and elevation angle specifies vertical rotation (upward if > 0, downward if <= 0).
 *
 * @param azimuth The desired azimuth angle in degrees for X motor rotation.
 * @param elevation The desired elevation angle in degrees for Y motor rotation.
 */
void rotateXY(const double azimuth, const double elevation) {
    // Set X motor direction based on azimuth sign
    if (azimuth > 0) {
        HAL_GPIO_WritePin(xDirPort, xDirPin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(xDirPort, xDirPin, GPIO_PIN_RESET);
    }

    // Set Y motor direction based on elevation sign
    if (elevation > 0) {
        HAL_GPIO_WritePin(yDirPort, yDirPin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(yDirPort, yDirPin, GPIO_PIN_RESET);
    }

    // Calculate the number of steps required for each motor's rotation
    int stepsX = round((abs(azimuth) / 1.8) * 4);
    int stepsY = round((abs(elevation) / 1.8) * 3);

    // Determine the maximum number of steps between X and Y rotations
    int maxSteps = fmax(stepsX, stepsY);

    // Iterate through the maximum number of steps, controlling both motors
    for (int step = 0; step < maxSteps; step++) {
        if (stop) {
            break;  // Break out of the loop if the motor should stop
        }

        // Move in the X direction if there are remaining steps in azimuth
        if (step < stepsX) {
            HAL_GPIO_WritePin(xStepPort, xStepPin, GPIO_PIN_SET);
            HAL_Delay(1);
            HAL_GPIO_WritePin(xStepPort, xStepPin, GPIO_PIN_RESET);
            HAL_Delay(1);
        }

        // Move in the Y direction if there are remaining steps in elevation
        if (step < stepsY) {
            if (stop) {
                break;  // Break out of the loop if the motor should stop
            }
            HAL_GPIO_WritePin(yStepPort, yStepPin, GPIO_PIN_SET);
            HAL_Delay(1);
            HAL_GPIO_WritePin(yStepPort, yStepPin, GPIO_PIN_RESET);
            HAL_Delay(1);
        }
    }
}

