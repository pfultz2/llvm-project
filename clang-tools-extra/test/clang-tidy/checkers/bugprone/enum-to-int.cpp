// RUN: %check_clang_tidy -std=c++11-or-later --fix-notes %s bugprone-enum-to-int %t

enum A { e1,
         e2 };

  enum B : unsigned int {
    e3, e4
  };

struct bar {
  bar(int);
};
void foo(int i);
void foo_unsigned(unsigned int i);
void f1() {
  foo(e1);
  // CHECK-NOTES: :[[@LINE-1]]:7: warning: enum is implictly converted to an integral [bugprone-enum-to-int]
  // CHECK-NOTES: :[[@LINE-2]]:7: note: insert an explicit cast
  // CHECK-NOTES: static_cast<int>( )
  // CHECK-FIXES: foo(static_cast<int>(e1));
}
void f2() {
  foo(static_cast<int>(e2));
}
void f3() {
  int i = e1;
  foo(i);
}
void f4() {
  bar a(e1);
  // CHECK-NOTES: :[[@LINE-1]]:9: warning: enum is implictly converted to an integral [bugprone-enum-to-int]
  // CHECK-NOTES: :[[@LINE-2]]:9: note: insert an explicit cast
  // CHECK-NOTES: static_cast<int>( )
  // CHECK-FIXES: bar a(static_cast<int>(e1));
}
void f5() {
  auto a = bar{e1};
  // CHECK-NOTES: :[[@LINE-1]]:16: warning: enum is implictly converted to an integral [bugprone-enum-to-int]
  // CHECK-NOTES: :[[@LINE-2]]:16: note: insert an explicit cast
  // CHECK-NOTES: static_cast<int>( )
  // CHECK-FIXES: auto a = bar{static_cast<int>(e1)};
}
int f6() {
  return e1;
  // CHECK-NOTES: :[[@LINE-1]]:10: warning: enum is implictly converted to an integral [bugprone-enum-to-int]
  // CHECK-NOTES: :[[@LINE-2]]:10: note: insert an explicit cast
  // CHECK-NOTES: static_cast<int>( )
  // CHECK-FIXES: return static_cast<int>(e1);
}
void f7() {
  foo_unsigned(e1);
  // CHECK-NOTES: :[[@LINE-1]]:16: warning: enum is implictly converted to an integral [bugprone-enum-to-int]
  // CHECK-NOTES: :[[@LINE-2]]:16: note: insert an explicit cast
  // CHECK-NOTES: static_cast<unsigned int>( )
  // CHECK-FIXES: foo_unsigned(static_cast<unsigned int>(e1));
}
void f8() {
  foo(e4);
  // CHECK-NOTES: :[[@LINE-1]]:7: warning: enum is implictly converted to an integral [bugprone-enum-to-int]
  // CHECK-NOTES: :[[@LINE-2]]:7: note: insert an explicit cast
  // CHECK-NOTES: static_cast<int>( )
  // CHECK-FIXES: foo(static_cast<int>(e4));
}
void f9() {
  foo_unsigned(e4);
  // CHECK-NOTES: :[[@LINE-1]]:16: warning: enum is implictly converted to an integral [bugprone-enum-to-int]
  // CHECK-NOTES: :[[@LINE-2]]:16: note: insert an explicit cast
  // CHECK-NOTES: static_cast<unsigned int>( )
  // CHECK-FIXES: foo_unsigned(static_cast<unsigned int>(e4));
}