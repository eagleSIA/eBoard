//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 22.06.2018 00:28:45
#ifndef EAGLE_EBOARD_HELPLIB_CHECKS
    #define EAGLE_EBOARD_HELPLIB_CHECKS
    
    


//=====================================================================================================================================================
//                                                                       Checker                                                                       
//=====================================================================================================================================================

    


	using namespace eagle_impl;

    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                 check index                                                                     
    //-------------------------------------------------------------------------------------------------------------------------------------------------

	

	void checkIdx(optVAL_t idx);

    

        void checkIdx(optVAL_t idx){
            #if EBOARD_DEBUG_MODE > 0x0
                assert(idx>=0x0 && idx < PIN_MAX); //changed pins? change me! (didn't want to use macros)
                assert(idx!=PIN_BLUETOOTH_RX&&idx!=PIN_BLUETOOTH_TX);
            #endif
        }
    


	    #if EBOARD_CHECK_PINS_PWM > 0x0

    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                count SET bit                                                                    
    //-------------------------------------------------------------------------------------------------------------------------------------------------

	        

	        optVAL_t countSetBits (optVAL_t x);

            

                optVAL_t countSetBits (optVAL_t x) {
                    optVAL_t count; //dont't want to overuse global space^^
                    for (count = 0; x; count++)
                        x &= x - 1;
                    return count;
                }
            

	    #endif

    #if EBOARD_CHECK_PINS > 0x0

    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                  variables                                                                      
    //-------------------------------------------------------------------------------------------------------------------------------------------------

        

        #if defined(__AVR_ATmega328P__) && not defined(__AVR_ATmega2560__)
            uint16_t pin_out = 0x0;
        #elif defined(__AVR_ATmega2560__)
            uint64_t pin_out = 0x0;
        #endif
        

        #if defined(__AVR_ATmega328P__) && not defined(__AVR_ATmega2560__)
            uint16_t pin_in = 0x0;
        #elif defined(__AVR_ATmega2560__)
            uint64_t pin_in = 0x0;
        #endif

    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                  pin check                                                                      
    //-------------------------------------------------------------------------------------------------------------------------------------------------

        

        bool checkPin(optVAL_t idx, optVAL_t mode = OUTPUT);

        

            bool checkPin(optVAL_t idx, optVAL_t mode){
                checkIdx(idx);
                return (mode == OUTPUT)? ((pin_out & (1<<idx))>0x0):((pin_in & (1<<idx))>0x0);
            }
        


    #endif

    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                  set  pins                                                                      
    //-------------------------------------------------------------------------------------------------------------------------------------------------

    

    void setPin(optVAL_t idx, optVAL_t mode = OUTPUT);

    

        void setPin(optVAL_t idx, optVAL_t mode){
            #if EBOARD_CHECK_PINS > 0x0
                checkIdx(idx);
                if(checkPin(idx,mode)) return;
                if(mode==OUTPUT) {  //possible to read from OUTPUT digital ... we won't do it
                    pin_out |=  (1<<idx);
                    pin_in  &=  ~(1<<idx);
                }
                else {
                    pin_in  |= (1<<idx);
                    pin_out &= ~(1<<idx);
                }
            #endif
            pinMode(idx, mode);
        }
    


	#endif

