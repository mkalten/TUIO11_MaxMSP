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
	
TuioWrapper::TuioWrapper(int p) {

	udp_port = p;
	running = false;
}

void TuioWrapper::addOutlet(void* m,  void* r) {
	message_outlet.push_back(m);
	refresh_outlet.push_back(r);	
}

void TuioWrapper::removeOutlet(void* m,  void* r) {
	std::list<void*>::iterator m_outlet = find(message_outlet.begin(), message_outlet.end(), m);
	if (m_outlet!=message_outlet.end()) message_outlet.remove(m);
	
	std::list<void*>::iterator r_outlet = find(refresh_outlet.begin(), refresh_outlet.end(), r);
	if (r_outlet!=refresh_outlet.end()) refresh_outlet.remove(r);
}

int TuioWrapper::outletCount() {
	return message_outlet.size();
}

void TuioWrapper::addTuioObject(TuioObject *tobj) {
	
	t_atom message[5];
	atom_setfloat(&message[0],(float)tobj->getSessionID());
	atom_setfloat(&message[1],(float)tobj->getSymbolID());
	atom_setfloat(&message[2],tobj->getX());
	atom_setfloat(&message[3],tobj->getY());
	atom_setfloat(&message[4],tobj->getAngle());
	
	for(std::list<void*>::iterator outlet = message_outlet.begin(); outlet!=message_outlet.end(); outlet++) {
		outlet_anything(*outlet, gensym("addObject"), 5, message);
	}
}

void TuioWrapper::updateTuioObject(TuioObject *tobj) {

	t_atom message[10];
	atom_setfloat(&message[0],(float)tobj->getSessionID());
	atom_setfloat(&message[1],(float)tobj->getSymbolID());
	atom_setfloat(&message[2],tobj->getX());
	atom_setfloat(&message[3],tobj->getY());
	atom_setfloat(&message[4],tobj->getAngle());
	atom_setfloat(&message[5],tobj->getXSpeed());
	atom_setfloat(&message[6],tobj->getYSpeed());
	atom_setfloat(&message[7],tobj->getRotationSpeed());
	atom_setfloat(&message[8],tobj->getMotionAccel());
	atom_setfloat(&message[9],tobj->getRotationAccel());	
	for(std::list<void*>::iterator outlet = message_outlet.begin(); outlet!=message_outlet.end(); outlet++) {
		outlet_anything(*outlet, gensym("updateObject"), 10, message);
	}
}

void TuioWrapper::removeTuioObject(TuioObject *tobj) {

	t_atom message[2];
	atom_setfloat(&message[0],(float)tobj->getSessionID());
	atom_setfloat(&message[1],(float)tobj->getSymbolID());
	for(std::list<void*>::iterator outlet = message_outlet.begin(); outlet!=message_outlet.end(); outlet++) {
		outlet_anything(*outlet, gensym("removeObject"), 2, message);
	}

}

void TuioWrapper::addTuioCursor(TuioCursor *tcur) {

	t_atom message[4];
	atom_setfloat(&message[0],(float)tcur->getSessionID());
	atom_setfloat(&message[1],(float)tcur->getCursorID());
	atom_setfloat(&message[2],tcur->getX());
	atom_setfloat(&message[3],tcur->getY());
	
	for(std::list<void*>::iterator outlet = message_outlet.begin(); outlet!=message_outlet.end(); outlet++) {
		outlet_anything(*outlet, gensym("addCursor"), 4, message);
	}

}

void TuioWrapper::updateTuioCursor(TuioCursor *tcur) {

	t_atom message[7];
	atom_setfloat(&message[0],(float)tcur->getSessionID());
	atom_setfloat(&message[1],(float)tcur->getCursorID());
	atom_setfloat(&message[2],tcur->getX());
	atom_setfloat(&message[3],tcur->getY());
	atom_setfloat(&message[4],tcur->getXSpeed());
	atom_setfloat(&message[5],tcur->getYSpeed());
	atom_setfloat(&message[6],tcur->getMotionAccel());
	for(std::list<void*>::iterator outlet = message_outlet.begin(); outlet!=message_outlet.end(); outlet++) {
		outlet_anything(*outlet, gensym("updateCursor"), 7, message);
	}
}

