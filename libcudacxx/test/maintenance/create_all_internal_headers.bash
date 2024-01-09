#!/usr/bin/env bash

#this creates a set of tests, that ensures, that all itnernal headers can be build independently

set -e

internal_headers=$(find ../../include -path "*cuda/std/detail/libcxx/include/__*/*" -not -path "*/__cuda/*")

cd ../libcudacxx/libcxx/internal_headers

for f in $internal_headers
do
    short_path=${f##*../include/}
    test_name=${f##*include/}
    test_name=${test_name%.h}.pass.cpp

    mkdir -p -- "${test_name%/*}"
    cat > $test_name << EOL
//===----------------------------------------------------------------------===//
//
// Part of libcu++, the C++ Standard Library for your entire system,
// under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES.
//
//===----------------------------------------------------------------------===//
#include <cuda/std/version>
#include <$short_path>
int main(int, char**) { return 0; }
EOL

  if [[ $(grep -c "#if .* && \!defined(_LIBCUDACXX_[A-Z_]*_FALLBACK" $f) -ne 0 ]]; then
    fallback=$(grep -o "_LIBCUDACXX_[A-Z_]*_FALLBACK[A-Z_]*" $f)
    fallback=($(echo ${fallback[@]} | tr ' ' '\n' | sort -nu))

    fallback_test_name=${test_name%.pass.cpp}_fallback.pass.cpp
    cat > $fallback_test_name << EOL
//===----------------------------------------------------------------------===//
//
// Part of libcu++, the C++ Standard Library for your entire system,
// under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES.
//
//===----------------------------------------------------------------------===//
#define $fallback
#include <cuda/std/version>
#include <$short_path>
int main(int, char**) { return 0; }
EOL
  fi
done
