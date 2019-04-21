//===--- M6502.h - Declare M6502 target feature support ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares M6502 TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_BASIC_TARGETS_M6502_H
#define LLVM_CLANG_LIB_BASIC_TARGETS_M6502_H

#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Support/Compiler.h"

namespace clang {
namespace targets {

class LLVM_LIBRARY_VISIBILITY M6502TargetInfo : public TargetInfo {
  static const char *const GCCRegNames[];

public:
  // TODO: support sub-targets for Apple II, Atari, Commodore 64, NES, etc.
  M6502TargetInfo(const llvm::Triple &Triple, const TargetOptions &Opts)
      : TargetInfo(Triple) {
    BigEndian = false;
    TLSSupported = false;
    NoAsmVariants = true;
    PointerWidth = 16;
    IntWidth = 16;
    PointerAlign = IntAlign = LongAlign = LongLongAlign = SuitableAlign =
        DefaultAlignForAttributeAligned = HalfAlign = FloatAlign =
        DoubleAlign = LongDoubleAlign = Float128Align
        = 8;
    SizeType = UnsignedInt;
    PtrDiffType = SignedInt;
    IntPtrType = SignedInt;
    Char32Type = UnsignedLong;
    resetDataLayout("e-p:16:8-n8");
  }
  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override {
    defineCPUMacros(Builder, "m6502");
    // FIXME: use an existing #define name if one has been established by other compilers.
    // See <http://cc65.github.io/doc/cc65.html#s6>
  }
  ArrayRef<Builtin::Info> getTargetBuiltins() const override {
    // FIXME: implement
    return None;
  }
  ArrayRef<const char *> getGCCRegNames() const override {
    // No GCC reg names.
    return None;
  }
  ArrayRef<TargetInfo::GCCRegAlias> getGCCRegAliases() const override {
    // No aliases.
    return None;
  }
  bool validateAsmConstraint(const char *&Name,
                             TargetInfo::ConstraintInfo &info) const override {
    // No target constraints for now.
    return false;
  }
  const char *getClobbers() const override {
    // FIXME: Is this really right?
    return "";
  }
  BuiltinVaListKind getBuiltinVaListKind() const override {
    // FIXME: implement
    return TargetInfo::CharPtrBuiltinVaList;
  }
};


} // namespace targets
} // namespace clang
#endif // LLVM_CLANG_LIB_BASIC_TARGETS_M6502_H
