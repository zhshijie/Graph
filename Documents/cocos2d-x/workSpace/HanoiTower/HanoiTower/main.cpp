//
//  main.cpp
//  HanoiTower
//
//  Created by 张世杰 on 15/4/22.
//  Copyright (c) 2015年 张世杰. All rights reserved.
//

#include <iostream>
#include "HanoiNode.h"
#include "SparseGraph.h"
#include "GraphEdge.h"
#include "Graph_SearchBFS.h"
#include "HanoidGraph.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //生成汉诺塔的第一个节点
    HanoiNode node =  HanoiNode(4,0);
    //目标节点
    HanoiNode target =  HanoiNode(4,0,0,1111,0);
    printf("%ld\n",node.GetA());
    
    //将节点加入图中
    HanoidGraph<HanoiNode, GraphEdge> graph =  HanoidGraph<HanoiNode, GraphEdge>(false);
    graph.AddNode(node);
    
    //进行搜索
     auto search =   Graph_SearchBFS<HanoidGraph<HanoiNode, GraphEdge>>(graph, 0,target);
    
    //获得搜索路径
   std::list<int> path =   search.GetPathToTarget();
    
    //输出搜索路径
    for (std::list<int>::iterator cur = path.begin();cur!=path.end() ;cur++) {
 
        HanoiNode node = graph.GetNode(*cur);
        printf(" A : %ld, B : %ld ,C : %ld \n",node.GetA(),node.GetB(),node.GetC());
    }
    
    return 0;
}
