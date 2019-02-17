//
//  basicbox.h
//  drop
//
//  Created by Zoe IAMZOE.io on 2/7/19.
//  Copyright © 2019 hyper-search. All rights reserved.
//

#ifndef basicbox_h
#define basicbox_h

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include <SFML/Graphics.hpp>

#include "obj.h"
#include "mmath.h"

#pragma mark - helper functions / data structures

template <class T>
struct vect
{
    T a; T b; T c;
};

template <class T, class R>
static R operator*(  std::vector<T>& lfs, R rhs )
{
    R total = 0;
    for ( auto& l: lfs )
        total += l * rhs;
    return total;
}

template <class T, class R>
static void operator+=(  std::vector<T>& lfs, R rhs )
{
    for ( auto& l: lfs )
        l += rhs;
}

template <class T, class R>
static void operator*=(  std::vector<T>& lfs, R rhs )
{
    for ( auto& l: lfs )
        l *= rhs;
}

template <class T, class R>
static bool operator>(  std::vector<T>& lfs, R rhs )
{
    bool greater = false;
    for ( auto& l: lfs ) greater = l > rhs;
    
    return greater;
}

template <class T, class R>
static bool operator<(  std::vector<T>& lfs, R rhs )
{
    bool less = false;
    for ( auto& l: lfs ) less = l < rhs;
    
    return less;
}

#pragma mark - basicblock

using namespace sf;

class basicblock : public obj
{
private:
    const double deltatime = 0.003; // time step
    const double acceleration = -500; // result of friction
    std::vector<double> pos = { 10, 10, 10 }; // x, y, color
    double direction = 1.0;
    std::vector<vector_type<decltype( pos )>::type> velocity = { 40, 40, 40 }; // initial velocity (20 is very low 60 is very high)
    
    void updatepos( );
    void changedirections( );
    void setdirection( double dir );
    
public:
    Shape* render( ) override;
    void onclick( ) override;
    void onkey( Keyboard::Key key ) override;
};

#pragma mark - methods

void basicblock::updatepos( )
{
    unsigned i = 0; // so we can also access position
    for ( auto& v: velocity ) // loop through every velocity
    {
        if ( (v > 0 && direction > 0) || (v < 0 && direction < 0) ) // velocity / position should not be updated after velocity is 0 (otherwise it will start going backwards increasingly quickly)
        {
            auto vectorcorrection = 0.5 * acceleration * deltatime * deltatime * direction; // correct for the fact that velocity isnt constant during the time stamp (time distributed)
            
            pos[i] += v * deltatime; // updating position based on velocity
            v += vectorcorrection; // adding friction in the from of constant acceleration in the opposite direction
            
            if ( verbose )
            {
                std::cout << "acc: " << acceleration
                << " cor: " << vectorcorrection
                << " pos: " << pos[i]
                << " vel: " << v // remember this is only the one that is being currently updated
                << std::endl;
            }
        };
        
        i++;
    }
}

void basicblock::changedirections( )
{ // make direction the oposite of what it is
    direction = -direction;
    velocity *= direction;
}

void basicblock::setdirection( double dir )
{ // set the direction to a specific direction
    direction = dir;
    velocity *= direction; // multiply the velocity by that direction
}

void basicblock::onclick( )
{
    // velocity += (30 * direction);
    changedirections( );
    
    // sleep after the click so that it isnt registered several times
    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
}

void basicblock::onkey( Keyboard::Key key )
{ // map to key then execute logic based on taht
    switch ( key ) {
        case sf::Keyboard::X: // X adds to the X axis
            velocity[0] += (5 * direction);
            break;
        case sf::Keyboard::Y: // Y adds to the Y axis
            velocity[1] += (5 * direction);
            break;
        case sf::Keyboard::C: // C adds to the Color axis
            velocity[2] = (20 * direction);
            break;
        case sf::Keyboard::Down: // Down makes the direction down (starting direction) and adds 15 in the y axis
            velocity[1] = (20 * direction);
            setdirection(1.0);
            break;
        case sf::Keyboard::Up: // Up does the same thing in the opisite direction as above
            velocity[1] = (20 * direction);
            setdirection(-1.0);
            break;
        case sf::Keyboard::Left: // Left makes the direction left (starting direction) and adds 15 in the x axis
            velocity[0] = (20 * direction);
            setdirection(-1.0);
            break;
        case sf::Keyboard::Right: // I wonder what this does :P
            velocity[0] = (20 * direction);
            setdirection(1.0);
            break;
        case sf::Keyboard::Space: // Reset position (but not velocity)
            pos[0] = 0;
            pos[1] = 0;
            pos[2] = 0;
            break;
        default:
            break;
    }
    
    // make sure we sleep so things arent registered several times
    // std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
}

Shape* basicblock::render( )
{    
    if ( pos < 0 || pos > 500 ) changedirections( ); // color can change direction too (fixme?)
    
    updatepos( );
    
    auto* rect = new RectangleShape( Vector2f( 100, 100 ) );
    rect->setPosition( pos[0], pos[1] );
    rect->setFillColor( Color( pos[2] / 2, 100, 100 ) ); // devide color by 2 so that it is within 255
    
    return rect;
}

#endif /* basicbox_h */
