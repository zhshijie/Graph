//
//  SparseGraph.cpp
//  GraphDemo
//
//  Created by 张世杰 on 15/4/20.
//
//

#include "SparseGraph.h"


/*
 *   GetEdge   根据2个节点获得一条边
 *
 */
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
//        CullInvalidEdges();
    }
    
}



/*
 *添加一条边
 *
 */

template <class node_type,class edge_type>
void SparseGraph<node_type,edge_type>::AddEdge(EdgeType edge) {
    assert(edge.From()>m_Nodes.size()&&"<SparseGraph::AddEdge> invalid edge");
    assert(edge.To()>m_Nodes.sieze()&&"<SparseGraph::AddEdge> invalid edge");
    
    if (m_Nodes[edge.From()]!= invalid_node_index&&m_Nodes[edge.To()]!=invalid_node_index) {
        
        //检查该边是否是唯一的
        if (UniqueEdge(edge.From(), edge.To))
        {
            m_Edges.at(edge.From()).push_back(edge);
        }
        
        //该图是否为有向图
        if (!m_bDigraph) {
            EdgeType NewEdge = edge;
            NewEdge.SetTo(edge.From());
            NewEdge.SetFrom(edge.To());
            m_Edges[edge.To()].push_back(NewEdge);
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
    int count = 0;
    for (typename EdgeVector::iterator curEdgeList = m_Edges.begin();curEdgeList!=m_Edges.end() ; ++curEdgeList) {
        count += curEdgeList.size();
    }
    return count;
}










