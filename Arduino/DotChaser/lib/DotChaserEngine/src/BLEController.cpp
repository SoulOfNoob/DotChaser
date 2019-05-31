/**
 * Project DCEngine
 * @author Jan Ryklikas
 * @version 0.1
 */


#include "BLEController.h"

/**
 * BLEController implementation
 */

int BLEController::connectionCount = 0;
bool BLEController::doConnect = false;
bool BLEController::doScan = true;
BLEAdvertisedDevice* BLEController::myDevice;
String BLEController::deviceName = "JDY-09-V4.3";
BLEUUID BLEController::serviceUUID = BLEUUID::fromString("0000FFE0-0000-1000-8000-00805F9B34FB");
BLEUUID BLEController::charUUID = BLEUUID::fromString("0000FFE1-0000-1000-8000-00805F9B34FB");

BLERemoteCharacteristic*  BLEController::connections[MAX_CONNECTIONS];
void (*BLEController::buttonCB)(int buttonID);

BLEController::BLEController() {

}

void BLEController::init(void (*callback)(int)) {
  buttonCB = callback;
  //Serial.begin(115200);
  Serial.println("Starting Arduino BLE Client application...");
  //BLEDevice::init("ESP32");
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);
}

// public methods
// maybe put this into engine and provide callback functions to BLEController
void BLEController::notifyCallback( BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
    Serial.print("data: ");
    Serial.println((char*)pData);

    for( int i = 0 ; i <= MAX_CONNECTIONS ; i++ ) {
      if(connections[i] == pBLERemoteCharacteristic) {
        Serial.print("Device Number: ");
        Serial.println(i);
        buttonCB(i);
      }
    }
}

void BLEController::scanCompleteCB(BLEScanResults results) {
    Serial.println("Scan Complete.");
}

bool BLEController::connectToServer() {
  Serial.print("Forming a connection to ");
  Serial.println(myDevice->getAddress().toString().c_str());

  BLEClient* pClient = BLEDevice::createClient();
  Serial.println(" - Created client");

  pClient->setClientCallbacks(new MyClientCallback());

  // Connect to the remove BLE Server.
  pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
  Serial.println(" - Connected to device");

  // Obtain a reference to the service we are after in the remote BLE server.
  BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr) {
  Serial.print("Failed to find our service UUID: ");
  Serial.println(serviceUUID.toString().c_str());
  pClient->disconnect();
  return false;
  }
  Serial.println(" - Found our service");

  // Obtain a reference to the characteristic in the service of the remote BLE server.
  BLERemoteCharacteristic* pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
  connections[connectionCount] = pRemoteService->getCharacteristic(charUUID);
  if (pRemoteCharacteristic == nullptr) {
  Serial.print("Failed to find our characteristic UUID: ");
  Serial.println(charUUID.toString().c_str());
  pClient->disconnect();
  return false;
  }
  Serial.println(" - Found our characteristic");

  if(pRemoteCharacteristic->canNotify()) pRemoteCharacteristic->registerForNotify(notifyCallback);
}

void BLEController::loop() {
  if (doConnect) {
    if (connectToServer()) {
      Serial.println("We are now connected to the BLE Server.");
      if(connectionCount <= MAX_CONNECTIONS) connectionCount++;
    } else {
      Serial.println("We have failed to connect to the server; there is nothin more we will do.");
    }
    doConnect = false;
  }
  if(doScan && connectionCount < MAX_CONNECTIONS) {
    Serial.println("Restarting scan");
    BLEDevice::getScan()->start(3, false);
  } else if(doScan) {
    Serial.println("Stopping scan");
    doScan = false;
  }
}

void MyClientCallback::onConnect(BLEClient* pclient) {
  Serial.println("onConnect");
  //doScan = false;
}

void MyClientCallback::onDisconnect(BLEClient* pclient) {
  Serial.println("onDisconnect");
  BLEController::connectionCount = 0;
  BLEController::doScan = true;
  //if(connectionCount > 0) connectionCount--;
}

void MyAdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice) {
  // We have found a device, let us now see if it contains the service and name we are looking for.
  if (advertisedDevice.haveName() && advertisedDevice.getName() == BLEController::deviceName.c_str() && advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(BLEController::serviceUUID)) {
    Serial.print("Correct ");
    BLEDevice::getScan()->stop();
    BLEController::myDevice = new BLEAdvertisedDevice(advertisedDevice);
    BLEController::doConnect = true;
  } // Found our server
  Serial.print("BLE Device found: ");
  Serial.println(advertisedDevice.toString().c_str());
} // onResult
