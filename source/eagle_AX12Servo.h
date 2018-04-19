//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 19.04.2018 16:49:13
#ifndef EAGLE_EBOARD_HELPLIB_AX12SERVO
#define EAGLE_EBOARD_HELPLIB_AX12SERVO
	
	struct DynamixelBoard;
	
	
	struct AX12Servo {
	    
	    AX12Servo(void);
	    
	    AX12Servo(DynamixelBoard &dBoard, optVAL_t servoID); //if borders => setPosLimit
	    DynamixelBoard *_conBoard;
	    #if EBOARD_USE_UTILITY > 0x0
	        
	        inline void setID(optVAL_t newID);
	        
	        inline void changeMotorID(optVAL_t newID);                    //this should change the hardwareaddress...
	        
	        inline void setPositionMode(void);
	        
	        inline void setSpeedMode(void);
	        
	        inline void setSpeed(optVAL_t);
	        
	        inline void ledOff(void);
	        
	        inline void ledOn(void);
	        
	        inline void setTorque(uint16_t);
	    #endif
	    
	    void setPosition(int pos, int speed=0x3FF);
	    
	    inline void storePosition(int pos, int speed = 0x3FF);
	    
	    inline optVAL_t getPosition(void);
	    
	    inline bool isMoving(void);
	    
	    int storedPos;
	    
	    int storedSpe;
	    //bool posMode; //we don't care wich mode we are in ^^
	    
	    optVAL_t id;
	private:
	    
	    int actPos;
	    
	    int actSpe;
	}; //shield //set limits auto register for begin
	
	AX12Servo::AX12Servo(void) {}
	#if EBOARD_USE_UTILITY > 0x0
	    void AX12Servo::setID(optVAL_t newID) {this->id = newID;_servoHandler.SetServoLimit(this->id,_servoHandler.upperLimit_temp);}
	    void AX12Servo::changeMotorID(optVAL_t newID) {this->id = newID; _servoHandler.SetID(this->id, newID);} //this -should- *does now* change the hardwareaddress...
	    //IF needed: _servoHandler.setID(this->id, newID);
	    void AX12Servo::setPositionMode(void)  {}
	    void AX12Servo::setSpeedMode(void) {}
	    void AX12Servo::setSpeed(optVAL_t) {} //i won't use the rotate functions...
	    void AX12Servo::ledOff(void) {} //noone needs the AX12-Servo LED
	    void AX12Servo::ledOn(void) {} //really.... noone ^^
	    void AX12Servo::setTorque(uint16_t) {} //which damn register? xD
	#endif
	void AX12Servo::setPosition(int pos, int speed) {
	    #if EBOARD_CLAMP > 0x0
	        if(pos>1023 || speed > 1023) return;
	        this->actPos=pos; this->storedPos=pos; this->storedSpe = speed;
	        speed = speed*600/1023 - 300;
	        pos   = pos  *600/1023 - 300;
	    #else
	        if(pos>300 || speed > 300) return;
	        this->actPos=pos; this->storedPos=pos; this->storedSpe = speed;
	    #endif
	    if(speed != actSpe){ _servoHandler.setVelocity(speed); this->actSpe=speed;}
	    _servoHandler.write(this->id,pos);
	}
	optVAL_t AX12Servo::getPosition(void) {
	    return this->actPos; //when moving... false value;
	}
	bool AX12Servo::isMoving(void) {return false;} //we don't know^^
	
#endif
