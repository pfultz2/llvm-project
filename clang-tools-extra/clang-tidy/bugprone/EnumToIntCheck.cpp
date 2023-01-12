//===--- EnumToIntCheck.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "EnumToIntCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Type.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"
#include <iostream>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bugprone {

void EnumToIntCheck::registerMatchers(MatchFinder *Finder) {
  auto ImplicitEnumToInt = implicitCastExpr(
      hasCastKind(CK_IntegralCast),
      hasSourceExpression(expr(hasType(enumType()))),
      anyOf(hasParent(callExpr()), hasParent(cxxConstructExpr()),
            hasParent(returnStmt())));
  Finder->addMatcher(ImplicitEnumToInt.bind("x"), this);
}

void EnumToIntCheck::check(const MatchFinder::MatchResult &Result) {
  if (const auto *MatchedExpr = Result.Nodes.getNodeAs<Expr>("x")) {
    diag(MatchedExpr->getBeginLoc(),
         "enum is implictly converted to an integral")
        << MatchedExpr->getSourceRange();
    auto Note = diag(MatchedExpr->getBeginLoc(), "insert an explicit cast",
                     DiagnosticIDs::Note);
    std::string TypeName = MatchedExpr->getType().getAsString();
    if (Result.Context->getLangOpts().CPlusPlus11) {
      SourceManager &SM = *Result.SourceManager;
      Note << FixItHint::CreateInsertion(MatchedExpr->getBeginLoc(),
                                         "static_cast<" + TypeName + ">(");
      Note << FixItHint::CreateInsertion(
          Lexer::getLocForEndOfToken(MatchedExpr->getEndLoc(), 0, SM,
                                     getLangOpts()),
          ")");
    } else {
      Note << FixItHint::CreateInsertion(MatchedExpr->getBeginLoc(),
                                         "(" + TypeName + ")");
    }
  }
}

} // namespace bugprone
} // namespace tidy
} // namespace clang
