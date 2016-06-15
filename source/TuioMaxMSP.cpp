/*
 TUIO Max/MSP External - part of the reacTIVision project
 Copyright (c) 2005-2016 Martin Kaltenbrunner <martin@tuio.org>
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3.0 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library.
 */

#include "TuioWrapper.h"
#include <ext.h>

// The standard random() function is not standard on Windows.
// We need to do this to setup the rand_s() function.
#ifdef WIN_VERSION
#define _CRT_RAND_S
#endif

std::list<TuioWrapper*> TuioClientList;

typedef struct tuioclient
{
	t_object p_ob;								// object header
	void *message_outlet;
	void *refresh_outlet;						// outlet creation
	int port;									// the UDP port used by this instance
} t_tuioclient;

static t_class *tuioclient_class;               // global pointer to the object class

// these are prototypes for the methods that are defined below
void tuioclient_assist(t_tuioclient *x, void *b, long m, long a, char *s);
void *tuioclient_new(t_symbol *s, long argc, t_atom *argv);
void tuioclient_free(t_tuioclient *x);

//--------------------------------------------------------------------------

int C74_EXPORT main(void)
{
    t_class *c;
    c = class_new("tuioclient", (method)tuioclient_new, (method)tuioclient_free, (long)sizeof(t_tuioclient), 0L, A_GIMME, 0);
    class_addmethod(c, (method)tuioclient_assist,	"assist",	A_CANT, 0);
    
    class_register(CLASS_BOX, c);
    tuioclient_class = c;
	return 0;
}

//--------------------------------------------------------------------------

void tuioclient_assist(t_tuioclient *x, void *b, long m, long a, char *s) 
{
	if (m == ASSIST_OUTLET)
		switch (a) {	
		case 0:
			sprintf(s,"TUIO event output in list form");
			break;
		case 1:
			sprintf(s,"frame refresh bang");
			break;
		}
	else {
		sprintf(s,"input not used ...");
	}
}

//--------------------------------------------------------------------------

void *tuioclient_new(t_symbol *s, long argc, t_atom *argv)
{
    long port = 3333;
    if (argc==1) {
        port = atom_getlong(argv);
    }

    t_tuioclient *x = NULL;
    if ((x = (t_tuioclient *)object_alloc(tuioclient_class))) {
	
        x->refresh_outlet = outlet_new(x,"bang");
        x->message_outlet = outlet_new(x,"list");

        x->port = (int)port;
        if(x->port<1024) x->port=3333;
        TuioWrapper *wrapper = NULL;
        std::list<TuioWrapper*>::iterator iter;
        for (iter=TuioClientList.begin(); iter != TuioClientList.end(); iter++) {
            if ((*iter)->getPort()==x->port) {
                wrapper = *iter;
                break;
            }
        }
	
        if (wrapper==NULL) wrapper = new TuioWrapper(x->port);
        wrapper->addOutlet(x->message_outlet, x->refresh_outlet);
        
        if (!wrapper->isRunning()) {
            wrapper->start();
            if (wrapper->isRunning()) {
                TuioClientList.push_back(wrapper);
                post("TuioClient: started listening to TUIO/UDP messages on port %d",x->port);
            } else {
                delete wrapper;
                post("TuioClient: could not bind to UDP port %d",x->port);
            }
        }
    }
	return(x);
}

void tuioclient_free(t_tuioclient *x) {
	
	TuioWrapper *wrapper = NULL;
	std::list<TuioWrapper*>::iterator iter;
	for (iter=TuioClientList.begin(); iter != TuioClientList.end(); iter++) {
		if ((*iter)->getPort()==x->port) {
			wrapper = *iter;
			wrapper->removeOutlet(x->message_outlet, x->refresh_outlet);
			
			if (wrapper->outletCount()==0) {
				wrapper->stop();
				TuioClientList.erase(iter);
				delete wrapper;
				wrapper = NULL;
				post("TuioClient: stopped listening to UDP port %d",x->port);
			}
			break;
		}
	}	
}
