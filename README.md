# Remote Control Car

**1. Test Motor Code**

	- This code will check if you've wired up your car correctly.
	- Copy the code from Test_Motor_Code.ino and paste onto your Arduino sketch.
	- If your car is turning in a circle, try changing one of the motor wirings on your motor driver (the red base).
	
**2. IR-Receiver**

	- You have to download the IR library onto your laptop first to use the code.
	- Download IRREMOTE.ZIP. Do not unzip.
	- Copy and paste the code from IR_Read onto your Arduino sketch.
	- Include the library onto Arduino: Sketch → Include Library → Add ZIP Library → … → IRREMOTE.ZIP
	- This code allows you to decode each button on your remote. Remember to open Serial Monitor to read them.

**3. Ultrasonic-sensor**

	- Copy and paste the code from sonic_sensor onto your Arduino sketch.
	- This code allows you to measure distance with your ultrasonic sensor. Remember to open Serial Monitor to read the distances.

**4. Display**

	- Copy and paste the code from display_test onto your Arduino sketch.
	- This code allows you to display the distance on a 7 segment display.
	
**0. Release Code**

	- This folder contains different versions of code that combines more than one function.
