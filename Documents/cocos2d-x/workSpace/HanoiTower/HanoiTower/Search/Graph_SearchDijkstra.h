//
//  Graph_SearchDijkstra.h
//  GraphDemo
//
//  Created by 张世杰 on 15/4/21.
//
//

#ifndef __GraphDemo__Graph_SearchDijkstra__
#define __GraphDemo__Graph_SearchDijkstra__

#include <stdio.h>
#include "PriorityQueue.h"
#include <list>
#include <vector>
/*
 *  对Dijkstra 算法的封装 ，即图的最小生成树
 */

template <class graph_type>
class Graph_SearchDijkstra {
    
private:
    typedef typename graph_type::EdgeType Edge;
    typedef typename graph_type::NodeType Node;
private:
    const graph_type & m_Graph;
    
    //这个动态数组保存最短路径树的边（SPT）
    //一个图的有向子树，该树包含了在SPT上的每个节点到源节点的最优路径
    std::vector<const Edge*> m_ShortestPathTree;
    
    //这是一个以节点的索引为索引的，包含目前到给定点最短路径的总开销的动态数组
    std::vector<double> m_CostToThisNode;
    
    //这是一个按节点来索引的保存“父”边的动态数组
    //“父边”指那些喝SPT相连的但是没有加入到SPT的节点
    std::vector<const Edge*> m_SearchFrontier;
    
    int m_iSource;
    int m_iTarget;
    void Search();
public:
    
    Graph_SearchDijkstra(const graph_type& graph,
                         int source,
                         int target = -1):
    m_Graph(graph),
    m_ShortestPathTree(graph.NumNodes()),
    m_SearchFrontier(graph.NumNodes()),
    m_CostToThisNode(graph.NumNodes()),
    m_iSource(source),
    m_iTarget(target){
        Search();
    }
    
//    //返回定义SPT的边的动态数组
//    //如果调用构造函数时指定目标节点，那么将返回
//    //在找到目标节点之前已经访问过所有节点的SPT
//    //如果不是这样，SPT将包含图的所有节点
//    std::vector<const Edge*> GetAllPaths()const;
    //返回包含从源节点到目标节点的最短路径的节点的索引构成的数组
    //通过从目标节点回溯SPT计算路径
    std::list<int>  GetPathToTarget() const;

    //返回到目标节点的总开销
    double GetCostToTarget()const{return m_CostToThisNode[m_iTarget];};
    
};

template <class graph_type>
void Graph_SearchDijkstra<graph_type>::Search() {
    //创建一个索引的优先队列，按照从前到后从最小到最大来排序
    //注意iPQ包含的最大节点数时NnmNodes（）；
    //这是因为没有节点在队列中会重复表示
    IndexedPriorityQLow<double >  pq(m_CostToThisNode,m_Graph.NumNodes());
    //源节点入队
    pq.insert(m_iSource);
    //当队列不空
    while (!pq.empty()) {
        
        
        //从队列中得到最小开销的节点，返回节点的索引。
        //这个节点是子啊SPT中没有的，但是又是距离源节点最近的节点
        
        int NextClosestNode = pq.Pop();
        //把这条边从搜索边界移到最短生成树上
        m_ShortestPathTree[NextClosestNode] = m_SearchFrontier[NextClosestNode];
        
        //如果找到目标节点，退出
        if (NextClosestNode == m_iTarget) {
            return;
        }
        
        //现在进行边放松。遍没一条连接下一个节点的边
        typename graph_type::ConstEdgeIterator ConstEdgeItr(m_Graph,NextClosestNode);
        for (const Edge* pE = ConstEdgeItr.begin(); !ConstEdgeItr.end(); pE = ConstEdgeItr.next()) {
            
            //到这条边指向的节点的总开销是到当前节点的开销加上这条边的开销
            double NewCost = m_CostToThisNode[NextClosestNode]+pE->Cost();
            
            //如果这条边没有在搜索边界上，记录它所指向的点的开销
            //把边加到搜索边界上
            //把指向节点加入到优先队列中
            int to = pE->To();
            if (m_SearchFrontier[to] == 0) {
                m_CostToThisNode[to] = NewCost;
                pq.insert(to);
                m_SearchFrontier[to] = pE;
            }
            
            //否则，测试是否从当前节点到达指向节点的开销小于但前找到的最小开销
            //如果这条路径更短的话，我们将新的开销记入指向的节点，更新优先队列
            //把边加入搜索边界
            else if((NewCost <m_CostToThisNode[to])&&m_ShortestPathTree[to] == 0){
                m_CostToThisNode[to] = NewCost;
                pq.ChangePriority(to);
                m_SearchFrontier[to] = pE;
            }
            
        }//for结束
        
        
        
    }//while 结束

} //Search 结束



template <class graph_type>
std::list<int> Graph_SearchDijkstra<graph_type>::GetPathToTarget()const
{
    std::list<int> path;
    
    //just return an empty path if no target or no path found
    if (m_iTarget < 0)  return path;
    
    int nd = m_iTarget;
    
    path.push_front(nd);
    
    while ((nd != m_iSource) && (m_ShortestPathTree[nd] != 0))
    {
        nd = m_ShortestPathTree[nd]->From();
        
        path.push_front(nd);
    }
    
    return path;
}

#endif /* defined(__GraphDemo__Graph_SearchDijkstra__) */
