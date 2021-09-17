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

#include "variant.h"
#include "wiring_constants.h"
#include "wiring_digital.h"
#include "nrf.h"

#include "variant.h"
#include "wiring_constants.h"
#include "wiring_digital.h"
#include "nrf.h"

const uint32_t g_ADigitalPinMap[] =
{
  // D0 .. D13
  13,  // D0  is P0.13 (UART TX)
  15,  // D1  is P0.15 (UART RX)
  47,  // D2  is P1.15
   0,  // D3  not expose
  45,  // D4  is P1.13
  42,  // D5  is P1.10
  38,  // D6 SW1
  41,  // D7 LD2 GREEN
   8,  // D8 LD2 RED
  24,  // D9 CS
   6,  // LD1 GREEN
  12,  // D11 LD2 BLUE
   0,  // D12 not expose
   0,  // D13 not expose

  // D14 .. D21 (aka A0 .. A7)
  31,  // D14 is P0.31 (A0 - DAC)
   0,  // D15 not expose
  29,  // D16 is P0.29 (A2)
   0,  // D17 not expose
   2,  // D18 is P0.02 (A4)
   0,  // D19 not expose

  //D20 .. D21 (aka I2C pins)
  20, // D20 is P0.20 (SDA)
  17,  // D21 is P0.17 (SCL)

  // // D22 .. D24 (aka SPI pins)
   9,  // D24 is P0.15 (SPI MISO)
  10,  // D25 is P0.13 (SPI MOSI)
  32   // D26 is P1.00 (SPI SCK )

  // // QSPI pins (not exposed via any header / test point)
  // 19,  // D27 is P0.19 (QSPI CLK)
  // 20,  // D28 is P0.20 (QSPI CS)
  // 17,  // D29 is P0.17 (QSPI Data 0)
  // 22,  // D30 is P0.22 (QSPI Data 1)
  // 23,  // D31 is P0.23 (QSPI Data 2)
  // 21,  // D32 is P0.21 (QSPI Data 3)

  // The remaining NFC pin
  // 9,  // D33 is P0.09 (NFC1, exposed only via test point on bottom of board)

  // Thus, there are 34 defined pins

  // The remaining pins are not usable:
  //
  //
  // The following pins were never listed as they were considered unusable
  //  0,      // P0.00 is XL1   (attached to 32.768kHz crystal)
  //  1,      // P0.01 is XL2   (attached to 32.768kHz crystal)
  // 18,      // P0.18 is RESET (attached to switch)
  // 32,      // P1.00 is SWO   (attached to debug header)
  //
  // The remaining pins are not connected (per schematic)
  // 33,      // P1.01 is not connected per schematic
  // 35,      // P1.03 is not connected per schematic
  // 36,      // P1.04 is not connected per schematic
  // 37,      // P1.05 is not connected per schematic
  // 38,      // P1.06 is not connected per schematic
  // 39,      // P1.07 is not connected per schematic
  // 43,      // P1.11 is not connected per schematic
  // 44,      // P1.12 is not connected per schematic
  // 45,      // P1.13 is not connected per schematic
  // 46,      // P1.14 is not connected per schematic
};


void initVariant()
{

  if (NRF_POWER->MAINREGSTATUS & (POWER_MAINREGSTATUS_MAINREGSTATUS_High << POWER_MAINREGSTATUS_MAINREGSTATUS_Pos)){
    if ((NRF_UICR->REGOUT0 & UICR_REGOUT0_VOUT_Msk) == (UICR_REGOUT0_VOUT_DEFAULT << UICR_REGOUT0_VOUT_Pos)){
       NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen;
       while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}

       NRF_UICR->REGOUT0 = (NRF_UICR->REGOUT0 & ~((uint32_t)UICR_REGOUT0_VOUT_Msk)) |
                           (UICR_REGOUT0_VOUT_3V0 << UICR_REGOUT0_VOUT_Pos);

       NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
       while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}

       // System reset is needed to update UICR registers.
       NVIC_SystemReset();
     }
  }else{
     if (NRF_UICR->REGOUT0 != UICR_REGOUT0_VOUT_1V8) {
       NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;    //write enable
       while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
       NRF_UICR->REGOUT0 = UICR_REGOUT0_VOUT_1V8;                        //configurate REGOUT0
       NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
       while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
       NVIC_SystemReset();                                               // Reset device
     }
   }

   // init all 4 onboard LEDs
    pinMode(PIN_LED1, OUTPUT);
    ledOff(PIN_LED1);

    pinMode(LED_RED, OUTPUT);
    ledOff(LED_RED);

    pinMode(LED_GREEN, OUTPUT);
    ledOff(LED_GREEN);

    pinMode(LED_BLUE, OUTPUT);
    ledOff(LED_BLUE);
 }
