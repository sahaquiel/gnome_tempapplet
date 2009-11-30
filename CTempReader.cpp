#include <stdio.h>
#include <string.h>

#include "CTempReader.h"


CTempReader::CTempReader()
:m_prefs()
{

}

CTempReader::CTempReader( CPrefs& prefs )
:m_prefs( prefs )
{

}

CTempReader::~CTempReader()
{

}


float CTempReader::tempStrToFloat( const char * temp_str )
{
	float ret;

	size_t i;
	size_t len_vorkomma = 0, len_nachkomma = 0;
	char vorkomma[4];
	char nachkomma[5];
	char floatstring[16];

/*
	for ( i = 0; i < strlen( temp_str ); i++ )
	{
		if ( temp_str[i] == '0' )
		{
			break;
		}
	}
*/
	i = 2;	// fixed for now. code above was wrong for values multiple of 10 (70000 => 7,0 instead of 70,0)

	len_vorkomma = i;
	len_nachkomma = strlen( temp_str ) - i;

	memcpy( &vorkomma[0], &temp_str[0], len_vorkomma );
	vorkomma[len_vorkomma+1] = '\0';

	memcpy( &nachkomma[0], &temp_str[i], len_nachkomma );
	vorkomma[len_nachkomma+1] = '\0';

	sprintf( floatstring, "%s.%s", vorkomma, nachkomma );

	if ( sscanf( floatstring, "%f", &ret ) != 1 )
	{
		ret = 0.0;
	}

	return ret;
}


bool CTempReader::getCurrTemp( float *tempFloat )
{
	bool ret;
	char tempStr[16];
	
	ret = getCurrTemp( tempStr );
	
	if ( ret )
	{
		*tempFloat = tempStrToFloat( tempStr );
		
		ret = true;
	}
	
	return true;
}


bool CTempReader::getCurrTemp( char *tempStr )
{
	FILE *fz = fopen( "/sys/class/hwmon/hwmon0/temp1_input", "r" );

	if ( fscanf( fz, "%15s", tempStr ) != 1 )
	{
		strcpy( tempStr, "<n/a>" );
	}

	fclose( fz );
	
	return true;
}
