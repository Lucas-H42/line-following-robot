# Line-Following Robot
This is the repo with the code for my line-following robot project for 3ELT. 

It uses the Waikato Uni CanSat Flight Computer instead of a normal Arduino because: 

1. We _were_ going to participate, then my teammates decided to give up a week after agreeing to continue, and
2. I wanted to make my life difficult.

But functionally, they're the same thing (kinda). So here's hoping it works and doesn't blow up in my face :)

## Connecting the board to a computer
So the flight computer has a history of being dumb annoying to connect to, so here's the how-to for using it with Arduino IDE.
(You do need STM32CubeProgrammer installed for this to work.)

To upload your code:

1. Connect the BOOT0 pin to the board's 3.3V pin
2. Connect the board to a computer via USB-C cable
3. In the IDE, choose the external option with the sub-text "debug-console", and select "Generic STM32F4 Series"
4. In the Tools menu, ensure that _Board part number_ is set to "Generic F405RGTx", and _Upload method_ is set to "STM32CubeProgrammer (DFU)"
5. Upload your code as usual

Then, to actually run the code (annoying, I know):

1. Ensure that, in the Tools menu, _USB Support_ is set to "CDC (generic 'Serial')" or equivalent (if you want to have Serial communication or similar)
2. After uploading your code, disconnect your board from your computer
3. Disconnect the BOOT0 pin from the 3.3V pin
4. Reconnect the board to your computer
5. Under the Select Board menu, choose the option containing "usbmodem..." followed by a string of numbers
