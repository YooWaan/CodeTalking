#ifndef STRUCT_HPP
#define STRUCT_HPP

#include <cstdint>
#include <memory>

using namespace std;

struct Value {
  virtual int64_t GetInt() const = 0;
  virtual float GetFloat() const = 0;
  virtual ~Value() {}
};

struct Expr : public Value {
  virtual shared_ptr<Value> GetLeft() const = 0;
  virtual void SetLeft(shared_ptr<Value> value) = 0;
  virtual shared_ptr<Value> GetRight() const = 0;
  virtual void SetRight(shared_ptr<Value> value) = 0;
  virtual shared_ptr<Value> CalcI() const = 0;
  virtual shared_ptr<Value> CalcF() const = 0;
  virtual ~Expr() {}
};

Value* NewInt(int64_t value);
Value* NewFloat(float value);
Expr* NewAdd(shared_ptr<Value> left, shared_ptr<Value> right);
Expr* NewMul(shared_ptr<Value> left, shared_ptr<Value> right);


#endif
