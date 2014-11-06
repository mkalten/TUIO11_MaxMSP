/*
 TUIO Max/MSP External - part of the reacTIVision project 
 Copyright (c) 2005-2014 Martin Kaltenbrunner <martin@tuio.org>
 
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

#ifndef INCLUDED_TuioWrapper_H
#define INCLUDED_TuioWrapper_H

#include "TuioListener.h"
#include "TuioClient.h"

#include "ext.h"  		// contains the external object's link to available Max functions
using namespace TUIO;

class TuioWrapper : public TuioListener { 
	
	public:
		TuioWrapper(int p);
		~TuioWrapper() {};

		void addOutlet(void* m, void* r);
		void removeOutlet(void* m, void *r);
		int outletCount();
	
		void start();
		void stop();
		bool isRunning() { return running; };

		int getPort() { return udp_port; };
	
		void addTuioObject(TuioObject *tuioObject);
		void updateTuioObject(TuioObject *tuioObject);
		void removeTuioObject(TuioObject *tuioObject);
	
		void addTuioCursor(TuioCursor *tuioCursor);
		void updateTuioCursor(TuioCursor *tuioCursor);
		void removeTuioCursor(TuioCursor *tuioCursor);
	
		void addTuioBlob(TuioBlob *tuioBlob);
		void updateTuioBlob(TuioBlob *tuioBlob);
		void removeTuioBlob(TuioBlob *tuioBlob);
	
		void refresh(TuioTime frameTime);

	private:

  		TuioClient *client;
		std::list<void*> message_outlet;
		std::list<void*> refresh_outlet;
		int udp_port;
		bool running;
};

#endif /* INCLUDED_TuioWrapper_H */
