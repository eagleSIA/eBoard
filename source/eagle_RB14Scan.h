//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 18.04.2018 23:34:37

struct RB14Scan {
inline RB14Scan(void);
inline int raw(optVAL_t);
inline char channel(optVAL_t);
inline void write(const char* const  val);
};

inline RB14Scan::RB14Scan(void) {}
inline int RB14Scan::raw(optVAL_t) {return isConnected();}
inline char RB14Scan::channel(optVAL_t) {return ((isConnected())?(readVal()):(-1));}
inline void RB14Scan::write(const char* const val) {writeVal(val);}
