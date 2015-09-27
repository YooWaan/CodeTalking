#ifndef STRUCT_HPP
#define STRUCT_HPP

#include <cstdint>


struct Value {
  virtual int64_t GetInt() const = 0;
  virtual float GetFloat() const = 0;
  virtual ~Value() {}
};

struct Expr {
  virtual Value* GetLeft() const = 0;
  virtual void SetLeft(Value* value) = 0;
  virtual Value* GetRight() const = 0;
  virtual void SetRight(Value* value) = 0;
  virtual Value* CalcI() const = 0;
  virtual Value* CalcF() const = 0;
  virtual ~Expr() {}
};

Value* NewInt(int64_t value);
Value* NewFloat(float value);

Expr* NewAdd(Value* left, Value* right);

#endif
