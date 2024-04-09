// Copyright (c) 2024 Steven Frost and Orion Lyau

#pragma once

#include <Utils/Serialisation/Writer.h>

#include <rapidjson/document.h>
#include <rapidjson/pointer.h>

#include <stack>
#include <utility>

// -----------------------------------------------------------------------------

namespace Utils
{
namespace Serialisation
{

// -----------------------------------------------------------------------------

class JSONWriter
	: public Writer
{
public:

	JSONWriter();

	virtual bool WriteProperty( const PropertyName& Name, const bool Value ) override final;
	virtual bool WriteProperty( const PropertyName& Name, const float Value ) override final;
	virtual bool WriteProperty( const PropertyName& Name, const double Value ) override final;

	virtual bool WriteProperty( const PropertyName& Name, const int8_t Value ) override final;
	virtual bool WriteProperty( const PropertyName& Name, const int16_t Value ) override final;
	virtual bool WriteProperty( const PropertyName& Name, const int32_t Value ) override final;
	virtual bool WriteProperty( const PropertyName& Name, const int64_t Value ) override final;

	virtual bool WriteProperty( const PropertyName& Name, const uint8_t Value ) override final;
	virtual bool WriteProperty( const PropertyName& Name, const uint16_t Value ) override final;
	virtual bool WriteProperty( const PropertyName& Name, const uint32_t Value ) override final;
	virtual bool WriteProperty( const PropertyName& Name, const uint64_t Value ) override final;

	virtual bool WriteProperty( const PropertyName& Name, const std::string& Value ) override final;

	virtual std::string ToString() const override final;

private:

	virtual void BeginObject( const PropertyName& Name ) override final;
	virtual void EndObject() override final;

private:

	virtual void BeginArray( const PropertyName& Name ) override final;
	virtual void EndArray() override final;

	virtual void BeginArrayObject() override final;
	virtual void EndArrayObject() override final;

	virtual bool WriteArrayElement( const bool Value ) override final;
	virtual bool WriteArrayElement( const float Value ) override final;
	virtual bool WriteArrayElement( const double Value ) override final;

	virtual bool WriteArrayElement( const int8_t Value ) override final;
	virtual bool WriteArrayElement( const int16_t Value ) override final;
	virtual bool WriteArrayElement( const int32_t Value ) override final;
	virtual bool WriteArrayElement( const int64_t Value ) override final;

	virtual bool WriteArrayElement( const uint8_t Value ) override final;
	virtual bool WriteArrayElement( const uint16_t Value ) override final;
	virtual bool WriteArrayElement( const uint32_t Value ) override final;
	virtual bool WriteArrayElement( const uint64_t Value ) override final;

	virtual bool WriteArrayElement( const std::string& Value ) override final;

private:

	std::string CurrentPath() const;

	rapidjson::Value* CurrentObject();

private:

	typedef std::string PathName;
	typedef std::pair< PathName, rapidjson::Pointer > NamedPointer;

	rapidjson::Document					JsonDocument;
	rapidjson::MemoryPoolAllocator<>*	Allocator;

	std::stack< NamedPointer >			Stack;
};

// -----------------------------------------------------------------------------

} // namespace Serialisation
} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
