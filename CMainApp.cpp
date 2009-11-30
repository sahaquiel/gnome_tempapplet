#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "CMainApp.h"

#if 0
class myConn
{
	myConn( const char *cname1, BonoboUIVerbFn cb1, gpointer user_data1 )
//	: cname( cname ), cb( cb ), user_data( user_data ), dummy( NULL )
	{
		m_verb.cname = cname1;
		m_verb.cb = cb1;
		m_verb.user_data = user_data1;
		m_verb.dummy = NULL;
	}
	
	BonoboUIVerb m_verb;
/*
 struct {
        const char    *cname;
        BonoboUIVerbFn cb;
        gpointer       user_data;
        gpointer       dummy;
} BonoboUIVerb;
*/
};
#endif


void CMainApp::applet_destroyed (GtkWidget * widget, void* data)
{
	CMainApp *app = static_cast<CMainApp *>(data);

	fprintf( stderr, "CMainApp::applet_destroyed() called! deleting %p\n", (void*)app );
	
	delete app;
}


CMainApp::CMainApp( PanelApplet *applet )
: m_globPrefs(),
  m_mainApplet( applet ),
  m_mainWidget( NULL ),
  m_degLabel( NULL ),  
  m_bgTaskId( 0 ),
  m_menuConns( NULL ),
//  m_menuConns( BONOBO_UI_VERB ("Properties", displayPropDialog), BONOBO_UI_VERB_END ),
  m_contextMenuXml( NULL )
{
	m_mainWidget = gtk_label_new ("00,00");
	gtk_container_add (GTK_CONTAINER (m_mainApplet), m_mainWidget); 

	m_degLabel = gtk_label_new ("111");
	// TODO: check how to add another label and have it show up after the one above!
//	gtk_container_add (GTK_CONTAINER (m_mainApplet), m_degLabel); 

	m_menuConns = new BonoboUIVerb[3];
	m_menuConns[0].cname = "Properties";
	m_menuConns[0].cb = displayDialog_wrapper;
	m_menuConns[0].user_data = this;
	m_menuConns[0].dummy = NULL;
	m_menuConns[1].cname = "About";
	m_menuConns[1].cb = displayDialog_wrapper;
	m_menuConns[1].user_data = this;
	m_menuConns[1].dummy = NULL;
	m_menuConns[2].cname = NULL;
	m_menuConns[2].cb = NULL;
	m_menuConns[2].user_data = NULL;
	m_menuConns[2].dummy = NULL;
	
	m_contextMenuXml = new std::string( "<popup name=\"button3\">\n"
   "   <menuitem name=\"Properties Item\" "
   "             verb=\"Properties\" "
   "           _label=\"_Preferences...\"\n"
   "          pixtype=\"stock\" "
   "          pixname=\"gtk-properties\"/>\n"
   "   <menuitem name=\"About Item\" "
   "             verb=\"About\" "
   "           _label=\"_About...\"\n"
   "          pixtype=\"stock\" "
   "          pixname=\"gnome-stock-about\"/>\n"
   "</popup>\n" );

	panel_applet_setup_menu (PANEL_APPLET (m_mainApplet),
                         m_contextMenuXml->c_str(),
                         m_menuConns,
                         NULL);
	
	// if we do this, we will clean up once the applet gets closed, but it will also get rid of all applet instances
//    g_signal_connect (m_mainApplet, "destroy", G_CALLBACK (applet_destroyed), this);
}


CMainApp::~CMainApp()
{
	delete m_contextMenuXml;
	delete[] m_menuConns;
	
	delete m_mainWidget;
	delete m_degLabel;
}


void CMainApp::displayPropDialog( BonoboUIComponent *component, gpointer user_data, const char *cname)
{
	fprintf( stderr, "%p->displayPropDialog() called!\n", (void*)this );
}


void CMainApp::displayAboutDialog( BonoboUIComponent *component, gpointer user_data, const char *cname)
{
	fprintf( stderr, "%p->displayAboutDialog() called!\n", (void*)this );
	
	GtkWidget *window, *label;
	GtkBox *box;
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	box = GTK_BOX (gtk_vbox_new (TRUE, 12));
	gtk_container_add (GTK_CONTAINER (window), GTK_WIDGET(box) );
	label = gtk_label_new ("Hello World");

	gtk_box_pack_start (GTK_BOX (box), label, TRUE, TRUE, 12);
	
	gtk_widget_show_all (window);
}


void CMainApp::displayDialog_wrapper( BonoboUIComponent *component, gpointer user_data, const char *cname)
{
	CMainApp *app = static_cast<CMainApp *>(user_data);
	
	if ( strcmp( cname, "Properties" ) == 0 )
	{
		app->displayPropDialog(component, user_data, cname);
	}
	else if ( strcmp( cname, "About" ) == 0 )
	{
		app->displayAboutDialog(component, user_data, cname);
	}
}
 
   
void CMainApp::showAll()
{
	gtk_widget_show_all (GTK_WIDGET (m_mainApplet));
}


void CMainApp::updateTempLabel( float curr_temp_val )
{
	char temp_str[256] = { "-" };

	if ( curr_temp_val > getPrefs().getWatermarkHigh() )
	{
//		printf( "Warning! high temp!\n" );
//
		sprintf( temp_str, "<span foreground=\"red\">%2.2f</span>", curr_temp_val );
	}
	else
	{
		sprintf( temp_str, "%2.2f", curr_temp_val );

//		gtk_label_set_text( GTK_LABEL (label), curr_temp_str );
	}

	gtk_label_set_markup (GTK_LABEL (m_mainWidget), temp_str );
}


void * CMainApp::bgTaskFunc()
{
	float curr_temp_val;
	CTempReader reader;
	
	for( ;; )
	{
		reader.getCurrTemp( &curr_temp_val );

//		printf( "got float: %f\n", curr_temp_val );

		updateTempLabel( curr_temp_val );

		sleep(2);
	}
}


void * CMainApp::threadfunc ( void * data )
{
	CMainApp *app = static_cast<CMainApp *>(data);
	
	app->bgTaskFunc();
	
	return NULL;
}


void CMainApp::startBgTask()
{
	pthread_create( &m_bgTaskId, NULL, threadfunc, static_cast<void *>(this) );
}
