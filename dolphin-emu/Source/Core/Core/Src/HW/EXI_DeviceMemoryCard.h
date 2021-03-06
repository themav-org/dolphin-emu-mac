// Copyright (C) 2003 Dolphin Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official SVN repository and contact information can be found at
// http://code.google.com/p/dolphin-emu/

#ifndef _EXI_DEVICEMEMORYCARD_H
#define _EXI_DEVICEMEMORYCARD_H

#include "Thread.h"

// Data structure to be passed to the flushing thread.
struct FlushData
{
	bool bExiting;
	std::string filename;
	u8 *memcardContent;
	int memcardSize, memcardIndex;
};

class CEXIMemoryCard : public IEXIDevice
{
public:
	CEXIMemoryCard(const int index);
	virtual ~CEXIMemoryCard();
	void SetCS(int cs);
	void Update();
	bool IsInterruptSet();
	bool IsPresent();
	void DoState(PointerWrap &p);
	void PauseAndLock(bool doLock, bool unpauseOnUnlock=true);
	IEXIDevice* FindDevice(TEXIDevices device_type, int customIndex=-1);

private:
	// This is scheduled whenever a page write is issued. The this pointer is passed
	// through the userdata parameter, so that it can then call Flush on the right card.
	static void FlushCallback(u64 userdata, int cyclesLate);

	// Flushes the memory card contents to disk.
	void Flush(bool exiting = false);

	enum 
	{
		cmdNintendoID			= 0x00,
		cmdReadArray			= 0x52,
		cmdArrayToBuffer		= 0x53,
		cmdSetInterrupt			= 0x81,
		cmdWriteBuffer			= 0x82,
		cmdReadStatus			= 0x83,
		cmdReadID				= 0x85,
		cmdReadErrorBuffer		= 0x86,
		cmdWakeUp				= 0x87,
		cmdSleep				= 0x88,
		cmdClearStatus			= 0x89,
		cmdSectorErase			= 0xF1,
		cmdPageProgram			= 0xF2,
		cmdExtraByteProgram		= 0xF3,
		cmdChipErase			= 0xF4,
	};

	std::string m_strFilename;
	int card_index;
	int et_this_card;
	//! memory card state

	// STATE_TO_SAVE
	int interruptSwitch;
	bool m_bInterruptSet;
	int command;
	int status;
	u32 m_uPosition;
	u8 programming_buffer[128];
	u32 formatDelay;
	bool m_bDirty;
	//! memory card parameters 
	unsigned int nintendo_card_id, card_id;
	unsigned int address;	
	int memory_card_size; //! in bytes, must be power of 2.
	u8 *memory_card_content; 

	FlushData flushData;
	std::thread flushThread;
	
protected:
	virtual void TransferByte(u8 &byte);
};

#endif

