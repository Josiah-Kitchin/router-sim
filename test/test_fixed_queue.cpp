
#include <gtest/gtest.h> 

#include "fixed_queue.hpp"

TEST(FixedQueue, push_pop)
{
    FixedQueue<int> queue(3); 
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    ASSERT_EQ(queue.dequeue(), 1);

    queue.dequeue(); 
    queue.enqueue(6);
    queue.enqueue(10);
    ASSERT_EQ(queue.dequeue(), 3);
}


