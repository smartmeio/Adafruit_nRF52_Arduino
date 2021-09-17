 /*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.
  Copyright (c) 2016 Sandeep Mistry All right reserved.
  Copyright (c) 2018, Adafruit Industries (adafruit.com)

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _VARIANT_ARANCINO_VOLANTE_
#define _VARIANT_ARANCINO_VOLANTE_

/** Master clock frequency */
#define VARIANT_MCK       (64000000ul)

#define USE_LFXO      // Board uses 32khz crystal for LF
// define USE_LFRC    // Board uses RC for LF

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

// Number of pins defined in PinDescription array
#define PINS_COUNT           (31)
#define NUM_DIGITAL_PINS     (31)
#define NUM_ANALOG_INPUTS    (6)
#define NUM_ANALOG_OUTPUTS   (0)

// LEDs
#define PIN_LED1             (10)
#define PIN_LED2_RED         (8)
#define PIN_LED2_GREEN       (7)
#define PIN_LED2_BLUE        (11)

#define LED_BUILTIN          PIN_LED1
#define LED_CONN             PIN_LED2

#define LED_RED              PIN_LED2_RED
#define LED_BLUE             PIN_LED2_BLUE
#define LED_GREEN            PIN_LED2_GREEN

#define LED_STATE_ON         0         // State when LED is litted

/*
 * Buttons
 */
#define PIN_BUTTON1          11
#define PIN_BUTTON2          12

/*
 * Analog pins
 */
#define PIN_A0               (3)
#define PIN_A1               (4)
#define PIN_A2               (28)
#define PIN_A3               (29)
#define PIN_A4               (30)
#define PIN_A5               (31)

static const uint8_t A0  = PIN_A0 ;
static const uint8_t A2  = PIN_A2 ;
static const uint8_t A4  = PIN_A4 ;

#define ADC_RESOLUTION    12

// Other pins
// #define PIN_AREF           (2)
// #define PIN_NFC1           (9)
// #define PIN_NFC2           (10)

// static const uint8_t AREF = PIN_AREF;

/*
 * Serial interfaces
 */

// Arduino Header D0, D1
#define PIN_SERIAL1_RX      (0) // P0.13
#define PIN_SERIAL1_TX      (1) // P0.15


/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 1

#define PIN_SPI_MISO         (22)
#define PIN_SPI_MOSI         (23)
#define PIN_SPI_SCK          (24)

static const uint8_t SS   = 9 ;
static const uint8_t MOSI = PIN_SPI_MOSI ;
static const uint8_t MISO = PIN_SPI_MISO ;
static const uint8_t SCK  = PIN_SPI_SCK ;

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 1

#define PIN_WIRE_SDA         (20)
#define PIN_WIRE_SCL         (21)

// static const uint8_t SDA = PIN_WIRE_SDA;
// static const uint8_t SCL = PIN_WIRE_SCL;

// QSPI Pins
// #define PIN_QSPI_SCK         19
// #define PIN_QSPI_CS          17
// #define PIN_QSPI_IO0         20
// #define PIN_QSPI_IO1         21
// #define PIN_QSPI_IO2         22
// #define PIN_QSPI_IO3         23

// On-board QSPI Flash
//#define EXTERNAL_FLASH_DEVICES   MX25R6435F
//#define EXTERNAL_FLASH_USE_QSPI

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#endif
