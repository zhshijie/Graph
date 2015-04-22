//
//  HanoiNode.h
//  HanoiTower
//
//  Created by 张世杰 on 15/4/22.
//  Copyright (c) 2015年 张世杰. All rights reserved.
//

#ifndef __HanoiTower__HanoiNode__
#define __HanoiTower__HanoiNode__

#include <stdio.h>
#include "GraphNode.h"
#include <stack>
#include <vector>
#include <iostream>
#include <cassert>
#include <math.h>
/*
 *  定义汉诺塔的节点
 *
 */

typedef enum{A,B,C} pillar;

class HanoiNode:public GraphNode {
    
    //定义柱子
private:
    //盘子的数量 ,每个盘子的权重为10^n。大盘子权重大。
    int m_iNum;
    
    //有3条柱子，分别表示为A，B，C;
    //如果假设有4个盘子，都放在A中，那么A的值为 1111;
    //用位权表示盘子的大小，1表示存在，0表示不存在
    long int pillars[3] = {0};
    
    //用来保存盘子
    std::vector<std::stack<int>> pillars_stacks;

public:
    
    //构造函数
    HanoiNode(int num,
              long A,
              long B,
              long C,
              int index):m_iNum(num),GraphNode(index){
        pillars[0] = A;
        pillars[1] = B;
        pillars[2] = C;
        
        for (int i =0; i<3; i++) {
            
            std::stack<int> k = std::stack<int>();
            for (int j = 100; j>0; j/=10) {
                k.push((int)pillars[i]/j);
            }
            pillars_stacks.push_back(k);
        }
    }
    
    HanoiNode(int num,int index):m_iNum(num),GraphNode(index){
        //默认所有盘子都在A柱子上
        for (int a = 0; a<num; a++) {
            pillars[0] = (pillars[0]*10+1);
        }
        
        pillars_stacks = std::vector<std::stack<int>>();
        int k = pow(10,num-1);
        std::stack<int> A;
        std::stack<int> B;

        std::stack<int> C;
        for (int a = 1; a<=num; a++) {
            A.push(k);
            k=k/10;
        }
        pillars_stacks.push_back(A);
        pillars_stacks.push_back(B);
        pillars_stacks.push_back(C);

        
    }
    //获得每根柱子上盘子的分布情况
    long GetA() const {return pillars[0];};
    long GetB() const {return  pillars[1];};
    long GetC() const {return  pillars[2];};
    
    
    //将from柱子最上面的盘子移动到to柱子上，移动成功返回true。
    bool MovePlate(int from,int to);
    
};

#endif /* defined(__HanoiTower__HanoiNode__) */
