//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 27.04.2018 00:20:08
#ifndef EAGLE_EBOARD_HELPLIB_SERVOCDS55
#define EAGLE_EBOARD_HELPLIB_SERVOCDS55
struct ServoCds55 {
			
        #if defined(__AVR_ATmega2560__)
          ServoCds55(int CS=53);
        #else
          ServoCds55(int CS=10);
        #endif
				
      	void begin();
				
        void WritePos(int ID,int Pos);
				
        void write(int ID,int Pos);
				
        inline void setVelocity(int velocity);
				
        inline void setPoslimit(int posLimit);
				
        inline void rotate(int ID,int velocity);
				
        void SetServoLimit(int ID,int upperLimit);
				
				void SetMotormode(int ID, int velocity);
				
				void SetID(int ID, int newID);
				
        void Reset(int ID);
				
        byte sendWait (const byte what);
				
        int velocity_temp;
				
        int upperLimit_temp;
				
        optVAL_t cs;
      };
	
      ServoCds55::ServoCds55 (int CS):cs(CS) {
        velocity_temp = 150;
        upperLimit_temp = 300;
      }
void ServoCds55::setVelocity(int velocity){   //set servo velocity
    velocity_temp = velocity;
  }
void ServoCds55::setPoslimit(int posLimit){  // set servo pos limit
    upperLimit_temp =  posLimit;
  }
inline void ServoCds55::rotate(int ID,int velocity){ // Motor Mode
    SetServoLimit(ID,0);
    delay(100);
    SetMotormode(ID,velocity);
  }
  void ServoCds55::begin() {
    pinMode(cs,OUTPUT);
    digitalWrite(cs,HIGH);
    SPI.begin ();
    SPI.setClockDivider(SPI_CLOCK_DIV8);
  }
byte ServoCds55::sendWait (const byte what) {
    byte a = SPI.transfer (what);
    delayMicroseconds (20);
    return a;
  }
void ServoCds55::write(int ID,int Pos){     //  Servo Mode
    SetServoLimit(ID,upperLimit_temp);
    WritePos(ID,Pos);// default velocity:150
  }
void ServoCds55::WritePos(int ID,int Pos){
    int PosB = (Pos>>8 & 0xff);//low
    int PosS = (Pos & 0xff);//high
    int velocityB = (velocity_temp>>8 & 0xff);
    int velocityS = (velocity_temp & 0xff);
    digitalWrite(cs, LOW);
    sendWait ('p'); sendWait (ID);
    sendWait (PosB); sendWait (PosS);
    sendWait (velocityB); sendWait (velocityS);
    sendWait ('\t'); sendWait ('\r'); sendWait ('\n');
    digitalWrite(cs, HIGH);
    delay(10);
  }
void ServoCds55::SetServoLimit(int ID,int  upperLimit_temp){
    int upperLimitB = (upperLimit_temp>>8 & 0xff);
    int upperLimitS =  (upperLimit_temp & 0xff);
    digitalWrite(cs, LOW);
    sendWait ('s'); sendWait (ID);
    sendWait (upperLimitB); sendWait (upperLimitS);
    sendWait ('\t'); sendWait ('\r'); sendWait ('\n');
    digitalWrite(cs, HIGH);
    delay(10);
  }
void ServoCds55::SetMotormode(int ID, int velocity){
    int velocityB = (velocity>>8 & 0xff);
    int velocityS = (velocity & 0xff);
    digitalWrite(cs, LOW);
    sendWait ('m'); sendWait (ID);
    sendWait (velocityB); sendWait (velocityS);
    sendWait ('\t'); sendWait ('\r'); sendWait ('\n');
    digitalWrite(cs, HIGH);
    delay(10);
  }
void ServoCds55::SetID(int ID, int newID){
    digitalWrite(cs, LOW);
    sendWait ('i'); sendWait (ID);
    sendWait (newID);
    sendWait ('\t'); sendWait ('\r'); sendWait ('\n');
    digitalWrite(cs, HIGH);
    delay(10);
  }
void ServoCds55::Reset(int ID){
    digitalWrite(cs, LOW);
    sendWait ('r'); sendWait (ID);
    sendWait ('\t'); sendWait ('\r'); sendWait ('\n');
    digitalWrite(cs, HIGH);
    delay(10);
  }
#endif
