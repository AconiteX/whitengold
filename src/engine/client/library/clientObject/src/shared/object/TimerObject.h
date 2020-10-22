// ======================================================================
//
// TimerObject.h
// asommers 8-2-99
//
// copyright 1999, bootprint entertainment
// copyright 2002, sony online entertainment
//
// ======================================================================

#ifndef INCLUDED_TimerObject_H
#define INCLUDED_TimerObject_H

// ======================================================================

#include "sharedFoundation/MemoryBlockManagerMacros.h"
#include "sharedObject/Object.h"
#include "sharedFoundation/Timer.h"

class MemoryBlockManager;

// ======================================================================

class TimerObject : public Object
{
	MEMORY_BLOCK_MANAGER_INTERFACE_WITH_INSTALL;

public:

	explicit TimerObject (float newTime, bool ignoreFirstAlter = false);
	virtual ~TimerObject ();

	virtual float alter (float elapsedTime);

private:

	TimerObject ();
	TimerObject (const TimerObject&);
	TimerObject& operator= (const TimerObject&);

private:

	bool  m_ignoreFirstAlter;
	Timer m_timer;
};

// ======================================================================

#endif
