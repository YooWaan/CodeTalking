#include <iostream>
#include <cstdint>
#include "struct.hpp"


int main(void) {
  Value* a = NewInt((int64_t)123);
  Value* c = NewFloat((float)1.5);

  std::cout << "a=" << a->GetInt()
            << " c=" << c->GetInt() << "(" << c->GetFloat() << ")"
            << std::endl;

  // (a + b) * c
  Expr* expr = NewAdd(a, c);

  Value* ansI = expr->CalcI();
  Value* ansF = expr->CalcF();

  std::cout << "I=" << ansI->GetInt()
            << " F=" << ansF->GetFloat()
            << std::endl;

  delete ansI;
  delete ansF;

  delete expr;
  return 0;
}
