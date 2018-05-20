 /*******************************
 * Copyright (c) <2007>, <Bruce Campbell> All rights reserved. Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  *  
 * Bruce B Campbell 07 08 2014  *
 ********************************/
#ifndef __kl_memory__
#define __kl_memory__

#include "kl_exception.h"
#define ANSI_INFO std::stringstream ANSI_INFO_ss (std::stringstream::in | std::stringstream::out );                            \
	ANSI_INFO_ss<<"ANSI COMPILE INFO: " <<__DATE__<<"     "<<__TIME__<<"   "<<__FILE__<<"   "<<__LINE__<<"       "<<std::endl; \
	std::string err = ANSI_INFO_ss.str();

#include <iostream>
#include <map>

using namespace std;

class klMemMgr{
public:
	virtual void* allocate(size_t size)=0;
	virtual bool free(void*)=0;
};


class klMKLMemMgr{
public:
	virtual void* allocate(size_t size)
	{
		//void* mkl_malloc (size_t alloc_size, int alignment);
		void* ptr=NULL;
		ptr = mkl_malloc(size,64);
		return ptr;
	};
	virtual bool free(void* ptr)
	{
		mkl_free(ptr);
		return true;
	};

	//Frees unused memory allocated by the Intel MKL Memory Allocator.
	void freeAllBuffers()
	{
			mkl_free_buffers();
	}

	 //Frees unused memory allocated by the Intel MKL Memory Allocator in the current thread.
	void freeCurrentThreadBuffers()
	{
		mkl_thread_free_buffers();
	}

	//mkl_disable_fast_mm //Turns off the Intel MKL Memory Allocator for Intel MKL functions to directly use the system malloc/free functions.
	
	 //Reports the status of the Intel MKL Memory Allocator.
	int64_t allocatorStatus()
	{
		int allocatedBytes=0;
		int64_t buffers =mkl_mem_stat(&allocatedBytes);
		return buffers;
	}

	//This may be new
	//Reports the peak memory allocated by the Intel MKL Memory Allocator.
	//__int64 getPeakMemoryUse()
	//{
	//	//MKL_PEAK_MEM_ENABLE - start gathering the peak memory data
	//	//MKL_PEAK_MEM_DISABLE - stop gathering the peak memory data
	//	//MKL_PEAK_MEM - return the peak memory
	//	//MKL_PEAK_MEM_RESET
	//	int mode =MKL_PEAK_MEM;
	//	__int64 peakMem=0;
	//	peakMem=mkl_peak_mem_usage(mode);
	//	return peakMem;
	//}
//mkl_calloc //Allocates and initializes an aligned memory buffer.
//mkl_realloc //Changes the size of memory buffer allocated by mkl_malloc/mkl_calloc.

};


#endif //__kl_memory__        
