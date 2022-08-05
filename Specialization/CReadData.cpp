#include <tgSystem.h>

#include "CReadData.h"

#include <CStringParser.cpp>
#include <tgCFileSystem.h>
#include <tgMemoryDisable.h>
#include <filesystem>
#include <fstream>
#include <string>
#include <tgMemoryEnable.h>

tgUInt8* CReadData::m_pData = NULL;
tgUInt32 CReadData::m_Size = 0;

tgBool CReadData::LoadFile(tgCString filePath)
{
	if ((m_pData = tgCFileSystem::GetInstance().FileLoad(filePath.String(), &m_Size)) == NULL)
		return false;

	return true;
}

void CReadData::UnloadCurrentFile()
{
	if (m_pData)
	{
		delete[] m_pData;
		m_pData = NULL;
		m_Size = 0;
	}
}

void CReadData::ReadString(tgCString searchTerm, tgCString* pString)
{
	tgUInt32	BytesRead = 0;

	if (CStringParser::CheckUTF8BOM(m_pData))
		BytesRead = 3;

	tgChar		ValueBuffer[128];
	tgMemoryClear(ValueBuffer, sizeof(ValueBuffer));

	while (true)
	{

		if (BytesRead >= m_Size)
		{
			break;
		}

		tgCString	Line = CStringParser::ParseLine(m_pData, BytesRead);


		if (Line.String()[0] != '/' &&
			Line.String()[0] != '\r' &&
			Line.String()[0] != '\n' &&
			Line.String()[0] != 0)
		{
			sscanf(Line.String(), "%s", ValueBuffer);

			if (strcmp(ValueBuffer, searchTerm.String()) == 0)
			{
				tgUInt32	ValueBufferStart = (tgUInt32)(strstr(Line.String(), ValueBuffer) - Line.String()) + (tgUInt32)strlen(ValueBuffer);

				while (Line.String()[ValueBufferStart] == '\t' ||
					Line.String()[ValueBufferStart] == ' ')
					++ValueBufferStart;
				tgCString	Value = &Line.String()[ValueBufferStart];
				if (pString)
					*pString = Value;

				break;
			}
		}
	}
}

void CReadData::ReadInt(tgCString searchTerm, tgUInt32* pInt)
{
	tgUInt32	BytesRead = 0;

	if (CStringParser::CheckUTF8BOM(m_pData))
		BytesRead = 3;

	tgChar		ValueBuffer[128];
	tgMemoryClear(ValueBuffer, sizeof(ValueBuffer));

	while (true)
	{

		if (BytesRead >= m_Size)
		{
			break;
		}

		tgCString	Line = CStringParser::ParseLine(m_pData, BytesRead);


		if (Line.String()[0] != '/' &&
			Line.String()[0] != '\r' &&
			Line.String()[0] != '\n' &&
			Line.String()[0] != 0)
		{
			sscanf(Line.String(), "%s", ValueBuffer);

			if (strcmp(ValueBuffer, searchTerm.String()) == 0)
			{
				tgUInt32	ValueBufferStart = (tgUInt32)(strstr(Line.String(), ValueBuffer) - Line.String()) + (tgUInt32)strlen(ValueBuffer);

				while (Line.String()[ValueBufferStart] == '\t' ||
					Line.String()[ValueBufferStart] == ' ')
					++ValueBufferStart;

				tgUInt32	Value = strtod(&Line.String()[ValueBufferStart], NULL);
				if (pInt)
					*pInt = Value;

				break;
			}
		}
	}
}

