# AstroNaviArm: Raumstation Tracker

## Overview
Welcome to AstroNaviArm, an exciting project dedicated to creating a sophisticated satellite tracking robot. This innovative system utilizes an STM32 Nucleo board (STM32F438ZI) for hardware control, programmed in C, coupled with a Qt-based GUI in C++. AstroNaviArm is designed to track a variety of satellites, including the International Space Station (ISS), Tiangong, Starlink, and more.


## Hardware Used
- **Microcontroller:** STM32 Nucleo Board (STM32F438ZI)
- **Programming Language:** C (for STM32), C++ (for Qt)

## Robot Design
AstroNaviArm is built upon a modified version of the jjrobots' design, incorporating enhancements to meet the specific requirements of satellite tracking. For detailed information on the robot's structure and modifications, please refer to the [jjrobots website](https://jjrobots.com/product/remotely-controlled-laser-pointer/).

## Features and Components

### 1. GUI Development with Qt
AstroNaviArm boasts an intuitive Qt-based GUI, allowing users to effortlessly select and monitor satellites.

### 2. Satellite Position API Integration
Real-time satellite tracking is achieved through seamless integration with a Satellite Position API, providing accurate and up-to-date information.

### 3. Endswitch Implementation
To ensure the safety and precision of AstroNaviArm's movements, end switches are strategically implemented.

### 4. Stepper Motor Control
AstroNaviArm controls two stepper motors with precision, allowing for accurate orientation based on user input and satellite positions.

### 5. Alignment Calculation
Sophisticated algorithms are employed to calculate and maintain the robot's alignment, ensuring optimal tracking accuracy.

### 6. Endswitch Monitoring
Parallel monitoring of end switches ensures the robot operates within predefined safe limits, minimizing the risk of unintended movements.

### 7. Display and Status Features
AstroNaviArm's GUI displays real-time satellite positions and provides clear status indicators for the robot's alignment.

### 8. Pointer Control
Enhancing user interaction, AstroNaviArm's GUI includes a pointer controlled by the robot's movements.

### 9. Testing and Debugging
AstroNaviArm undergoes rigorous testing, including comprehensive component and integration tests, to ensure reliability and functionality.

### 10. Documentation
Thorough documentation, including code documentation and user guides, is provided to assist users and future developers.

## Project Timeline
The project unfolds in two phases:

- **Phase 1 (20.11.23 - 08.12.23):** Detailed development and implementation of project components, with an interim presentation on 14.11.23.

- **Phase 2 (18.12.23 - 19.01.24):** Finalization of features, testing, bug fixing, optimization, documentation preparation, and a final presentation.

