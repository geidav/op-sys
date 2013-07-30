#include <iostream>

#include "opsys.hpp"

void FooOpExec(Op *op, const Size2 &size, float val, const std::string &str)
{
    std::cout << size.x << ", " << size.y << std::endl;
    std::cout << val << std::endl;
    std::cout << str << std::endl;
}

int main(int argc, char **argv)
{
    OpParam fooParams[3] =
    {
        {OPT_INT, 2},
        {OPT_FLT, 1},
        {OPT_STR}
    };

    // cannot be directly initialized in declaration
    // above, because of the way unions are treated
    // in aggregate initializion
    fooParams[0].ints[0] = 256;
    fooParams[0].ints[1] = 256;
    fooParams[1].flts[0] = 2.0f;
    fooParams[2].str = "test";

    Op op(&FooOpExec, fooParams, 3);
    op.execute();
    return 0;
}