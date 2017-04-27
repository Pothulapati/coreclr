// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

#ifndef __FASTSERIALIZER_H__
#define __FASTSERIALIZER_H__

#include "fastserializableobject.h"
#include "fstream.h"

class FastSerializer;

enum class FastSerializerTags : BYTE 
{
    Error,              // To improve debugabilty, 0 is an illegal tag.  
    NullReference,      // Tag for a null object forwardReference. 
    ObjectReference,    // Followed by StreamLabel 
    ForwardReference,   // Followed by an index (32-bit integer) into the Forward forwardReference array and a Type object
    BeginObject,        // Followed by Type object, object data, tagged EndObject
    BeginPrivateObject, // Like beginObject, but not placed in interning table on deserialiation 
    EndObject,          // Placed after an object to mark its end. 
    ForwardDefinition,  // Followed by a forward forwardReference index and an object definition (BeginObject)
    Byte,
    Int16,
    Int32,
    Int64,
    SkipRegion,
    String,
    Limit,              // Just past the last valid tag, used for asserts.  
};

class FastSerializer
{
public:

    FastSerializer(SString &outputFilePath, FastSerializableObject &object);
    ~FastSerializer();

    unsigned int GetStreamLabel() const;
    void GoToStreamLabel(unsigned int streamLabel);

    void WriteObject(FastSerializableObject *pObject);
    void WriteBuffer(BYTE *pBuffer, size_t length);
    void WriteTag(FastSerializerTags tag, BYTE *payload = NULL, size_t payloadLength = 0);
    void WriteString(const char *strContents, int length);

private:

    void WriteEntryObject();
    void WriteSerializationType(FastSerializableObject *pObject);
    void WriteFileHeader();
    CFileStream *m_pFileStream;
    bool m_writeErrorEncountered;
    FastSerializableObject *m_pEntryObject;
    size_t m_currentPos;
};

#endif // __FASTSERIALIZER_H__