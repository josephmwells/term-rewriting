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

/////////////////////////////////////////////////////////////////
// TERM
/////////////////////////////////////////////////////////////////

template<typename T>
class term {
public:
    typedef term<T> value_type;
    typedef term_ptr<T> pointer;
    typedef term<T>& reference;
    typedef size_t size_type;
    typedef std::forward_iterator_tag iterator_category;
    typedef term_iterator<T> iterator;
    typedef term_iterator<const T> const_iterator;

    term<T>() {};

    term<T>& operator=(const term<T>& other) { return *this;}

    iterator begin() { return iterator(*this, true); }

    iterator end() { return iterator(*this, false); }

    virtual std::vector<term_ptr<T>> children() { return std::vector<term_ptr<T>>(); }

    virtual void set_child(term_ptr<T> sub, int index) {}

    virtual term_ptr<T> substitute(const Sub<T> &sigma) const = 0;

    virtual term_ptr<T> make_ptr() const = 0;

    virtual void print() const = 0;

private:
};

/////////////////////////////////////////////////////////////////
// VARIABLE
/////////////////////////////////////////////////////////////////

template<typename T>
class variable : public term<T> {
public:
    variable<T>() : term<T>() {};

    variable<T>(const variable<T>& copy) : term<T>(), name_{copy.name_} {};

    variable<T>(std::string name) : term<T>(), name_{name} {};

    variable<T>& operator=(const variable<T> &other);

    term_ptr<T> substitute(const Sub<T> &sigma) const override;

    term_ptr<T> make_ptr() const override;

    void print() const override;

private:
    std::string name_;
};

template<typename T>
variable<T>& variable<T>::operator=(const variable<T> &other) {
    name_ = other.name_;
    return *this;
}

template<typename T>
term_ptr<T> variable<T>::substitute(const Sub<T> &sigma) const {
    term<T>& t = sigma(name_);
    return t.make_ptr();
}

template<typename T>
term_ptr<T> variable<T>::make_ptr() const {
    return std::make_shared<variable<T>>(*this);
}

template<typename T>
void variable<T>::print() const {
    std::cout << name_;
}

/////////////////////////////////////////////////////////////////
// LITERAL
/////////////////////////////////////////////////////////////////

template<typename T>
class literal : public term<T> {
public:
    literal<T>() : term<T>() {};

    literal<T>(const literal<T> &copy) : term<T>(), value_{copy.value_} {};

    literal<T>(T value) : term<T>(), value_{value} {};

    literal<T>& operator=(const literal<T> &other);

    term_ptr<T> substitute(const Sub<T> &sigma) const override;

    term_ptr<T> make_ptr() const override;

    void print() const override;

private:
    T value_;
};

template<typename T>
literal<T>& literal<T>::operator=(const literal<T> &other) {
    value_ = other.value_;
    return *this;
}

template<typename T>
term_ptr<T> literal<T>::substitute(const Sub<T> &sigma) const {
    return make_ptr();
}

template<typename T>
term_ptr<T> literal<T>::make_ptr() const {
    return std::make_shared<literal<T>>(*this);
}

template<typename T>
void literal<T>::print() const {
    std::cout << value_;
}

template<>
void literal<bool>::print() const {
    if (value_) std::cout << "true";
    if (!value_) std::cout << "false";
}


/////////////////////////////////////////////////////////////////
// FUNCTION
/////////////////////////////////////////////////////////////////

template<typename T>
class function : public term<T> {
public:
    function<T>() : term<T>() {};

    function<T>(const function<T> &copy)
            : term<T>(), name_{copy.name_}, arity_{copy.arity_}, children_{copy.children_} {};

    function<T>(std::string name, int arity, std::vector<term_ptr<T>> children)
            : term<T>(), name_{name}, arity_{arity}, children_{children} {};

    function<T>& operator=(const function<T> &other);

    std::vector<term_ptr<T>> children() override { return children_; };

    void set_child(term_ptr<T> sub, int index) override;

    term_ptr<T> substitute(const Sub<T> &sigma) const override;

    term_ptr<T> make_ptr() const override;

    void print() const override;

private:
    std::string name_;
    int arity_;
    std::vector<term_ptr<T>> children_;
};

template<typename T>
function<T>& function<T>::operator=(const function<T>& other) {
    name_ = other.name_;
    arity_ = other.arity_;
    children_ = other.children_;
    return *this;
}

template<typename T>
void function<T>::set_child(term_ptr<T> sub, int index) {
    children_[index] = sub;
}

template<typename T>
term_ptr<T> function<T>::substitute(const Sub<T>& sigma) const {
    function<T> t_copy = *this;
    for(term_ptr<T>& t : t_copy.children_) {
        t = t->substitute(sigma);
    }
    return t_copy.make_ptr();
}

template<typename T>
term_ptr<T> function<T>::make_ptr() const {
    return std::make_shared<function<T>>(*this);
}

template<typename T>
void function<T>::print() const {
    std::cout << name_;
    std::cout << "(";
    for (const term_ptr<T>& t : children_) {
        t->print();
        if (t != children_.back()) std::cout << ", ";
    }
    std::cout << ")";
}



/////////////////////////////////////////////////////////////////
//
// unify
//
/////////////////////////////////////////////////////////////////

template<typename T>
bool unify(const term<T> &t1, const term<T> &t2, Sub<T> &sigma) {
}

/////////////////////////////////////////////////////////////////
//
// reduce
//
/////////////////////////////////////////////////////////////////

template<typename T>
term_ptr<T> reduce(term_ptr<T> t, const std::vector<rule<T>> &rules) {
}

/////////////////////////////////////////////////////////////////
//
// rewrite
//
/////////////////////////////////////////////////////////////////

template<typename T>
term_ptr<T> rewrite(term_ptr<T> t, const term<T>& rhs, std::vector<int> path, const Sub<T>& sigma) {
    if(path.empty()) {
        term_ptr<T> t_new = rhs.substitute(sigma);
        return t_new;
    }

    term_ptr<T> current = t;
    for(int i : path) {
        if(i != path.back()) current = current->children()[i-1];
    }
    current->set_child(rhs.substitute(sigma), path.back() - 1);
    return t;
}

/////////////////////////////////////////////////////////////////
//
// operator<<
//
/////////////////////////////////////////////////////////////////

template<typename T>
std::ostream &operator<<(std::ostream& out, const term<T>& t) {
    t.print();
    return out;
}

#endif // TERM_HPP
