//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCUDACXX___CONCEPTS_SEMIREGULAR_H
#define _LIBCUDACXX___CONCEPTS_SEMIREGULAR_H

#ifndef __cuda_std__
#include <__config>
#endif //__cuda_std__

#include "../__concepts/__concept_macros.h"
#include "../__concepts/constructible.h"
#include "../__concepts/copyable.h"

#if defined(_CCCL_IMPLICIT_SYSTEM_HEADER_GCC)
#  pragma GCC system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_CLANG)
#  pragma clang system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_MSVC)
#  pragma system_header
#endif // no system header

_LIBCUDACXX_BEGIN_NAMESPACE_STD

#if _CCCL_STD_VER > 2017

// [concept.object]

template<class _Tp>
concept semiregular = copyable<_Tp> && default_initializable<_Tp>;

#elif _CCCL_STD_VER > 2011

// [concept.object]

template<class _Tp>
_LIBCUDACXX_CONCEPT_FRAGMENT(
  __semiregular_,
  requires()(
    requires(copyable<_Tp>),
    requires(default_initializable<_Tp>)
  ));

template<class _Tp>
_LIBCUDACXX_CONCEPT semiregular = _LIBCUDACXX_FRAGMENT(__semiregular_, _Tp);

#endif // _CCCL_STD_VER > 2011

_LIBCUDACXX_END_NAMESPACE_STD

#endif // _LIBCUDACXX___CONCEPTS_SEMIREGULAR_H
