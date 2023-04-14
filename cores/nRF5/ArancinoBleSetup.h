#ifndef ArancinoBleSetup_h
#define ArancinoBleSetup_h

#include <bluefruit.h>

//All UUIDs are dummy
const uint8_t SERVICE_BLEUART_UUID_SERVICE[] = {
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1
};

const uint8_t SERVICE_BLEUART_UUID_CHR_RXD[] =
{
    0x9E, 0xCA, 0xDC, 0x24, 0x0E, 0xE5, 0xA9, 0xE0,
    0x93, 0xF3, 0xA3, 0xB5, 0x02, 0x00, 1, 1
};

const uint8_t SERVICE_BLEUART_UUID_CHR_TXD[] =
{
    0x9E, 0xCA, 0xDC, 0x24, 0x0E, 0xE5, 0xA9, 0xE0,
    0x93, 0xF3, 0xA3, 0xB5, 0x03, 0x00, 1, 1
};

BLEUart serviceUart = BLEUart(SERVICE_BLEUART_UUID_SERVICE, SERVICE_BLEUART_UUID_CHR_RXD, SERVICE_BLEUART_UUID_CHR_TXD);

void connect_callback(uint16_t conn_handle)
{
  // Get the reference to current connection
  BLEConnection* connection = Bluefruit.Connection(conn_handle);

  char central_name[32] = { 0 };
  connection->getPeerName(central_name, sizeof(central_name));
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;
  NVIC_SystemReset();
}

void serviceUart_rxCallback(uint16_t conn_handle){
  (void) conn_handle;
  char buff[21];
  int nbytes = serviceUart.read(buff, 20);

  //Get rid of EOF
  char cmd[20];
  memcpy(cmd, buff, nbytes);

  //Reset
  if(strcmp(cmd, "reset") == 0){
    NVIC_SystemReset();
  } 
}

void startAdv(BLEUart& bleuart)
{
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addService(bleuart);
  Bluefruit.Advertising.addService(serviceUart);
  Bluefruit.ScanResponse.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds  
}

void ArancinoBleSetup(BLEUart& bleuart, BLEDis& bledis, BLEDfu& bledfu){
  Bluefruit.autoConnLed(true);
  Bluefruit.configPrphBandwidth(BANDWIDTH_MAX);
  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);

  bledfu.begin();

  bledis.setManufacturer("SmartMe.IO");
  bledis.setModel("Arancino Volante");
  
  bleuart.begin();
  serviceUart.begin();
  serviceUart.setRxCallback(serviceUart_rxCallback);
  bledis.begin();

  startAdv(bleuart);

}

#endif