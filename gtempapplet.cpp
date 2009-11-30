#include <stdio.h>
#include <string.h>


#include <panel-applet.h>
#include <gtk/gtklabel.h>

#include "CMainApp.h"

CMainApp *theApp = NULL;


static gboolean
myexample_applet_fill (PanelApplet *applet,
   const gchar *iid,
   gpointer data)
{
	if (strcmp (iid, "OAFIID:FE_GNOME_Temp_Applet") != 0)
		return FALSE;
				
	// init mainapp
	theApp = new CMainApp( applet );	

	// show main widget
	theApp->showAll();
	
	// start bg activity
	theApp->startBgTask();
	
	return TRUE;
}

PANEL_APPLET_BONOBO_FACTORY ("OAFIID:FE_GNOME_Temp_Applet_Factory",
                             PANEL_TYPE_APPLET,
                             "CPU Temperature Applet",
                             "0",
                             myexample_applet_fill,
                             NULL)
