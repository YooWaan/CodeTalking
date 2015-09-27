
#include <cstdint>
#include "struct.hpp"

// Value
class VarInt : public Value {
public:
  VarInt();
  VarInt(int64_t v);
  int64_t GetInt() const;
  float GetFloat() const;

private:
  int64_t value;
};


VarInt::VarInt() {
  value = 0;
}

VarInt::VarInt(int64_t v) {
  value = v;
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

int64_t VarFloat::GetInt() const {
  return static_cast<int64_t>(this->value);
}

float VarFloat::GetFloat() const {
  return this->value;
}

class Add : public Expr, public Value {
public:
  Add();
  Add(Value* left, Value* right);
  ~Add();
  // Expr
  Value* GetLeft() const;
  void SetLeft(Value* value);
  Value* GetRight() const;
  void SetRight(Value* value);
  Value* CalcI() const;
  Value* CalcF() const;
  // Value
  int64_t GetInt() const;
  float GetFloat() const;
private:
  Value* left;
  Value* right;
};


Add::Add() {
  left = NULL;
  right = NULL;
}

Add::Add(Value* l, Value* r) {
  left = l;
  right = r;
}

Add::~Add() {
  delete left;
  delete right;
}

Value* Add::GetLeft() const { return this->left;}
void Add::SetLeft(Value* v) { this->left = v;}
Value* Add::GetRight() const { return this->right;}
void Add::SetRight(Value* v) { this->right = v;}

int64_t Add::GetInt() const {
  return this->left->GetInt() + this->right->GetInt();
}
float Add::GetFloat() const {
  return this->left->GetFloat() + this->right->GetFloat();
}

Value* Add::CalcI() const {
  return NewInt(this->GetInt());
}

Value* Add::CalcF() const {
  return NewFloat(this->GetFloat());
}

// Create Factory Method
Value* NewInt(int64_t value) {
  return new VarInt(value);
}

Value* NewFloat(float v) {
  return new VarFloat(v);
}

Expr* NewAdd(Value* left, Value* right) {
  return new Add(left, right);
}
