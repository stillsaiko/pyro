# include "com.h"
# include <cassert>
# include <cstdio>
COM::~COM(void){
	if(operator bool( )){
		printf("warning: COM (destructor)\n");
		assert( TerminateProcess(PI.hProcess, 0u) );
		CloseHandle(PI.hProcess);
		CloseHandle(PI.hThread);
	}
}
COM::COM(void){ }
COM::COM(const char * cmdline){
	SI.cb = sizeof SI ;
	PI.hProcess = NULL ;
	PI.hThread = NULL ;
	assert( CreateProcessA(cmdline, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &SI, &PI) );
}
COM& COM::operator = (COM&& a)noexcept {
	PI = a.PI ; memset(&a.PI, 0, sizeof PI);
	SI = a.SI ; memset(&a.SI, 0, sizeof SI);
	return *this ;
}
# include <cstdio>
COM::operator bool(void){
	if( PI.hProcess == NULL )return false ;
	switch( WaitForSingleObject(PI.hProcess, 0) ){
		case WAIT_TIMEOUT:
			return true ;
		case WAIT_OBJECT_0:
			CloseHandle(PI.hProcess);
			CloseHandle(PI.hThread);
			memset(&PI, 0, sizeof PI);
			memset(&SI, 0, sizeof SI);
			return false ;
		case WAIT_ABANDONED:
			printf("WAIT_ABANDONED\n");
			return false ;
		case WAIT_FAILED:
			printf("WAIT_FAILED\n");
			return false ;
		default:
			return false ; // error
	}
}