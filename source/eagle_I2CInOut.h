//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 21.05.2018 05:40:11
#ifndef EAGLE_EBOARD_HELPLIB_I2CINOUT
#define EAGLE_EBOARD_HELPLIB_I2CINOUT

    


//=====================================================================================================================================================
//                                                                  Macro Definitions                                                                  
//=====================================================================================================================================================

	//To avoid not_found issues
	

	#define DIGITAL_IN            0x0
	

	#define DIGITAL_IN_INV        0x1
	

	#define DIGITAL_IN_PULLUP     0x2
	

	#define DIGITAL_IN_PULLUP_INV 0x3
	

	#define DIGITAL_OUT           0x4
	

	#define DIGITAL_OUT_INV       0x5
	

	#define DIGITAL_OUT_LOW       0x6
	

	#define DIGITAL_OUT_HIGH      0x7
	

	#define ANALOG_IN_8_BIT       0x8
	

	#define ANALOG_IN_10_BIT      0x9
	

	#define ANALOG_IN_MEAN_8_BIT  0xA
	

	#define ANALOG_IN_MEAN_10_BIT 0xB
	

	#define COUNTER_8_BIT         0xC
	

	#define COUNTER_16_BIT        0xD
	

	#define COUNTER_RISE_8_BIT    0xE
	

	#define COUNTER_RISE_16_BIT   0xF
	

	#define PWM_SLOW              0x8
	

	#define PWM_FAST              0x9
	

	#define FREQ_LOW              0xA
	

	#define FREQ_HIGH             0xB
	

	#define COUNTER_B_DIR         0xC
	

	#define COUNTER_B_DIR_PULLUP  0xD
	

	#define COUNTER_MEAN_8_BIT    0xE
	

	#define COUNTER_MEAN_16_BIT   0xF

//=====================================================================================================================================================
//                                                                      I2CInOut                                                                       
//=====================================================================================================================================================

    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                    class                                                                        
    //-------------------------------------------------------------------------------------------------------------------------------------------------

	

	struct I2CInOut{
	    

	    I2CInOut(SoccerBoard&, optVAL_t, optVAL_t, optVAL_t, optVAL_t);
	    #if EBOARD_USE_UTILITY > 0x0
	        

	        inline void read(void);
	        

	        inline void changeAddress(optVAL_t);
	        

	        inline void changeModes(optVAL_t,optVAL_t,optVAL_t);
	    #endif
	    

	    inline void write(void);

	    

	    optVAL_t A; //if you've used uint16_t values you'll have to replace it here
	    //we only have B - DiOut and C - AO [OUT]
	    

	    optVAL_t B;
	    

	    optVAL_t C;
	};

	


    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                definitions                                                                      
    //-------------------------------------------------------------------------------------------------------------------------------------------------

	I2CInOut::I2CInOut(SoccerBoard&, optVAL_t, optVAL_t, optVAL_t, optVAL_t) {
	    this->A=0x0;this->B=0x0;this->C=0x0;
	}
	#if EBOARD_USE_UTILITY > 0x0
	    void I2CInOut::read(void) {}
	    void I2CInOut::changeAddress(optVAL_t){}
	    void I2CInOut::changeModes(optVAL_t,optVAL_t,optVAL_t) {}
	#endif
	void I2CInOut::write(void){
	    setPin(PIN_MOTOR_DIR,((this->B)!=0x0));
	    writePWM(this->C);
	}
	

#endif
