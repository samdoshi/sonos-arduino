# Hardware Favourite Buttons for Sonos
This is a simple Arduino sketch to allow using physical buttons to select internet radio stations for your Sonos.

Four buttons provide access to 2 favourites each via a short and long press, the fifth button pauses on a short click, plays on a long click. Two LEDs provide user interface feedback.

## Requirements
- 1x Arduino ethernet board
- 5x microswitches
- 2x LEDs (1x green, 1x red & resistors)

## Hardware Setup
Pins 2, 3, 5, 6 & 7, connected to one input of a microswitch, the other input connected to ground.

Pin 8 to positive side of the green LED, the negative side connected to the resistor, the other side of the resistor is connected to ground. Similarly with pin 9, but to the red LED instead.

## Software Setup
Set your internet stream URLs in the 2 arrays declared at the top of the main sketch file.

Don't forget to set your Arduino's MAC address and the IP address of your Sonos.

# TODO
- Make serial debug output conditional.
- Automatically find the IP address of your Sonos.