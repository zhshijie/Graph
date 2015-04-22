//
//  HanoiNode.cpp
//  HanoiTower
//
//  Created by 张世杰 on 15/4/22.
//  Copyright (c) 2015年 张世杰. All rights reserved.
//

#include "HanoiNode.h"


bool HanoiNode::MovePlate(int from, int to)
{
    int pillar;
    
        //获得from 柱子上的最上面的一个圆盘
    std::stack<int> from_s = pillars_stacks[from];
    if (from_s.empty()) {
        return false;
    }else{
        pillar = from_s.top();
    }
    
    //获得to柱子最上面的一个圆盘
    std::stack<int> to_s = pillars_stacks[to];
    //如果目标柱子是空的，直接把盘子已过去
    if (to_s.empty()) {
        pillars_stacks[from].pop();
        pillars_stacks[to].push(pillar);
        pillars[from]-= pillar;
        pillars[to]+= pillar;
        return true;
    }
    //否则判断目标柱子最上的盘子是否比移动的盘子大
    //比移动盘子大，就移动成功，否则返回失败
    else{
        int target = to_s.top();
        if (target>pillar) {
            pillars_stacks[from].pop();
            pillars_stacks[to].push(pillar);
            pillars[from]-= pillar;
            pillars[to]+= pillar;
            return true;
        }
    }
    return false;
}