//
//  main.cpp
//  drop
//
//  Created by Zoe IAMZOE.io on 2/7/19.
//  Copyright © 2019 hyper-search. All rights reserved.
//

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "config.h"
#include "obj.h"
#include "basicbox.h"

using namespace sf;

int main( int argc, const char * argv[] )
{
    auto objs = std::vector<obj*>( );
    objs.push_back( new basicblock( ) );
    
    RenderWindow window( sf::VideoMode( 600, 600 ), "Main Window" );
    
    while ( window.isOpen( ) )
    {
        Event event;
        while ( window.pollEvent( event ) )
        {
            if ( event.type == Event::Closed ) window.close( );
        }
        
        window.clear(background);
        
        for ( auto& item: objs )
        {
            if ( Mouse::isButtonPressed( Mouse::Left ) )
                item->onclick();
            
            for ( auto& k: item->keys )
                if ( Keyboard::isKeyPressed( k ) )
                    item->onkey( k );
            
            window.draw( *item->render() );
        }
        
        window.display();
    }
    
    return 0;
}
