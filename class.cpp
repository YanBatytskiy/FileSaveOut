#include "class.h"
#include <fstream>
#include <string>

void User::save(std::ofstream &out) const {
  out << _name << std::endl << _login << std::endl << _pass << std::endl;
}

void User::load(std::ifstream &in) {
  std::getline(in, _name);
  std::getline(in, _login);
  std::getline(in, _pass);
}

void Message::save(std::ofstream &out) const {
  out << _text << std::endl << _sender << std::endl << _receiver << std::endl;
}

void Message::load(std::ifstream &in) {
  std::getline(in, _text);
  std::getline(in, _sender);
  std::getline(in, _receiver);
}
