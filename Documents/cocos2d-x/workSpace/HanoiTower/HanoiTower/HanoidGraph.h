//
//  HanoidGraph.h
//  HanoiTower
//
//  Created by 张世杰 on 15/4/22.
//  Copyright (c) 2015年 张世杰. All rights reserved.
//

#ifndef __HanoiTower__HanoidGraph__
#define __HanoiTower__HanoidGraph__

#include <stdio.h>
#include "SparseGraph.h"

template <class node_type , class edge_type>
class HanoidGraph:public SparseGraph<node_type,edge_type> {
public:
    //使得图中的各种边和节点的类型都能被使用
    typedef edge_type EdgeType;
    typedef node_type NodeType;
    
    typedef std::vector<node_type> NodeVector; //存储稀疏图的所有节点
    typedef std::list<edge_type> EdgeList;   //
    typedef std::vector<EdgeList>  EdgeVector;  //储存稀疏图的邻接表
    
public:
    
    HanoidGraph(bool digraph):SparseGraph<node_type,edge_type>(digraph){}

    
    //根据现有的一个状态，派生出相邻的状态
    void addHanoidNode(int no)
    {
        NodeType node = this->GetNode(no);
        
        for (int i =0; i<=2; i++) {
            
            NodeType newNode = node;
            if(newNode.MovePlate(i,(i+1)%3))
            {
                int l;
                if (( l = checkNode(newNode))==-1) {
                    newNode.setIndex(this->GetNextFreeNodeIndex());
                    EdgeType newEdge = EdgeType(no,newNode.Index());
                    this->AddNode(newNode);
                  
                    this->AddEdge(newEdge);
                }else{
                    EdgeType newEdge = EdgeType(no,l);
                    this->AddEdge(newEdge);
                    
                }
            }
            
            NodeType newNode1 = node;
            if(newNode1.MovePlate(i,(i+2)%3))
            {
                int l;
                if ((l = checkNode(newNode1))==-1) {
                    newNode1.setIndex(this->GetNextFreeNodeIndex());
                    EdgeType newEdge = EdgeType(no,newNode1.Index());
                    this->AddNode(newNode1);
                    this->AddEdge(newEdge);
                }else {
                    EdgeType newEdge = EdgeType(no,l);
                    this->AddEdge(newEdge);
                }
                
            }
        }
    }
    
    
    //检查该状态是否已经存在
    int checkNode(NodeType node)
    {
        for (int i =0; i<(this->GetNodes()).size(); i++) {
            NodeType e_node = (this->GetNodes())[i];
            if (e_node.GetA()==node.GetA()&&e_node.GetB()==node.GetB()&&e_node.GetC()==node.GetC()) {
                return i;
            }
        }
        return -1;
    }

    
    
    
    
};

//客户可能使用的用来存取边和节点的迭代器


#endif /* defined(__HanoiTower__HanoidGraph__) */
