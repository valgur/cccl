//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCUDACXX___TYPE_TRAITS_REMOVE_CV_H
#define _LIBCUDACXX___TYPE_TRAITS_REMOVE_CV_H

#ifndef __cuda_std__
#include <__config>
#endif // __cuda_std__

#include "../__type_traits/remove_const.h"
#include "../__type_traits/remove_volatile.h"

#if defined(_CCCL_IMPLICIT_SYSTEM_HEADER_GCC)
#  pragma GCC system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_CLANG)
#  pragma clang system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_MSVC)
#  pragma system_header
#endif // no system header

_LIBCUDACXX_BEGIN_NAMESPACE_STD

#if defined(_LIBCUDACXX_REMOVE_CV) && !defined(_LIBCUDACXX_USE_REMOVE_CV_FALLBACK)
template <class _Tp>
struct remove_cv {
  using type _LIBCUDACXX_NODEBUG_TYPE = _LIBCUDACXX_REMOVE_CV(_Tp);
};

template <class _Tp>
using __remove_cv_t = _LIBCUDACXX_REMOVE_CV(_Tp);

#else

template <class _Tp> struct _LIBCUDACXX_TEMPLATE_VIS remove_cv
{typedef __remove_volatile_t<__remove_const_t<_Tp> > type;};

template <class _Tp>
using __remove_cv_t = __remove_volatile_t<__remove_const_t<_Tp> >;

#endif // defined(_LIBCUDACXX_REMOVE_CV) && !defined(_LIBCUDACXX_USE_REMOVE_CV_FALLBACK)

#if _CCCL_STD_VER > 2011
template <class _Tp> using remove_cv_t = __remove_cv_t<_Tp>;
#endif

_LIBCUDACXX_END_NAMESPACE_STD

#endif // _LIBCUDACXX___TYPE_TRAITS_REMOVE_CV_H
