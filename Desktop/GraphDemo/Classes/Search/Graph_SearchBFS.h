//
//  Graph_SearchBFS.h
//  GraphDemo
//
//  Created by 张世杰 on 15/4/21.
//
//

#ifndef __GraphDemo__Graph_SearchBFS__
#define __GraphDemo__Graph_SearchBFS__

#include <stdio.h>

/*
 *  对广度优先算法的封装
 *   依赖于 Graph 文件的的图类
 */

template <class graph_type>
class Graph_SearchBFS {
private:
    
    enum{ visited ,unvisited,no_parent_assigned};
    //为图所使用的节点和边类型
    
    typedef typename graph_type::EdgeType Edge;
    typedef typename graph_type::NodeType Node;
    
private:
    //一个被搜索的的图的引用
    const graph_type & m_Graph;
    //记录在搜索过程中访问的所有节点
    std::vector<int> m_Visitied;
    //保存到达目的节点的路径
    std::vector<int> m_Route;
    
    int m_iSource,m_iTarget;
    
    //当找到一条源节点到目标节点的路径时值为真
    bool m_bFound;
    
    //这个方法进行DFSss
    bool Search();
public:
    
    Graph_SearchBFS(const graph_type& graph,
                    int source,
                    int  target = -1):
    m_Graph(graph),
    m_iSource(source),
    m_iTarget(target),
    m_bFound(false),
    m_Visitied(m_Graph.NumNodes(),unvisited),
    m_Route(m_Graph.NumNodes(),no_parent_assigned)
    {
        m_bFound = Search();
    }
    
    //目标被找到，返回true
    bool Found() const{return m_bFound;};
    //返回一个节点索引动态数组，包含从源到目标的最短路径
    std::list<int> GetPathToTarget()const;
};


template <class graph_type>
bool Graph_SearchBFS<graph_type>::Search() {
    
    //创建一个堆栈，用来保存边的指针
    std::queue<const Edge*> queue;
    //创建一条哑边
    Edge Dummy(m_iSource,m_iSource,0);
    queue.push(&Dummy);
    
    //当栈中有边
    while (!queue.empty()) {
        //获得栈顶的边
        const Edge* Next = queue.front();
        //将栈顶的边出栈
        queue.pop();
        m_Route[Next->To()] = Next->From();
        m_Visitied[Next->To()] = visited;
        
        //如果找到目标，返回
        if (Next->To() == m_iTarget) {
            return true;
        }
        //将这条边指向的节点的所有相关联的边入栈
        //只要关联的边指向的节点没有被访问过
        
        //获得图中边的迭代器
        typename graph_type::ConstEdgeIterator ConstEdgeItr(m_Graph,Next->To());
        for (const Edge* pE = ConstEdgeItr.begin();!ConstEdgeItr.end(); pE = ConstEdgeItr.next())
        {
            if (m_Visitied[pE->To()] == unvisited) {
                queue.push(pE);
                m_Visitied[pE->To()] = visited;
            }
        }
    }//while 结束
    
    return false;
}//Search 结束



template <class graph_type>
std::list<int > Graph_SearchBFS<graph_type>::GetPathToTarget()const {
    std::list<int> path;
    
    if (!m_bFound||m_iTarget<0) return path;
    
    int nd = m_iTarget;
    path.push_back(nd);
    while (nd != m_iSource) {
        nd = m_Route[nd];
        path.push_back(nd);
    }
    return path;
}


#endif /* defined(__GraphDemo__Graph_SearchBFS__) */
