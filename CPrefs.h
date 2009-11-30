#ifndef _PREFS_H_
#define _PREFS_H_


class CPrefs
{
public:
	CPrefs();
	CPrefs( const CPrefs &src );
	virtual ~CPrefs();
	
	float getWatermarkHigh()
	{
		return m_watermarkHigh;
	};
	
	float getWatermarkHigh() const
	{
		return m_watermarkHigh;
	};
	
	float getWatermarkLow()
	{
		return m_watermarkLow;
	};
	
	float getWatermarkLow() const
	{
		return m_watermarkLow;
	};
	
	int   getUpdateInterval()
	{
		return m_updateInterval;
	};

	int   getUpdateInterval() const
	{
		return m_updateInterval;
	};

private:
	float m_watermarkLow;
	float m_watermarkHigh;
	int m_updateInterval;
};


#endif