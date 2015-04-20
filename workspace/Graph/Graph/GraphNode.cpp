//
//  GraphNode.cpp
//  GraphDemo
//
//  Created by 张世杰 on 15/4/20.
//
//

#define invalid_node_index -1   // 表示改节点不存在的索引
#include "GraphNode.h"

/*
 *   封装一个表示邻接表图所需要的关于一个节点的最小信息，所有类型的节点都继承于这个节点
 *   m_iIndex : 一个唯一标识符
 *
 */


class GraphNode {
protected:
    //每一个节点有一个索引，一个有效的索引>=0
    int m_iIndex;
public:
    GraphNode():m_iIndex(invalid_node_index){};
    GraphNode(int idx):m_iIndex(idx){};
    virtual ~GraphNode(){};
    int Index()const{return m_iIndex;};
    void setIndex(int NewIndex){m_iIndex = NewIndex;};
};