# Tiny85-I2C-Scanner
Beginner project to scan I2C bus and report on LCD (also I2C) all the I2C addresses found.

Written for a AT Tiny85 but easily adapted to Arduinos, etc., but should hopefully help beginners get their AT Tiny 85's up and talking to the world.  (Granted there is a small Catch-22 in that you need to have the I2C LCD working in the first place, but still it helps from there on in.)

A couple things I had difficulty with was getting a standard LCD (with backpack I2C adaptor) working with the Tiny, as I had to find a suitable library (in the future I'll be able to write my own libraries, but gotta walk before I run).

This little sketch has some other good beginner topics such as:
- generating a custom character for the LCD and displaying it
- a "hit any key to continue" loop
- basic formatting when you don't have access to a 'printf' type function
