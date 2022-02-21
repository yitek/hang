/*

*/
#pragma once
#ifndef __HANG_MM_STD__
#define __HANG_MM_STD__
#include <stdlib.h>
#ifdef  __cplusplus
extern "C" {
#endif //  __cplusplus

	inline hang_Mem* hang_Mem__new__(void* vm, unsigned int threadid) {
		hang_GcObj* gcobj=(hang_GcObj*)malloc(sizeof(hang_Mem) + sizeof(hang_GcObj));
		gcobj->__gcflags = 1;
		return (hang_Mem*)(gcobj + 1);
	}
	
	inline void hang_Mem__construct__(hang_Mem*const self,void* vm, unsigned int threadid) {
		
		self->threadid = threadid;
		self->vm = vm;
	}
	
	inline void* hang_Mem_alloc(hang_Mem* const self, size_t size) { return malloc(size); }


	inline void hang_Mem_free(hang_Mem* const self, void* p) { return free(p); }

	inline hang_Obj* hang_Mem_new(hang_Mem* const self, hang_Type* type,size_t extraSize) {
		hang_GcObj* gcobj = (hang_GcObj*) malloc(sizeof(hang_GcObj) + type->size + extraSize);
		gcobj->__gcflags = 1;
		return (hang_Obj*)(gcobj+1);
	}

	inline void hang_Mem_delete(hang_Mem* const self, hang_Obj* obj) {
		free(((hang_GcObj*)obj)-1);
	}
	


#ifdef  __cplusplus
}
#endif //  __cplusplus

#endif  //__HANG_MM_STD__
