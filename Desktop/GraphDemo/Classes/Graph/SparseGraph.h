//
//  SparseGraph.h
//  GraphDemo
//
//  Created by 张世杰 on 15/4/20.
//
//

#ifndef __GraphDemo__SparseGraph__
#define __GraphDemo__SparseGraph__

#include <stdio.h>
#include <cassert>
#include <iostream>

#define invalid_node_index -1   // 表示改节点不存在的索引


/**
 * SparseGraph 稀疏图的类模版 储存一张稀疏图的邻接表
 *
 *
 */

template <class node_type , class edge_type>
class SparseGraph {
    
public:
    //使得图中的各种边和节点的类型都能被使用
    typedef edge_type EdgeType;
    typedef node_type NodeType;
    
    typedef std::vector<node_type> NodeVector; //存储稀疏图的所有节点
    typedef std::list<edge_type> EdgeList;   //
    typedef std::vector<EdgeList>  EdgeVector;  //储存稀疏图的邻接表
 
private:
    //组成图的节点
    NodeVector m_Nodes;
    //一个边的动态数字(通过节点的索引，获得与改节点相连的所有的边(EdgeList))
    EdgeVector m_Edges;
    //是否为有向图
    bool m_bDigraph;
    //下一个有效的索引号
    int m_iNextNodeIndex;
    //检查边是否唯一的
    bool UniqueEdge(int from,int to)const;
    //清除掉无效的边 ,一条边只有有一个节点是 invalid_node_index ，即无效
    void CullInvalidEdges();
public:
    
    //构造函数
    SparseGraph(bool digraph):m_iNextNodeIndex(0),m_bDigraph(digraph){}
    
    //返回给定的索引的节点
    const NodeType& GetNode(int idx)const{return m_Nodes.at(idx);};
    //返回非常量的方法
    NodeType& GetNode(int idx){return m_Nodes.at(idx);};
    
    //获得一个边的引用的常量方法
    const EdgeType& GetEdge(int from,int to)const;
    //非常量方法
    EdgeType& GetEdge(int from,int to);
    
    //获得下一个可用的节点索引
    int GetNextFreeNodeIndex() const{return m_iNextNodeIndex;};
    
    //添加一个节点到图中并返回其索引
    int AddNode(NodeType node);
    
    //通过设置一个节点的索引为invalid_nod_index来删除一个节点
    void RemoveNode(int node);

    //添加和删除边的方法
    void AddEdge(EdgeType edge);
    void RemoveEdge(int from ,int to);
    
    //返回但前图中的节点数
    int NumNodes()const {return m_Nodes.size();};
    //返回当前图中活动的节点数
    int NumActiveNodes() const;
    //返回当前图中的边数
    int NumEdges() const;
    
    //如果图是有向的，返回true;
    bool isDigraph()const {return m_bDigraph;};
    //如果图中没有节点，返回true
    bool isEmpty() const{if(m_Nodes.size()<=0)return false;else return true;};
    //该节点在图中是否存在，不存在返回false
    bool isPresent(int nd) const{if(m_Nodes.at(nd)->Index()!=invalid_node_index) return true;else return false;};
    //通过打开一个文件流或文件名来装入货储存图
    bool Save(const char* FileName)const;
    bool Save(std::ofstream& stream);
    
    bool Load(const char*FileName)const;
    bool Load(std::ifstream& stream);
    
    //为新节点的插入清空图
    void Clear(){m_iNextNodeIndex = 0; m_Nodes.clear(); m_Edges.clear();};
    //清除所有的边
    void RemoveEdges()
    {
        for (typename EdgeVector::iterator it = m_Edges.begin(); it != m_Edges.end(); ++it)
        {
            it->clear();
        }
    }
    
    //客户可能使用的用来存取边和节点的迭代器
    class ConstEdgeIterator
    {
    private:
        
        typename EdgeList::const_iterator        curEdge;
        
        const SparseGraph<node_type, edge_type>& G;
        
        const int                                NodeIndex;
        
    public:
        
        ConstEdgeIterator(const SparseGraph<node_type, edge_type>& graph,
                          int                           node): G(graph),
        NodeIndex(node)
        {
            /* we don't need to check for an invalid node index since if the node is
             invalid there will be no associated edges
             */
            
            curEdge = G.m_Edges[NodeIndex].begin();
        }
        
        const EdgeType*  begin()
        {
            curEdge = G.m_Edges[NodeIndex].begin();
            
            return &(*curEdge);
        }
        