void TuioWrapper::removeTuioCursor(TuioCursor *tcur) {
	
	t_atom message[2];
	atom_setfloat(&message[0],(float)tcur->getSessionID());
	atom_setfloat(&message[1],(float)tcur->getCursorID());
	for(std::list<void*>::iterator outlet = message_outlet.begin(); outlet!=message_outlet.end(); outlet++) {
		outlet_anything(*outlet, gensym("removeCursor"), 2, message);
	}
	
}
void TuioWrapper::addTuioBlob(TuioBlob *tblb) {
	
	t_atom message[8];
	atom_setfloat(&message[0],(float)tblb->getSessionID());
	atom_setfloat(&message[1],(float)tblb->getBlobID());
	atom_setfloat(&message[2],tblb->getX());
	atom_setfloat(&message[3],tblb->getY());
	atom_setfloat(&message[4],tblb->getAngle());
	atom_setfloat(&message[5],tblb->getWidth());
	atom_setfloat(&message[6],tblb->getHeight());
	atom_setfloat(&message[7],tblb->getArea());
	
	for(std::list<void*>::iterator outlet = message_outlet.begin(); outlet!=message_outlet.end(); outlet++) {
		outlet_anything(*outlet, gensym("addBlob"), 8, message);
	}
}

void TuioWrapper::updateTuioBlob(TuioBlob *tblb) {
	
	t_atom message[13];
	atom_setfloat(&message[0],(float)tblb->getSessionID());
	atom_setfloat(&message[1],(float)tblb->getBlobID());
	atom_setfloat(&message[2],tblb->getX());
	atom_setfloat(&message[3],tblb->getY());
	atom_setfloat(&message[4],tblb->getAngle());
	atom_setfloat(&message[5],tblb->getWidth());
	atom_setfloat(&message[6],tblb->getHeight());
	atom_setfloat(&message[7],tblb->getArea());
	atom_setfloat(&message[8],tblb->getXSpeed());
	atom_setfloat(&message[9],tblb->getYSpeed());
	atom_setfloat(&message[10],tblb->getRotationSpeed());
	atom_setfloat(&message[11],tblb->getMotionAccel());
	atom_setfloat(&message[12],tblb->getRotationAccel());	
	for(std::list<void*>::iterator outlet = message_outlet.begin(); outlet!=message_outlet.end(); outlet++) {
		outlet_anything(*outlet, gensym("updateBlob"), 13, message);
	}
}

void TuioWrapper::removeTuioBlob(TuioBlob *tblb) {
	
	t_atom message[2];
	atom_setfloat(&message[0],(float)tblb->getSessionID());
	atom_setfloat(&message[1],(float)tblb->getBlobID());
	for(std::list<void*>::iterator outlet = message_outlet.begin(); outlet!=message_outlet.end(); outlet++) {
		outlet_anything(*outlet, gensym("removeBlob"), 2, message);
	}
	
}

void TuioWrapper::refresh(TuioTime frameTime) {
	for(std::list<void*>::iterator outlet = refresh_outlet.begin(); outlet!=refresh_outlet.end(); outlet++) {
		outlet_bang(*outlet);
	}
}

void TuioWrapper::start() {

	if (!running) {
		client = new TuioClient(udp_port);
		client->addTuioListener(this);
		client->connect();

		if (client->isConnected()) running = true;
		else {
			client->removeTuioListener(this);
			delete client;
		}
	}
}

void TuioWrapper::stop() {
	
	if (running) {
		client->removeTuioListener(this);
		client->disconnect();
		delete client;
		running = false;
	}
}



