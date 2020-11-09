from ctypes import cdll
import ctypes
#lib = cdll.LoadLibrary('./libfoo.so') # the original code
lib = ctypes.CDLL('./libfoo.so') # the one used in horovod basics.py

#lib.add_int.argtypes = [ctypes.c_int, ctypes.c_int]
#lib.add_int.rettype = ctypes.c_int

#res_int = lib.add_int(2, 3)
#print (res_int)

lib.add_double.argtypes = [ctypes.c_float, ctypes.c_float]
lib.add_double.rettype = ctypes.c_float
res_double = lib.add_double(3, 3)
print (res_double)

#lib.MakePersonPtr.argtypes = [ctypes.c_int, ctypes.c_float]
#lib.MakePersonPtr.restype = ctypes.c_int
#lib.ret_str.restype = ctypes.c_char_p
#lib.accumulate.argtypes = [ctypes.c_char_p]
#lib.accumulate.restype = ctypes.c_char_p

#me = lib.MakePersonPtr(30, 178.9)
#me = lib.MakePersonPtr()
#me = lib.MakePerson()
#ret_str = lib.ret_str()
#ret_str = lib.accumulate(b"xx") # looks like we have to use byte type strings
#print (ret_str)
#ret_str = lib.accumulate(b"yy") # as expected in c++, it does accumulate the values added 
#lib.ShowPerson(me)

#print (ret_str, type(ret_str))
#ret_str = ret_str.decode("utf-8")
#print (ret_str, type(ret_str))
