//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 18.04.2018 23:34:37
#include <assert.h>
void __assert (const char *__func, const char *__file, optVAL_t __lineno, const char *__sexp);
void __assert (const char *__func, const char *__file, optVAL_t __lineno, const char *__sexp){
    Serial.print("Error with: "); Serial.print(__func);
    Serial.print(" in "); Serial.print(__file);
    Serial.print("         >>");
    Serial.println(__sexp);
    if(strcmp(__func,"checkIdx")==0){
        Serial.println("   This happens if an out of bounds exception");
        Serial.println("   has occured. Following pins shouldn't be used:");
        Serial.print("   D" + PIN_BLUETOOTH_RX);Serial.print("&");
        Serial.print("D");Serial.print(PIN_BLUETOOTH_TX);
        Serial.println(" : Used for Bluetooth communication");
        Serial.print("   D");Serial.print(PIN_MOTOR_DIR);Serial.print("&");
        Serial.print("D");Serial.print(PIN_MOTOR_SPE);
        Serial.println(" : Used for main motor control");
        #if EBOARD_USE_SPI > 0x0
            Serial.print("   D10-13");
            Serial.println(": Used for smart-servo-shield");
        #endif
    } else if (strcmp(__func,"readPin")==0){
        Serial.println("You've tried to access an analogPin that isn't present on the board you're currently working on!");
    }
    Serial.flush();
    abort(); // halt after outputting information
}
