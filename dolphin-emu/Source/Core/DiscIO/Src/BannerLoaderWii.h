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

#ifndef _BANNER_LOADER_WII_H_
#define _BANNER_LOADER_WII_H_

#include "BannerLoader.h"

namespace DiscIO
{
class CBannerLoaderWii
	: public IBannerLoader
{
	public:

		CBannerLoaderWii(DiscIO::IVolume *pVolume);

		virtual ~CBannerLoaderWii();

		virtual bool IsValid();

		virtual bool GetBanner(u32* _pBannerImage);

		virtual bool GetName(std::string* _rName);

		bool GetName(std::vector<std::wstring>&  _rNames);

		virtual bool GetCompany(std::string& _rCompany);

		virtual bool GetDescription(std::string* _rDescription);

		bool GetDescription(std::wstring& _rDescription);

	private:
		
		enum
		{
			TEXTURE_SIZE = 192 * 64 * 2,
			ICON_SIZE = 48 * 48 * 2,
			COMMENT_SIZE = 32
		};

		enum CommentIndex
		{
			NAME_IDX,
			DESC_IDX
		};

		struct SWiiBanner
		{
			u32 ID;

			u32 m_Flag;
			u16 m_Speed;
			u8  m_Unknown[22];

			// Not null terminated!
			u16 m_Comment[2][COMMENT_SIZE];
			u8  m_BannerTexture[TEXTURE_SIZE];
			u8  m_IconTexture[8][ICON_SIZE];
		} ;

		u8* m_pBannerFile;

		bool m_IsValid;

		void decode5A3image(u32* dst, u16* src, int width, int height);

		bool GetStringFromComments(const CommentIndex index, std::string& s);
		bool GetStringFromComments(const CommentIndex index, std::wstring& s);
};
} // namespace

#endif

