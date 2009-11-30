
#include "CPrefs.h"

CPrefs::CPrefs()
: m_watermarkLow(0),
  m_watermarkHigh(80),
  m_updateInterval(2)
{

}

CPrefs::CPrefs( const CPrefs &src )
: m_watermarkLow(src.m_watermarkLow),
  m_watermarkHigh(src.m_watermarkHigh),
  m_updateInterval(src.m_updateInterval)
{

}

CPrefs::~CPrefs()
{

}
