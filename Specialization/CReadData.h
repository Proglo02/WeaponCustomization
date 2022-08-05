#pragma once

#include <tgCV3D.h>

class CReadData
{
public:

	tgBool static LoadFile(tgCString filePath);

	void static UnloadCurrentFile();

	void static ReadString(tgCString searchTerm, tgCString* pString);
	void static ReadInt(tgCString searchTerm, tgUInt32* pInt);
	void static ReadFloat(tgCString searchTerm, tgFloat* pFloat);
	void static ReadBool(tgCString searchTerm, tgBool* pBool);
	void static ReadVector3(tgCString searchTerm, tgCV3D* pVector);

private:

	static tgUInt8* m_pData;
	static tgUInt32 m_Size;
};

