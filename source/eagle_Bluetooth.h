//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 27.04.2018 20:00:37
#ifndef EAGLE_EBOARD_HELPLIB_BLUETOOTH
#define EAGLE_EBOARD_HELPLIB_BLUETOOTH
inline char readVal(char oF = '.');
inline bool checkOverflow(void);
template <typename T>
    inline void writeVal(const T& val);
inline bool isConnected(void);
inline bool checkOverflow(void) {
        #if (EBOARD_BLUETOOTH > 0x0) && (((PIN_BLUETOOTH_RX==0x13) && (PIN_BLUETOOTH_TX==0x12)) && defined(__AVR_ATmega2560__))
            return false; //there is no hardware provided control for hardwareserial overflow
        #else
            return (_serial.overflow());
        #endif
    }
    inline char readVal(char oF) {
        #if (EBOARD_BLUETOOTH > 0x0) && (((PIN_BLUETOOTH_RX==0x13) && (PIN_BLUETOOTH_TX==0x12)) && defined(__AVR_ATmega2560__))
            return ((Serial1.available())?(Serial1.read()):(oF));
        #else
            return ((_serial.available())?(_serial.read()):(oF));
        #endif
    }
    template<typename T>
    inline void writeVal(const T& val){
        #if (EBOARD_BLUETOOTH > 0x0) && (((PIN_BLUETOOTH_RX==0x13) && (PIN_BLUETOOTH_TX==0x12)) && defined(__AVR_ATmega2560__))
            Serial1.write(val);
        #else
            _serial.write(val);
        #endif
    }
    inline bool isConnected(void) {
        #if PIN_BLUETOOTH_RX != PIN_BLUETOOTH_STATE
            return digitalRead(PIN_BLUETOOTH_STATE);
        #else
            return true;
        #endif
    }
#endif