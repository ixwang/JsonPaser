//
//  RapidJsonMgr.cpp
//  tinyXMLSample
//
//  Created by xwang on 8/25/16.
//
//

#include "RapidJsonMgr.hpp"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "json/rapidjson.h"
#include "json/document.h"

using namespace rapidjson;

RapidJsonMgr::RapidJsonMgr()
: _isRootObject( true )
, _filename( "sample.json" )
{
    
}

RapidJsonMgr::~RapidJsonMgr()
{
    
}

RapidJsonMgr* RapidJsonMgr::rjMgr = nullptr;

RapidJsonMgr* RapidJsonMgr::getInstance()
{
    if( rjMgr == nullptr )
    {
        rjMgr = new RapidJsonMgr();
    }
    return rjMgr;
}

void RapidJsonMgr::writeJson()
{
    rapidjson::Document document;
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    
    if( _isRootObject )
    {
        // Define root as object
        document.SetObject();
        
        /*
         *  {
         *    "key" : "value",
         *    "ArrayKey" : ["ArrayValue","ArrayValue"],
         *    "object" :
         *    {
         *       "key" : "value"
         *    },
         *  }
         */
        
        // "key" : "value"
        document.AddMember( "key", rapidjson::Value( "value", allocator ), allocator );
        
        // "ArrayKey" : ["ArrayValue","ArrayValue"]
        rapidjson::Value array( rapidjson::kArrayType );
        int arraySize = 2;
        for ( int j = 0; j < arraySize; ++j )
        {
            array.PushBack( rapidjson::Value( "ArrayValue", allocator ), allocator );
        }
        document.AddMember( "ArrayKey", array, allocator );
        
        // "object" : { "key" : "value" }
        rapidjson::Value object( rapidjson::kObjectType );
        object.AddMember( "key", rapidjson::Value( "value", allocator ), allocator );
        document.AddMember( "object", object, allocator );
    }
    else
    {
        // Define root as array
        document.SetArray();
        
        /*
         *  [
         *      1,
         *      { "key" : "value" }
         *  ]
         */
        
        document.PushBack( 1, allocator );
        
        rapidjson::Value object( rapidjson::kObjectType );
        object.AddMember( "key", rapidjson::Value( "value", allocator ), allocator );
        document.PushBack( object, allocator );
    }
    
    // Get json string
    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer( buffer );
    document.Accept(writer);
    string jsonResult = buffer.GetString();

    // Save json file
    string filePath = cocos2d::FileUtils::getInstance()->getWritablePath().append( _filename );
    FILE *fp = fopen( filePath.c_str(), "wb" );
    fwrite( jsonResult.c_str(), 1, jsonResult.size(), fp );
    fclose( fp );
    
}
