/**
 * Project DCEngine
 * @author Jan Ryklikas
 * @version 0.1
 */

#ifndef _BLECONTROLLER_H
#define _BLECONTROLLER_H

  #define MAX_CONNECTIONS 2

  #include <Arduino.h>
  #include <BLEDevice.h>

  class BLEController {
    public:
      BLEController();

      static void init();

      // public variables
      int                             weird;
      static int                      connectionCount;
      static boolean                  doConnect;
      static boolean                  doScan;

      static String                   deviceName;
      static BLEUUID                  serviceUUID;
      static BLEUUID                  charUUID;

      static BLERemoteCharacteristic* connections[MAX_CONNECTIONS];
      static BLEAdvertisedDevice*     myDevice;

      // public methods
      static void notifyCallback( BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify);
      static void scanCompleteCB(BLEScanResults results);
      static bool connectToServer();
      static void loop();
  };

  class MyClientCallback : public BLEClientCallbacks {
    void onConnect(BLEClient* pclient);
    void onDisconnect(BLEClient* pclient);
  };

  class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice);
  };

#endif //_BLECONTROLLER_H
