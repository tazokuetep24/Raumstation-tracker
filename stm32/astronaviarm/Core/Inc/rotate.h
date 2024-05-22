#ifndef ROTATE_H_
#define ROTATE_H_

/* Includes */
#include "main.h"

/* Pins definitions */
// X Motor
#define xStepPort GPIOF
#define xStepPin GPIO_PIN_15
#define xDirPort GPIOE
#define xDirPin GPIO_PIN_11
#define xLimPort GPIOD
#define xLimPin GPIO_PIN_15
// Y Motor
#define yStepPort GPIOE
#define yStepPin GPIO_PIN_13
#define yDirPort GPIOE
#define yDirPin GPIO_PIN_9
#define yLimPort GPIOD
#define yLimPin GPIO_PIN_14

/*
 * @brief Rotate the X motor to a specified azimuth angle.
 *
 * This function controls the rotation of the X motor to achieve a desired azimuth angle.
 * If the azimuth angle is greater than 0, the rotation will be in a clockwise direction;
 * otherwise, it will be in a counterclockwise direction.
 *
 * @param azimuth The desired azimuth angle in degrees.
 */
void rotateX(const double azimuth);

/*
 * @brief Rotate the Y motor to a specified elevation angle.
 *
 * This function controls the rotation of the Y motor to achieve a desired elevation angle.
 * If the elevation angle is greater than 0, the rotation will be upward;
 * otherwise, it will be downward.
 *
 * @param elevation The desired elevation angle in degrees.
 */
void rotateY(const double elevation);

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
void rotateXY(const double azimuth, const double elevation);

#endif /* ROTATE_H_ */
