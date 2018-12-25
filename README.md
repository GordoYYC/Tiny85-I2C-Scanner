# Tiny85-I2C-Scanner
*Beginner* project to scan I2C bus and report on LCD (also I2C) all the I2C addresses found (including the LCD's).

*Beginners:* Make a directory, load all these and only these files into it.  Open the Arduino IDE and load in support for the ATtiny's (google it).  Then open this .ino file and burn it.  It works.

There is a pushbutton to quickly rescan, so you can pull a I2C wire from modules and rescan and see what changed and thus identify which module is which address.  This same pushbutton will need to be pushed each time the number of found I2C addresses exceed the screen lines  to see the next set of addresses.  I've used it for 1 to 5 addresses, it should cover them all.

Written for a AT Tiny85 but easily adapted to Arduinos, etc., and should hopefully help beginners get their AT Tiny 85's up and talking to the world.  (Granted there is a small Catch-22 in that you need to have the I2C LCD working in the first place, but still it helps from there on in.)

The main thing I had difficulty with was getting a standard LCD (with backpack I2C adaptor) working with the Tiny, as I had to find a suitable library that would fit in and work with the tiny (in the future I'll be able to write my own libraries, but gotta walk before I run).  Many Thanks to BroHogan and his predecessors for the libraries!

It's certainly not the smallest or the shortest sketch, but looks nice and I hope readable.  It isn't designed as a library but as a utility to load in and use, then get written over.  It has some other good beginner topics such as:
- generating a custom character for the LCD and displaying it
- a "hit any key to continue" loop
- basic formatting when you don't have access to a 'printf' type function
- setting up a screen size define that is used to init LCD and to control program prints to LCD (lines and cols)
- my first git

![.](https://raw.githubusercontent.com/GordoYYC/Tiny85-I2C-Scanner/master/I2C-Scanner_bb.jpg)