        const EdgeType*  next()
        {
            ++curEdge;
            
            if(end())
            {
                return NULL;
            }
            else
            {
                return &(*curEdge);
            }
            
        }
        
        //return true if we are at the end of the edge list
        bool end()
        {
            return (curEdge == G.m_Edges[NodeIndex].end());
        }
    };
    
    friend class ConstEdgeIterator;
    
    class EdgeIterator
    {
    private:
        
        typename EdgeList::iterator         curEdge;
        
        SparseGraph<node_type, edge_type>&  G;
        
        const int                           NodeIndex;
        
    public:
        
        EdgeIterator(SparseGraph<node_type, edge_type>& graph,
                     int                                node): G(graph),
        NodeIndex(node)
        {
            /* we don't need to check for an invalid node index since if the node is
             invalid there will be no associated edges
             */
            
            curEdge = G.m_Edges[NodeIndex].begin();
        }
        
        EdgeType*  begin()
        {
            curEdge = G.m_Edges[NodeIndex].begin();
            
            return &(*curEdge);
        }
        
        EdgeType*  next()
        {
            ++curEdge;
            
            if (end()) return NULL;
            
            return &(*curEdge);
            
        }
        
        //return true if we are at the end of the edge list
        bool end()
        {
            return (curEdge == G.m_Edges[NodeIndex].end());
        }
    };
    
    friend class EdgeIterator;
    

    class NodeIterator;
    class ConstNodeIterator;
    
};


template <class node_type , class edge_type>
const edge_type& SparseGraph<node_type,edge_type>::GetEdge(int from, int to)
const
{
    assert((from<m_Nodes.size())&&
           (from >= 0)&&
           m_Nodes[from].Index()!= invalid_node_index&&
           "<SparseGraph::GetEdge>: invalid 'from' index");
    assert((to<m_Nodes.size())&&
           (to>=0)&&
           m_Nodes[to].Index()!= invalid_node_index&&
           "<SparseGraph::GetEdge>: invalid 'to' index>");
    
    for (typename EdgeList::const_iterator curEdge = m_Nodes[from].begin();curEdge != m_Nodes[from].end(); ++curEdge) {
        if (curEdge->To() == to) {
            return curEdge;
        }
    }
    assert(0&&"<SparseGraph::GetEdge>: edge does not exist");
}

template <class node_type,class edge_type>
edge_type& SparseGraph<node_type,edge_type>::GetEdge (int from,int to) {
    
    assert((from<m_Nodes.size())&&
           (from >= 0)&&
           m_Nodes[from].Index()!= invalid_node_index&&
           "<SparseGraph::GetEdge>: invalid 'from' index");
    assert((to<m_Nodes.size())&&
           (to>=0)&&
           m_Nodes[to].Index()!= invalid_node_index&&
           "<SparseGraph::GetEdge>: invalid 'to' index>");
    
    for (typename EdgeList::const_iterator curEdge = m_Nodes[from].begin();curEdge != m_Nodes[from].end(); ++curEdge) {
        if (curEdge->To() == to) {
            return curEdge;
        }
    }
    assert(0&&"<SparseGraph::GetEdge>: edge does not exist");
}



/*
 *
 *  AddNode   添加节点
 *
 */
template <class node_type,class edge_type>
int SparseGraph<node_type,edge_type>::AddNode(node_type NewNode)
{
    if (NewNode.Index() < (int)m_Nodes.size() ) {
        
        assert(m_Nodes[NewNode.Index()].Index()!= invalid_node_index&&"<SparseGraph::AddNode>: Attempting to add a node with a duplicate ID");
        m_Nodes[NewNode.Index()] = NewNode;
        
        return m_iNextNodeIndex;
    }else {
        assert(NewNode.Index() == m_iNextNodeIndex && "<SparseGraph::AddNode>: invalid node index");
        
        m_Nodes.push_back(NewNode);
        m_Edges.push_back(EdgeList());
        m_iNextNodeIndex++;
        return m_iNextNodeIndex;
    }
}

/*
 * 删除一个节点
 * int node 传入节点的索引
 */

template <class node_type,class edge_type>
void SparseGraph<node_type,edge_type>::RemoveNode(int node)
{
    assert(node<(int)m_Nodes.size()&&"<SparseGraph::RemoveNode>: invalid node index");
    typename EdgeList::iterator curEdge;
    
    m_Nodes[node].SetIndex(invalid_node_index);
    
    if (!m_bDigraph) {
        for (typename EdgeList::iterator curEdge = m_Edges[node].begin() ; curEdge != m_Edges[node].end(); ++curEdge) {
            for (typename EdgeList::iterator curE = m_Edges[curEdge->To()].begin(); curE!=m_Edges[curEdge->To()].end(); ++curE) {
                if (curE->To() == node) {
                    curE = m_Edges[curEdge->To()].erase(curE);
                    break;
                }
            }
        }
        m_Edges[node].clear();
    }else{
        CullInvalidEdges();
    }
    
}

