
/* -*- mode: c; tab-width: 4; c-basic-offset: 4; -*- */ 

#ifndef __VECTOR_MACHINE_H__
#define __VECTOR_MACHINE_H__

#include <stdint.h> /* C99 types */
#include <stddef.h> /* size_t, ptrdiff_t and friends */
/*
 * The idea is making the execution engine to work on some kind of long-vector virtual machine.
 * Main point being that its "registers" will fit into the L1 cache and the operations are functions
 * that work on those "registers." The "registers" will be vectors long enough so that they can be
 * implemented efficiently using SIMD instructions with unrolling.
 */

#if defined (__cplusplus)
#   define VVM_API extern "C"
#else
#   define VVM_API
#endif

#define VVM_REGISTER_SIZE (1024) 
#define VVM_ALIGNMENT       (64)
#define VVM_REGISTER_COUNT  (16)


#define VVM_REGISTER_ALIGN __attribute__((aligned (VVM_ALIGNMENT)))

typedef uint8_t vvm_register[VVM_REGISTER_SIZE] VVM_REGISTER_ALIGN;

/*
 * Functions that act as a "load". They return the updated source.
 */
VVM_API void vvm_prefetch_stream(const void* base, ptrdiff_t stride, size_t count);

VVM_API const void* vvm_load_stream (vvm_register* target, const void* base, size_t element_size, ptrdiff_t stride, size_t count);
VVM_API const void* vvm_load        (vvm_register* target, const void* base, size_t element_size, size_t count);

VVM_API const void* vvm_load_size4_stream_plain_c (vvm_register* target, const void* base, ptrdiff_t stride, size_t count);
VVM_API const void* vvm_load_size4_stream_unroll4_c (vvm_register* target, const void* base, ptrdiff_t stride, size_t count);
VVM_API const void* vvm_load_size4_stream_sse_v1 (vvm_register* target, const void* base, ptrdiff_t stride, size_t count);
VVM_API const void* vvm_load_size4_stream_sse_v2 (vvm_register* target, const void* base, ptrdiff_t stride, size_t count);
VVM_API const void* vvm_load_size4_stream_sse_v3 (vvm_register* target, const void* base, ptrdiff_t stride, size_t count);
VVM_API const void* vvm_load_size4_stream_sse_v4 (vvm_register* target, const void* base, ptrdiff_t stride, size_t count);
VVM_API const void* vvm_load_size4_stream_sse_v5 (vvm_register* target, const void* base, ptrdiff_t stride, size_t count);
VVM_API const void* vvm_load_size4_stream_sse_v6 (vvm_register* target, const void* base, ptrdiff_t stride, size_t count);


/*
 * Functions that act as a "store". They return the updated destination
 */
VVM_API void* vvm_store_stream      (const vvm_register* source, void* base, size_t element_size, ptrdiff_t stride, size_t count);
VVM_API void* vvm_store             (const vvm_register* source, void* base, size_t element_size, size_t count);
VVM_API void* vvm_store_size4_stream_plain_c(const vvm_register* source, void* base, ptrdiff_t stride, size_t count);
VVM_API void* vvm_store_size4_stream_unroll4_c(const vvm_register* source, void* base, ptrdiff_t stride, size_t count);
VVM_API void* vvm_store_size4_stream_unroll4_nt(const vvm_register* source, void* base, ptrdiff_t stride, size_t count);
VVM_API void* vvm_store_size4_stream_seq(const vvm_register* source, void* target, ptrdiff_t stride, size_t count);
VVM_API void* vvm_store_size4_stream_seq_nt(const vvm_register* source, void* target, ptrdiff_t stride, size_t count);

/*
 * A sample operation
 */
VVM_API void vvm_add_float_single   (const vvm_register* srcA, const vvm_register* srcB, vvm_register* target, size_t count);

/*
 * A sample transcendental
 */
VVM_API void vvm_sin_float_single (const vvm_register* src, vvm_register* target, size_t count);

#endif // __VECTOR_MACHINE_H__
