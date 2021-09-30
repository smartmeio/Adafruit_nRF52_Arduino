# Arduino Core for Arancino nRF52 Boards

Following board are included:

- [Arancino Volante](https://arancino.cc)

## BSP Installation

There are two methods that you can use to install this BSP. We highly recommend the first option unless you wish to participate in active development of this codebase via Github.

### Arancino nRF52 BSP via the Arduino Board Manager

 1. [Download and install the Arduino IDE](https://www.arduino.cc/en/Main/Software)
 2. Start the Arduino IDE
 3. Go into Preferences
 4. Add https://git.smartme.io/smartme.io/arancino/arduino/smartmeio-package-index/raw/dev/package_smartmeio_index.json as an 'Additional Board Manager URL'
 5. Open the Boards Manager from the Tools -> Board -> Board Manager menu and install 'Arancino nRF52 Boards'
 6. Once the BSP is installed, select 'Arancino Volante' from the Tools -> Board -> Arancino nRF52 Boards menu, which will update your system config to use the right compiler and settings for the nRF52.


### Adafruit's nrfutil tools

[adafruit-nrfutil](https://github.com/adafruit/Adafruit_nRF52_nrfutil) (derived from Nordic [pc-nrfutil](https://github.com/NordicSemiconductor/pc-nrfutil)) is needed to upload sketch via serial port.

- For Windows and macOS, pre-built executable binaries are included in the BSP at `tools/adafruit-nrfutil/`. It should work out of the box.
- Linux user need to run follow command to install it from PyPi

```
$ pip3 install adafruit-nrfutil --user
```

## Bootloader

Bootloader can be updated via UF2 file or DFU if already existed. Or flash on new blank chip using following guide

### Update Bootloader with UF2

This require existing bootloader version is at least 0.4.0:

- Quickly double tap reset button to put your board into bootloader mode. A mass storage device i.e `NRF52BOOT` will appear
- Download latest UF2 for your board i.e `arancino_volante_bootloader_s140_6.1.1.uf2`
- Drap and drop the UF2 file into `NRF52BOOT` drive to perform update then wait until the board reset.x

### Update Bootloader with DFU

To upgrade to the latest Bootloader + Softdevice using the serial port within Arduino IDE.

- Select `Tools -> Board -> Arancino nRF52 Board -> Arancino Volante`
- Select `Tools -> Programmer -> Bootloader DFU for Bluefruit nRF52`
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

## Credits

This core is based on [Arduino-nRF5](https://github.com/sandeepmistry/arduino-nRF5) by Sandeep Mistry,
which in turn is based on the [Arduino SAMD Core](https://github.com/arduino/ArduinoCore-samd).

The following libraries are used:

- [FreeRTOS](https://www.freertos.org/) as operating system
- [LittleFS](https://github.com/ARMmbed/littlefs) for internal file system
- [nrfx](https://github.com/NordicSemiconductor/nrfx) for peripherals driver
- [TinyUSB](https://github.com/hathach/tinyusb) as usb stack
