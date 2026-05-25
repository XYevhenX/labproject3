// Àâòîð êîäó: Çþç³í ªâãåí, Ê16

#pragma once

#include <initializer_list>
#include <utility>
#include <cstddef>
#include <iterator>

using namespace std;

struct Point
{
    double x;
    double y;
};

class DS
{
public:
    using value_type = Point;
    using reference = Point&;
    using const_reference = const Point&;
    using size_type = size_t;

    class const_iterator;

    friend class Test;

private:
    struct Node
    {
        Point data;
        Node* prev;
        Node* next;

        template <typename... Args>
        Node(
            Node* p,
            Node* n,
            Args&&... args
        )
            : data{ forward<Args>(args)... },
            prev(p),
            next(n)
        {
        }
    };

    Node* head;
    size_type sz;

public:
    class const_iterator
    {
    public:
        using iterator_category = bidirectional_iterator_tag;
        using value_type = const Point;
        using difference_type = ptrdiff_t;
        using pointer = const Point*;
        using reference = const Point&;

    private:
        Node* current;
        Node* head;
        bool is_end;

        friend class DS;

        const_iterator(
            Node* c,
            Node* h,
            bool e
        )
            : current(c),
            head(h),
            is_end(e)
        {
        }

    public:
        const_iterator()
            : current(nullptr),
            head(nullptr),
            is_end(true)
        {
        }

        reference operator*() const
        {
            return current->data;
        }

        pointer operator->() const
        {
            return &(current->data);
        }

        const_iterator& operator++()
        {
            if (!is_end && current)
            {
                current = current->next;
                if (current == head)
                {
                    is_end = true;
                }
            }
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        const_iterator& operator--()
        {
            if (is_end && head)
            {
                current = head->prev;
                is_end = false;
            }
            else if (current)
            {
                current = current->prev;
            }
            return *this;
        }

        const_iterator operator--(int)
        {
            const_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(
            const const_iterator& other
            ) const
        {
            return current == other.current
                && is_end == other.is_end
                && head == other.head;
        }

        bool operator!=(
            const const_iterator& other
            ) const
        {
            return !(*this == other);
        }
    };

    DS();

    DS(
        initializer_list<Point> init
    );

    DS(
        const DS& other
    );

    DS(
        DS&& other
    ) noexcept;

    DS& operator=(
        const DS& other
        );

    DS& operator=(
        DS&& other
        ) noexcept;

    ~DS();

    size_type size() const;
    size_type capacity() const;
    bool empty() const;

    const_iterator begin() const;
    const_iterator end() const;

    template <typename... Args>
    const_iterator emplace(
        const_iterator pos,
        Args&&... args
    )
    {
        if (empty())
        {
            head = new Node(
                nullptr,
                nullptr,
                forward<Args>(args)...
            );
            head->next = head;
            head->prev = head;
            ++sz;

            return const_iterator(
                head,
                head,
                false
            );
        }

        Node* current_node = pos.is_end ? head : pos.current;
        Node* prev_node = current_node->prev;

        Node* new_node = new Node(
            prev_node,
            current_node,
            forward<Args>(args)...
        );

        prev_node->next = new_node;
        current_node->prev = new_node;

        if (pos.current == head && !pos.is_end)
        {
            head = new_node;
        }

        ++sz;

        return const_iterator(
            new_node,
            head,
            false
        );
    }

    const_iterator insert(
        const_iterator pos,
        const Point& val
    );

    const_iterator erase(
        const_iterator pos
    );

    void push_back(
        const Point& val
    );

    void push_front(
        const Point& val
    );

    void pop_back();
    void pop_front();

    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    void clear();
};