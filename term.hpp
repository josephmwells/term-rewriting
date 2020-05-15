#ifndef TERM_HPP
#define TERM_HPP

#include<memory>
#include<vector>
#include<string>
#include<algorithm>
#include<iostream>
#include<exception>
#include "sub.hpp"
#include "term_iterator.hpp"

/////////////////////////////////////////////////////////////////
//
// forward declarations;
//
/////////////////////////////////////////////////////////////////

// This just makes life a lot more convenient
template<typename T>
using term_ptr = std::shared_ptr<term<T>>;

template<typename T>
using rule = std::pair<term_ptr<T>, term_ptr<T>>;

/////////////////////////////////////////////////////////////////
//
// class definitions
//
// The overall structure is pretty simple
// variable <: term
// literal  <: term
// function <: term
//
// Each term can have subterms in it.
//
/////////////////////////////////////////////////////////////////

template<typename T>
class term { 
  public:
    term() {};

  private:
};

template<typename T>
class variable : public term<T> { 
  public:
    variable() : term<T>() {};
    variable(std::string name) : term<T>(), name_{name} {};
  private:
    std::string name_;
};

template<typename T>
class literal : public term<T> { 
  public:
    literal() : term<T>() {};
    literal(T lit) : term<T>(), literal_{lit} {};
  private:
    T literal_;
};

template<typename T>
class function : public term<T> { 
  public:
    function() : term<T>() {};
    function(std::string name, int arity, std::vector<term_ptr<T>> children) : term<T>(), name_{name}, arity_{arity}, children_{children} {}; 
  private:
    std::string name_;
    int arity_;
    std::vector<term_ptr<T>> children_;
    


};


/////////////////////////////////////////////////////////////////
//
// unify
//
/////////////////////////////////////////////////////////////////

template<typename T>
bool unify(const term<T>& t1, const term<T>& t2, Sub<T>& sigma)
{
}

/////////////////////////////////////////////////////////////////
//
// reduce
//
/////////////////////////////////////////////////////////////////

template<typename T>
term_ptr<T> reduce(term_ptr<T> t, const std::vector<rule<T>>& rules)
{
}

/////////////////////////////////////////////////////////////////
//
// rewrite
//
/////////////////////////////////////////////////////////////////

template<typename T>
term_ptr<T> rewrite(term_ptr<T> t, term<T>& rhs, std::vector<int> path, const Sub<T>& sigma)
{
}

/////////////////////////////////////////////////////////////////
//
// operator<<
//
/////////////////////////////////////////////////////////////////

template<typename T>
std::ostream& operator<<(std::ostream& out, const term<T>& t)
{
}

#endif // TERM_HPP
