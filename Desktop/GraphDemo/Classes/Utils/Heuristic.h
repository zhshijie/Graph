//
//  Heuristic.h
//  GraphDemo
//
//  Created by 张世杰 on 15/4/21.
//
//

#ifndef __GraphDemo__Heuristic__
#define __GraphDemo__Heuristic__

#include <stdio.h>


/*
 *  A＊算法的启发开销的计算
 */
#include "cocos2d.h"

class Heuristic_Euclid {
    
public:
    Heuristic_Euclid(){};
    
    template <class graph_type>
    //返回两点之间的距离
    static double CalCulate_Euclidean(const graph_type& G,int nd1,int nd2 )
    {
        return G.GetNode(nd1).getPosition().distance(G.GetNode(nd2).getPosition());
    }
    
    template <class graph_type>
    static double CalCulate_Manhattan(const graph_type& G,int nd1,int nd2 )
    {
        cocos2d::Vec2 dis = G.GetNode(nd1).getPosition() - G.GetNode(nd2).getPosition();
        
        double result = std::fabs(dis.x) +std::fabs(dis.y);
        return result;
    }
};
#endif /* defined(__GraphDemo__Heuristic__) */
