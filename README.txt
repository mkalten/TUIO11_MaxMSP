TUIO MaxMSP Client
------------------
Copyright (c) 2005-2016 Martin Kaltenbrunner <martin@tuio.org>
This software is part of reacTIVision, an open source fiducial
tracking and multi-touch framework based on computer vision. 
http://reactivision.sourceforge.net/

Demo Patch:
-----------
This package contains a simple patch that receives and decodes
TUIO messages received from any TUIO enabled tracker or TUIO simulator.
This package provides a MaxMSP extra for Windows and MacOS X.

The TuioClient object takes an alternative UDP port number 
as an optional argument. The default TUIO/UDP port is 3333.

There are two outputs, the first one is sending all relevant
TUIO events such as addObject, updateObject and removeObject
as well as addCursor, updateCursor and removeCursor and
addBlob, updateBlob and removeBlob.

The second output sends simple bangs for each fully received
frame, and every second while no new messages are received, 
in order to indicate that the connection is still alive.

The list format of the messages received at the first output
are in analogy to the TUIO message format:

addObject session_id symbol_id
updateObject session_id symbol_id xpos ypos angle xspeed yspeed rspeed maccel raccel
removeObject session_id symbol_id

addCursor session_id cursor_id
updateCursor session_id cursor_id xpos ypos xspeed yspeed maccel
removeCursor session_id cursor_id

addBlob session_id blob_id
updateBlob session_id blob_id xpos ypos angle width height area xspeed yspeed rspeed maccel raccel
removeBlob session_id blob_id

Source Code:
------------
The TuioClient external comes with its full source code which can be
built under Windows and Mac OS X. There is an Visual Studio 2012
and an XCode project included with the source code. Remember that
you will need the MaxMSP 6.1 SDK in order to compile this external.

License:
--------
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3.0 of the License, or (at your option) any later version.
 
This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

