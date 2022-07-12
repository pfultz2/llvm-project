//===--- EnumToIntCheck.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "EnumToIntCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bugprone {

void EnumToIntCheck::registerMatchers(MatchFinder *Finder) {
  auto ImplicitEnumToInt = implicitCastExpr(
      hasCastKind(CK_IntegralCast),
      hasSourceExpression(expr(hasType(enumType()))),
      anyOf(hasParent(callExpr()), hasParent(cxxConstructExpr()))
  );
  Finder->addMatcher(ImplicitEnumToInt.bind("x"), this);
}

void EnumToIntCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *MatchedExpr = Result.Nodes.getNodeAs<Expr>("x");
  diag(MatchedExpr->getBeginLoc(),
       "Enum is implictly converted to an integral.")
      << MatchedExpr->getSourceRange();
}

} // namespace bugprone
} // namespace tidy
} // namespace clang
