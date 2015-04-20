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

template <class node_type,class edge_type>
void SparseGraph<node_type,edge_type>::RemoveNode(int node)
{
    assert(node<(int)m_Nodes.size()&&"<SparseGraph::RemoveNode>: invalid node index");
    
}


