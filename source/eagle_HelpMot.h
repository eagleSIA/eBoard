//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 02.05.2018 22:41:44
#ifndef EAGLE_EBOARD_HELPLIB_HELPMOT
#define EAGLE_EBOARD_HELPLIB_HELPMOT
	
	inline void set_motor_speed(optVAL_t spe);
	
	inline void set_steer_angle(optVAL_t ang);
	
	inline void set_motor_speed(optVAL_t spe){
	    if(spe < 0 || spe > 180) return;
	    mainMotor.write(spe);
	}
	inline void set_steer_angle(optVAL_t ang){
	    if(ang < 0 || ang > 180) return;
	    steerMotor.write(ang);
	}
	
#endif
