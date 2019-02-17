//
//  math.h
//  drop
//
//  Created by Zoe IAMZOE.io on 2/8/19.
//  Copyright © 2019 hyper-search. All rights reserved.
//

#ifndef math_h
#define math_h

#include <cmath>

template <typename T>
struct vector_type
{
    using type = typename T::value_type;
};

template <class T>
T sigmoid( T x )
{
    return 1 / (1 + exp( -(x - 1) ));
}


#endif /* math_h */
