//
//  GraphEdge.h
//  GraphDemo
//
//  Created by 张世杰 on 15/4/20.
//
//

#ifndef __GraphDemo__GraphEdge__
#define __GraphDemo__GraphEdge__

#define invalid_node_index -1   // 表示改节点不存在的索引

#include <stdio.h>


/*
 * GraphEdge 封装了两个节点的边的基本信息
 * m_iFrom : 边的一个起源节点
 * m_iTo : 边的另外一个结束节点
 * m_dCost : 边的权重
 */

class GraphEdge {
    
protected:
    //一条边连接两个节点,有效的节点索引都是正值
    int m_iFrom;
    int m_iTo;
    
    //经过此边需要的开销/权重
    int m_dCost;
public:
    //构造函数
    GraphEdge(int from,int to,double cost): m_dCost(cost),
    m_iFrom(from),
    m_iTo(to)
    {};
    GraphEdge(int from,int to): m_iFrom(from),
    m_iTo(to),
    m_dCost(0)
    {};
    
    GraphEdge():m_dCost(0),
                m_iFrom(invalid_node_index),
                m_iTo(invalid_node_index)
    {};
    
    virtual ~GraphEdge(){};
    int From()const{return m_iFrom;};
    void SetFrom(int from){m_iFrom = from;};
    int To()const{return m_iTo;};
    void SetTo(int to){m_iTo = to;};
    int Cost() const {return m_dCost;};
    void SetCost(int cost){m_dCost = cost;};
    
    };

#endif /* defined(__GraphDemo__GraphEdge__) */
