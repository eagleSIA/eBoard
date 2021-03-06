//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 22.06.2018 00:28:45
#ifndef EAGLE_EBOARD_HELPLIB_PINCTRL
    #define EAGLE_EBOARD_HELPLIB_PINCTRL

    


//=====================================================================================================================================================
//                                                                     Pin control                                                                     
//=====================================================================================================================================================

    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                  variables                                                                      
    //-------------------------------------------------------------------------------------------------------------------------------------------------

	

	optVAL_t _pwmValue = 0x0, _OpwmValue = 0x0;

    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                     PWM                                                                         
    //-------------------------------------------------------------------------------------------------------------------------------------------------

	

	inline void writePWM (optVAL_t val);

	

	inline void writePWM(optVAL_t val){
	    val = min(val,0xFF); val = max(0x0,val);
	    _pwmValue = val;
	}
	


    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                    write                                                                        
    //-------------------------------------------------------------------------------------------------------------------------------------------------

	

	inline void writePin(optVAL_t idx,bool val);

	

	inline void writePin(optVAL_t idx,bool val){
	    #if EBOARD_SHIFT_REGISTER > 0x0
	        if(idx>0x63) {
	            idx -= 0x64;
	            shiftSingle(idx,val);
	            return;
	        }
	    #endif
	    #if EBOARD_CHECK_PINS > 0x0
	        checkIdx(idx);
	        if(!checkPin(idx))
	    #endif
        setPin(idx);
	    digitalWrite(idx,val);
	}

    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                    read1                                                                        
    //-------------------------------------------------------------------------------------------------------------------------------------------------

	

	

	inline optVAL_t readPin(optVAL_t idx,bool dig = true);

	

	inline optVAL_t readPin(optVAL_t idx,bool dig){
	    #if EBOARD_CHECK_PINS > 0x0
	        if(dig) checkIdx(idx);
	        #if defined (__AVR_ATmega2560__)
	            else if (idx<0||idx>0xF){ //use I2C? change => Wire
	        #else
	            else if (idx<0||idx>0x7){ //use I2C? change => Wire
	        #endif
	        #if EBOARD_DEBUG_MODE > 0x0
	          assert(false);
	        #endif
	        return 0;
	        }
	        if(dig && !checkPin(idx,INPUT))
	    #endif
	        setPin(idx,INPUT);

	    return((dig)? digitalRead(idx) : analogRead(idx));
	}
	

#endif
