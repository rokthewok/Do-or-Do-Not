#ifndef THEREISNO_EXCEPTIONS_H
#define THEREISNO_EXCEPTIONS_H

#include <exception>


namespace tin {

class ChildNodeNotFoundException : public std::exception {
};

class ChildNodeAlreadyExistsException : public std::exception {
};

} // namespace tin

#endif // THEREISNO_EXCEPTIONS_H
