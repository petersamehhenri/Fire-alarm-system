# Fire-alarm-system
A system uses an LM35 temperature sensor and a smoke sensor to detect fire emergencies, then unlocks the door, activates a water pump, buzzer, and red LED. It returns to normal when the owner enters the correct password (stored on an EEPROM and changeable) and the sensors read normal levels.

## Project sequnces and notes:
1) The system is reading smoke and temperature levels by the sensors, the temperature is showed on the LCD with the status of the enviroment (FINE/HEAT).
2) If the temperature is increased to 50 Celsius the status will be changed to "HEAT" on the LCD, activate an yellow LED to alarm the operators and the smoke sensor will start to get readings from the enviroment and the readings will be showed in the LCD.
3) If the smoke sensor senses with a ceratin level (50%) will activate a buzzer, bumb (motor), red LED and the system requires to enter the password to reset the system.
4) If the smoke is still more the 50% the system will not reset and will show on the LCD that the passowrd is correct but the smoke is more the 50.
5) The smoke must read less than 50% to reset the system.
6) The password is saved in an EEPROM and it can be changed by the user.
