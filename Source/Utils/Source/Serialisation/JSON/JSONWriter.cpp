// Copyright (c) 2024 Steven Frost and Orion Lyau

#include <Utils/Serialisation/JSON/JSONWriter.h>

#include <Utils/Logging/Log.h>

#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

// -----------------------------------------------------------------------------

DEFINE_LOG_CATEGORY( JSONWriter, Info )

// -----------------------------------------------------------------------------

namespace Utils
{
namespace Serialisation
{

// -----------------------------------------------------------------------------

JSONWriter::JSONWriter()
	: JsonDocument()
	, Allocator( nullptr )
	, Stack()
{
	JsonDocument.SetObject();
	Allocator = &JsonDocument.GetAllocator();

	Stack.push( std::make_pair( "", rapidjson::Pointer( "" ) ) );
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteProperty( const PropertyName& Name, const bool Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to write property '%s' in object '%s' since the current object is invalid.", Name.c_str(), CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonKey;
	JsonKey.SetString( Name.c_str(), Name.length(), *Allocator );

	rapidjson::Value JsonValue;
	JsonValue.SetBool( Value );

	Object->AddMember( JsonKey, JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteProperty( const PropertyName& Name, const float Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to write property '%s' in object '%s' since the current object is invalid.", Name.c_str(), CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonKey;
	JsonKey.SetString( Name.c_str(), Name.length(), *Allocator );

	rapidjson::Value JsonValue;
	JsonValue.SetFloat( Value );

	Object->AddMember( JsonKey, JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteProperty( const PropertyName& Name, const double Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to write property '%s' in object '%s' since the current object is invalid.", Name.c_str(), CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonKey;
	JsonKey.SetString( Name.c_str(), Name.length(), *Allocator );

	rapidjson::Value JsonValue;
	JsonValue.SetDouble( Value );

	Object->AddMember( JsonKey, JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteProperty( const PropertyName& Name, const int8_t Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to write property '%s' in object '%s' since the current object is invalid.", Name.c_str(), CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonKey;
	JsonKey.SetString( Name.c_str(), Name.length(), *Allocator );

	rapidjson::Value JsonValue;
	JsonValue.SetInt( Value );

	Object->AddMember( JsonKey, JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteProperty( const PropertyName& Name, const int16_t Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to write property '%s' in object '%s' since the current object is invalid.", Name.c_str(), CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonKey;
	JsonKey.SetString( Name.c_str(), Name.length(), *Allocator );

	rapidjson::Value JsonValue;
	JsonValue.SetInt( Value );

	Object->AddMember( JsonKey, JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteProperty( const PropertyName& Name, const int32_t Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to write property '%s' in object '%s' since the current object is invalid.", Name.c_str(), CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonKey;
	JsonKey.SetString( Name.c_str(), Name.length(), *Allocator );

	rapidjson::Value JsonValue;
	JsonValue.SetInt( Value );

	Object->AddMember( JsonKey, JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteProperty( const PropertyName& Name, const int64_t Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to write property '%s' in object '%s' since the current object is invalid.", Name.c_str(), CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonKey;
	JsonKey.SetString( Name.c_str(), Name.length(), *Allocator );

	rapidjson::Value JsonValue;
	JsonValue.SetInt64( Value );

	Object->AddMember( JsonKey, JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteProperty( const PropertyName& Name, const uint8_t Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to write property '%s' in object '%s' since the current object is invalid.", Name.c_str(), CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonKey;
	JsonKey.SetString( Name.c_str(), Name.length(), *Allocator );

	rapidjson::Value JsonValue;
	JsonValue.SetUint( Value );

	Object->AddMember( JsonKey, JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteProperty( const PropertyName& Name, const uint16_t Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to write property '%s' in object '%s' since the current object is invalid.", Name.c_str(), CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonKey;
	JsonKey.SetString( Name.c_str(), Name.length(), *Allocator );

	rapidjson::Value JsonValue;
	JsonValue.SetUint( Value );

	Object->AddMember( JsonKey, JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteProperty( const PropertyName& Name, const uint32_t Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to write property '%s' in object '%s' since the current object is invalid.", Name.c_str(), CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonKey;
	JsonKey.SetString( Name.c_str(), Name.length(), *Allocator );

	rapidjson::Value JsonValue;
	JsonValue.SetUint( Value );

	Object->AddMember( JsonKey, JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteProperty( const PropertyName& Name, const uint64_t Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to write property '%s' in object '%s' since the current object is invalid.", Name.c_str(), CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonKey;
	JsonKey.SetString( Name.c_str(), Name.length(), *Allocator );

	rapidjson::Value JsonValue;
	JsonValue.SetUint64( Value );

	Object->AddMember( JsonKey, JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteProperty( const PropertyName& Name, const std::string& Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to write property '%s' in object '%s' since the current object is invalid.", Name.c_str(), CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonKey;
	JsonKey.SetString( Name.c_str(), Name.length(), *Allocator );

	rapidjson::Value JsonValue;
	JsonValue.SetString( Value.c_str(), Value.length(), *Allocator);

	Object->AddMember( JsonKey, JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

std::string JSONWriter::ToString() const
{
	rapidjson::StringBuffer StringBuffer;
	rapidjson::PrettyWriter< rapidjson::StringBuffer > Writer( StringBuffer );

	JsonDocument.Accept( Writer );

	return StringBuffer.GetString();
}

// -----------------------------------------------------------------------------

void JSONWriter::BeginObject( const PropertyName& Name )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to write property '%s' in object '%s' since the current object is invalid.", Name.c_str(), CurrentPath().c_str() );
		return;
	}

	rapidjson::Value JsonKey;
	JsonKey.SetString( Name.c_str(), Name.length(), *Allocator );

	Object->AddMember( JsonKey, rapidjson::Value( rapidjson::kObjectType ), *Allocator );

	const std::string Path = CurrentPath().append( "/" ).append( Name );
	Stack.push( std::make_pair( Path, rapidjson::Pointer( Path.c_str() ) ) );
}

// -----------------------------------------------------------------------------

void JSONWriter::EndObject()
{
	Stack.pop();
}

// -----------------------------------------------------------------------------

void JSONWriter::BeginArray( const PropertyName& Name )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to write property '%s' in object '%s' since the current object is invalid.", Name.c_str(), CurrentPath().c_str() );
		return;
	}

	rapidjson::Value JsonKey;
	JsonKey.SetString( Name.c_str(), Name.length(), *Allocator );

	Object->AddMember( JsonKey, rapidjson::Value( rapidjson::kArrayType ), *Allocator );

	const std::string Path = CurrentPath().append( "/" ).append( Name );
	Stack.push( std::make_pair( Path, rapidjson::Pointer( Path.c_str() ) ) );
}

// -----------------------------------------------------------------------------

void JSONWriter::EndArray()
{
	Stack.pop();
}

// -----------------------------------------------------------------------------

void JSONWriter::BeginArrayObject()
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to add a new object in array '%s' since the current object is invalid.", CurrentPath().c_str() );
		return;
	}

	const size_t ArraySize = Object->Size();

	Object->PushBack( rapidjson::Value( rapidjson::kObjectType ), *Allocator );

	const std::string Path = CurrentPath().append( "/" ).append( std::to_string( ArraySize ) );
	Stack.push( std::make_pair( Path, rapidjson::Pointer( Path.c_str() ) ) );
}

// -----------------------------------------------------------------------------

void JSONWriter::EndArrayObject()
{
	Stack.pop();
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteArrayElement( const bool Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to add a new element to array '%s' since the current object is invalid.", CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonValue;
	JsonValue.SetBool( Value );

	Object->PushBack( JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteArrayElement( const float Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to add a new element to array '%s' since the current object is invalid.", CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonValue;
	JsonValue.SetFloat( Value );

	Object->PushBack( JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteArrayElement( const double Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to add a new element to array '%s' since the current object is invalid.", CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonValue;
	JsonValue.SetDouble( Value );

	Object->PushBack( JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteArrayElement( const int8_t Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to add a new element to array '%s' since the current object is invalid.", CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonValue;
	JsonValue.SetInt( Value );

	Object->PushBack( JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteArrayElement( const int16_t Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to add a new element to array '%s' since the current object is invalid.", CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonValue;
	JsonValue.SetInt( Value );

	Object->PushBack( JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteArrayElement( const int32_t Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to add a new element to array '%s' since the current object is invalid.", CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonValue;
	JsonValue.SetInt( Value );

	Object->PushBack( JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteArrayElement( const int64_t Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to add a new element to array '%s' since the current object is invalid.", CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonValue;
	JsonValue.SetInt64( Value );

	Object->PushBack( JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteArrayElement( const uint8_t Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to add a new element to array '%s' since the current object is invalid.", CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonValue;
	JsonValue.SetUint( Value );

	Object->PushBack( JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteArrayElement( const uint16_t Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to add a new element to array '%s' since the current object is invalid.", CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonValue;
	JsonValue.SetUint( Value );

	Object->PushBack( JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteArrayElement( const uint32_t Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to add a new element to array '%s' since the current object is invalid.", CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonValue;
	JsonValue.SetUint( Value );

	Object->PushBack( JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteArrayElement( const uint64_t Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to add a new element to array '%s' since the current object is invalid.", CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonValue;
	JsonValue.SetUint64( Value );

	Object->PushBack( JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONWriter::WriteArrayElement( const std::string& Value )
{
	auto* Object = CurrentObject();
	if ( !Object )
	{
		LOG( JSONWriter, Error, "Unable to add a new element to array '%s' since the current object is invalid.", CurrentPath().c_str() );
		return false;
	}

	rapidjson::Value JsonValue;
	JsonValue.SetString( Value.c_str(), Value.length(), *Allocator );

	Object->PushBack( JsonValue, *Allocator );
	return true;
}

// -----------------------------------------------------------------------------

std::string JSONWriter::CurrentPath() const
{
	return Stack.top().first;
}

// -----------------------------------------------------------------------------

rapidjson::Value* JSONWriter::CurrentObject()
{
	auto Pointer = Stack.top().second;
	return Pointer.Get( JsonDocument );
}

// -----------------------------------------------------------------------------

} // namespace Serialisation
} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
