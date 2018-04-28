#include "ringqueue.h"
#include <iostream>
template <class T>
RingQueue<T>::RingQueue(uint32_t compacity){
    m_length = m_in = m_out = 0;
    m_compacity = compacity;
    m_queue = new T[compacity];
}

template <class T>
RingQueue<T>::~RingQueue(){
    delete [] m_queue;
    m_queue = NULL;
}

template <class T>
bool RingQueue<T>::IsFull(){
    return (m_out - m_in == m_compacity);
}

template <class T>
bool RingQueue<T>::IsEmpty(){
    return (m_out == m_in);
}

template <class T>
uint32_t RingQueue<T>::GetLength(){
    return m_length;
}

template <class T>
uint32_t RingQueue<T>::GetCompacity(){
    return m_compacity;
}

template <class T>
bool RingQueue<T>::EnQueue(const T& element){
    if(!IsFull()){
        m_queue[m_in & (MASK)] = element;
        m_in++;
        m_length++;
        return true;
    }
    return false;
}

template <class T>
T* RingQueue<T>::DeQueue(){
    if(IsEmpty()){
        return NULL;
    }else{
        T* ret = &m_queue[m_out & (MASK)];
        m_out++;
        m_length--;
        return ret;
    } 
}
