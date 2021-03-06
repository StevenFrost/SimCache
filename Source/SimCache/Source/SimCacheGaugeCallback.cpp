/**********************************************************************************
*                                                                                *
* Copyright (c) 2016 Steven Frost, Orion Lyau. All rights reserved.              *
*                                                                                *
* This source is subject to the MIT License.                                     *
* See http://opensource.org/licenses/MIT                                         *
*                                                                                *
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,    *
* EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED          *
* WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.         *
*                                                                                *
**********************************************************************************/

#include "SimCacheGaugeCallback.h"

#include <Localization/Resolver.h>

namespace SimCache
{

//-----------------------------------------------------------------------------

enum SimCacheVar
{
    SIMCACHE_VAR_DISTANCE,
    SIMCACHE_VAR_NAME,
    SIMCACHE_VAR_HINT,
    SIMCACHE_VAR_STATUS,
    SIMCACHE_VAR_INDEX,
};

//-----------------------------------------------------------------------------

SimCacheGaugeCallback::SimCacheGaugeCallback(UINT32 containerId) :
    m_refCount(1),
    m_containerId(containerId),
    m_distanceToSimCache(1.0),
    m_simCacheIndex(0.0),
    m_unitsRadians(get_units_enum("radians")),
    m_unitsMeters(get_units_enum("meters")),
    m_aircraftVarLatitude(get_aircraft_var_enum("PLANE LATITUDE")),
    m_aircraftVarLongitude(get_aircraft_var_enum("PLANE LONGITUDE")),
    m_aircraftVarAltitude(get_aircraft_var_enum("PLANE ALTITUDE"))
{}

//-----------------------------------------------------------------------------

ULONG SimCacheGaugeCallback::AddRef()
{
    return ++m_refCount;
}

//-----------------------------------------------------------------------------

ULONG SimCacheGaugeCallback::Release()
{
    ULONG result = --m_refCount;
    if (result < 1)
    {
        delete this;
    }
    return result;
}

//-----------------------------------------------------------------------------

void SimCacheGaugeCallback::Update()
{
    FLOAT64 currentLat = aircraft_varget(m_aircraftVarLatitude, m_unitsRadians, 0);
    FLOAT64 currentLon = aircraft_varget(m_aircraftVarLongitude, m_unitsRadians, 0);
    FLOAT64 currentAlt = aircraft_varget(m_aircraftVarAltitude, m_unitsMeters, 0);

    m_distanceToSimCache = SimCache::CacheManager::Instance().CurrentCache()->GetDistance(Transformations::FromEllipsoidal(currentLat, currentLon, currentAlt));
}

//-----------------------------------------------------------------------------

bool SimCacheGaugeCallback::GetPropertyValue(SINT32 id, FLOAT64* value)
{
    if (!value)
    {
        return false;
    }

    *value = 1.0;
    SimCacheVar var = static_cast<SimCacheVar>(id);

    switch (var)
    {
    case SIMCACHE_VAR_DISTANCE:
        *value = GetSimCacheDistance();
        break;
    case SIMCACHE_VAR_INDEX:
        *value = GetSimCacheIndex();
        break;
    default:
        return false;
    }
    return true;
}

//-----------------------------------------------------------------------------

bool SimCacheGaugeCallback::GetPropertyValue(SINT32 id, PCSTRINGZ* value)
{
    if (!value)
    {
        return false;
    }

    *value = "null";
    SimCacheVar var = static_cast<SimCacheVar>(id);

    switch (var)
    {
    case SIMCACHE_VAR_NAME:
        *value = GetSimCacheName();
        break;
    case SIMCACHE_VAR_HINT:
        *value = GetSimCacheHint();
        break;
    case SIMCACHE_VAR_STATUS:
        *value = GetSimCacheStatus();
        break;
    default:
        return false;
    }
    return true;
}

//-----------------------------------------------------------------------------

bool SimCacheGaugeCallback::SetPropertyValue(SINT32 id, FLOAT64 value)
{
    SimCacheVar var = static_cast<SimCacheVar>(id);

    switch (var)
    {
    case SIMCACHE_VAR_INDEX:
        SetSimCacheIndex(value);
        break;
    default:
        return false;
    }
    return true;
}

//-----------------------------------------------------------------------------

bool SimCacheGaugeCallback::SetPropertyValue(SINT32 id, PCSTRINGZ value)
{
    return false;
}

//-----------------------------------------------------------------------------

IGaugeCDrawable* SimCacheGaugeCallback::CreateGaugeCDrawable(SINT32 id, const IGaugeCDrawableCreateParameters* parameters)
{
    return nullptr;
}

//-----------------------------------------------------------------------------

double SimCacheGaugeCallback::GetSimCacheDistance() const
{
    return m_distanceToSimCache;
}

//-----------------------------------------------------------------------------

const char* SimCacheGaugeCallback::GetSimCacheName() const
{
    return SimCache::CacheManager::Instance().CurrentCache()->GetName().c_str();
}

//-----------------------------------------------------------------------------

const char* SimCacheGaugeCallback::GetSimCacheHint() const
{
    return SimCache::CacheManager::Instance().CurrentCache()->GetHint().c_str();
}

//-----------------------------------------------------------------------------

const char* SimCacheGaugeCallback::GetSimCacheStatus() const
{
    if (m_distanceToSimCache < 1852 * 2)
    {
        return Localization::GetString("distance_l2nm").c_str();
    }
    else if (m_distanceToSimCache < 1852 * 5)
    {
        return Localization::GetString("distance_l5nm").c_str();
    }
    else if (m_distanceToSimCache < 1852 * 10)
    {
        return Localization::GetString("distance_l10nm").c_str();
    }
    else if (m_distanceToSimCache < 1852 * 25)
    {
        return Localization::GetString("distance_l25nm").c_str();
    }
    else if (m_distanceToSimCache < 1852 * 50)
    {
        return Localization::GetString("distance_l50nm").c_str();
    }
    return Localization::GetString("distance_g50nm").c_str();
}

//-----------------------------------------------------------------------------

double SimCacheGaugeCallback::GetSimCacheIndex() const
{
    return m_simCacheIndex;
}

//-----------------------------------------------------------------------------

void SimCacheGaugeCallback::SetSimCacheIndex(double value)
{
    if (value > m_simCacheIndex)
    {
        SimCache::CacheManager::Instance().NextCache();
    }
    else
    {
        SimCache::CacheManager::Instance().PreviousCache();
    }
    m_simCacheIndex = value;
}

//-----------------------------------------------------------------------------

} // namespace SimCache
