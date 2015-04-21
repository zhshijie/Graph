//
//  Graph_SearchAStar.h
//  GraphDemo
//
//  Created by 张世杰 on 15/4/21.
//
//

#ifndef __GraphDemo__Graph_SearchAStar__
#define __GraphDemo__Graph_SearchAStar__

#include <stdio.h>
#include "PriorityQueue.h"
#include "Heuristic.h"


/*
 * A*算法的实现
 */

template <class graph_type,class heuristic>
class Graph_SearchAStar {
    
private:
    typedef typename graph_type::EdgeType Edge;
private:
    const graph_type & m_Graph;
    
    //按节点索引，包含到那个节点的累计
    std::vector<double> m_GCosts;
    //按节点索引。通过计算m_GCosts[n]加上从节点n到目标节点的启发因子开销得到
    std::vector<double> m_FCosts;
    std::vector<const Edge*> m_ShortestPathTree;
    std::vector<const Edge*> m_SearchFrontier;
    
    int m_iSource;
    int m_iTarget;
    
    void Search();
public:
    
    Graph_SearchAStar(graph_type & graph,
                    int source,
                      int target):
m_Graph(graph),
m_ShortestPathTree(graph.NumNodes()),
m_GCosts(graph.NumNodes(),0.0),
m_FCosts(graph.NumNodes(),0.0),
m_iSource(source),
m_iTarget(target)
    {
        Search();
    }
    //返回算法得到的边的动态
    std::vector<const Edge*> GetSPT()const;
    
    //返回从源到目标最短路径点序列大索引构成的动态数组
    std::list<int> GetPathToTarget() const;
    //返回 到目标节点的总开销
    double GetCostToTraget() const;
};



template <class graph_type,class heuristic>
void  Graph_SearchAStar<graph_type,heuristic>::Search() {
    
    //创建一个节点索引的优先队列，队列的优先级通过开销F决定
    IndexedPriorityQLow<double> pq (m_FCosts,m_Graph.NumNodes());
    
    //源节点入队
    pq.insert(m_iSource);
    
    //当队列不空时
    while (!pq.empty()) {
        
        //从队列得到最小开销的节点
        int NextClosestNode = pq.Pop();
        
        //将节点从搜索边界移动到展开树上
        m_ShortestPathTree[NextClosestNode] = m_SearchFrontier[NextClosestNode];
        
        //如果找到目标系节点，退出
        if (NextClosestNode == m_iTarget) {
            return;
        }
        
        typename graph_type::constEdgeIterator ConstEdgeItr(m_Graph,NextClosestNode);
        
        for (const Edge* pE = ConstEdgeItr.begin(); !ConstEdgeItr.end(); pE = ConstEdgeItr.next()) {
            //计算这个节点的开销 F ＝ G ＋ H
            double HCost = heuristic::Calculate(m_Graph,NextClosestNode);
            double GCost = m_GCosts[NextClosestNode] + pE->Cost();
            //如果节点还没有加入搜索边界 ，加入
            //并且更新开销G和F
            int to = pE->To();
            if (m_SearchFrontier[pE->To()]==nullptr) {
                m_FCosts[to] = GCost+HCost;
                m_GCosts[to] = GCost;
                pq.insert(to);
                m_SearchFrontier[to] = pE;
            }
            //如果节点已经在搜索边界上，并且到这儿的开销比以前找到的小
            //相应地更新节点的开销和搜索边界
            else if(GCost <m_GCosts[to]&&m_ShortestPathTree[to] == nullptr)
            {
                
                m_FCosts[to] = GCost+HCost;
                m_GCosts[to] = GCost;
                pq.ChangePriority(to);
                m_SearchFrontier[to] = pE;
            }
        }
    }
}

#endif /* defined(__GraphDemo__Graph_SearchAStar__) */
