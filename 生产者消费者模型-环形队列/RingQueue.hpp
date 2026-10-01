#include "Sem.hpp"
#include <vector>
static const int Space = 5;

template <class T>
class RingQueue
{
public:
    RingQueue()
        : _cap(Space), _rq(_cap), _c_step(0), _p_step(0), _c_sem(0), _p_sem(_cap)
    {
    }

    void Equeue(const T &in)
    {
        _p_sem.P();

        _rq[_p_step] = in;

        _p_step++;

        _p_step %= _cap;

        _c_sem.V();
    }

    void Pop(T *out)
    {
        _c_sem.P();

        *out = _rq[_c_step];

        _c_step++;

        _c_step %= _cap;

        _p_sem.V();
    }

private:
    int _cap;
    std::vector<T> _rq;

    SemModule _c_sem;
    SemModule _p_sem;

    int _c_step;
    int _p_step;
};