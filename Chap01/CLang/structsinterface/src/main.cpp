#include <iostream>
#include <cstdint>
#include <memory>
#include "struct.hpp"


int main(void) {
  std::shared_ptr<Value> a = std::shared_ptr<Value>(NewInt(5));
  std::shared_ptr<Value> b = std::shared_ptr<Value>(NewInt(5));
  std::shared_ptr<Value> c = std::shared_ptr<Value>(NewFloat(1.5));

  std::cout << "a=" << a->GetInt()
            << " b=" << b->GetInt()
            << " c=" << c->GetFloat() << "(int64_t:" << c->GetInt() << ")"
            << " a.use_count->" << a.use_count()
            << " b.use_count->" << b.use_count()
            << " c.use_count->" << c.use_count()
            << std::endl;

  

  // (a + b) * c
  std::shared_ptr<Expr> expr
    = std::shared_ptr<Expr>(NewMul(std::shared_ptr<Expr>(NewAdd(a, b)), c));
  cout << "NewExpr"
       << " a.use_count->" << a.use_count()
       << " b.use_count->" << b.use_count()
       << " c.use_count->" << c.use_count()
       << endl;

  std::shared_ptr<Value> ansI = expr->CalcI();
  std::shared_ptr<Value> ansF = expr->CalcF();
  std::cout << "Int64_t=" << ansI->GetInt()
            << " Float=" << ansF->GetFloat()
            << std::endl;

  return 0;
}
