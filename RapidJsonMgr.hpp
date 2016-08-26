//
//  RapidJsonMgr.hpp
//  tinyXMLSample
//
//  Created by xwang on 8/25/16.
//
//

#ifndef RapidJsonMgr_hpp
#define RapidJsonMgr_hpp

#include <stdio.h>

using namespace std;

class RapidJsonMgr
{
private:
    RapidJsonMgr();
    ~RapidJsonMgr();
private:
    //** */
    static RapidJsonMgr* rjMgr;

private:
    bool   _isRootObject;
    string _filename;
public:
    //** singleton */
    static RapidJsonMgr* getInstance();
    
public:
    void writeJson();


};

#endif /* RapidJsonMgr_hpp */
