//
//  SparseGraph.cpp
//  GraphDemo
//
//  Created by 张世杰 on 15/4/20.
//
//

#include "SparseGraph.h"
#include <iostream>


/*
 *   GetEdge   根据2个节点获得一条边
 *
 */
/*
//-------------------------------- Save ---------------------------------------

template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::Save(const char* FileName)const
{
    //open the file and make sure it's valid
    std::ofstream out(FileName);
    
    if (!out)
    {
        throw std::runtime_error("Cannot open file: " + std::string(FileName));
        return false;
    }
    
    return Save(out);
}

//-------------------------------- Save ---------------------------------------
template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::Save(std::ofstream& stream)const
{
    //save the number of nodes
    stream << m_Nodes.size() << std::endl;
    
    //iterate through the graph nodes and save them
    typename NodeVector::const_iterator curNode = m_Nodes.begin();
    for (curNode; curNode!=m_Nodes.end(); ++curNode)
    {
        stream << *curNode;
    }
    
    //save the number of edges
    stream << NumEdges() << std::endl;
    
    
    //iterate through the edges and save them
    for (unsigned int nodeIdx = 0; nodeIdx < m_Nodes.size(); ++nodeIdx)
    {
        for (EdgeList::const_iterator curEdge = m_Edges[nodeIdx].begin();
             curEdge!=m_Edges[nodeIdx].end(); ++curEdge)
        {
            stream << *curEdge;
        }
    }
    
    return true;
}

//------------------------------- Load ----------------------------------------
//-----------------------------------------------------------------------------
template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::Load(const char* FileName)
{
    //open file and make sure it's valid
    std::ifstream in(FileName);
    
    if (!in)
    {
        throw std::runtime_error("Cannot open file: " + std::string(FileName));
        return false;
    }
    
    return Load(in);
}

//------------------------------- Load ----------------------------------------
//-----------------------------------------------------------------------------
template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::Load(std::ifstream& stream)
{
    Clear();
    
    //get the number of nodes and read them in
    int NumNodes, NumEdges;
    
    stream >> NumNodes;
    
    for (int n=0; n<NumNodes; ++n)
    {
        NodeType NewNode(stream);
        
        //when editing graphs it's possible to end up with a situation where some
        //of the nodes have been invalidated (their id's set to invalid_node_index). Therefore
        //when a node of index invalid_node_index is encountered, it must still be added.
        if (NewNode.Index() != invalid_node_index)
        {
            AddNode(NewNode);
        }
        else
        {
            m_Nodes.push_back(NewNode);
            
            //make sure an edgelist is added for each node
            m_Edges.push_back(EdgeList());
            
            ++m_iNextNodeIndex;
        }
    }
    
    //now add the edges
    stream >> NumEdges;
    for (int e=0; e<NumEdges; ++e)
    {
        EdgeType NextEdge(stream);
        
        AddEdge(NextEdge);
    }
    
    return true;
}
*/








