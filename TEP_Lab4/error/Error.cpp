#include "Error.h"

using namespace std;

Error::Error(const string &errorMessage){
  this->errorMessage = errorMessage;
}

Error::Error(const Error &other){
  this->errorMessage = other.errorMessage;
}

Error::~Error(){
}

std::ostream& operator<<(std::ostream& os, const Error& err) {
  os << err.errorMessage;
  return os;
}

string Error::getErrorMessage() {
  return errorMessage;
}