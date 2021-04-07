#include "list.h"
#include "very-nice-code.h"

template<typename T>
class Queue {
  protected:
    List<T> *entries_;
  public:
    Queue() {
      entries_ = new List<T>();
    }
    ~Queue() {
      delete entries_;
    }

    int Size() const {
      return entries_->Count();
    }

    bool IsEmpty() const {
      return entries_->Count() == 0;
    }

    Error_code Append(const T &entry) {
      entries_->Add(entry);

      return success;
    }

    void Serve() {
      entries_->RemoveAt(0);
    }

    void Retrieve(T &entry) const {
      entry = entries_->At(0);
      entries_->RemoveAt(0);
    }
};
