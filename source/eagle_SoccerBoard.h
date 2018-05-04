//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 04.05.2018 22:38:04
#ifndef EAGLE_EBOARD_HELPLIB_SOCCERBOARD
    #define EAGLE_EBOARD_HELPLIB_SOCCERBOARD

    


//=====================================================================================================================================================
//                                                                     SoccerBoard                                                                     
//=====================================================================================================================================================

    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                    class                                                                        
    //-------------------------------------------------------------------------------------------------------------------------------------------------

	

	struct SoccerBoard {
	    

	    inline SoccerBoard(void);
	    //inline ~SoccerBoard(void) {}
	    #if EBOARD_USE_UTILITY > 0x0 or defined(__AVR_ATmega2560__) //won't shrink space... just speed things up
	        

	        inline void led(int idx,bool state);
	        

	        inline void ledOn(int idx);
	        

	        inline void ledOff(int idx);
	        

	        inline void ledsOff(void);
	        

	        inline void ledMeter(int);

	    #endif
	    #if EBOARD_USE_UTILITY > 0x0
	        

	        inline void 
 button(int);
	        

	        inline void waitForButton(int);
	    #endif
	    

	    void motor(uint8_t id,int16_t val);
	    

	    void motorsOff(void);
	    //ARDUINO UNO PINOUT
	    //D0,D1   => Bluetooth connection
	    //D4,D5   => MotorControl (D5: 980Hz)
	    //D10,D13 => SPI

	    

	    inline void power(optVAL_t id, bool state);
	    

	    inline void powerOn(optVAL_t id);
	    

	    inline void powerOff(optVAL_t id);
	    

	    inline void sleep(uint16_t t);
	    

	    inline void msleep(uint16_t t);
	    

	    inline bool digital (optVAL_t id);
	    

	    inline optVAL_t  analog (optVAL_t id);
	    

	    inline void reset(void); 
 

	};

	


    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                definitions                                                                      
    //-------------------------------------------------------------------------------------------------------------------------------------------------

    SoccerBoard::SoccerBoard(void) {}

	#if defined(__AVR_ATmega2560__)
	    inline void SoccerBoard::led(int idx, bool state) {writePin(13,state);}
	    void SoccerBoard::ledOn(int) {writePin(13,HIGH);}
	    void SoccerBoard::ledOff(int) {writePin(13,LOW);}
	    void SoccerBoard::ledsOff(void) {writePin(13,LOW);}
	    void SoccerBoard::ledMeter(int) {writePin(13,HIGH);}
	#elif EBOARD_USE_UTILITY > 0x0
	    void SoccerBoard::led(int, bool) {}
	    void SoccerBoard::ledOn(int) {}
	    void SoccerBoard::ledOff(int) {}
	    void SoccerBoard::ledsOff(void) {}
	    void SoccerBoard::ledMeter(int) {}
	#endif

	#if EBOARD_USE_UTILITY > 0x0
	    void SoccerBoard::button(int) {}
	    void SoccerBoard::waitForButton(int) {}
	#endif

	

	void SoccerBoard::reset(void) {
	    #if EBOARD_USE_RESET > 0x0
	        wdt_enable(WDTO_15MS);
	        for(;;) {}
	    #endif
	}

	

    void SoccerBoard::motor(uint8_t id,int16_t val) {
        #ifndef EBOARD_HELPCAR
            if(id==0&&(val>-256 && val < 256)) {setPin(PIN_MOTOR_DIR,val<0); writePWM(abs(val));}
            else if(id>0&&id<3) {_servoHandler.write(id,val);}
        #else
            if (id == 0) {
            if(val < 0 || val > 180) return;
                mainMotor.write(val);   
            }
            else if (id == 1){
                if(val < 0 || val > 180) return;
                steerMotor.write(val);
            }
        #endif
        }
        void SoccerBoard::motorsOff(void) {
            #ifndef EBOARD_HELPCAR
                    writePWM(0);
            #else
                mainMotor.write(90);
            #endif

        }
    


	
	void SoccerBoard::power(optVAL_t id, bool state) {writePin(id,state);}
	void SoccerBoard::powerOn(optVAL_t id) {this->power(id,1);}
	void SoccerBoard::powerOff(optVAL_t id) {this->power(id,0);}
	void SoccerBoard::sleep(uint16_t t) {delay(1000*t);}
	void SoccerBoard::msleep(uint16_t t) {delay(t);}
	bool SoccerBoard::digital (optVAL_t id) {return readPin(id);}
	optVAL_t  SoccerBoard::analog (optVAL_t id) {pinMode(id,INPUT); return analogRead(id);}
	

#endif
