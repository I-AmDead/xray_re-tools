//**************************************************************************/
// Copyright (c) 1998-2006 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// FILE:        SpaceArrayCallback.H
// DESCRIPTION: SpaceArrayCallback class definition
// AUTHOR:      Peter Sauerbrei
// HISTORY:     - created January 1998
//	        - changed object type to CloneType 01/28/98 (PJS)
//	        - changed CloneType back to OTYPE 01/30/98 (PJS)
//	        - added proc to act as callback 02/02/98 (PJS)
//	        - added new context modes 02/17/98 (PJS)
//**************************************************************************/



#ifndef __SPACEARRAYCALLBACK_H
#define __SPACEARRAYCALLBACK_H

// include files
#include "maxheap.h"
#include <limits.h>
#include <max.h>
#include <splshape.h>

// needed types
enum STYPE { SPACE_CENTER, SPACE_EDGE };
enum OTYPE { NODE_CPY, NODE_INST, NODE_REF };
enum CTYPE { CTXT_FREE, CTXT_CNTRCOUNT, CTXT_CNTRSPACE,
				CTXT_END, CTXT_ENDCOUNT, CTXT_ENDSPACE,
				CTXT_START, CTXT_STARTCOUNT, CTXT_STARTSPACE,
				CTXT_FULLSPACE, CTXT_FULLCOUNT, CTXT_ENDLOCK,
				CTXT_ENDLOCKCOUNT, CTXT_ENDLOCKSPACE, CTXT_STARTLOCK,
				CTXT_STARTLOCKCOUNT, CTXT_STARTLOCKSPACE,
				CTXT_FULLLOCKSPACE, CTXT_FULLLOCKCOUNT,};



////////////////////////////////////////////////////////////////////////////////
// SpaceArracyCallback
//
class SpaceArrayCallback: public MaxHeapOperators
{
private:
	ShapeObject * path;
	float start, end, space;
	int count;
	OTYPE oType;
	bool follow;
	STYPE sType;
	CTYPE context;
	float width;
	char buffer[100];
	int countLimit;

public:
	SpaceArrayCallback() { path = NULL; start = end = space = 0.0f; count = 1; oType = NODE_CPY; sType = SPACE_CENTER; follow = false; 
							context = CTXT_FREE; width = 0.0f; countLimit = INT_MAX; }
	virtual ~SpaceArrayCallback() {}

	// methods
	virtual bool isModal(void) { return true; }
	virtual bool doPickPath(void) { return false; }
	virtual TCHAR * dialogTitle(void) { return _T(""); }
	virtual TCHAR * startMessage(void) { return _T(""); }
	virtual TCHAR * buttonText(void) { return _T("OK"); }
	virtual bool isSilent(void) { return false; }
	virtual bool doObjectType(void) { return true; }
	virtual void proc(void) {}
	
	// accessors
	ShapeObject * getPath(void)	{ return path; }
	void setPath(ShapeObject * p) { path = p; }
 	CoreExport void setPath(Point3 pt1, Point3 pt2);       
 	CoreExport void setPath(Spline3D *s);    
	float getStart(void)	{ return start; }
	float getEnd(void)		{ return end; }
	float getSpace(void)	{ return space; }
	int getCount(void)		{ return count; }
	int getContext(void)	{ return context; }
	float getWidth(void) { return width; }
	void setStart(float f)	{ start = f; }
	void setEnd(float f)	{ end = f; }
	void setSpace(float f)	{ space = f; }
	void setCount(int n)	{ count = n > countLimit ? countLimit : n; }
	bool getFollow(void)	{ return follow; }
	void setFollow(bool t)	{ follow = t; }
  void setContext(CTYPE c)	{ context = c; }
	OTYPE getObjectCreationType(void)	{ return oType; }
	void setObjectCreationType(OTYPE t) { oType = t; }
	STYPE getSpacingType(void){ return sType; }
	void setSpacingType(STYPE s) { sType = s; }
	CoreExport void setMessage(char * buf);
	void setWidth(float nWidth) { width = nWidth; }
	void setCountLimit(int limit) { countLimit = limit; }
	int getCountLimit(void) { return countLimit; }
};

#endif