# Stop-watch-System

## Aim
Design a Stop Watch System using ***`ATmega32`*** microcontroller, 
Use ATmega32 Microcontroller with frequency 1Mhz.

![This is an image](Project%20SnapShots/Protues_Circuit.png)


## Description

1. **`Timer1`** is used here and configured with ***`CTC mode`*** to count the Stop Watch time.
2. **`Six Common Anode 7-segments`** is used .
3. The six 7-segments in the project is connected using the **`multiplexed technique`**. and one **`7447 decoder`** for all 7-segments and control the enable/disable for each 7-segement using a NPN BJT transistor connect to one of the MCU pins. Like the below image:

![This is an image](Project%20SnapShots/Protues_Circuit.png)

4. We can connect more than one 7-segment display by using the Multiplexing method. In this method, at a time one 7-segment display is driven by the Microcontroller and the rest are OFF. It keeps switching the displays using transistors. Due to the persistence of vision, it appears as a normal display.
5. The 7447 decoder 4-pins is connected to the first 4-pins in `PORTC`.
6. The first 6-pins in `PORTA` is used as the enable/disable pins for the six 7-segments.
7. Stop Watch counting should start once the power is connected to the MCU.
8. External Interrupts Configurations and Usage as Below:

| External Interrupt ID | Usage  | Interrupt Triggering Edge  | Push Button Connection          |
| :---                  | :--- |     :---        |          :---                   |
| External INT0         | RESET Stop Watch | FALLING Edge    | Internal PULL-UP resistor       |
| External INT1         | PAUSE Stop Watch | RISING Edge     | External PULL-DOWN resistor     |
| External INT2         | RESUME Stop Watch| FALLING Edge    | Internal PULL-UP resistor       |

11. The LCD should display the temperature value and the fan state continuously like 
that:

![This is an image]()



## Embedded Drivers Used

- GPIO (General Purpose Input Output)
- External Interrupts 
- Common Macros 
- Timer1 Implemented inside StopWatch.c
  

## Deployment

To deploy this project 

Install the Following Software:

- [Protues Simulator](https://ettron.com/proteus-8-14-download-free-with-arduino-libraries-latest-version/).
- [Eclipse IDE](https://www.eclipse.org/downloads/packages/)

## 🔗 Personal Links

[![linkedin](https://img.shields.io/badge/linkedin-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/mostafa-mahmoud23/)
