
#include <cstdint>
#include <memory>
#include <iostream>
#include "struct.hpp"

using namespace std;

// Value

class VarInt : public Value {
public:
  VarInt();
  VarInt(int64_t v);
  int64_t GetInt() const;
  float GetFloat() const;
  ~VarInt();
private:
  int64_t value;
};


VarInt::VarInt() {
  value = 0;
}

VarInt::VarInt(int64_t v) {
  value = v;
}

VarInt::~VarInt() {
  cout <<  "Destory VarInt" << endl;
}

int64_t VarInt::GetInt() const {
  return this->value;
}

float VarInt::GetFloat() const {
  return static_cast<float>(this->value);
}

class VarFloat : public Value {
public:
  VarFloat();
  VarFloat(float f);
  ~VarFloat();
  int64_t GetInt() const;
  float GetFloat() const;

private:
  float value;
};

VarFloat::VarFloat() {
  value = 0.0;
}

VarFloat::VarFloat(float f) {
  value = f;
}

VarFloat::~VarFloat() {
  cout <<  "Destory VarFloat" << endl;
}

int64_t VarFloat::GetInt() const {
  return static_cast<int64_t>(this->value);
}

float VarFloat::GetFloat() const {
  return this->value;
}

class Add : public Expr, public Value {
public:
  Add();
  Add(shared_ptr<Value> left, shared_ptr<Value> right);
  ~Add();
  // Expr
  shared_ptr<Value> GetLeft() const;
  void SetLeft(shared_ptr<Value> value);
  shared_ptr<Value> GetRight() const;
  void SetRight(shared_ptr<Value> value);
  shared_ptr<Value> CalcI() const;
  shared_ptr<Value> CalcF() const;
  // Value
  int64_t GetInt() const;
  float GetFloat() const;
private:
  shared_ptr<Value> left;
  shared_ptr<Value> right;
};

Add::Add() {
  left = nullptr;
  right = nullptr;
}

Add::Add(shared_ptr<Value> l, shared_ptr<Value> r) {
  left = l;
  right = r;
}

Add::~Add() {
  cout << "Destory Add" << endl;
}

shared_ptr<Value> Add::GetLeft() const { return this->left;}
void Add::SetLeft(shared_ptr<Value> v) { this->left = v;}
shared_ptr<Value> Add::GetRight() const { return this->right;}
void Add::SetRight(shared_ptr<Value> v) { this->right = v;}

int64_t Add::GetInt() const {
  return this->left->GetInt() + this->right->GetInt();
}
float Add::GetFloat() const {
  return this->left->GetFloat() + this->right->GetFloat();
}

shared_ptr<Value> Add::CalcI() const {
  return shared_ptr<Value>(NewInt(this->GetInt()));
}

shared_ptr<Value> Add::CalcF() const {
  return shared_ptr<Value>(NewFloat(this->GetFloat()));
}

// Mul
class Mul : public Expr, public Value {
public:
  Mul();
  Mul(shared_ptr<Value> left, shared_ptr<Value> right);
  ~Mul();
  // Expr
  shared_ptr<Value> GetLeft() const;
  void SetLeft(shared_ptr<Value> value);
  shared_ptr<Value> GetRight() const;
  void SetRight(shared_ptr<Value> value);
  shared_ptr<Value> CalcI() const;
  shared_ptr<Value> CalcF() const;
  // Value
  int64_t GetInt() const;
  float GetFloat() const;
private:
  shared_ptr<Value> left;
  shared_ptr<Value> right;
};

Mul::Mul() {
  left = nullptr;
  right = nullptr;
}

Mul::Mul(shared_ptr<Value> l, shared_ptr<Value> r) {
  left = l;
  right = r;
}

Mul::~Mul() {
  cout << "Destory Mull" << endl;
}

shared_ptr<Value> Mul::GetLeft() const { return this->left;}
void Mul::SetLeft(shared_ptr<Value> v) { this->left = v;}
shared_ptr<Value> Mul::GetRight() const { return this->right;}
void Mul::SetRight(shared_ptr<Value> v) { this->right = v;}

int64_t Mul::GetInt() const {
  return this->left->GetInt() * this->right->GetInt();
}
float Mul::GetFloat() const {
  return this->left->GetFloat() * this->right->GetFloat();
}

shared_ptr<Value> Mul::CalcI() const {
  return shared_ptr<Value>(NewInt(this->GetInt()));
}

shared_ptr<Value> Mul::CalcF() const {
  return shared_ptr<Value>(NewFloat(this->GetFloat()));
}


// Create Factory Method
Value* NewInt(int64_t value) {
  return new VarInt(value);
}

Value* NewFloat(float v) {
  //cout << "NewFloat" << endl;
  return new VarFloat(v);
}

Expr* NewAdd(shared_ptr<Value> left, shared_ptr<Value> right) {
  return new Add(left, right);
}

Expr* NewMul(shared_ptr<Value> left, shared_ptr<Value> right) {
  return new Mul(left, right);
}
