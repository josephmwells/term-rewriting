#ifndef TERM_ITER_HPP
#define TERM_ITER_HPP

#include<memory>
#include<vector>
#include<stack>
#include<string>
#include<algorithm>

template<typename T>
using term_ptr = std::shared_ptr<term<T>>;

template<typename T>
class term_iterator {
public:
    typedef term<T> value_type;
    typedef term<T> &reference;
    typedef term_ptr<T> pointer;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef std::forward_iterator_tag iterator_category;

    term_iterator<T>() = delete;

    term_iterator<T>(term<T> &t, bool begin);

    term<T>& operator*() { return *path_.top(); }

    term_iterator<T>& operator++();

    friend bool operator!=(term_iterator<T> &lhs, term_iterator<T> &rhs) {
        return lhs.path_ != rhs.path_;
    }

private:
    term<T>* root_;
    std::stack<term<T>*> path_;
};

template<typename T>
term_iterator<T>::term_iterator(term<T>& t, bool begin) {
    root_ = &t;
    if (begin) {
        term<T>* tmp = &t;
        for(; tmp->children().size() > 0; tmp = tmp->children()[0].get()) {
            path_.push(tmp);
        }
        path_.push(tmp);
    }
}

template<typename T>
term_iterator<T>& term_iterator<T>::operator++() {
    if(!path_.empty()) {
        if(path_.top()->children().size() >= 2) {
            path_.push(path_.top()->children()[1].get());
            while(path_.top()->children().size() >= 1) {
                path_.push(path_.top()->children()[0].get());
            }
        } else {
            term<T>* child = path_.top();
            path_.pop();
            while(!path_.empty() && path_.top()->children().size() >= 2 && path_.top()->children()[1].get() == child) {
                child = path_.top();
                path_.pop();
            }
        }
    }
    return *this;
}

#endif // TERM_ITER_HPP
