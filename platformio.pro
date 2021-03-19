
win32 {
    HOMEDIR += $$(USERPROFILE)
}
else {
    HOMEDIR += $$(HOME)
}

INCLUDEPATH += "$${HOMEDIR}/radio/GMSK_Receive/include"
INCLUDEPATH += "$${HOMEDIR}/radio/GMSK_Receive/src"
INCLUDEPATH += "$${HOMEDIR}/radio/GMSK_Receive/.pio/libdeps/ttgo-t-beam/AXP202X_Library/src"
INCLUDEPATH += "$${HOMEDIR}/radio/GMSK_Receive/.pio/libdeps/ttgo-t-beam/TinyGPSPlus/src"
INCLUDEPATH += "$${HOMEDIR}/radio/GMSK_Receive/.pio/libdeps/ttgo-t-beam/Time"
INCLUDEPATH += "$${HOMEDIR}/radio/GMSK_Receive/.pio/libdeps/ttgo-t-beam/ESP8266 and ESP32 OLED driver for SSD1306 displays/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/Wire/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/BluetoothSerial/src"
INCLUDEPATH += "$${HOMEDIR}/radio/GMSK_Receive/lib/BitMatcher"
INCLUDEPATH += "$${HOMEDIR}/radio/GMSK_Receive/lib/BitSlicer"
INCLUDEPATH += "$${HOMEDIR}/radio/GMSK_Receive/.pio/libdeps/ttgo-t-beam/Streaming"
INCLUDEPATH += "$${HOMEDIR}/radio/GMSK_Receive/.pio/libdeps/ttgo-t-beam/RadioLib/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/SPI/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/config"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/app_trace"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/app_update"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/asio"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/bootloader_support"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/bt"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/coap"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/console"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/driver"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/esp-tls"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/esp32"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/esp_adc_cal"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/esp_event"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/esp_http_client"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/esp_http_server"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/esp_https_ota"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/esp_ringbuf"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/ethernet"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/expat"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/fatfs"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/freemodbus"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/freertos"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/heap"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/idf_test"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/jsmn"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/json"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/libsodium"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/log"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/lwip"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/mbedtls"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/mdns"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/micro-ecc"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/mqtt"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/newlib"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/nghttp"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/nvs_flash"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/openssl"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/protobuf-c"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/protocomm"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/pthread"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/sdmmc"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/smartconfig_ack"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/soc"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/spi_flash"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/spiffs"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/tcp_transport"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/tcpip_adapter"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/ulp"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/vfs"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/wear_levelling"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/wifi_provisioning"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/wpa_supplicant"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/xtensa-debug-module"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/esp-face"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/esp32-camera"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/tools/sdk/include/fb_gfx"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/cores/esp32"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/variants/t-beam"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/ArduinoOTA/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/AsyncUDP/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/AzureIoT/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/BLE/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/DNSServer/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/EEPROM/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/ESP32/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/ESPmDNS/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/FFat/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/FS/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/HTTPClient/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/HTTPUpdate/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/NetBIOS/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/Preferences/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/SD/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/SD_MMC/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/SPIFFS/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/SimpleBLE/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/Ticker/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/Update/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/WebServer/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/WiFi/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif32/libraries/WiFiClientSecure/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-xtensa32/xtensa-esp32-elf/include/c++/5.2.0"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-xtensa32/xtensa-esp32-elf/include/c++/5.2.0/xtensa-esp32-elf"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-xtensa32/lib/gcc/xtensa-esp32-elf/5.2.0/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-xtensa32/lib/gcc/xtensa-esp32-elf/5.2.0/include-fixed"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-xtensa32/xtensa-esp32-elf/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/tool-unity"

DEFINES += "PLATFORMIO=50003"
DEFINES += "ARDUINO_T_Beam"
DEFINES += "BOARD_HAS_PSRAM"
DEFINES += "ESP32"
DEFINES += "ESP_PLATFORM"
DEFINES += "F_CPU=240000000L"
DEFINES += "HAVE_CONFIG_H"
DEFINES += "MBEDTLS_CONFIG_FILE=&quot;mbedtls/esp_config.h&quot;"
DEFINES += "ARDUINO=10805"
DEFINES += "ARDUINO_ARCH_ESP32"
DEFINES += "ARDUINO_VARIANT=&quot;t-beam&quot;"
DEFINES += "ARDUINO_BOARD=&quot;TTGO T-Beam&quot;"

OTHER_FILES += platformio.ini

SOURCES += src/main.cpp

CONFIG += c++11
