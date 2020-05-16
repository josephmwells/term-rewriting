#ifndef TERM_ITER_HPP 
#define TERM_ITER_HPP

#include<memory>
#include<vector>
#include<stack>
#include<string>
#include <algorithm>

//using term_ptr = std::shared_ptr<term<T>>;

template<typename T>
class term_iterator {
  public:
    term_iterator<T>() {};
  
    term<T>& operator*() {return *root_;}
    term_iterator<T>& operator++();
    friend bool operator!=(term_iterator<T>& lhs, term_iterator<T>& rhs);

  private:
    std::shared_ptr<term<T>> root_;
    std::stack<std::shared_ptr<term<T>>> path_;
};

template<typename T>
term_iterator<T>& term_iterator<T>::operator++()
{
  return *this;
}

template<typename T>
bool operator!=(term_iterator<T>& lhs, term_iterator<T>& rhs)
{
  return false;
}

#endif // TERM_ITER_HPP
