
#ifndef _CTEMPREADER_H_
#define _CTEMPREADER_H_

#include "CPrefs.h"

class CTempReader
{

public:
	CTempReader();
	CTempReader( CPrefs& prefs );
	virtual ~CTempReader();
	
	bool getCurrTemp( char * const tempStr );
	bool getCurrTemp( float * const tempFloat );
	
private:
	float tempStrToFloat( const char * temp_str );
	CPrefs m_prefs;
};

#endif
