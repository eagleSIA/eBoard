//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 04.05.2018 22:38:04
#ifndef EAGLE_EBOARD_HELPLIB_BLUETOOTH
    #define EAGLE_EBOARD_HELPLIB_BLUETOOTH

    


//=====================================================================================================================================================
//                                                                      bluetooth                                                                      
//=====================================================================================================================================================

    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                    read1                                                                        
    //-------------------------------------------------------------------------------------------------------------------------------------------------

    

    inline char readVal(char oF = '.');

    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                   overflow                                                                      
    //-------------------------------------------------------------------------------------------------------------------------------------------------

    

    inline bool checkOverflow(void);

    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                    send1                                                                        
    //-------------------------------------------------------------------------------------------------------------------------------------------------

    

    template <typename T>
    inline void writeVal(const T& val);

    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                  connected                                                                      
    //-------------------------------------------------------------------------------------------------------------------------------------------------

    

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
