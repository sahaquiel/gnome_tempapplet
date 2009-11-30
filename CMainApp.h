#ifndef _MAINAPP_H_
#define _MAINAPP_H_

#include <string>
#include <panel-applet.h>
#include <gtk/gtklabel.h>
#include "CPrefs.h"
#include "CTempReader.h"


class CMainApp
{
public:
	CMainApp( PanelApplet *applet);
	virtual ~CMainApp();
	
	void showAll();
	void startBgTask();
	
	const CPrefs& getPrefs()
	{
		return m_globPrefs;
	}
	
private:
	void updateTempLabel( float curr_temp_val );
	void * bgTaskFunc();
	static void * threadfunc ( void * data );
	
	CPrefs m_globPrefs;
	PanelApplet *m_mainApplet;
	GtkWidget *m_mainWidget;
	GtkWidget *m_degLabel;
	pthread_t m_bgTaskId;
	
	BonoboUIVerb *m_menuConns;	
	std::string *m_contextMenuXml;

	static void applet_destroyed (GtkWidget * widget, void* data);
	static void displayDialog_wrapper( BonoboUIComponent *component, gpointer user_data, const char *cname);
	void displayPropDialog( BonoboUIComponent *component, gpointer user_data, const char *cname);
	void displayAboutDialog( BonoboUIComponent *component, gpointer user_data, const char *cname);

};

#endif