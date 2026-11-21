# Line-Following Robot
This is the repo with the code for my line-following robot project for 3ELT. 

It uses the Waikato Uni CanSat Flight Computer instead of a normal Arduino because: 

1. We _were_ going to participate, then my teammates decided to give up a week after agreeing to continue, and
2. I wanted to make my life difficult.

But functionally, they're the same thing (kinda). So here's hoping it works and doesn't blow up in my face :)

## Connecting the board to a computer
So the flight computer has a history of being dumb annoying to connect to, so here's the how-to for using it with CLion (used to be for Arduino IDE, but I migrated, and the Arduino IDE system no longer supports this).
(You do need STM32CubeProgrammer installed for this to work.)

To upload your code:

1. Make sure you have the proper platformio.ini setup. You MUST have (aside from the obvious) the build_flags set as "-D USBCON" and "-D PIO_FRAMEWORK_ARDUINO_ENABLE_CDC". monitor_port should also be set to "/dev/cu.usbmodem*".
2. Connect the BOOT0 pin to the board's 3.3V pin
3. Connect the board to a computer via USB-C cable
4. Ensure your platformio.ini has been refreshed and can build
5. Make sure the environment you want to upload is selected in the top bar of the window
6. Choose "Upload" from the PIO menu, or run the code from the top bar.
7. If you want to monitor, choose "PlatformIO Serial Monitor" from the PIO menu.

No weird unplugging and replugging, yay!