void CReadData::ReadFloat(tgCString searchTerm, tgFloat* pFloat)
{
	tgUInt32	BytesRead = 0;

	if (CStringParser::CheckUTF8BOM(m_pData))
		BytesRead = 3;

	tgChar		ValueBuffer[128];
	tgMemoryClear(ValueBuffer, sizeof(ValueBuffer));

	while (true)
	{

		if (BytesRead >= m_Size)
		{
			break;
		}

		tgCString	Line = CStringParser::ParseLine(m_pData, BytesRead);


		if (Line.String()[0] != '/' &&
			Line.String()[0] != '\r' &&
			Line.String()[0] != '\n' &&
			Line.String()[0] != 0)
		{
			sscanf(Line.String(), "%s", ValueBuffer);

			if (strcmp(ValueBuffer, searchTerm.String()) == 0)
			{
				tgUInt32	ValueBufferStart = (tgUInt32)(strstr(Line.String(), ValueBuffer) - Line.String()) + (tgUInt32)strlen(ValueBuffer);

				while (Line.String()[ValueBufferStart] == '\t' ||
					Line.String()[ValueBufferStart] == ' ')
					++ValueBufferStart;

				tgFloat	Value = strtod(&Line.String()[ValueBufferStart], NULL);
				if (pFloat)
					*pFloat = Value;

				break;
			}
		}
	}
}

void CReadData::ReadBool(tgCString searchTerm, tgBool* pBool)
{
	tgUInt32	BytesRead = 0;

	if (CStringParser::CheckUTF8BOM(m_pData))
		BytesRead = 3;

	tgChar		ValueBuffer[128];
	tgMemoryClear(ValueBuffer, sizeof(ValueBuffer));

	while (true)
	{

		if (BytesRead >= m_Size)
		{
			break;
		}

		tgCString	Line = CStringParser::ParseLine(m_pData, BytesRead);


		if (Line.String()[0] != '/' &&
			Line.String()[0] != '\r' &&
			Line.String()[0] != '\n' &&
			Line.String()[0] != 0)
		{
			sscanf(Line.String(), "%s", ValueBuffer);

			if (strcmp(ValueBuffer, searchTerm.String()) == 0)
			{
				tgUInt32	ValueBufferStart = (tgUInt32)(strstr(Line.String(), ValueBuffer) - Line.String()) + (tgUInt32)strlen(ValueBuffer);

				while (Line.String()[ValueBufferStart] == '\t' ||
					Line.String()[ValueBufferStart] == ' ')
					++ValueBufferStart;

				tgUInt32 Value = 0;

				Value = strtod(&Line.String()[ValueBufferStart], NULL);

				if (pBool)
					*pBool = Value;

				break;
			}
		}
	}
}

void CReadData::ReadVector3(tgCString searchTerm, tgCV3D* pVector)
{
	tgUInt32	BytesRead = 0;

	if (CStringParser::CheckUTF8BOM(m_pData))
		BytesRead = 3;

	tgChar		ValueBuffer[128];
	tgMemoryClear(ValueBuffer, sizeof(ValueBuffer));

	while (true)
	{

		if (BytesRead >= m_Size)
		{
			break;
		}

		tgCString	Line = CStringParser::ParseLine(m_pData, BytesRead);


		if (Line.String()[0] != '/' &&
			Line.String()[0] != '\r' &&
			Line.String()[0] != '\n' &&
			Line.String()[0] != 0)
		{
			sscanf(Line.String(), "%s", ValueBuffer);

			if (strcmp(ValueBuffer, searchTerm.String()) == 0)
			{
				tgUInt32	ValueBufferStart = (tgUInt32)(strstr(Line.String(), ValueBuffer) - Line.String()) + (tgUInt32)strlen(ValueBuffer);

				while (Line.String()[ValueBufferStart] == '\t' ||
					Line.String()[ValueBufferStart] == ' ')
					++ValueBufferStart;

				tgCV3D	Value = tgCV3D(0.0f, 0.0f, 0.0f);

				Value.x = strtod(&Line.String()[ValueBufferStart], NULL);
				tgChar* chars = tgCString("%.3f", Value.x).String();
				ValueBufferStart += strlen(chars) + 1;
				Value.y = strtod(&Line.String()[ValueBufferStart], NULL);
				chars = tgCString("%.3f", Value.y).String();
				ValueBufferStart += strlen(chars) + 1;
				Value.z = strtod(&Line.String()[ValueBufferStart], NULL);

				if (pVector)
					*pVector = Value;

				break;
			}
		}
	}
}
