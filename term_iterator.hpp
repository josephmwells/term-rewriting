#ifndef TERM_ITER_HPP 
#define TERM_ITER_HPP

#include<memory>
#include<vector>
#include<stack>
#include<string>
#include <algorithm>

template<typename T>
using term_ptr = std::shared_ptr<term<T>>;

template<typename T>
class term_iterator {
  public:
    term_iterator<T>() {};
  
    term<T>& operator*() {return *root_;}
    term_iterator<T>& operator++();
    friend bool operator!=(term_iterator<T>& lhs, term_iterator<T>& rhs)
    {
      return false;
    }

  private:
    term_ptr<T> root_;
    std::stack<term_ptr<T>> path_;
};

template<typename T>
term_iterator<T>& term_iterator<T>::operator++()
{
  return *this;
}

#endif // TERM_ITER_HPP
