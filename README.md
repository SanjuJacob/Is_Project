# AUTOMATED TEMPERATURE AND LIGHT CONTROL SYSTEM IN A CONFINED SPACE BASED ON THE NUMBER OF PEOPLE


The issue of energy consumption and efficiency is crucial due to the escalating global energy demand and the depletion of non-renewable resources. As population increase and urbanization expands, the need for sustainable and efficient energy management becomes more pressing. 

In confined spaces like classrooms, offices, or event halls, manually managing lighting and
temperature can lead to significant energy waste, especially when people forget to turn off
systems when not in use. 

Therefore, automating these processes based on real-time occupancy data not only conserves energy but also ensures a comfortable environment, highlighting the importance of developing advanced automated control systems. 

Our specific research question focuses on how to **effectively control the temperature and lighting in a confined space based on the number of people present**, utilizing technology to
enhance energy efficiency and user comfort. This inquiry seeks to explore the feasibility and practicality of implementing an automated system that adjusts environmental conditions
dynamically in response to occupancy changes. By addressing this question, we aim to
contribute to the broader efforts of reducing energy consumption and promoting sustainability in everyday environments.

Our research design centers on developing an automated temperature and light control system
that relies on various technological components to achieve its goals. The system uses **NFC card readers** to count the number of people entering and leaving the room, **a DHT22 temperature sensor**  to monitor the room's temperature, and **two servo motor** as a proxy regulator for the heating and cooling system. An interface from the web will enable the user to manually control the brightness of the **LEDs** and set the temperature thereby varying the speed of the motor. The **ESP8266 microcontroller** is the heart of the system, processing data and controlling the outputs. The methodology involves programming the microcontroller using the Arduino IDE, integrating the sensors and actuators, and testing the system in different scenarios to ensure it responds accurately to occupancy changes. The user interaction with the web interface will turn off all the automatic processes. Further **a push button** is also interfaced with the system such that it will be used to turn off or turn on all operations which are currently working.

From our research, we did learn that such an automated system can significantly reduce energy wastage and improve user comfort by maintaining optimal environmental conditions based on real-time data. The implications of this research are substantial, offering a scalable solution for energy management in various settings. Implementing these systems on a larger scale could lead to considerable energy savings and operational efficiency, contributing to sustainability goals and reducing the carbon footprint of buildings. This project demonstrates the potential of integrating advanced sensor technology and microcontrollers to create intelligent, responsive environments that align with modern energy conservation needs.
