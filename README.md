# Arduino Core for Arancino nRF52 Boards
![Release](https://img.shields.io/github/v/release/smartmeio/arancino-core-nrf52?style=plastic)

This core is a fork of the [Adafruit nRF52 Arduino](https://github.com/adafruit/Adafruit_nRF52_Arduino) core modified to support the functionality of the Arancino architecture.

# Supported Boards
* Arancino Volante

## Installation on Arduino IDE

This core is available as a package in the Arduino IDE cores manager. If you want to install it:

  1. Open the **Preferences** of the Arduino IDE.
  2. Add this URL `https://raw.githubusercontent.com/smartmeio/arancino-boards/master/package_smartmeio_index.json` in the **Additional Boards Manager URLs** field, and click OK.
  3. Open the **Boards Manager** (menu `Tools` -> `Board` -> `Board Manager...`)
  4. Install **Arancino nRF52 Boards**
  5. Select one of the boards under **Arancino nRF52 Boards** in `Tools` -> `Board` menu

### Adafruit's nrfutil tools

[adafruit-nrfutil](https://github.com/adafruit/Adafruit_nRF52_nrfutil) (derived from Nordic [pc-nrfutil](https://github.com/NordicSemiconductor/pc-nrfutil)) is needed to upload sketch via serial port.

- For Windows and macOS, pre-built executable binaries are included in the BSP at `tools/adafruit-nrfutil/`. It should work out of the box.
- Linux user need to run follow command to install it from PyPi

```
$ pip3 install adafruit-nrfutil --user
```

## Installation on PlatformIO and Visual Studio Code
To create a project with Visual Studio Code and PlatformIO it is necessary to initially create a project for `Nordic nRF52-DK` and then modify the `platformio.ini` file in order to point to the Arancino packages. The `platformio.ini` file must be modififed in order to contains this configuration:
```
[env:arancino_volante]
platform = https://github.com/smartmeio/platform-nordicnrf52.git#9.4.0-arancino
board = arancino_volante
framework = arduino
platform_packages = smartme-io/framework-arduinoarancinonrf52@https://git.smartme.io/smartme.io/arancino/ide/arancino-nrf52-core.git
upload_port = ...
```
Any used library (e.g. Arancino library) must be included under the `lib` folder, so the project structure should look like:
```
include
lib
+-- your_library
     +-- examples
     +-- include
     +-- keywords.txt
     +-- library.json
     +-- src
src
+-- main.cpp
test
```

Alternatively, you can set an extra directory in which to search for libraries. For example, if you want to include all the libraries installed in the Arduino IDE, you can specify it adding this lines to the `platformio.ini` configuration file:
```
lib_extra_dirs = ~/Arduino/libraries
```

# Enabling FreeRTOS support
In nRF52-based boards FreeRTOS is enabled by default and cannot be disabled.

# Bootloader

Bootloader can be updated via UF2 file or DFU if already existed. Or flash on new blank chip using following guide

### Update Bootloader with UF2

This require existing bootloader version is at least 0.4.0:

- Quickly double tap reset button to put your board into bootloader mode. A mass storage device i.e `NRF52BOOT` will appear
- Download latest UF2 for your board i.e `arancino_volante_bootloader_s140_6.1.1.uf2`
- Drap and drop the UF2 file into `NRF52BOOT` drive to perform update then wait until the board reset.x

### Update Bootloader with DFU

To upgrade to the latest Bootloader + Softdevice using the serial port within Arduino IDE.

- Select `Tools -> Board -> Arancino nRF52 Board -> Arancino Volante`
- Select `Tools -> Programmer -> Bootloader DFU for Arancino nRF52`
- Select `Tools -> Burn Bootloader`
- **WAIT** until the process complete ~30 seconds

**Note: close the Serial Monitor before you click "Burn Bootloader". Afterwards, you shouldn't close the Arduino IDE, unplug the Feather, launch Serial Monitor etc ... to abort the process. There is a high chance it will brick your device! Do this with care and caution.**

### Burning new Bootloader

To burn the bootloader from within the Arduino IDE, you will need the following tools installed
on your system and available in the system path:

- Segger [JLink Software and Documentation Pack](https://www.segger.com/downloads/jlink)
- Nordic [nRF5x Command Line Tools](https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF-Command-Line-Tools)

Check to make sure you can run `nrfjprog` from your terminal/command prompt

**macOS Note** At present, you will need to create a symlink in `/usr/local/bin` to the
`nrfjprog` tool wherever you have added it. You can run the following command, for example:

```
$ ln -s $HOME/prog/nordic/nrfjprog/nrfjprog /usr/local/bin/nrfjprog
```

#### Manually Burning the Bootloader via nrfjprog

The bootloader hex file can be found at `bin/bootloader` run the command as follows:

```
$ nrfjprog -e -f nrf52
$ nrfjprog --program arancino_volante_bootloader_s140_6.1.1.hex -f nrf52
$ nrfjprog --reset -f nrf52
```
## Notes
**Important**: Since the introduction of FreeRTOS in the core, the code in the ``` loop() ```  function may not work properly, so we suggest implementing your code as a task.

## Credits

This core is based on [Arduino-nRF5](https://github.com/sandeepmistry/arduino-nRF5) by Sandeep Mistry,
which in turn is based on the [Arduino SAMD Core](https://github.com/arduino/ArduinoCore-samd).

The following libraries are used:

- [FreeRTOS](https://www.freertos.org/) as operating system
- [LittleFS](https://github.com/ARMmbed/littlefs) for internal file system
- [nrfx](https://github.com/NordicSemiconductor/nrfx) for peripherals driver
- [TinyUSB](https://github.com/hathach/tinyusb) as usb stack
