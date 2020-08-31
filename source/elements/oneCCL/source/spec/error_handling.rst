Error Handling
==============

oneCCL error handling relies on the mechanism of C++ exceptions. If an error occurs,
it shall be propagated at the point of a function call where it is caught
using standard C++ error handling mechanism.

oneCCL specification defines ``exception`` as a type for exceptions that may be thrown by oneCCL API.
