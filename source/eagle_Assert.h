//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 21.05.2018 05:40:11
#ifndef EAGLE_EBOARD_HELPLIB_ASSERT
	#define EAGLE_EBOARD_HELPLIB_ASSERT

    


//=====================================================================================================================================================
//                                                                       _assert                                                                       
//=====================================================================================================================================================

	#include <assert.h>
	

	void __assert (const char *func_call, const char *file_call, optVAL_t lineno_call, const char *sexp_call);

    

    void __assert (const char *func_call, const char *file_call, optVAL_t lineno_call, const char *sexp_call){
	    Serial.print("Error with: "); Serial.print(func_call);
	    Serial.print(" in "); Serial.print(file_call);
	    Serial.print("         >>");
	    Serial.println(sexp_call);
	    if(strcmp(func_call,"checkIdx")==0){
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
	    } else if (strcmp(func_call,"readPin")==0){
	        Serial.println("You've tried to access an analogPin that isn't present on the board you're currently working on!");
	    }
	    Serial.flush();
	    abort(); // halt after outputting information
	}
	


#endif
