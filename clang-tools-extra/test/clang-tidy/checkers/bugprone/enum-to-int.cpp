// RUN: %check_clang_tidy %s bugprone-enum-to-int %t

enum A { e1,
         e2 };

struct bar {
  bar(int);
};
void foo(int i);
void f1() {
  foo(e1);
  // CHECK-MESSAGES: :[[@LINE-1]]:9: warning: Enum is implictly converted to an integral. [bugprone-enum-to-int]
}
void f2() {
  foo(static_cast<int>(e1));
}
void f3() {
  int i = e1;
  foo(i);
}
void f4() {
  bar a(e1);
  // CHECK-MESSAGES: :[[@LINE-1]]:11: warning: Enum is implictly converted to an integral. [bugprone-enum-to-int]
}
void f5() {
  auto a = bar{e1};
  // CHECK-MESSAGES: :[[@LINE-1]]:18: warning: Enum is implictly converted to an integral. [bugprone-enum-to-int]
}
