//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 03.05.2018 21:51:29
#ifndef EAGLE_EBOARD_HELPLIB_SETUP
    #define EAGLE_EBOARD_HELPLIB_SETUP

    


//=====================================================================================================================================================
//                                                                       Setup                                                                         
//=====================================================================================================================================================

    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                 cheat  :D                                                                       
    //-------------------------------------------------------------------------------------------------------------------------------------------------

	

	extern int eVirtual_main();
	


    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                   setup                                                                         
    //-------------------------------------------------------------------------------------------------------------------------------------------------

	void eagle_setup(void);

	

	void setup(void);


	


    //-------------------------------------------------------------------------------------------------------------------------------------------------
    //                                                                definitions                                                                      
    //-------------------------------------------------------------------------------------------------------------------------------------------------

	void eagle_setup(void) {
	    //setup of RX and TX should be handled manually - in everyCase ^^
	    #if EBOARD_NANO == 0x0
	      setPin(PIN_MOTOR_DIR);
	      setPin(PIN_MOTOR_SPE);
	    #endif
	    #if EBOARD_DEBUG_MODE > 0x0
	        Serial.begin(EBOARD_DEBUG_SPEED);
	    #endif
	    //this will initialize the interrupt handling!
	    #if (EBOARD_NANO == 0x0) || defined(REPT_TASK)
	      cli();
	      TIMSK2 &= ~(1<<TOIE2);
	      TCCR2A &= ~((1<<WGM21) | (1<<WGM20));
	      TCCR2B &= ~(1<<WGM22);
	      ASSR &= ~(1<<AS2);
	      TIMSK2 &= ~(1<<OCIE2A);
	      TCCR2B |= (1<<CS22);
	      TCCR2B &= ~((1<<CS21) | (1<<CS20));
	      TCNT2 = 256 - (int)((float)F_CPU * 0.001 / 64);
	      TIMSK2 |= (1<<TOIE2);
	      sei();
	    #endif
	    #if EBOARD_BLUETOOTH > 0x0
	        

	        

	        #if (EBOARD_BLUETOOTH > 0x0) && (((PIN_BLUETOOTH_RX==0x13) && (PIN_BLUETOOTH_TX==0x12)) && defined(__AVR_ATmega2560__))
	            Serial1.begin(38400);
	        #else
	            _serial.begin(38400);
	        #endif
	        if(PIN_BLUETOOTH_STATE!=PIN_BLUETOOTH_RX) setPin(PIN_BLUETOOTH_STATE,INPUT);
	    #endif
	    #if EBOARD_I2C > 0x0
	        Wire.begin();
	    #endif
	    #if EBOARD_SHIFT_REGISTER > 0x0
	        pinMode(PIN_SHIFT_CLK,OUTPUT);
	        pinMode(PIN_SHIFT_DAT,OUTPUT);
	        pinMode(PIN_SHIFT_LAT,OUTPUT);
	        shiftAll(); //set all to 0
	    #endif
	    #if EBOARD_USE_SPI > 0x0 && (EBOARD_NANO == 0)
	        _servoHandler.begin(); //Setup SPI
	    #endif
	    #if defined(EBOARD_HELPCAR)
	      mainMotor.attach(EBOARD_HELPCAR_MAIN);
	      steerMotor.attach(EBOARD_HELPCAR_STEER);
	      #if EBOARD_DEBUG_MODE > 0x0
	        Serial.println("Initializing main driving motor (3s)");
	      #endif
	        mainMotor.write(90);
	        delay(3005);
	      #if EBOARD_DEBUG_MODE > 0x0
	        Serial.println("Initializing of main driving motor completed");
	      #endif
	    #endif
	    #if EBOARD_DEBUG_MODE > 0x0
	        Serial.print((char) eVirtual_main());
	        Serial.println("fin");
	    #else
	        eVirtual_main();
	    #endif
	    if (STOP) {} //prevent unused error
	    delay(200);
	    #if defined(EBOARD_HELPCAR)
	      mainMotor.write(90);
	    #endif
	    cli(); //disable timers after running the program :D
	    #if EBOARD_USE_SPI > 0x0
	      writePWM(0);analogWrite(PIN_MOTOR_SPE,0);
	    #endif
	}
	
    void setup(void) {
	  eagle_setup();
	}



#endif
