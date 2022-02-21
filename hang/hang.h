/*

*/
#pragma once
#ifndef __HANG__
#define __HANG__

#define HANG_MEM_STD

#define char_t char


#ifdef  __cplusplus
extern "C" {
#endif //  __cplusplus
	struct hang_Type_t;
	struct hang_Obj_t;
	struct hang_Str_t;
	typedef void (*hang_fn_t)();

	typedef struct hang_TObj {
		hang_fn_t* __vptr;
	}hang_Obj;
	typedef struct hang_TGcObj {
		unsigned int __gcflags;
	} hang_GcObj;
	typedef struct hang_TType {
		size_t size;
		hang_Str* name;
	} hang_Type;
	typedef struct hang_TStr {
		struct hang_TObj;
		size_t length;
		char_t buffer[];
	} hang_Str;

	inline hang_Type* hang_obj_type(const hang_Obj* p) {
		return (hang_Type*)(((p)->__vptr) - 1);
	}

	typedef struct hang_TMem {
		struct hang_TObj;
		void* vm;
		unsigned int threadid;
	} hang_Mem;

	hang_Mem* hang_Mem__new__(void* vm, unsigned int threadid);
	/// <summary>
	///  new a memory manager associate with a thread
	/// </summary>
	/// <param name="vm">instanceof the virtual machine</param>
	/// <param name="threadid">the threadid</param>
	/// <returns></returns>
	void hang_Mem__construct__(hang_Mem* self,void* vm,unsigned int threadid);
	/// <summary>
	///  allocate some memory from the global(when the mm==0) or the mem which associated with a thread
	/// </summary>
	/// <param name="mem">mem object</param>
	/// <param name="size">the bytes allocated</param>
	/// <returns>the address of the memory</returns>
	void* hang_Mem_alloc(hang_Mem*const self, size_t size);

	/// <summary>
	///  allocate memory for an object from the global(when the mm==0) or the mem which associated with a thread
	/// </summary>
	/// <param name="mem">mem object</param>
	/// <param name="size">the bytes allocated</param>
	/// <returns>the address of the memory</returns>
	hang_Obj* hang_Mem_new(hang_Mem*const self, hang_Type* type, size_t extraSize);

	void hang_Mem_delete(hang_Mem* const self, hang_Obj* obj);
	/// <summary>
	/// release the object to the memory-manager
	/// </summary>
	/// <param name="mem">memory</param>
	/// <param name="p">pointer</param>
	void hang_Mem_free(hang_Mem* mem, void* p);

	inline const size_t hang_Str_cstrlen(const char_t* buffer) {
		size_t length = 0;
		while (*buffer != 0) { length++; buffer++; }
		return length;
	}

	inline const hang_Str* hang_Str__new__(hang_Mem* mem, const size_t length) {
		hang_Str* str = (hang_Str*)hang_Mem_new(mem, 0, length + 1);
		str->length = length;
		
		return str;
	}

	inline const hang_Str* hang_Str__new1__(hang_Mem* mem, const char_t* buffer) {
		return hang_Str__new__(mem,hang_Str_cstrlen(buffer));
	}

	inline void hang_Str__construct__(hang_Str* self, const char_t* buffer) {
		char_t* buf = self->buffer;
		while (*buffer != 0) {
			*(buf++) = *(buffer++);
		}
	}
	inline const hang_Str* hang_Str_concat(hang_Mem* mem, const hang_Str* left, const hang_Str* right) {
		hang_Str* newStr = (hang_Str*)hang_Str__new__(mem, left->length + right->length + 1);
		char_t* dest = newStr->buffer;
		const char_t* src = left->buffer;
		while (*src != 0) *(dest++) = *(src++);
		src = right->buffer;
		while (*src != 0) *(dest++) = *(src++);
		*dest = 0;
		return newStr;
	}

	inline const int hang_Str__compare__(const hang_Str* left,const hang_Str* right) {
		const char* lb = left->buffer;
		const char* rb = right->buffer;
		while (*lb == *rb && *lb!=0) {
			lb++; rb++;
		}
		return *lb == *rb ? 0 : (*lb > *rb?1:-1);
	}
	
	inline const int hang_Str__equal__(const hang_Str*  left, const hang_Str* right) {
		return hang_Str__compare__(left,right)==0;
	}

	

#ifdef  __cplusplus
}
#endif //  __cplusplus


#if defined(HANG_MEM_STD)
#include "hang_mem_std.h"
#endif

#endif  //__HANG__
