// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

#include "common.h"
#include "eventpipeevent.h"
#include "eventpipeprovider.h"

EventPipeEvent::EventPipeEvent(EventPipeProvider &provider, INT64 keywords, int eventID, int level, bool needStack)
{
    LIMITED_METHOD_CONTRACT;

    m_pProvider = &provider;
    m_keywords = keywords;
    m_eventID = eventID;
    m_level = level;
    m_needStack = needStack;
}

EventPipeProvider* EventPipeEvent::GetProvider() const
{
    LIMITED_METHOD_CONTRACT;

    return m_pProvider;
}

INT64 EventPipeEvent::GetKeywords() const
{
    LIMITED_METHOD_CONTRACT;

    return m_keywords;
}

int EventPipeEvent::GetEventID() const
{
    LIMITED_METHOD_CONTRACT;

    return m_eventID;
}

int EventPipeEvent::GetLevel() const
{
    LIMITED_METHOD_CONTRACT;

    return m_level;
}

bool EventPipeEvent::NeedStack() const
{
    LIMITED_METHOD_CONTRACT;

    return m_needStack;
}

bool EventPipeEvent::IsEnabled() const
{
    LIMITED_METHOD_CONTRACT;

    return m_pProvider->EventEnabled(m_keywords, m_level);
}
