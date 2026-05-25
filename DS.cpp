// Автор коду: Зюзін Євген, К16

#include "DS.h"

DS::DS()
    : head(nullptr),
    sz(0)
{
}

DS::DS(
    initializer_list<Point> init
)
    : head(nullptr),
    sz(0)
{
    try
    {
        for (const auto& item : init)
        {
            push_back(item);
        }
    }
    catch (...)
    {
        clear();
        throw;
    }
}

DS::DS(
    const DS& other
)
    : head(nullptr),
    sz(0)
{
    try
    {
        for (auto it = other.begin(); it != other.end(); ++it)
        {
            push_back(*it);
        }
    }
    catch (...)
    {
        clear();
        throw;
    }
}

DS::DS(
    DS&& other
) noexcept
    : head(other.head),
    sz(other.sz)
{
    other.head = nullptr;
    other.sz = 0;
}

DS& DS::operator=(
    const DS& other
    )
{
    if (this != &other)
    {
        DS tmp(other);
        swap(head, tmp.head);
        swap(sz, tmp.sz);
    }
    return *this;
}

DS& DS::operator=(
    DS&& other
    ) noexcept
{
    if (this != &other)
    {
        clear();
        head = other.head;
        sz = other.sz;
        other.head = nullptr;
        other.sz = 0;
    }
    return *this;
}

DS::~DS()
{
    clear();
}

DS::size_type DS::size() const
{
    return sz;
}

DS::size_type DS::capacity() const
{
    return sz;
}

bool DS::empty() const
{
    return sz == 0;
}

DS::const_iterator DS::begin() const
{
    return const_iterator(
        head,
        head,
        head == nullptr
    );
}

DS::const_iterator DS::end() const
{
    return const_iterator(
        head,
        head,
        true
    );
}

DS::const_iterator DS::insert(
    const_iterator pos,
    const Point& val
)
{
    return emplace(pos, val);
}

DS::const_iterator DS::erase(
    const_iterator pos
)
{
    Node* target = pos.current;

    if (sz == 1)
    {
        delete target;
        head = nullptr;
        sz = 0;
        return end();
    }

    bool was_last = (target == head->prev);
    Node* next_node = target->next;
    Node* prev_node = target->prev;

    prev_node->next = next_node;
    next_node->prev = prev_node;

    if (target == head)
    {
        head = next_node;
    }

    delete target;
    --sz;

    if (was_last)
    {
        return end();
    }

    return const_iterator(
        next_node,
        head,
        false
    );
}

void DS::push_back(
    const Point& val
)
{
    emplace(end(), val);
}

void DS::push_front(
    const Point& val
)
{
    emplace(begin(), val);
}

void DS::pop_back()
{
    if (head->next == head)
    {
        delete head;
        head = nullptr;
    }
    else
    {
        Node* last = head->prev;
        Node* prev_node = last->prev;

        prev_node->next = head;
        head->prev = prev_node;

        delete last;
    }
    --sz;
}

void DS::pop_front()
{
    if (head->next == head)
    {
        delete head;
        head = nullptr;
    }
    else
    {
        Node* last = head->prev;
        Node* second = head->next;

        last->next = second;
        second->prev = last;

        delete head;
        head = second;
    }
    --sz;
}

DS::reference DS::front()
{
    return head->data;
}

DS::const_reference DS::front() const
{
    return head->data;
}

DS::reference DS::back()
{
    return head->prev->data;
}

DS::const_reference DS::back() const
{
    return head->prev->data;
}

void DS::clear()
{
    while (!empty())
    {
        pop_front();
    }
}