#include "pch.h"
#include "func.h"

#include "CObj.h"

bool IsValid(CObj*& _pTarget)
{
    if (_pTarget == nullptr)
    {
        _pTarget = nullptr;
        return false;
    }

    else if (_pTarget->IsDead())
        return false;

    return true;
}