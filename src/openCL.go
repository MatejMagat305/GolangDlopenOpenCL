package main
/*
#cgo LDFLAGS: -ldl
#include "./execute_functions.h"
*/
import "C"
import "fmt"

func main() {

	fmt.Println(C.open_libopencl_so_with_path(C.CString("/usr/lib/x86_64-linux-gnu/libOpenCL.so")))
}
