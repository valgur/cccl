//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCUDACXX___CONCEPTS_BOOLEAN_TESTABLE_H
#define _LIBCUDACXX___CONCEPTS_BOOLEAN_TESTABLE_H

#ifndef __cuda_std__
#include <__config>
#endif //__cuda_std__

#include "../__concepts/__concept_macros.h"
#include "../__concepts/convertible_to.h"
#include "../__utility/forward.h"

#if defined(_CCCL_IMPLICIT_SYSTEM_HEADER_GCC)
#  pragma GCC system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_CLANG)
#  pragma clang system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_MSVC)
#  pragma system_header
#endif // no system header

_LIBCUDACXX_BEGIN_NAMESPACE_STD

#if _CCCL_STD_VER > 2017

// [concepts.booleantestable]

template<class _Tp>
concept __boolean_testable_impl = convertible_to<_Tp, bool>;

template<class _Tp>
concept __boolean_testable = __boolean_testable_impl<_Tp> && requires(_Tp&& __t) {
  { !_CUDA_VSTD::forward<_Tp>(__t) } -> __boolean_testable_impl;
};

#elif _CCCL_STD_VER > 2011

template<class _Tp>
_LIBCUDACXX_CONCEPT __boolean_testable_impl = convertible_to<_Tp, bool>;

template<class _Tp>
_LIBCUDACXX_CONCEPT_FRAGMENT(
  __boolean_testable_,
  requires(_Tp&& __t)(
    requires(__boolean_testable_impl<_Tp>),
    requires(__boolean_testable_impl<decltype(!_CUDA_VSTD::forward<_Tp>(__t))>)
  ));

template<class _Tp>
_LIBCUDACXX_CONCEPT __boolean_testable = _LIBCUDACXX_FRAGMENT(__boolean_testable_, _Tp);

#endif // _CCCL_STD_VER > 2011

_LIBCUDACXX_END_NAMESPACE_STD

#endif // _LIBCUDACXX___CONCEPTS_BOOLEAN_TESTABLE_H
