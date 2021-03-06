// Copyright (C) 2003-2009 Dolphin Project.

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

#ifndef _DEBUGUTIL_H
#define _DEBUGUTIL_H

namespace DebugUtil
{
    void Init();

    void GetTextureBGRA(u8 *dst, u32 texmap, s32 mip, u32 width, u32 height);

    void DumpActiveTextures();

    void OnObjectBegin();
    void OnObjectEnd();

    void OnFrameEnd();

    void DrawObjectBuffer(s16 x, s16 y, u8 *color, int bufferBase, int subBuffer, const char *name);

	void DrawTempBuffer(u8 *color, int buffer);
	void CopyTempBuffer(s16 x, s16 y, int bufferBase, int subBuffer, const char *name);
}

#endif 
