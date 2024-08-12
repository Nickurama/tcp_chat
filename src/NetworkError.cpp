#include "NetworkError.hpp"

NetworkError::NetworkError(const std::string &message) : std::runtime_error(message) {};
