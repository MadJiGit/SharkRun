//
//  MyBodyParser.hpp
//  MyCppGame-mobile
//
//  Created by Madji on 27.04.19.
//

#ifndef MyBodyParser_hpp
#define MyBodyParser_hpp


//
//  MyBodyParser.h
//
//  Created by Jason Xu.
//
//

#pragma once

#include <stdio.h>
#include <string>
#include "cocos2d.h"
USING_NS_CC;
#include "json/document.h"

class MyBodyParser {
    MyBodyParser(){}
    rapidjson::Document doc;
public:
    static MyBodyParser* getInstance();
    bool parseJsonFile(const std::string& pFile);
    bool parse(unsigned char* buffer, long length);
    void clearCache();
    PhysicsBody* bodyFormJson(Node* pNode, const std::string& name, PhysicsMaterial material);
};

#endif /* MyBodyParser_hpp */
