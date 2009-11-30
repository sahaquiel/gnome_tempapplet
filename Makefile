

SERVERFILE_DESTDIR=/usr/lib/bonobo/servers
APP_DESTDIR=/usr/lib/gnome-panel

CFLAGS := -Wall -pedantic
CFLAGS += -O2
#CFLAGS += -g

CPPFLAGS := $(CFLAGS)


gtempapplet: gtempapplet.cpp CPrefs.cpp CTempReader.cpp CMainApp.cpp CPrefs.h CTempReader.h CMainApp.h 
	g++ $$(pkg-config --cflags --libs libpanelapplet-2.0) $(CPPFLAGS) -lpthread -o gtempapplet CPrefs.cpp CTempReader.cpp CMainApp.cpp gtempapplet.cpp


all: gtempapplet


clean:
	-rm gtempapplet

# TODO: use "install" and take care of access rights
install:
	cp gtempapplet $(APP_DESTDIR)
	cp GTempApplet.server $(SERVERFILE_DESTDIR)

uninstall:
	rm $(APP_DESTDIR)/gtempapplet
	rm $(SERVERFILE_DESTDIR)/GTempApplet.server

# refreshes bonobo-server (so that our applet shows up in the applet-list)
refresh:
	kill -HUP `pidof bonobo-activation-server`

