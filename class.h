#pragma once
#include <string>

class User {
public:
  std::string _name;
  std::string _login;
  std::string _pass;

  void save(std::ofstream &out) const;

  void load(std::ifstream &in);
};

class Message {
public:
  std::string _text;
  std::string _sender;
  std::string _receiver;

  void save(std::ofstream &out) const;

  void load(std::ifstream &in);
};