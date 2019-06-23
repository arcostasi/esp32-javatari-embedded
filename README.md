# ESP32-JAVATARI-EMBEDDED.

This project is an Atari 2600 cross platform emulator embedded in an Atari CX40 joystick with ESP32 and designed for the modern browsers like Chrome, Firefox, Safari and Edge.

The Atari 2600 (also known as Video Computer System or simply VCS) is a second-generation console released by Atari on September 11, 1977. It retailed for $199 and had a 6507 CPU at 1.19 MHz with 128 bytes of RAM.

As the Atari 2600 cross platform emulator was used the [Javatari.js](https://github.com/ppeccin/javatari.js) handcraft by [ppeccino](https://github.com/ppeccin) and together with the image ROMs that can be embedded in the ESP32 using SPIFFS file system.

<img src="https://github.com/arcostasi/esp32-javatari-embedded/blob/master/doc/pic1.jpg?raw=true" width="600">

Pitfall! is a video game designed by David Crane for the Atari 2600 and released by Activision in 1982.

You can launch the emulator and load ROMs with a single link. And now you can play Atari 2600 games with your CX40 joystick.

All the source code was documented, like as the steps required to set up your own Atari emulator in the ESP32.

## Part List & Tools

1. Atari CX40 joystick with Infrared and batteries (2x AAA 1.5v alkaline)
2. ESP32 NodeMCU-32S WiFi / Bluetooth
3. IR Receiver Sensor (Arduino Compatible)
4. Micro USB to USB Cable used to program the ESP32
5. Double-Sided Bonding Tape
6. Screwdriver
7. Soldering iron
8. Soldering tin
9. Utility knife
10. [Atom](https://atom.io/) or [Visual Studio Code](https://code.visualstudio.com/), the two have supports for PlatformIO
11. [PlatformIO](https://platformio.org/), An open source ecosystem for IoT development

## Step by Step

### Step 1:

Remove the four screws from the back of the Atari CX40 joystick, for this use a suitable screwdriver.

<img src="https://github.com/arcostasi/esp32-javatari-embedded/blob/master/doc/step1.jpg?raw=true" width="600">

### Step 2:

Use a utility knife to remove the plastic parts to accommodate an ESP32 board as indicated below:

<img src="https://github.com/arcostasi/esp32-javatari-embedded/blob/master/doc/step2.jpg?raw=true" width="600">

### Step 3:

Place a double-sided bonding tape on the indicated base to fix the  ESP32 NodeMCU and drill a hole in the location indicated to connect the USB programming cable.

<img src="https://github.com/arcostasi/esp32-javatari-embedded/blob/master/doc/step3.jpg?raw=true" width="600">

### Step 4:

Remove the plastic base on the bottom of the ESP32 NodeMCU to better secure the base of the board.

<img src="https://github.com/arcostasi/esp32-javatari-embedded/blob/master/doc/step4.jpg?raw=true" width="600">

### Step 5:

Make the power and signal connections as shown below.

Note: Change the IR receiver pin from 15 to 34 (White Wire), I made this change later for better compatibility of IR library. If you do not want to change the connection, change the pinout from 34 to 15 in the main.cpp source code on line 5.

<img src="https://github.com/arcostasi/esp32-javatari-embedded/blob/master/doc/step5.jpg?raw=true" width="600">

### Step 6:

Solder the power wires to the battery as the picture below:

<img src="https://github.com/arcostasi/esp32-javatari-embedded/blob/master/doc/step6.jpg?raw=true" width="600">

### Step 7:

Let's close the joystick carefully and let the infrared sensors (transmitter and receiver) approximate.

<img src="https://github.com/arcostasi/esp32-javatari-embedded/blob/master/doc/step7.jpg?raw=true" width="600">

### Step 8:

Insert the USB cable into the joystick and into USB PC to upload program into the ESP32.

<img src="https://github.com/arcostasi/esp32-javatari-embedded/blob/master/doc/step8.jpg?raw=true" width="600">

### Step 9:

Clone this repository: https://github.com/arcostasi/esp32-javatari-embedded

### Step 10:

Open this project and the main.cpp file in your favorite IDE editor that supports the PlatformIO and upload the program into ESP32:

<img src="https://github.com/arcostasi/esp32-javatari-embedded/blob/master/doc/step10.jpg?raw=true" width="600">

### Step 11:

Let's now store our favorite game images inside the roms directory in storage and send ROM files to ESP32 file system.

<img src="https://github.com/arcostasi/esp32-javatari-embedded/blob/master/doc/step11.jpg?raw=true" width="600">

### Step 12:

Use a SmartConfig or EspTouch application for your smartphone connected to your Wifi network to put ESP32 on your network.

<img src="https://github.com/arcostasi/esp32-javatari-embedded/blob/master/doc/step12.jpg?raw=true" width="600">

### Step 13:

If a successful message appeared on your SmartConfig or EspTouch application, access the IP address of your ESP32 and your emulator will be loaded.

### Step 14:

Access the ROMs list route of your IP: http://esp32_ip/roms and put the path of your ROM to a URL of your emulator (F6 keyboard) or upload a ROM of your local storage (F5 keyboard).

I hope it worked out well and you can play your favorite games using your Atari emulador embedded.

## TODO
- Sends the Infrared (IR) commands from the Atari CX40 joystick to the emulator via IR Receiver connected to the ESP32 and decoded to the [Javatari.js](https://github.com/ppeccin/javatari.js) API. If you are using a USB joystick, you are probably already working with this emulator.

- Replace the joystick batteries (2x AAA 1.5v alkaline) with a cell phone rechargeable battery, approximately 3.3 to 5 volts.

## Credits
- Paulo Peccino ([@ppeccino](https://twitter.com/ppeccin)) for his amazing cross platform Atari 2600 emulator [Javatari.js](https://github.com/ppeccin/javatari.js).

- David Crane ([@PitfallCreator](https://twitter.com/pitfallcreator)) for his adorable Pitfall game
illustrated in the [picture 1](https://github.com/arcostasi/esp32-javatari-embedded/blob/master/doc/pic1.jpg?raw=true).

## Licence
This code source is signed under GNU AGPLv3, see license.txt distributed with this file.
