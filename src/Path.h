#ifndef PATH_H
#define PATH_H
#include "Transition.h"

class Path
{
    public:
        Path();
        virtual ~Path();
        std::vector<Transition*> transitionsThatRepresents;
        Node* a;
        Node* b;
        double weight;
    protected:
    private:
};

#endif // PATH_H
