/*
 * Copyright (c) 2015-2017, Stanford University
 *  
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 * 
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 *  * Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copyright 2013-16 Board of Trustees of Stanford University
 * Copyright 2013-16 Ecole Polytechnique Federale Lausanne (EPFL)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * byteorder.h - utilties for swapping bytes and converting endianness
 */

#pragma once

#include <asm/cpu.h>
#include <ix/compiler.h>

static inline uint16_t __bswap16(uint16_t val)
{
#ifdef HAS_BUILTIN_BSWAP
	return __builtin_bswap16(val);
#else
	return (((val & 0x00ffU) << 8) |
		((val & 0xff00U) >> 8));
#endif
}

static inline uint32_t __bswap32(uint32_t val)
{
#ifdef HAS_BUILTIN_BSWAP
	return __builtin_bswap32(val);
#else
	return (((val & 0x000000ffUL) << 24) |
		((val & 0x0000ff00UL) << 8) |
		((val & 0x00ff0000UL) >> 8) |
		((val & 0xff000000UL) >> 24));
#endif
}

static inline uint64_t __bswap64(uint64_t val)
{
#ifdef HAS_BUILTIN_BSWAP
	return __builtin_bswap64(val);
#else
	return (((val & 0x00000000000000ffULL) << 56) |
		((val & 0x000000000000ff00ULL) << 40) |
		((val & 0x0000000000ff0000ULL) << 24) |
		((val & 0x00000000ff000000ULL) << 8) |
		((val & 0x000000ff00000000ULL) >> 8) |
		((val & 0x0000ff0000000000ULL) >> 24) |
		((val & 0x00ff000000000000ULL) >> 40) |
		((val & 0xff00000000000000ULL) >> 56));
#endif
}

#ifndef __BYTE_ORDER
#error __BYTE_ORDER is undefined
#endif

#if __BYTE_ORDER == __LITTLE_ENDIAN

#define cpu_to_le16(x)	(x)
#define cpu_to_le32(x)	(x)
#define cpu_to_le64(x)	(x)
#define cpu_to_be16(x)	(__bswap16(x))
#define cpu_to_be32(x)	(__bswap32(x))
#define cpu_to_be64(x)	(__bswap64(x))

#define le16_to_cpu(x)	(x)
#define le32_to_cpu(x)	(x)
#define le64_to_cpu(x)	(x)
#define be16_to_cpu(x)	(__bswap16(x))
#define be32_to_cpu(x)	(__bswap32(x))
#define be64_to_cpu(x)	(__bswap64(x))

#else /* __BYTE_ORDER == __LITLE_ENDIAN */

#define cpu_to_le16(x)	(__bswap16(x))
#define cpu_to_le32(x)	(__bswap32(x))
#define cpu_to_le64(x)	(__bswap64(x))
#define cpu_to_be16(x)	(x)
#define cpu_to_be32(x)	(x)
#define cpu_to_be64(x)	(x)

#define le16_to_cpu(x)	(__bswap16(x))
#define le32_to_cpu(x)	(__bswap32(x))
#define le64_to_cpu(x)	(__bswap64(x))
#define be16_to_cpu(x)	(x)
#define be32_to_cpu(x)	(x)
#define be64_to_cpu(x)	(x)

#endif /* __BYTE_ORDER == __LITTLE_ENDIAN */

#define ntoh16(x)	(be16_to_cpu(x))
#define ntoh32(x)	(be32_to_cpu(x))
#define ntoh64(x)	(be64_to_cpu(x))

#define hton16(x)	(cpu_to_be16(x))
#define hton32(x)	(cpu_to_be32(x))
#define hton64(x)	(cpu_to_be64(x))

