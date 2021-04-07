#ifndef EXTENDED_QUEUE_H
#define EXTENDED_QUEUE_H

#include "queue.h"

template<typename T>
class ExtendedQueue: public Queue<T> {
  public:
    bool IsFull() const {
      return false;
    }
    void Clear() {
      this->entries_->Clear();
    }
    void ServeAndRetrieve(T &entry) const {
      this->Retrieve(entry);
      this->Serve();
    }
};

#endif
