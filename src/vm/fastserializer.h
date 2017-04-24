// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

#ifndef __FASTSERIALIZER_H__
#define __FASTSERIALIZER_H__

#include "fstream.h"

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

    FastSerializer(SString &outputFilePath);
    ~FastSerializer();

private:

    void WriteFileHeader();
    void Write(SString &contents);
    CFileStream *m_pFileStream;
    bool m_writeErrorEncountered;
};

#endif // __FASTSERIALIZER_H__
