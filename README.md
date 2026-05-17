# Qt Scientific Calculator
A fully functional scientific calculator application built with Qt 5/6 and C++.

## Features
- Basic arithmetic operations: addition, subtraction, multiplication, division
- Advanced scientific functions:
  - Trigonometric functions: sin, cos, tan
  - Logarithmic functions: ln, log
  - Power and root: x², x^y, square root
  - Factorial: x!
  - Modulo operation: mod
- Number base conversion: binary (bin), octal (oct), decimal (dec), hexadecimal (hex)
- History tracking
- Error handling for invalid expressions
- Clean and intuitive user interface

## How to Run
1. Clone this repository
2. Open Qt Creator
<img width="1254" height="726" alt="8173ccb9-2c66-4ccb-b9be-2fd782e20a20" src="https://github.com/user-attachments/assets/3f5cb182-0f93-473f-bd6b-20cf538630c5" />

3. Click the **Open** button in the Projects panel
4. Select the `calcfunction.pro` file from the cloned folder
5. Click the Run button (▶️) in the bottom left corner
<img width="1250" height="444" alt="c4753c8c-4b32-42b7-b231-6cfab337a3b5" src="https://github.com/user-attachments/assets/edad6f7c-e8be-48d2-a6ac-7ecf11918822" />

## Result Preview
<img width="795" height="513" alt="c27cb5e5-0efd-4214-9754-c91b594f79ce" src="https://github.com/user-attachments/assets/39132249-5f79-4c16-b6df-305c3ebbbe8f" />

## Project Structure
- `main.cpp` - Application entry point
- `calculator.h/cpp` - Main calculator UI and logic
- `calcfunction.h/cpp` - Core calculation engine
- `complex.h/cpp` - Complex number support
- `calcfunction.pro` - Qt project file

## Requirements
- Qt 5.15+ or Qt 6.x
- C++11 or later compiler
