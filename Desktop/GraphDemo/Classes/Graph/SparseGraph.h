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
    
    
    //客户可能使用的用来存取边和节点的迭代器
    class ConstEdgeIterator;
    class EdgeIterator;
    class NodeIterator;
    class ConstNodeIterator;
    
};

#endif /* defined(__GraphDemo__SparseGraph__) */
