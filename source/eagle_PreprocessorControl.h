//This was created by EagleoutIce 'document creator: create_doc' using doxygen 1.8.15 and python 3.5.2
//Created: 22.06.2018 00:28:45

    


//=====================================================================================================================================================
//                                                                 Preprocessor Macros                                                                 
//=====================================================================================================================================================

// This file contains various preprocessor tools provided by eBoard


    #define VALUE_TO_STRING(x) #x



#ifdef DOC
	 

	 #define PREPROCESS_DEBUG 1
#endif



    #define VALUE(x) VALUE_TO_STRING(x)



#ifndef PREPROCESS_DEBUG
    #define PREPROCESS_DEBUG 0
#endif



    #define PPERFORM_PRAGMA(str) _Pragma(#str)

    #if PREPROCESS_DEBUG > 0
        #pragma message("You are using eBoard-header 🐉" VALUE(EBOARD_VERSION) "{" VALUE(EBOARD_VERSION_NBR) "} written by EagleoutIce")
        #define DEBUG_MSG(str) PPERFORM_PRAGMA(message ("" #str))
        #define MACRO_MSG(mac,str) PPERFORM_PRAGMA(message("You set " #mac " to " VALUE(mac) ": " #str))
    #else
        #define DEBUG_MSG(str) ;
        #define MACRO_MSG(mac,str) ;
    #endif


