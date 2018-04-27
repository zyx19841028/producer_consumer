#ifndef RINGQUEUE_H
#define RINGQUEUE_H
#include <stdint.h>
#define COMPACITY (10<<1)
#define MASK (COMPACITY-1)
template<class T>
class RingQueue{
    private:
        uint32_t m_length;
        uint32_t m_compacity;
        uint32_t m_in;
        uint32_t m_out;
        T* m_queue;
    public:
        RingQueue(uint32_t compacity = COMPACITY);
        ~RingQueue(); 
        uint32_t GetLength();
        bool EnQueue(const T& element);
        T* DeQueue();
        bool IsFull();
        bool IsEmpty();
        uint32_t GetCompacity();
};
 
#endif
