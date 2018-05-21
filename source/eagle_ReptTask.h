//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 21.05.2018 05:40:11
#ifndef EAGLE_EBOARD_HELPLIB_REPTTASK
#define EAGLE_EBOARD_HELPLIB_REPTTASK


    


//=====================================================================================================================================================
//                                                                      Rept Task                                                                      
//=====================================================================================================================================================



void trig_rept_task(void);



	  void trig_rept_task() {

			#if EBOARD_NANO == 0x0 || defined(DOC)
                if (_pwmValue!=_OpwmValue){
                analogWrite(PIN_MOTOR_SPE,_pwmValue);
                _OpwmValue = _pwmValue;
                }
			#endif

            #ifdef REPT_TASK
                rept_task();
            #endif
		}

	  int timer_count = 0;
	  bool timer_ofl = false;

	  ISR(TIMER2_OVF_vect) {
	    timer_count++;
	    if(timer_count >= EBOARD_PWM_SPE*1000 && !timer_ofl){
	      timer_ofl = true;
	      timer_count -= EBOARD_PWM_SPE*1000;
	      trig_rept_task();
	      timer_ofl = false;
	    }
	    TCNT2 =  256 - (int)((float)F_CPU * 0.001 / 64);
	  }



#endif
