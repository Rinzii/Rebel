#pragma once
#include <stdexcept>

namespace rebel
{
    struct Error : std::runtime_error
{
        using std::runtime_error::runtime_error;
    };

    struct InitError : Error
	{
        using Error::Error;
    };

    struct ValidationError : Error
	{
        using Error::Error;
    };
}
