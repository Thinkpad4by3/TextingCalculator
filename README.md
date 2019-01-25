# TextingCalculator
Ti-30 calculators modified with Arduinos to text each other wirelessly

# How it works
These calculators are original TI-30 scientific calculators "retrofitted" with an arduino inside. The original display and keyboard were reverse engineered and set up to work with the arduino. 8 of the original 9 segments are used due to the limitations with the MAX7219 LED driver IC. The character set is also limited by the nature of 7 segment displays and the decimal point selects the active cell. The keyboard has only 6 button wired up because wiring all 40 up would have taken up too many pins. Instead, I used a simple control scheme using these buttons. Two of them controller a "pointer", displayed with the decimal point. For a given active cell, two buttons could increment up and down through the alphabet, and looping around when necessary. The last two buttons were clear and send. The sent information would be displayed on the other person's calculator, although due to time constraints I only programmed them to wipe out the other person's message.

# Demonstration

The calculators from the front look entirely unmodified outside of the 9V battery attached to the side. Due to space constraints the battery couldn't be placed inside.
![texting calculator](https://i.imgur.com/IWsrofpm.jpg)
This is how the calculators are wired up. The orange wires go up to the original board where the LEDs are controlled.
![T.C wiring](https://i.imgur.com/FM3UEZUm.jpg)
Any 8 character string can be programmed as long as all the characters are supported(K,Q,W,M are not supported)
For this example, I typed "HiGithub". 
![T.C typing](https://i.imgur.com/CwKnwAMm.jpg)
Once messages are written out, they can be sent. (the default start up message is "HelloPPL")
Before:
![before send](https://i.imgur.com/xOpcOARm.jpg)
After:
![after send](https://i.imgur.com/ped5LrFm.jpg)
