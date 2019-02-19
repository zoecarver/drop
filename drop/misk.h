//
//  helpers.h
//  drop
//
//  Created by Zoe IAMZOE.io on 2/18/19.
//  Copyright © 2019 hyper-search. All rights reserved.
//

#ifndef helpers_h
#define helpers_h

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
static typename std::enable_if<!std::is_same<R, std::vector<T>>::value, void>::type
operator*=(  std::vector<T>& lfs, R rhs )
{
    for ( auto& l: lfs )
        l *= rhs;
}

template <class T>
static void operator*=(  std::vector<T>& lfs, std::vector<T>& rhs )
{
    assert( lfs.size( ) == rhs.size( ) && "Vectors must have same size!" );
    
    unsigned i = 0;
    for ( auto& l: lfs )
        l *= rhs[i++];
}


template <class T, class R>
static bool operator>(  std::vector<T>& lfs, R rhs )
{
    bool greater = false;
    for ( auto& l: lfs ) greater = (l > rhs || greater);
    
    return greater;
}

template <class T, class R>
static bool operator<(  std::vector<T>& lfs, R rhs )
{
    bool less = false;
    for ( auto& l: lfs ) less = (l < rhs || less);
    
    return less;
}

#pragma mark - type traits

template <typename T>
struct vector_type
{
    using type = typename T::value_type;
};

#endif /* helpers_h */
