#ifndef OP_SYS_HPP
#define OP_SYS_HPP

#include <algorithm>
#include <cstdint>
#include <string>

#include "types.hpp"

extern "C" void callFunc(const void *funcPtr, const size_t *stack, size_t numArgs);

enum OpParamType
{
    OPT_INT,
    OPT_FLT,
    OPT_STR
};

struct OpParam
{
    OpParamType type;
    int         chans;
 
    union
    {
        float   flts[4];
        int     ints[4];
    };

    std::string str; // can't be in union
};

struct Op
{
    Op(const void *execFunc, const OpParam *params, size_t numParams) : 
        m_execFunc(execFunc),
        m_numParams(numParams)
    {
        std::copy(params, params+numParams, m_params);
    }

    void execute()
    {
        size_t args[16+1] = {(size_t)this};

        for (uint32_t i=0; i<m_numParams; i++)
        {
            const OpParam &p = m_params[i];
            switch (p.type)
            {
            case OPT_STR:
                args[i+1] = (size_t)&p.str;
                break;
            default: // float and integer types (it's a union!)
                args[i+1] = (p.chans > 1 ? (size_t)p.ints : (size_t)p.ints[0]);
                break;
            }
        }

        callFunc(m_execFunc, args, m_numParams+1);
    }
 
public:
    const void * m_execFunc;
    size_t       m_numParams;
    OpParam      m_params[16];
};

#endif