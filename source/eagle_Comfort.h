//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 02.05.2018 21:53:42
#ifndef EAGLE_EBOARD_HELPLIB_COMFORT
#define EAGLE_EBOARD_HELPLIB_COMFORT
	
	inline int sine8(uint8_t val);
	
	inline int sine8(uint8_t val){
	  return int((__builtin_sin((val/128.0*PI))+1)*127.5+0.5);
	}
	
	
	inline int gamma8(uint8_t val);
	
	inline int gamma8(uint8_t val){
	  return int(pow((val)/255.0,2.6)*255.0+0.5);
	}
	
#endif
