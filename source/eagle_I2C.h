//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 18.04.2018 20:47:12

inline optVAL_t sendI2C(optVAL_t deviceID,byte *buf, byte buf_len);
inline optVAL_t sendI2C(optVAL_t deviceID, byte buf);
inline void pingI2C(optVAL_t ret[], optVAL_t ret_len);
inline void pingI2C(optVAL_t ret[], optVAL_t ret_len){
    optVAL_t count = 0;
    for (byte i = 1; (i < 255 && !STOP); i++)  {
        if(i==200)continue; //internal
        Wire.beginTransmission (i);
        if (Wire.endTransmission () == 0) {
            if(count < ret_len) ret[count] = i;
                count++;
            delay (1);
        }
    }
}
inline optVAL_t sendI2C(optVAL_t deviceID,byte *buf, byte buf_len) {
    Wire.beginTransmission(deviceID);
    Wire.write(buf,buf_len);
    return Wire.endTransmission();
}
inline optVAL_t sendI2C(optVAL_t deviceID, byte buf){
    Wire.beginTransmission(deviceID);
    Wire.write(buf);
    return Wire.endTransmission();
}
inline void readI2C(optVAL_t deviceID, optVAL_t ret[], optVAL_t ret_len,bool blocking=true);
inline void readI2C(optVAL_t deviceID,optVAL_t ret[] , optVAL_t ret_len,bool blocking) {
    for(optVAL_t rect = 0x0; (Wire.available() || (((blocking && (rect < ret_len))) && (!STOP))); rect++)
        ret[rect] = Wire.read();
}
