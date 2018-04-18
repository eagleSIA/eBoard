//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 18.04.2018 19:59:08

struct DynamixelBoard {
inline DynamixelBoard(SoccerBoard&);
    //inline ~DynamixelBoard(void) {}
    #if EBOARD_USE_UTILITY > 0x0
inline void changeId(optVAL_t);
inline void changeMotorID(optVAL_t);
inline void ledOn(optVAL_t);
inline void ledOff(optVAL_t);
    #endif
inline void action(void);
friend struct AX12Servo;
protected:
AX12Servo* connected[EBOARD_SPI_SERVO_MAX];
};
DynamixelBoard::DynamixelBoard(SoccerBoard&) {
    for(optVAL_t i = 0; i < EBOARD_SPI_SERVO_MAX; i++ ) {this->connected[i] = NULL;} //wanna use nullptr... wanna have c++11^^
}
//inline ~DynamixelBoard(void) {}
#if EBOARD_USE_UTILITY > 0x0
    void DynamixelBoard::changeId(optVAL_t) {}
    void DynamixelBoard::changeMotorID(optVAL_t) {}
    void DynamixelBoard::ledOn(optVAL_t) {}
    void DynamixelBoard::ledOff(optVAL_t) {}
#endif
void DynamixelBoard::action(void) {
    for(optVAL_t i = 0; (i < EBOARD_SPI_SERVO_MAX && !STOP); i++ ){
        if(this->connected[i] != NULL)
            (*connected[i]).setPosition((*connected[i]).storedPos,(*connected[i]).storedSpe);
    }
}

void AX12Servo::storePosition(int pos, int speed){
    if(this->id < EBOARD_SPI_SERVO_MAX) _conBoard->connected[this->id] = this;
    this->storedPos=pos;this->storedSpe=speed;
}
AX12Servo::AX12Servo(DynamixelBoard &dBoard, optVAL_t servoID): _conBoard( &dBoard),id(servoID-1), actSpe(0x96) {
    //#if EBOARD_DEBUG_MODE > 0x0
    //    assert(servoID<EBOARD_SPI_SERVO_MAX);
    //#endif
}
