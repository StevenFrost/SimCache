// Copyright (c) 2024 Steven Frost and Orion Lyau

#include <Utils/Serialisation/JSON/JSONReader.h>

#include <Utils/Logging/Log.h>

// -----------------------------------------------------------------------------

DEFINE_LOG_CATEGORY( JSONReader, Info )

// -----------------------------------------------------------------------------

namespace Utils
{
namespace Serialisation
{

// -----------------------------------------------------------------------------

JSONReader::JSONReader( const std::string& Data )
	: JsonDocument()
	, Stack()
{
	JsonDocument.Parse( Data.c_str() );

	Stack.push( std::make_pair( "", rapidjson::Pointer( "" ) ) );
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadProperty( const PropertyName& Name, bool& Value )
{
	auto* Member = GetMember( Name );
	if ( !Member )
	{
		LOG( JSONReader, Error, "Unable to resolve member '%s' in object '%s'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	if ( !Member->IsBool() )
	{
		LOG( JSONReader, Error, "Member '%s' in object '%s' is not of type 'bool'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	Value = Member->GetBool();
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadProperty( const PropertyName& Name, float& Value )
{
	auto* Member = GetMember( Name );
	if ( !Member )
	{
		LOG( JSONReader, Error, "Unable to resolve member '%s' in object '%s'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	if ( !Member->IsFloat() )
	{
		LOG( JSONReader, Error, "Member '%s' in object '%s' is not of type 'float'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	Value = Member->GetFloat();
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadProperty( const PropertyName& Name, double& Value )
{
	auto* Member = GetMember( Name );
	if ( !Member )
	{
		LOG( JSONReader, Error, "Unable to resolve member '%s' in object '%s'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	if ( !Member->IsDouble() )
	{
		LOG( JSONReader, Error, "Member '%s' in object '%s' is not of type 'double'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	Value = Member->GetDouble();
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadProperty( const PropertyName& Name, int8_t& Value )
{
	auto* Member = GetMember( Name );
	if ( !Member )
	{
		LOG( JSONReader, Error, "Unable to resolve member '%s' in object '%s'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	if ( !Member->IsInt() )
	{
		LOG( JSONReader, Error, "Member '%s' in object '%s' is not of type 'int'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	Value = static_cast< int8_t >( Member->GetInt() );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadProperty( const PropertyName& Name, int16_t& Value )
{
	auto* Member = GetMember( Name );
	if ( !Member )
	{
		LOG( JSONReader, Error, "Unable to resolve member '%s' in object '%s'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	if ( !Member->IsInt() )
	{
		LOG( JSONReader, Error, "Member '%s' in object '%s' is not of type 'int'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	Value = static_cast< int16_t >( Member->GetInt() );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadProperty( const PropertyName& Name, int32_t& Value )
{
	auto* Member = GetMember( Name );
	if ( !Member )
	{
		LOG( JSONReader, Error, "Unable to resolve member '%s' in object '%s'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	if ( !Member->IsInt() )
	{
		LOG( JSONReader, Error, "Member '%s' in object '%s' is not of type 'int'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	Value = static_cast< int32_t >( Member->GetInt() );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadProperty( const PropertyName& Name, int64_t& Value )
{
	auto* Member = GetMember( Name );
	if ( !Member )
	{
		LOG( JSONReader, Error, "Unable to resolve member '%s' in object '%s'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	if ( !Member->IsInt64() )
	{
		LOG( JSONReader, Error, "Member '%s' in object '%s' is not of type '64-bit int'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	Value = static_cast< int64_t >( Member->GetInt64() );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadProperty( const PropertyName& Name, uint8_t& Value )
{
	auto* Member = GetMember( Name );
	if ( !Member )
	{
		LOG( JSONReader, Error, "Unable to resolve member '%s' in object '%s'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	if ( !Member->IsUint() )
	{
		LOG( JSONReader, Error, "Member '%s' in object '%s' is not of type 'unsigned int'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	Value = static_cast< uint8_t >( Member->GetUint() );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadProperty( const PropertyName& Name, uint16_t& Value )
{
	auto* Member = GetMember( Name );
	if ( !Member )
	{
		LOG( JSONReader, Error, "Unable to resolve member '%s' in object '%s'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	if ( !Member->IsUint() )
	{
		LOG( JSONReader, Error, "Member '%s' in object '%s' is not of type 'unsigned int'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	Value = static_cast< uint16_t >( Member->GetUint() );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadProperty( const PropertyName& Name, uint32_t& Value )
{
	auto* Member = GetMember( Name );
	if ( !Member )
	{
		LOG( JSONReader, Error, "Unable to resolve member '%s' in object '%s'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	if ( !Member->IsUint() )
	{
		LOG( JSONReader, Error, "Member '%s' in object '%s' is not of type 'unsigned int'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	Value = static_cast< uint32_t >( Member->GetUint() );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadProperty( const PropertyName& Name, uint64_t& Value )
{
	auto* Member = GetMember( Name );
	if ( !Member )
	{
		LOG( JSONReader, Error, "Unable to resolve member '%s' in object '%s'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	if ( !Member->IsUint64() )
	{
		LOG( JSONReader, Error, "Member '%s' in object '%s' is not of type '64-bit unsigned int'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	Value = static_cast< uint64_t >( Member->GetUint64() );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadProperty( const PropertyName& Name, std::string& Value )
{
	auto* Member = GetMember( Name );
	if ( !Member )
	{
		LOG( JSONReader, Error, "Unable to resolve member '%s' in object '%s'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	if ( !Member->IsString() )
	{
		LOG( JSONReader, Error, "Member '%s' in object '%s' is not of type 'string'.", Name.c_str(), GetCurrentPath().c_str() );
		return false;
	}

	Value = Member->GetString();
	return true;
}

// -----------------------------------------------------------------------------

void JSONReader::BeginObject( const PropertyName& Name )
{
	const std::string ObjectPath = GetCurrentPath().append( "/" ).append( Name );
	Stack.push( std::make_pair( ObjectPath, rapidjson::Pointer( ObjectPath.c_str() ) ) );
}

// -----------------------------------------------------------------------------

void JSONReader::EndObject()
{
	Stack.pop();
}

// -----------------------------------------------------------------------------

size_t JSONReader::GetArraySize() const
{
	auto* Object = GetCurrentObject();
	if ( !Object )
	{
		LOG( JSONReader, Error, "Unable to determine the array size of an invalid object" );
		return 0;
	}

	if ( !Object->IsArray() )
	{
		LOG( JSONReader, Error, "Object '%s' is not an array", GetCurrentPath().c_str() );
		return 0;
	}

	return Object->Size();
}

// -----------------------------------------------------------------------------

void JSONReader::BeginArray( const PropertyName& Name )
{
	const std::string Path = GetCurrentPath().append( "/" ).append( Name );
	Stack.push( std::make_pair( Path, rapidjson::Pointer( Path.c_str() ) ) );
}

// -----------------------------------------------------------------------------

void JSONReader::EndArray()
{
	Stack.pop();
}

// -----------------------------------------------------------------------------

void JSONReader::BeginArrayObject( const size_t Index )
{
	const std::string Path = GetCurrentPath().append( "/" ).append( std::to_string( Index ) );
	Stack.push( std::make_pair( Path, rapidjson::Pointer( Path.c_str() ) ) );
}

// -----------------------------------------------------------------------------

void JSONReader::EndArrayObject()
{
	Stack.pop();
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadArrayElement( bool& Value )
{
	auto* Object = GetCurrentObject();
	if ( !Object )
	{
		LOG( JSONReader, Error, "Unable to read an array element from an invalid object" );
		return false;
	}

	if ( !Object->IsBool() )
	{
		LOG( JSONReader, Error, "Array element '%s' is not of type 'bool'.", GetCurrentPath().c_str() );
		return false;
	}

	Value = Object->GetBool();
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadArrayElement( float& Value )
{
	auto* Object = GetCurrentObject();
	if ( !Object )
	{
		LOG( JSONReader, Error, "Unable to read an array element from an invalid object" );
		return false;
	}

	if ( !Object->IsFloat() )
	{
		LOG( JSONReader, Error, "Array element '%s' is not of type 'float'.", GetCurrentPath().c_str() );
		return false;
	}

	Value = Object->GetFloat();
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadArrayElement( double& Value )
{
	auto* Object = GetCurrentObject();
	if ( !Object )
	{
		LOG( JSONReader, Error, "Unable to read an array element from an invalid object" );
		return false;
	}

	if ( !Object->IsDouble() )
	{
		LOG( JSONReader, Error, "Array element '%s' is not of type 'double'.", GetCurrentPath().c_str() );
		return false;
	}

	Value = Object->GetDouble();
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadArrayElement( int8_t& Value )
{
	auto* Object = GetCurrentObject();
	if ( !Object )
	{
		LOG( JSONReader, Error, "Unable to read an array element from an invalid object" );
		return false;
	}

	if ( !Object->IsInt() )
	{
		LOG( JSONReader, Error, "Array element '%s' is not of type 'int'.", GetCurrentPath().c_str() );
		return false;
	}

	Value = static_cast< int8_t >( Object->GetInt() );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadArrayElement( int16_t& Value )
{
	auto* Object = GetCurrentObject();
	if ( !Object )
	{
		LOG( JSONReader, Error, "Unable to read an array element from an invalid object" );
		return false;
	}

	if ( !Object->IsInt() )
	{
		LOG( JSONReader, Error, "Array element '%s' is not of type 'int'.", GetCurrentPath().c_str() );
		return false;
	}

	Value = static_cast< int16_t >( Object->GetInt() );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadArrayElement( int32_t& Value )
{
	auto* Object = GetCurrentObject();
	if ( !Object )
	{
		LOG( JSONReader, Error, "Unable to read an array element from an invalid object" );
		return false;
	}

	if ( !Object->IsInt() )
	{
		LOG( JSONReader, Error, "Array element '%s' is not of type 'int'.", GetCurrentPath().c_str() );
		return false;
	}

	Value = static_cast< int32_t >( Object->GetInt() );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadArrayElement( int64_t& Value )
{
	auto* Object = GetCurrentObject();
	if ( !Object )
	{
		LOG( JSONReader, Error, "Unable to read an array element from an invalid object" );
		return false;
	}

	if ( !Object->IsInt64() )
	{
		LOG( JSONReader, Error, "Array element '%s' is not of type '64-bit int'.", GetCurrentPath().c_str() );
		return false;
	}

	Value = static_cast< int64_t >( Object->GetInt64() );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadArrayElement( uint8_t& Value )
{
	auto* Object = GetCurrentObject();
	if ( !Object )
	{
		LOG( JSONReader, Error, "Unable to read an array element from an invalid object" );
		return false;
	}

	if ( !Object->IsUint() )
	{
		LOG( JSONReader, Error, "Array element '%s' is not of type 'unsigned int'.", GetCurrentPath().c_str() );
		return false;
	}

	Value = static_cast< uint8_t >( Object->GetUint() );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadArrayElement( uint16_t& Value )
{
	auto* Object = GetCurrentObject();
	if ( !Object )
	{
		LOG( JSONReader, Error, "Unable to read an array element from an invalid object" );
		return false;
	}

	if ( !Object->IsUint() )
	{
		LOG( JSONReader, Error, "Array element '%s' is not of type 'unsigned int'.", GetCurrentPath().c_str() );
		return false;
	}

	Value = static_cast< uint16_t >( Object->GetUint() );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadArrayElement( uint32_t& Value )
{
	auto* Object = GetCurrentObject();
	if ( !Object )
	{
		LOG( JSONReader, Error, "Unable to read an array element from an invalid object" );
		return false;
	}

	if ( !Object->IsUint() )
	{
		LOG( JSONReader, Error, "Array element '%s' is not of type 'unsigned int'.", GetCurrentPath().c_str() );
		return false;
	}

	Value = static_cast< uint32_t >( Object->GetUint() );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadArrayElement( uint64_t& Value )
{
	auto* Object = GetCurrentObject();
	if ( !Object )
	{
		LOG( JSONReader, Error, "Unable to read an array element from an invalid object" );
		return false;
	}

	if ( !Object->IsUint64() )
	{
		LOG( JSONReader, Error, "Array element '%s' is not of type '64-bit unsigned int'.", GetCurrentPath().c_str() );
		return false;
	}

	Value = static_cast< uint64_t >( Object->GetUint64() );
	return true;
}

// -----------------------------------------------------------------------------

bool JSONReader::ReadArrayElement( std::string& Value )
{
	auto* Object = GetCurrentObject();
	if ( !Object )
	{
		LOG( JSONReader, Error, "Unable to read an array element from an invalid object" );
		return false;
	}

	if ( !Object->IsString() )
	{
		LOG( JSONReader, Error, "Array element '%s' is not of type 'string'.", GetCurrentPath().c_str() );
		return false;
	}

	Value = Object->GetString();
	return true;
}

// -----------------------------------------------------------------------------

std::string JSONReader::GetCurrentPath() const
{
	return Stack.top().first;
}

// -----------------------------------------------------------------------------

rapidjson::Value* JSONReader::GetCurrentObject()
{
	auto Pointer = Stack.top().second;
	return Pointer.Get( JsonDocument );
}

// -----------------------------------------------------------------------------

const rapidjson::Value* JSONReader::GetCurrentObject() const
{
	auto Pointer = Stack.top().second;
	return Pointer.Get( JsonDocument );
}

// -----------------------------------------------------------------------------

rapidjson::Value* JSONReader::GetMember( const PropertyName& Name )
{
	auto* Object = GetCurrentObject();
	if ( !Object )
	{
		return nullptr;
	}

	auto MemberIt = Object->FindMember( Name.c_str() );
	if ( MemberIt == Object->MemberEnd() )
	{
		return nullptr;
	}

	return &MemberIt->value;
}

// -----------------------------------------------------------------------------

} // namespace Serialisation
} // namespace Utils

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
