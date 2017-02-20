#include "win32errorhandling.h"

#include <comdef.h>
#include <cstring>
#include <stdexcept>
#include <iostream>

void testHR(HRESULT hr)
{
    if(FAILED(hr)) {
        _com_error err(hr);
        LPCTSTR errMsg = err.ErrorMessage();
        char msg[256];
        wcstombs(msg, errMsg, 256);
        std::cerr << "HRESULT: " << hr << " " << msg << std::endl;
        throw std::runtime_error(msg);
    }
}
