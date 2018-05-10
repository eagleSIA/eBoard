//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 10.05.2018 16:26:20
#ifndef EAGLE_EBOARD_HELPLIB_SHIFTEXT
    #define EAGLE_EBOARD_HELPLIB_SHIFTEXT

    


//=====================================================================================================================================================
//                                                                   Shift extension                                                                   
//=====================================================================================================================================================

    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                  variables                                                                      
    //-------------------------------------------------------------------------------------------------------------------------------------------------

	

	long store_bits = 0L;

    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                 shift single                                                                    
    //-------------------------------------------------------------------------------------------------------------------------------------------------

	

	void shiftSingle(optVAL_t idx, bool val);

    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                  shift all                                                                      
    //-------------------------------------------------------------------------------------------------------------------------------------------------

	

	void shiftAll(void);

    

        void shiftSingle(optVAL_t idx, bool val) {
                bitWrite(store_bits,idx,val);
                shiftAll();
            }
        void shiftAll(void){
            digitalWrite(PIN_SHIFT_LAT,LOW);
            for(optVAL_t c = 0; (c<32 && !STOP); c++){
                digitalWrite(PIN_SHIFT_CLK,LOW);
                shiftOut(PIN_SHIFT_DAT,PIN_SHIFT_CLK,MSBFIRST,bitRead(store_bits,c));
            }
            digitalWrite(PIN_SHIFT_LAT,LOW);
        }
    

    
#endif