template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::CullInvalidEdges()
{
    for (typename EdgeVector::iterator curEdgeList = m_Edges.begin(); curEdgeList != m_Edges.end(); ++curEdgeList)
    {
        for (typename EdgeList::iterator curEdge = (*curEdgeList).begin(); curEdge != (*curEdgeList).end(); ++curEdge)
        {
            if (m_Nodes[curEdge->To()].Index() == invalid_node_index ||
                m_Nodes[curEdge->From()].Index() == invalid_node_index)
            {
                curEdge = (*curEdgeList).erase(curEdge);
            }
        }
    }
}



/*
 *添加一条边
 *
 */

template <class node_type,class edge_type>
void SparseGraph<node_type,edge_type>::AddEdge(EdgeType edge) {
    assert(edge.From()<m_Nodes.size()&&"<SparseGraph::AddEdge> invalid edge");
    assert(edge.To()<m_Nodes.size()&&"<SparseGraph::AddEdge> invalid edge");
    
    if (m_Nodes[edge.From()].Index()!= invalid_node_index&&m_Nodes[edge.To()].Index()!=invalid_node_index) {
        
        //检查该边是否是唯一的
        
        if (UniqueEdge(edge.From(), edge.To()))
        {
            m_Edges.at(edge.From()).push_back(edge);
        }
        
        //该图是否为有向图
        if (!m_bDigraph) {
            
            if (UniqueEdge(edge.To(), edge.From()))
            {
                EdgeType NewEdge = edge;
                
                NewEdge.SetTo(edge.From());
                NewEdge.SetFrom(edge.To());
                
                m_Edges[edge.To()].push_back(NewEdge);
            }
        }
    }
}



/*
 *
 *删除一条边
 *
 */


template <class node_type,class edge_type>
void  SparseGraph<node_type,edge_type>::RemoveEdge(int from, int to) {
    assert (from>m_Nodes.size()&&"<SparseGraph::RemoveEdge>: This edge does not exits");
    assert (to>m_Nodes.size()&&"<SparseGraph::RemoveEdge>: This edge does not exits");
    
    if (m_Nodes[from]!=invalid_node_index&&m_Nodes[to]!=invalid_node_index) {
        for (typename EdgeList::iterator curEdge = m_Edges[from].begin(); curEdge!=m_Edges[from].end(); ++curEdge) {
            if (curEdge->To() == to) {
                m_Edges[from].earse(curEdge);
                break;
            }
        }
        
        //判断是否是有向图
        if (!m_bDigraph) {
            for (typename  EdgeList::iterator curEdge = m_Edges[to].begin(); curEdge!=m_Edges[to]; +++curEdge) {
                if (curEdge->To() == from) {
                    m_Edges[to].earse(curEdge);
                    break;
                }
            }
        }
    }
}




/*
 * 获得当前活动的节点
 */

template <class node_type,class edge_type>
int SparseGraph<node_type,edge_type>::NumActiveNodes()const {
    
    int num = 0;
    for (typename EdgeVector::iterator curNode = m_Nodes.begin(); curNode!=m_Nodes.end(); ++curNode) {
        if (curNode->Index()!=invalid_node_index) {
            num++;
        }
    }
    
    return num;
}


/*
 * 获得当前的边数
 *  无向图的 from－to  和  to －from 是2条边
 */

template <class node_type,class edge_type>
int SparseGraph<node_type,edge_type>::NumEdges() const
{
    int coun = 0;
    
    for (typename EdgeVector::const_iterator curEdge = m_Edges.begin();
         curEdge != m_Edges.end();
         ++curEdge)
    {
        coun += curEdge->size();
        
    }
    return coun;
}


//-------------------------------- UniqueEdge ----------------------------
//
//  returns true if the edge is not present in the graph. Used when adding
//  edges to prevent duplication
//------------------------------------------------------------------------
template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::UniqueEdge(int from, int to)const
{
    for  (typename  EdgeList::const_iterator curEdge = m_Edges[from].begin();
         curEdge != m_Edges[from].end();
         ++curEdge)
    {
        if (curEdge->To() == to)
        {
            return false;
        }
    }
    
    return true;
}




#endif /* defined(__GraphDemo__SparseGraph__) */
