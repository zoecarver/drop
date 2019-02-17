//
//  obj.h
//  drop
//
//  Created by Zoe IAMZOE.io on 2/7/19.
//  Copyright © 2019 hyper-search. All rights reserved.
//

#ifndef obj_h
#define obj_h

#include <SFML/Graphics.hpp>

using namespace sf;

class obj
{
public:
    virtual Shape* render( ) = 0;
    virtual void onclick( ) = 0;
    virtual void onkey( Keyboard::Key ) = 0;
    
    virtual ~obj( ) = default;
    
    std::vector<Keyboard::Key> keys = {
        Keyboard::D, Keyboard::Y, Keyboard::X, Keyboard::C,
        Keyboard::Down, Keyboard::Up, Keyboard::Right, Keyboard::Left,
        Keyboard::Space
    };
};

#endif /* obj_h */
