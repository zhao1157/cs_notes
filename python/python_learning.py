#====== 220 ========
# This is to practice shared memory between processes to communicate
import multiprocessing

def f(num, arr):
    num.value = True
    for i in range(9, 9+10):
        arr[i-9] = i


if __name__ == "__main__":
    num = multiprocessing.Value('b', False)
    arr = multiprocessing.Array('i', 10)
    procs = multiprocessing.Process(target = f, args = (num, arr))
    procs.start()
    procs.join()
    print (num.value, arr[:])

"""
#========== 219 ==========
# set_aspect(): controls the ratio of y- and x-axes
#===== 218 ======
# matplotlib.pyplot: zorder controls the order of drawing, which is on top of which
#===== 217 =====
# This is to test list*2
a = [2, 3]
b = a * 2
print (b)
a[0] = 9
print (b)

a = [[1, 2], [3, 4]] # a[0] and a[1] refer to two lists
b = a * 2 # b[0], b[1], b[2] and b[3] refer to the same two objects twice
print (b)
print (id(a[0]) == id(b[0]), id(a[1]) == id(b[3]), id(b[0]) == id(b[2]), id(b[1]) == id(b[3]))
a[0][0] = 99 # the first object element is mutated, so the changes are reflected through all reference
print (b)

a = [2, 2]
print (id(a[0]) == id(a[1]))

a = [[], []]
b = a * 2
a[0].append(2)
print (a, b)

#========== 216 ==========
#This is to practice some python myth
a = [2, 3]
print (id(a))
a += [4] # it mutates the original object, not creat a new one. WEIRD!
print (id(a))
a = a+[5] # it creates a new object
print (id(a))

print (1000+1 is 1001, 1000+1 == 1001) # different object, but with the same value
print (1001 is 1001)
print (id(1000+1), id(1001))
print (2+2 is 4, 3+3 is 6, 3+4 is 7)

#========== 215 ==========
#This is to practice shalow and deep copy
# anything on the left side of = is a reference, so l[1] is a reference, d["xx"] is also a reference
# thus in a shallow copy [2, 3, [4, 5]], a[0], a[1] refer to the same immutable objects, mutations in a[2] are visible
# before after shallow copy
# both copy.copy() and copy.deepcopy() create distinct objects, so removing or appending new elements will not affect the other
# but for the mutables elements, the behavior for copy and deepcopy is distinctively different
# copy.copy(), i.e. shallow copy, does reflect the changes in both objects
# copy.deepcopy(), i.e. deepcopy, never reflect the chagnes in other another
# assignment = is a completely different story, refer to the same object, while copy module make two different objects
import copy

# immutables (share the same object)
a = 2
b = a
print (id(a) == id(b)) # id: returns the object's memory address
b = 2
print (id(a) == id(b))

a = [2]
b = a
print (id(a) == id(b))
# mutables (not share)
b = [2]
print (id(a) == id(b))

# a and b refer to the same object or memory address
# any change in a or b will be reflected in the other
a = [2, 3]
b = a
print (a == b, id(a) == id(b))
a[0] = 9
print (a, b)
a.append(23)
print (a, b)
b[0] = 99
print (a, b)
b.append(2323)
print (a, b)

# shallow copy
a = [2, 3, [4, 5]]
b = copy.copy(a) # shallow copy creates a different object, the memory address is different
                 # for the immutable elements, they do not reflect into the other copy
                 # for the mutable elements, they do reflect into the other copy
print (id(a[2]) == id(b[2]), id(a[0]) == id(b[0])) # mutable elelments always refer to the same object
print (a, b)
a[0] = 200
a[2][0] = 99
print (id(a[2]) == id(b[2]), id(a[0]) == id(b[0])) # mutable objects refer to the same object, changes are reflected into one another
print (a, b)
a[2] = [23] # now the element is changed to a different object
print (id(a[2]) == id(b[2]), id(a[0]) == id(b[0]))

# deep copy
a = [2, 3, [4, 5]]
b = copy.deepcopy(a) # also a different object

print (id(a) == id(b))
print (id(a[0]) == id(b[0]), id(a[2]) == id(b[2])) # immutable objects still refer to the same object
                                                   # mutable objects refer to a different copy
a[2][1] = 99
print (a, b)



#========== 214 ==========
# This is to practice customizing Thread class
import threading
import multiprocessing
import time

class MyThread(multiprocessing.Process): #(threading.Thread):

    def __init__(self, target=None, return_dict = False): #{"stop": False}, args=(), kwargs = {}):
        print ("init")
        self._fn = target
        self._return_dict = return_dict
        #threading.Thread.__init__(self) #, target = target, args=args, kwargs = kwargs)
        multiprocessing.Process.__init__(self)
        self._terminate = False
    def run(self):
        print ("executing", self._return_dict.value)
        while not self._return_dict.value: #["stop"]:
            print ("__", self._return_dict.value, end = " ")
            self._fn()
        print (self._return_dict.value)
    def stop(self): 
        self._return_dict=True #["stop"] = True

def f():
    time.sleep(1)
    print ("Done sleeping")

manager = multiprocessing.Manager()
return_dict = manager.Value(bool, False, lock = True) #.dict()
return_dict.value = False
#return_dict = False #["stop"] = False

t1 = MyThread(f, return_dict = return_dict)
#t2 = MyThread(f)
t1.start()
#t2.start()


time.sleep(6)
#t1.stop()
#t2.stop()
return_dict.value = True #["stop"] = True
print ("resetting")


t1.join()
#t2.join()



#======== 213 =======
# threading model is not parallel due to GIL restriction, i.e
# only one thread can execute python code, so I/O-bound tasks is 
# appropriate for threading model. To enalbe fully parallel execution
# use multiprocessing module instead
# This is to practice terminating a thread
import threading
import time

stop = False

def f():
    while True:
        if stop:
            print ("exit")
            break
        print ("sleep 1s")
        time.sleep(2)

t = threading.Thread(target = f)
t.start()
stop = True
print ("active? {}".format(t.is_alive()))
t.join(0.5)
print ("active? {}".format(t.is_alive()))
t.join()
print ("active? {}".format(t.is_alive()))


#======== 212 =======
#This is to practice multithreading
import threading
import time

def f(interval):
    time.sleep(interval)
    print ("collecting gpu metric data ...")
    print ("Done sleeping {}s {}".format(interval, threading.currentThread().getName())) #threading.current_thread().getName()))

all_threads = []
for i in range(3, 0, -1):
    t = threading.Thread(target = f, args = (2**i,)) #, name = "Thread_"+str(i))
    all_threads.append(t)
    t.setName("Thread_"+str(i))
    t.start()
    print ("**")
    #t.join() # wait for the the thread to terminate, so execute serially, not parallelly
    print ("***")

print ("active threads: {}".format(threading.activeCount()))
print ("??: {}".format(threading.currentThread()))
    time.sleep(1)
    print ([thread.isAlive() for thread in all_threads])
    



#======== 211 =======
# checkout the tensors saved in the checkpoint
from tensorflow.python.tools.inspect_checkpoint import print_tensors_in_checkpoint_file
latest_ckpt = tf.train.latest_checkpoint("./tmp_old/")
#print_tensors_in_checkpoint_file (latest_ckpt, all_tensors=False, tensor_name="v0/cg/affine0/biases")
print_tensors_in_checkpoint_file (latest_ckpt, all_tensors=True, tensor_name="")

#========= 210 =======
#pip install gin-config==0.1.1

#========= 209 =======
# find out the number of records in tfrecord file
c = 0
for record in tf.python_io.tf_record_iterator("wmt-val-00001-of-00001"):
    c+=1
#======  208 ====
# clear() to remove all elements
a = {2:3, 's': 3}
a.clear()

b = [2, 3, 4]
b.clear()

#======== 207 ======
raise NotImplementedError("this module is not implemented")

#======== 206 =========
a = {2:3, '3':2}
a.clear # remove all items in the dictionary

#======== 205 =====
# This is to practice str.isdigit()
"23".isdigit()
"2.3".isdigit()
"2.3x".isdigit()

#========== 204 ==========
# multi-threading in python
import threading
import time

def a():
    # take 1s
    for i in range(100):
        print ('xx')
        time.sleep(0.01)
def b():
    # take 1s
    for j in range(100):
        print ('  yy')
        time.sleep(0.01)

time_0 = time.time()

#multi-threading processing
t1=threading.Thread(target=a)
t2=threading.Thread(target=b)
# start the thread
t1.start()
t2.start()
# thread is stopped
t1.join()
t2.join()


a()
b()

# sequential execution takes 2s, while parallel processing only takes 1s
print (time.time()-time_0)

#========= 203 ==========
import time, sys
time.sleep(1)
print ("Done sleeping")
# quit() and exit() are not good to be used in production code
#print (quit)
#quit()
#print (exit)
#exit()

#sys.exit("This is the end of the execution")
def f():
    for i in range(4):
        print (i, 's')
        time.sleep(1)
    #sys.exit("end of function")

sys.exit([f(), "exit() can only take at most one argument and is considered to be good in production code."])

#========== 202 =======
#This is to pratice calling c++ modules in python using ctypes
from ctypes import cdll
import ctypes
#lib = cdll.LoadLibrary('./libfoo.so') # the original code
lib = ctypes.CDLL('./libfoo.so') # the one used in horovod basics.py

#lib.MakePersonPtr.argtypes = [ctypes.c_int, ctypes.c_float]
#lib.MakePersonPtr.restype = ctypes.c_int

#me = lib.MakePersonPtr(30, 178.9)
me = lib.MakePersonPtr()
#me = lib.MakePerson()
lib.ShowPerson(me)

#========== 201 ============
from decorator import decorator # it is not available in python 3.7, weird
def _cache(func):
    d = {} # d gets accumulated
    def inner(k):
        d.setdefault(k, func(k))
        print ('d:', d)
    return inner
'''
@decorator
def _cache(func, k):
    d = {} # d does NOT get accumulated
    d.setdefault(k, func(k))
    print ('d:', d)
'''

@_cache
def f1(k):
    return str(k)+'_1'
print ('=============')
f1(2)
f1(3) # d is accumulated

@_cache
def f2(k):
    return str(k)+'_2'
f2(4)

#===== 210 ====
# cache modification
from decorator import decorator

def cache(d):
    @decorator
    def mod_dict(func, k):
        '''
        result = d.get(k)
        if not result:
            d[k] = func(k)
        '''
        d.setdefault(k, func(k))
    return mod_dict

d = {2:'2', 3:'3'}

@cache(d)
def gen_val(k):
    return str(k)+'_zls'

gen_val(4)
print (d)

#======= 209 ======
# this is to practice class decorator
import time
from decorator import decorator
class time_it(object):
    '''
    # non-argument decorator, __init__ takes the function as its argument
    def __init__(self, func):
        self._func = func

    def __call__(self, *args, **kwargs):
        print ('timing it')
        t1 = time.time()
        result = self._func (*args, **kwargs)
        t2 = time.time()
        print ('done timing it {} s'.format(t2 - t1))
    '''
    # argument decorator
    def __init__(self, name):
        self._name = name
        print ('before calling __call__ {}'.format(self._name))
    def __call__(self, func):#, *args, **kwargs):
        def inner(*args, **kwargs):
            print ('{} timing it'.format(self._name))
            t1 = time.time()
            func(*args, **kwargs)
            t2 = time.time()
            print ('done timing it {} s'.format(t2 - t1))
        return inner

@time_it('zls')
def sl(t):
    time.sleep(t)

sl(2)

#====== 208 =====
# this is to practice class decorator
import time
class time_it(object):
    def __init__(self, func):
        self._func = func
    def __call__(self, *args, **kwargs):
        print ('timing it')
        t1 = time.time()
        result = self._func (*args, **kwargs)
        t2 = time.time()
        print ('done timing it {} s'.format(t2 - t1))

@time_it
def sl(t):
    time.sleep(t)

sl(2)

#========= 207 =======
class my_class(object):
    def __init__(self, n):
        self._n = n

    @staticmethod # ignore the instance object being passed to it
    def square(a):
        return a**2
    # staticmethod can be called by instance
    def get_square(self):
        print (self.square(self._n))
    # staticmethod can be called by a class method
    @classmethod
    def make_instance(cls, i):
        #cls.test() # now work: cls has to be an instance object
        return cls(cls.square(i))
    # only accessible by an instance, not class
    # even though test() only needs self, it has to be an instance ,no a class
    def test(self):
        print ('test')

me = my_class(2)
me.get_square()
me.test()

me = my_class.make_instance(1)
me.get_square()
me.test()

#========== 206 =======
class my_class(object):
    def __init__(self, n):
        self._n = n

    @staticmethod # ignore the instance object being passed to it
    def square(a):
        return a**2
    # staticmethod can be called by instance
    def get_square(self):
        print (self.square(self._n))
    # staticmethod can be called by a class method
    @classmethod
    def make_instance(cls, i):
        return cls(cls.square(i))

me = my_class(2)
me.get_square()

me = my_class.make_instance(1)
me.get_square()

#========== 205 =======
import time
from decorator import decorator

class my_class(object):
    def __init__(self, name):
        self._name = name

    # the decorator has to be defined before being used, otherwise error
    @decorator
    def time_it(func, *args, **kwargs):
        print ('\t1')
        t1 = time.time()
        func(*args, **kwargs)
        t2 = time.time()
        print ('\t2')
        print ('{} took {} s'.format(func.__name__, t2 - t1))

    @time_it
    def sl(self, t):
        print ('{} is sleeping'.format(self._name))
        time.sleep(t)
# it has to be defined before being applied, so time_it shoule be before the class definition
'''
@decorator
def time_it(func, *args, **kwargs):
    print ('\t1')
    t1 = time.time()
    func(*args, **kwargs)
    t2 = time.time()
    print ('\t2')
    print ('{} took {} s'.format(func.__name__, t2 - t1))
'''

me = my_class('zls')
me.sl(1)

#======== 204 =======
#more than one decorated applied and the order matters, i.e. the inner one applies first
from decorator import decorator
import inspect
import time

def time_it_arg(current_time):
    @decorator
    def time_it(func, *args, **kwargs):
        print ('{} start timing'.format(current_time))
        t1 = time.time()
        f = func(*args, **kwargs)
        t2 = time.time()
        print ('time spend {}'.format(t2-t1))
        return 2*f
    return time_it

def sl_arg(name):
    @decorator # the function is that we can directly take function and its arguments
    def sl(func, *args, **kwargs):
        print ('{} sleeping for 1 s'.format(name))
        time.sleep(1)
        f = func(*args, **kwargs)
        print ('done sleeping')
        return 100
    return sl

# the order of the decorator placed matters.
#@sl
@time_it_arg(20)
@sl_arg('zls')
def my_print (n):
    print ('\t*****')
    for i in range(n):
        n ** 3
    print('\t*****')
    return 2

v = my_print(10)
print(v, my_print.__name__)

print(inspect.getsource(my_print))

#========== 203 =======
#more than one decorated applied and the order matters, i.e. the inner one applies first
from decorator import decorator
import inspect
import time

@decorator
def time_it(func, *args, **kwargs):
    print ('start timing')
    t1 = time.time()
    f = func(*args, **kwargs)
    t2 = time.time()
    print ('time spend {}'.format(t2-t1))
    return 2*f

@decorator
def sl(func, *args, **kwargs):
    print ('sleeping for 1 s')
    time.sleep(1)
    f = func(*args, **kwargs)
    print ('done sleeping')
    return 100

# the order of the decorator placed matters.
#@sl
@time_it
@sl
def my_print (n):
    print ('\t*****')
    for i in range(n):
        n**3
    print ('\t*****')
    return 2

#========== 202 ========
from decorator import decorator

def outer_most(name):
    # alternatives after decorator argument is passed
    '''
    def outer(func):
        a = 2
        def inner(*args, **kwargs):
            print (a)
            func(*args, **kwargs)
            print ('end')
        return inner
    return outer
    '''
    @decorator
    def outer(func, *args, **kwargs):
        a = 2
        print (a)
        func(*args, **kwargs)
        print ('end')
    return outer

@outer_most('Z')
def f(b, c):
    print ('\t{} {}'.format(b, c))

f(3, 4)

#========= 201 ==========
from decorator import decorator
import datetime

# a decorator that returns another decorator
def close_it_arg(year):
    @decorator
    def close_it(func, *args, **kwargs):
        f = func(*args, **kwargs)
        f.close()
        print ("done closing file in year {}".format(year))
        return 'done' # this is returned to the final instance
    return close_it

#@close_it # function name and arguments are all passed to the decorator function
@close_it_arg(datetime.date.today().year)
def f_read(filename):
    f = open(filename)
    for line in f:
        print(line.strip())
    return f # this is returned to the decorator

a = f_read('love.txt')
print (a)

#============ 200 ==========
# using decorator to close a file
# the down side of this is that we can not freely manipulate the texts
# so use with context manager decorator and generator function
from decorator import decorator

@decorator
def close_it(func, *args, **kwargs):
    # so here we do not need to pass explicitly each argument, just use *args and **kwargs
    f = func(*args, **kwargs)
    print ('closing the file {}'.format(args[0]))
    print (args)
    print (kwargs)
    f.close()

@close_it
def f_write(filename, mode, text):
    assert mode == 'w'
    f = open(filename, mode)
    f.write(text)
    return f

f_write('love.txt', 'w', text)

@close_it
def f_read(filename, mode, *args, **kwargs):
    assert mode == '' or mode =='r'
    f = open(filename, mode)
    for line in f:
        print(line.strip())
    return f

    f_read('love.txt', 'r', 2, 3, a=4)

    # compare with generator function and context manager
    import contextlib

    @contextlib.contextmanager
    def f_read_write(filename, mode):
        f = open(filename, mode)
        yield f
        f.close()
        print('Done closing file {}'.format(filename))

    print('\n\n***********')
    with f_read_write('love.txt', 'w') as f:
        f.write(text)
    print('\n\n***********')
    with f_read_write('love.txt', 'r') as f:
        for line in f:
            print(line)


#====== 199 ======
from functools import wraps
  
def out(author):
    def wrap(func): #(func, a) error: it only takes one argument, i.e. the function to be decorated
        @wraps(func)
        def inside(au, title):
            print (author)
            print ('show you {}'.format(func.__name__))
            func(au+author, title)
            print ('end')
        return inside
    return wrap

@out('zls')
def author_title(author, title):
    print ('\t the author is {}, the title is {}'.format(author, title))

author_title('xx', 3)

# an althernative
from decorator import decorator

def out(author):
    @decorator
    def wrap(func, au, title):
        func(au+author, title)
    return wrap

@out('zls')
def author_title(author, title):
    print ('\t the author is {}, the title is {}'.format(author, title))

author_title('xx', 3)

#======= 198 =====
# using keyword decorator is much easier
import time
from decorator import decorator

@decorator
def time_it(func, *a): # in this case, it takes functions and its arguments
    print (a, type(a))
    print ('timing {}'.format(func.__name__))
    t1 = time.time()
    func(a[0])
    t2 = time.time()
    print ('timing {} is done'.format(func.__name__))
@time_it
def sl(a, *b):
    for i in range(a):
        print ('\t', i+1)
        time.sleep(1)
print ('***')
print (sl, sl.__name__)
print ('***')
sl(2, 3, 4)

#========= 197 ========
from functools import wraps
def dec(func):
    @wraps(func)
    def inside(a=2):
        print('before', func.__name__)
        func(a)
        print('after', func.__name__)
    return inside

@dec
def being_decorated(a):
    print(a)
print (being_decorated, being_decorated.__name__)
being_decorated(3)

from decorator import decorator
import time
@decorator # no need a closure
def dec(func, a):
    print ('{} is running'.format(func.__name__))
    func(a)
    print ('{} is done'.format(func.__name__))

@dec
def sl(t):
    time.sleep(t)

sl(1)

#=========== 196 =======
from functools import wraps
# this is to understand the functionality of @ in the case of decorator
import time
# not a closure
def time_it_1(func):
    print('time_it_1: start')
    func(3)
    print('time_it_1: end')
    # it returns nothing, the target function becomes None
# a closure
def time_it_2(func):
    @wraps(func) # retain  the name of the original function
    def inner(t):
        print ('time_it_2: start')
        func(t)
        print ('time_it_2: end')
    return inner

#@time_it_1 # it executes the decorator, so sl gets executed
@time_it_2 #sl becomes function inner, and is not being called
def sl(t):
    for i in range(t):
        time.sleep(1)
        print('\t{} s'.format(i+1))
print(sl)
sl(5) # call the decorated function

#========= 195 ========
#use contextmanager inside a class
from contextlib import contextmanager

class my_class(object):
    def __init__(self, name, age):
        self._name = name
        self._age = age
    @contextmanager
    def _reset_after(self, new_name, new_age):
        self._old_name = self._name
        self._old_age = self._age

        self._name = new_name
        self._age = new_age

        yield 'temporary'

        self._name = self._old_name
        self._age = self._old_age

    def temporary_instance(self, new_name, new_age):
        with self._reset_after(new_name, new_age) as status:
            print (status)
            print (self._name, self._age)
        print ('permanent')
        print (self._name, self._age)

me = my_class('zls', 30)
me.temporary_instance('xx', 40)

#========= 194=========
# two ways of mimicing the native with open() context manager
from contextlib import contextmanager

@contextmanager
def file_write(filename, mode):
    print ('opening {}'.format(filename))
    f = open(filename, mode)
    yield f
    f.close()
    print ('done closing {}'.format(filename))

with file_write('me.txt', 'w') as f:
    for i in range(3):
        f.write(str(i)+'\n')

class my_open(object):
    def __init__(self, filename, mode):
        self._mode = mode
        self._filename = filename
        print('opening {}'.format(self._filename))
        self._file = open(self._filename, self._mode)
    def __enter__(self):
        return self._file
    def __exit__(self, *a, **b):
        self._file.close()
        print ('done closing {}'.format(self._filename))

with my_open('notme.txt', 'w') as f:
    for i in range(3):
        f.write(str(i)+'\n')
#=========== 193 =========
class my_class(object):
    def __init__(self, name, age):
        self._name = name
        self._age = age
    def __call__(self, new_name, new_age):
        self._old_name = self._name
        self._old_age = self._age

        self._name = new_name
        self._age = new_age
        return self # have to return self, otherwise 'with' won't use the attribute of __enter__ and __exit__
    def __enter__(self):
        return self
    def __exit__(self, *a, **b):
        print ('done exiting')
    def get_attributes(self):
        return self._name, self._age
    def year(self):
        for i in range(self._age):
            yield i

me = my_class('zls', 30)

with me('xx', 40) as obj:
    print (obj.get_attributes())
    for i in obj.year():
        print (i)

#======== 192 ========
# use contextlib.contextmanager to do some pre- and post-processing
import contextlib

class my_class(object):
    def __init__(self, name, age):
        self._name = name
        self._age = age

    @contextlib.contextmanager
    def set_values(self, NAME, AGE):
        old_name = self._name
        old_age = self._age

        self._name = NAME
        self._age = AGE
        yield "Done preprocessing\n"
        print ('\npost-processing')
        self._name = old_name
        self._age = old_age

me = my_class('zls', 30)

with me.set_values('xx', 40) as x:
    print (x)
    print ('change attributes:', me._name, me._age)
print ('return to the original attributes:', me._name, me._age)

#=========== 191 =========
# decorator: add more functionality to a function without modifying it
import time

def time_sleep(func, a=2):
    def time_func(t=1):
        print ('Time it')
        start = time.time()
        print ('*'*10)
        func(t+a)
        print ('*'*10)
        end = time.time()
        print ('Slept for {} s'.format(end-start))
    return time_func

@time_sleep # time this function without modifying it
def awhile(t):
    print ('sleeping...')
    time.sleep(t)
    print('done sleeping for {} s'.format(t))

awhile()

#========== 190 ========
# make sure the previous process is finished before going to the next one
import subprocess

content = '''import argparse
import time
parser = argparse.ArgumentParser(description = "sleep in each subprocess")
parser.add_argument("duration", type = int)
args = parser.parse_args()
print ('sleep', args.duration, 's')
for i in range(args.duration):
        time.sleep(1)
        print ('\t', i+1, 's')
print ('done sleeping for', args.duration, 's')
'''
with open('sub.py', 'w') as f:
    f.write(content)

sub_cmd = "python sub.py "
for i in range(1, 10):
    cmd = sub_cmd + str(i) + ' 2>&1 | tee out_'+str(i)
    process = subprocess.Popen(cmd, shell=True) # stdin = subprocess.PIPE, stderr = subprocess.PIPE, shell=True)
    #process.wait(timeout=4.1)
    out, err = process.communicate()

#========== 189 ========
class my_class(object):
    _instances = []
    _limit = 3

    def __new__(cls, a):
        if len(cls._instances) == cls._limit:
            mesg = 'Could not create more than {0} instances'.format(cls._limit)
            raise ValueError(mesg)
        instance = super().__new__(cls)
        cls._instances.append(instance)

for i in range(3):
    my_class(2)

for i in my_class._instances:
    print(i)

my_class(3)

#========== 186 =======
class CustomizeInstance(object):
    def __new__(cls, a, b):
        #instance = super(CustomizeInstance, cls).__new__(cls)
        instance = super().__new__(cls)
        instance._a = a
        instance._b = b
        return instance, 3

    def add(self):
        return self._a + self._b

me, _ = CustomizeInstance(2, 3)
print (me.__dict__)
print (me.add())

#========= 185 ========
# practice __call__ which enables instance callable
class my_class(object):
    def __init__(self, a):
        self._a = a

    def __call__(self, a):
        self._a = a

    def square(self):
        return self._a ** 2

me = my_class(None)
for i in range(5):
    me(i)
    print(me.square())

#=========== 184 ==========
import datetime
class my_class(object):
        # class variable
        default_date = '04-02'
        def __init__(self, age):
                print (self, age)
                self._age = age
        @classmethod
        def create_instance(cls, birth_year):
                print ('Day of birth:', str(birth_year)+'-'+ cls.default_date)
                return cls(datetime.date.today().year - birth_year)

me = my_class.create_instance(1990)

print (me.__dict__) # class variable is not included here

#=========== 183 =======
import datetime
datetime.date.today().year
datetime.date.today().month
datetime.date.today().day

#========== 182 ===========
class my_class(object):
    def __init__(self, a):
        print(self)
        self._a = a

    @staticmethod  # without this decorator, it can not be called by instance
    def stat_func(b):
        return b ** 2

    def get_square(self):
        return self.stat_func(self._a)

print(my_class.stat_func(2))

me = my_class(3)
print(me.stat_func(4))  # instance.staticmethod

me.get_square()  # instance.staticmethod
#========= 181 =======
# practice __name__
class my_class(object):
    def __init__(self, a):
        self._a = a

# class object does not have __name__
print(my_class.__name__)

def f():
    pass

print(f.__name__)

def outside(x):
    def inside():
        return x
    return inside

print(outside.__name__)
print(outside(2).__name__)

#========= 180 =========
def get_closure_contents(clos):
    if not hasattr(clos, '__closure__'):
        print('not have __closure__ attribute')
        return
    elif clos.__closure__ is None:
        print('its __closure__ is None')
        return
    print("===========")
    for c in clos.__closure__:
        print(c.cell_contents)
    print('*' * 7)

a = [2, 3]
f = outside(1, a)
get_closure_contents(f)
f(3)
get_closure_contents(f)

a.pop()
f(3)

get_closure_contents(f)

# it seems every function has __closure__ attribute, but its value may be None
print(hasattr(f, '__closure__') and f.__closure__ is not None,
      hasattr(outside, '__closure__') and outside.__closure__ is not None)

def xx():
    pass

print(hasattr(xx, '__closure__') and xx.__closure__ is not None)

get_closure_contents(xx)
get_closure_contents(outside)

#========= 179 =========
# map(self_defined_function_class)
class my_class(object):
    def __init__(self, a):
        self._a = a

    def square(self):
        return self._a ** 2

for me in map(my_class, [2, 3, 4]):
    print(me.square())

#========= 178 =========
class my_class(object):
    def __init__(self, a):
        self._a = a

me = my_class(2)
me._b = 3
me.__dict__['_c'] = 4
print(me.__dict__)
print(me._c)

print(dir(my_class))

#============ 176 ==========
# practice classmethod
class my_class(object):
    def __init__(self, a, b):
        # self refers to a class instance
        self._a = a
        self._b = b

    @staticmethod
    def util_plus(a, b):
        return a + b

    @staticmethod
    def util_minus(a, b):
        return a - b

    @classmethod
    def create_class(this_class, a, b):
        # the first argument refers to the class itself
        return this_class(this_class.util_plus(a, b), this_class.util_minus(a, b))

    def get_val(self):
        return self._a, self._b

me = my_class.create_class(2, 3)
print(me.get_val())

#========== 175 =========
class my_class(object):
    def __init__(self, a):
        self._a = a

    def get_val(self):
        return self._a

print(hasattr(my_class, '__init__'))
print(hasattr(my_class, 'get_val'))

me = my_class(2)
print(hasattr(me, '__init__'))
print(hasattr(me, 'get_val'))

get_val = getattr(my_class, 'get_val')
print(get_val)
print(me.get_val())

#=========== 174 ========
# practice getattr and hasattr
sp = getattr(str, 'split')
print (sp('a b c', 'b'))

sp = getattr(str, 'xx', str.split)
print (sp('a b c', 'b'))

print (hasattr(str, 'split'), hasattr(str, 'xx'))

#=========== 173 =========
#practice closure
def outside(val):
        def inside():
                print(val)
        return inside

a = [2,3]
f = outside(a)
f()

a.append(4)
f()

del a
f()

b = {'a':2, 'c':4}
f = outside(b)
f()

del b['a']
f()

#========== 172 ===========
import subprocess
import time
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('sleep_time', nargs='?', type = int, default = 0)
args = parser.parse_args([])

code = '''import time
import argparse
parser = argparse.ArgumentParser()
parser.add_argument('sleep_time', type = int)
args = parser.parse_args()
print("sleeping for", args.sleep_time, 'seconds')
time.sleep(args.sleep_time)
print ('\tDone sleeping for', args.sleep_time, 'seconds')
'''

with open('code.py', 'w') as f:
        f.write(code)
# submit multiple processes
for i in range(10):
        cmd = 'python code.py ' + str(i)
        subprocess.Popen(cmd, shell = True)
time.sleep(args.sleep_time)

#========= 171 ==========
# contextmanager decorator makes __enter__ and __exit__ unnecessary
from contextlib import contextmanager

@contextmanager
def my_with(n):
        def f():
                for i, j in enumerate(range(2, n+2)):
                        print('>>', i)
                        yield(j**2)
        print ('beginning of with')
        yield f()
        print ('end of with')

with my_with(3) as me:
        print ('me')
        for i in me:
                print(i)
        print ('end of me')

#======== 170 ========
# practice generator function and with statement mechanism
class my_with(object):
    def __init__(self, iteration):
        self._iteration = iteration
        print("1. done init")
    def __enter__(self):
        def gen():
            for i in range(self._iteration):
                yield i ** 2
        print(type(gen()))
        print("2. done enter")
        return gen()
    def __exit__(self, *a, **b):
        print('3. done exiting')
with my_with(8) as me:
    for i in me:
        print(i)

#========== 169 ========
# practice how with statement works
class my_open(object):
    def __init__(self, file_name):
        self._file_name = file_name
        print('1. done calling __init__')
    def __enter__(self):
        self._f = open(self._file_name)
        print('2. done calling __enter__')
        return self._f
    def __exit__(self, *args, **keyargs):
        self._f.close()
        print("3. Done closing file")
with my_open('in.txt') as my_f:
    for line in my_f:
        print(line, end='')

#========== 168 =========
import argparse

parser = argparse.ArgumentParser(description = "practice store_const, which can not be followed by an argument.")

parser.add_argument('-x', '--xx', '---xxx', action = 'store_true', default = False) # no const =

args = parser.parse_args ('---xxx'.split())
print ('store_true:', args.xx) # can only use the name with --, not - nor ---

args = parser.parse_args (''.split())
print ('default:', args.xx)
# general case of setting up true/false
parser.add_argument('-y', '--yy', action = 'store_const', default = True, const = False)

args = parser.parse_args('-x --yy'.split())
print (args.xx, args.yy)

#========== 167 ========
import argparse

parser = argparse.ArgumentParser(description = "practice store_const, which can not be followed by an argument.")

# only two possible values, const or default
parser.add_argument('-x', '--xx', action = 'store_const', const = 43)
parser.add_argument('-y', '--yy', action = 'store_const', const = 44, default = -111)

args = parser.parse_args('-x --yy'.split())
print (args.xx, args.yy)

args = parser.parse_args (''.split())
print (args.xx, args.yy)

args = parser.parse_args ('--xx '.split())
print (args.xx, args.yy)

#======== 166 =======
import argparse

parser = argparse.ArgumentParser(description = "practice store_const")

parser.add_argument('x', nargs = '+', type = int)
#parser.add_argument('--sum', nargs = '?', dest = 'accumulate', default = max, const = sum)
parser.add_argument('-sum', action = 'store_const', dest = 'accumulate', default = max, const = sum)

args = parser.parse_args('2 3 4 '.split())
print ('max', args.accumulate(args.x))

args = parser.parse_args('2 3 4 -sum'.split())
print ('sum', args.accumulate(args.x))

#========= 165 ==========
import argparse

parser = argparse.ArgumentParser(description = "practice required")

# use required = True to enforce this optional argument be specified on the command line
parser.add_argument('-x', '--xx', type = int, action = 'append', required = True)
# if -y is present on the command without being followed by an argument, then 3
parser.add_argument('-y', '--yy', action = 'store_const', const = 3, default = 'unspecified')

args = parser.parse_args('-x 2 --xx 3 '.split())
print (args.xx, args.yy)

args = parser.parse_args('-x 2 -y'.split())
print (args.xx, args.yy)

#======== 164 =========
import argparse

parser = argparse.ArgumentParser(description = "practice dest")
#names will collect s1_name and s2_name arguments
parser.add_argument('--s1_name', dest = 'names', action = 'append', nargs = 1)
parser.add_argument('--s2_name', dest = 'names', action = 'append')

parser.add_argument('rest', nargs = argparse.REMAINDER)

# the rest argument must start with argument whose value does not start wit -
args = parser.parse_args('--s1_name zls --s2_name dsy sd --zz sdf'.split())

print (args.names)
print (args.rest)

#======== 163 =========
import argparse
import sys

parser = argparse.ArgumentParser(description = "practice argparse.REMAINDER")

#test with +/*/?
parser.add_argument('-x', nargs = '+', action = 'append')

args = parser.parse_args('-x 9 8 7 -x i love you'.split())

print (args.x)

#====== 162 ========
import argparse
import sys

parser = argparse.ArgumentParser(description = "practice argparse.REMAINDER")

parser.add_argument('-x', '--xx', nargs = 1)
parser.add_argument('yy', nargs = 2, type = int)
parser.add_argument('rest', nargs = argparse.REMAINDER)

args = parser.parse_args('-x 9 8 7 --zz i love you'.split())

print (args.xx, args.yy)
print (args.rest)

#========= 161 ==========
import argparse
import sys

parser = argparse.ArgumentParser(description = "practice */+ for positional and optioanl arguments")

parser.add_argument('pos', type = int, nargs = '*', help = "get all positional arguments")
# it does not make sense of using a second positional argument with arbitrary arguments
parser.add_argument('emp', type = float, nargs = '*', help = "won't get any arguemnts", default = [-11111111111.0, 0]) # change * to + to always get the last one arguemnt for this position

parser.add_argument('-x', '--xx', type = float, nargs = '*')
parser.add_argument('-y', '--yy', type = float, nargs = '*')


args = parser.parse_args('2 3 4 9 --xx 9 3 23 -y 10 0'.split())

print (args.pos, args.emp)
print (args.xx, args.yy)

#======== 160 ========
import argparse
import sys

parser = argparse.ArgumentParser()

parser.add_argument('infile', nargs = '?', type = argparse.FileType('r'), default=sys.stdin)
parser.add_argument('outfile', nargs = '?', type = argparse.FileType('w'),default=sys.stdout)

args = parser.parse_args()

print (args.infile)
# transcribe the content of infile to outfile
# for stdin/out, use ctl+d to signal the end of the input
for line in args.infile: # THE SAME AS open('infile_name', 'r')
        args.outfile.write(line) # THE SAME AS open('outfile_name', 'w')

#====== 159 ====
import argparse

parser = argparse.ArgumentParser()
#+ requires at least one argument
parser.add_argument('xx', nargs='+')
parser.add_argument('yy', nargs = '+')
parser.add_argument('zz', nargs = '?', default = 23)
parser.add_argument('mm', nargs = '+', default = 999)
args = parser.parse_args('0 0 2 3 4'.split())
print (args.xx, type(args.xx))
print (args.yy)
print (args.zz)
print (args.mm)

#====== 158 =====
import argparse

parser = argparse.ArgumentParser()

#parser.add_argument('xx', default = -1) # xx is required
parser.add_argument('xx', nargs = '?', default = -2) # xx is not required

args = parser.parse_args()
print (args.xx, type(args.xx))

#====== 157 ====
import argparse

parser = argparse.ArgumentParser()
# only take 3 arguments
parser.add_argument('-x', '--xx', type = int, nargs = 3)

args = parser.parse_args('-x 1 2 3'.split())
print (args.xx)

del args
args = parser.parse_args('--xx 4 5 6'.split())
for i in args.xx:
        print(i)

#====== 156 =====
import argparse

parser = argparse.ArgumentParser()
# nargs specifies the number of arguments and append creats a list of sets of
# arguments
parser.add_argument('-f', "--foo", action="append", nargs='+', type=str)
args = parser.parse_args(["--foo", "f1", '1', '2', "-f", "f2", '2'])

print (args.foo)

#====== 155 =======
import argparse

parser = argparse.ArgumentParser(description = "practice argparser")
parser.add_argument("-x", '--val', type=int, help = 'allow more than one instance of the same argument on the command line', action = 'append')
args = parser.parse_args('-x 2 --val 9'.split())

print (args.val) # when both -x and --val exist, use args.val, not args.x

#========== 154 ===========
# an argument, which can not be changed (const)
import argparse
parser = argparse.ArgumentParser(description = "The purpose of this script: practice argparser")
parser.add_argument('-x', action = "store_const", const = 3)
# if -x is present on the command line, then
args = parser.parse_args(['-x']) # if -x present then 3 else none
print (args.x)

# if -x is not present on the command line, then
del args
args = parser.parse_args()
print (args.x)

#========== 153 ========
# make sure only one of the arguments can be set
import argparse
parser = argparse.ArgumentParser(description = "The purpose of this script:\
        practice mutually exclusive arguments")
# we can not set -xy simultaneously in the command line
group = parser.add_mutually_exclusive_group()
group.add_argument ("-x", action = 'store_false') # if -x present then false else true
group.add_argument ("-y", action = "store_true") # if -y present then true else false

args = parser.parse_args()

if args.x:
        print('x')
elif args.y:
        print ('y')

print (args.x, args.y)

#========= 152 =======
# add some description to the file
import argparse
parser = argparse.ArgumentParser(description = "The purpose of this script: practice argparser")
args = parser.parse_args()
print (args.v, type(args.v))

#========= 151 =======
# usage of count
import argparse

parser = argparse.ArgumentParser()

parser.add_argument('-v', action = 'count', help = "value is equal to the number of occurrences of v")

#args = parser.parse_args(['-vv']) # overwrite the commandline input
args = parser.parse_args()

print (args.v)
#========== 150 =======
# values can only be from a set of values
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('class_', type = int, choices=[0, 1, 2], help = "the class number")
args = parser.parse_args()
if args.class_ == 0:
        print (0)
elif args.class_ == 1:
        print (1)
elif args.class_ == 2:
        print (2)
else:
        raise ValueError("should not be this value")

#========= 149 =========
# argparse usage dealing with positional and optional arguments
import argparse
parser = argparse.ArgumentParser()

# positional arguments and type enforces string being converted to a specific type
parser.add_argument('x', type = int, help = "int: first argument")

parser.add_argument('y', type = str, help = "string: second argument")

# optional arguments starting with -
parser.add_argument('-v', '--verbosity', help = "verbosity")
# not a correct way of setting bool
parser.add_argument('--f_type', type = bool, default = 20, help = 'f type')
# correct way of settting bool, if --f, then action value, otherwise the opposite
parser.add_argument('--f', action = 'store_false', help = 'true or false')

args = parser.parse_args()

print (args.x, args.y, args.verbosity, args.f_type, args.f)

#========== 148 =========
import glob
glob.glob('*/*/love.txt', recursive=True)
#========== 147 ========
#download
import urllib.request

url = 'https://docs.python.org/3/library/argparse.html'
response = urllib.request.urlopen(url)

with open('download', 'w') as f:
        f.write(response.read().decode('utf-8'))

#========= 146 =========
# pass arguments to generator function using args
def gen(stop, start):
    i = start
    while i < stop:
        yield i
        i += 1

dataset = tf.data.Dataset.from_generator(gen, tf.int32, args=(10,4))

print (list(dataset.as_numpy_iterator()))

for ele in dataset.repeat().batch(3).take(5):
    print (ele.numpy())

#========= 145 =========
#range type
dataset = tf.data.Dataset.range(5, output_type=tf.int32)
dataset.reduce(2, lambda x, y: x-y).numpy()

#======== 144 =======
# dataset zip: take the shortest length
a = tf.data.Dataset.range(2, 9)
b = tf.data.Dataset.range(5)
c = tf.data.Dataset.range(20).batch(5)

dataset = tf.data.Dataset.zip(a, b, c)
#========= 143 =======
# from_generator() function
def gen():
    for i in range(10):
        yield (i, [i]*i)
dataset = tf.data.Dataset.from_generator(gen, output_types=[tf.int32, tf.float32])

#=========== 142 ==========
dataset.take(-1) # take all datasets if empty or negative

#========= 141 =======
dataset = tf.data.Dataset.range(2, 9)
# the following two steps might be switchable
result = dataset.shuffle(7, seed = 3, reshuffle_each_iteration=True)
result.repeat(num_epochs)

#========= 140 =========
# distributed training so that different worker work o different portion of datasets
dataset = tf.data.Dataset.range(13)
a = dataset.shard(4, 0)
b = dataset.shard(4, 1)
#======= 130 =========
# repeat ()
dataset = tf.data.Dataset.from_tensors([2,3])
d1=dataset.repeat() # repeat indefinitely
d2=dataset.repeat(3) # repeat only two times

#========= 129 ========
# control the output dtype of range
dataset = tf.data.Dataset.range(1, -9, -2, output_type=tf.bfloat16)
#========= 128 =======
# convert byte into string
a = b'sdfs'
a.decode("utf-8")
#========= 127 ======
feature = [[2,3], [4,5], [7, 8]]
dataset = tf.data.Dataset.from_tensors(feature) #only one element
d = dataset.take(1).repeat(9)

dataset = tf.data.Dataset.from_tensor_slices(feature) # three ELEMENTS
d = dataset.take(2).repeat(3)

#========= 126 ======
# concatenate
features = [[1,2], [3,4], [5,6]]
lables = ['a', 'b', 'c']

dataset = tf.data.Dataset.from_tensor_slices((features, lables)) # 1-D tuple

features_data = tf.data.Dataset.from_tensor_slices(features)
lables_data = tf.data.Dataset.from_tensor_slices(labels)
dataset = tf.data.Dataset.zip((features_data, lables_data)) # zip

#=========== 125 =========
# these two datasets are complete different
dataset_1= tf.data.Dataset.from_tensor_slices(([1, 2], [3, 4], [5, 6]))
dataset_2 = tf.data.Dataset.from_tensor_slices([[1, 2], [3, 4], [5, 6]])
print (list(dataset_1.as_numpy_iterator()))
print (list(dataset_2.as_numpy_iterator()))

#========= 124 ==========
# tensorflow  2
import tensorflow as tf
d_1 = {'a':([1, 2], [3, 4]), 'b':[5, 6]}
d_2 = {'a':[[1, 2], [3, 4]], 'b':[5, 6]}
dataset = tf.data.Dataset.from_tensor_slices(d_1)
print (list(dataset.as_numpy_iterator()))

dataset = tf.data.Dataset.from_tensor_slices(d_2)
print (list(dataset.as_numpy_iterator()))

#======= 123 ========
#path
import os
path = os.getcwd()
parent = os.path.join(path, os.pardir)
os.path.abspath(parent) # absolute path
os.path.relpath(parent) # relative path

#========= 122 =========
# dict.get('me', 'if_not_exist')
# dict.setdefault('me', 'set_if_not_exit')
import os
os.environ.get('me', 'xx') # return 'xx' since 'me' is not in os.environ
os.environ.setdefault('me', 'xx') # return 'xx', and set os.environ['me'] = 'xx'

#========== 121 =======
import subprocess, os
import signal
# execute /bin/bash a.sh
exe = subprocess.Popen(["/bin/bash", "a.sh"]) # ERROR with " a.sh" # WEIRD
print (exe.pid)
try:
    exe.communicate()
except KeyboardInterrupt:
    # get group process id
    print (os.getpgid(exe.pid), os.getpgrp())
    #os.killpg(os.getpgrp(), signal.SIGKILL)
    os.killpg(os.getpgid(exe.pid), signal.SIGKILL)
#done with the previous process
exe = subprocess.Popen("bash a.sh", shell=True)
print (exe.pid)

#=========== 120 =========
import subprocess
# execute /bin/bash a.sh
exe = subprocess.Popen(["/bin/bash", "a.sh"]) # ERROR with " a.sh" # WEIRD
exe.communicate()
#in shell execute "echo ..."
exe = subprocess.Popen("echo using shell", shell=True)
#exe.communicate()

#=========== 119 ======
# practice yield function
import sys
# generator function is a function with yield in it
# when called, only returns a generator, not executing the code, only when next() is
# called will the code get executed.
def n_square(n):
    assert isinstance(n, int)
    for i in range(n):
        yield i**2

for s in n_square(3):
    print (s)

g = n_square(4)
try:
    while True:
        print (next(g))
except StopIteration: # StopIteration get caught
    print ('StopIteration')
except Exception as e:
    print ('error:', e)
    print ('end')
finally:
    print ('finally')

# =========== 118 ========
# for list, tuple, set, we need to iter() and then next()
a = (2,3,4)
b = iter(a)
next(b)
#========== 117 =========
# practice try...finally
try:
    print (2)
except:
    print ('exception')
finally:
    # this part is always executed no matter the prior was successful or not
    print ('finally')

#====== 116 ======
# practice class __dict__
class A(object):
  def __new__(cls, a, b):
    return super(A, cls).__new__(cls)

  def __init__(self, a, b):
    self._a = a
    self._b = b
  def set_values(self, c, d):
    self.__dict__['c'] = c
    self.__dict__['d'] = d

  def print_values(self):
    print (self.c, self.d)


a = A(2, 3)
print (a.__dict__) #attributes of the instance
a.set_values(4, 5)
print (a.__dict__)
a.print_values()

#======= 115 =======
# practice staticmethod
class A(object):
  def __new__(cls):
    print ('__new__')
    return super(A, cls).__new__(cls)

  @staticmethod
  def s_method():
    return 's_method'

  @staticmethod
  def s_2(cls): #since this method is not dependent on any instance, thus just use class name
    print('calling s_method')
    cls.s_method() # better use the second approach
    A.s_method() # use this approach

  @classmethod
  def call_staticmethod(cls):
    print ('calling s_method:', cls.s_method())
    cls()

A.s_method()
A().s_method()
A.s_2(A)
A.call_staticmethod()

#====== 114 =====
# practice classmethod
class A(object):
  # the initializing values are passed to __init__ from __new__
  def __new__(cls, name, age):
    print ('__new__')
    return super(A, cls).__new__(cls)

  def __init__(self, name, age):
    print ('got name and age from __new__')
    self._name = name
    self._age = age

  def get_name(self):
    return self._name
  def get_age(self):
    return self._age

  @classmethod
  def input_initial_values(cls):
    name = input("Please enter your name:")
    age = input("Please enter your age:")
    return (name, age)

  @classmethod
  def instantiate(cls):
    # call another classmethod
    name, age = cls.input_initial_values()
    a = A(name, age) #or cls(name,age)
    # call an instance method
    print ('calling an instance method:', cls.get_name(a))
    return a

a = A.instantiate()
print (a.get_name(), a.get_age())

# ======= 113 ========
# insert into list using assignment
a = list(range(3))
a[1:1] = [3,4]
a[1:2] = [23, 3, 9]
a[1:3] = [9, 8, 7]
a[1:3] = [10]

#=========== 112 ========
# __init__ can return more than None if and only if __new__ returns more than just one
#object
class A(object):
    def __new__(cla): # cla is just a random placeholder
        print ('1 new')
        # this is what the class object returns
        return super(A, cla).__new__(cla), 3 # a class object and an int object

    def __init__(self):
        print ('init')
        return 2 # so it can return more than None

a = A()
print (a)

#========== 111 ========
# this practice illustrates the differences between __new__ and __init__
class A(object):
    def __new__(cla): # cla is just a random placeholder
        print ('1 new')
        # this is what the class object returns
        return super(A, cla).__new__(cla), 2

    def __init__(self):
        print ('__init__ is called immediatedly after __new__')
# the object is returned by __new__()
a, b = A()
print (a)
print (b)

#========= 110 ========
# dict.items() is set-like
d_1 = {2:3, 4:6, 'a':3}
d_2 = {2:3, 4:7, 'a':3}
d_1.items() & d_2.items() # returns the element existing in both d_1 and d_2
d_1.items() | d_2.items()
d_1.items() - d_2.items()
# delete all elements in
d_1.clear()
d_2.clear()
#make a copy of a dictionary
d = d_1.copy() #d is not d_1, but d==d_1
#dict.pop, which is like list.pop(only_one_argument)
d.pop(2) # del(d[2]), and returns d[2]
d.pop(23, 'not exists') # 23 is not in the key, thus return the default value

#========== 109 =========
# practict dict.setdefault(key, set value if not exist)
d = {2:3, 'a':9}
d.setdefault(2)
d.setdefault(23, 'sdf') #create d[23]='sdf'
d.setdefault(9) # create d[9] = None

#======= 108 ========
# practice map function
a = map(lambda a: a[1], dict(zip(range(3), 'abc')).items())
next(a)
#======== 107 ========
# practice dict.fromkeys()
k = [1, 2, 2, 3, 3]
dict.fromkeys(k, 'value not set')

#====== 106 =====
# not sure !r or !s means
print ("{0!r:^20} {1!s}".format(2, 3))

#===== 105 =====
# list
l = [2,3,4,77]
print ("{0[1]} {0[3]}".format(l))
# tuple
t = (2, 3, 4, 77)
print ("{0[1]} {0[3]}".format(t))

#===== 104 ======
# attribute in format
import sys
print ("{0.platform}".format(sys))

#===== 103 ======
# practice dict in format
a = dict(a=2,b=3,c=4)
a.update({5:6, 7:8})
print (a)

for key, val in a.items():
  # output: {key=val} {{}} return {}
  output = "{{{}={}}}".format(key, val)
  print (output)

b = {10:11}
print ('{[a]} {[10]}'.format(a, b))

print ('{a} {b}'.format(a = "love", b = "you"))
print ('{0[a]} {0[b]}'.format(dict(a="love", b = "you")))

#===== 102 =====
#output {} in string.format()
"{}{{}}".format(2) # output "2{}", not work even with \{\}

#========= 101 ========
# nonlocal variables
def outer():
  a = 3
  b = 4
  global c # c is visible throughout the file
  c = 5
  print ("locals:", locals())
  print ("globals:", globals())
  def inner():
    nonlocal a
    a = 10 # change the value of a in the outer scope
    b = 20 # b is local to inner scope, so won't change the value of b in the outer scope
  inner()
  print (a, b, c)
  print ("locals:", locals())
  print ("globals:", globals())

outer()
print (c)
print ("locals:", locals())
print ("globals:", globals())

#======= 100 ========
# make local variables global
a = [2,3]
def f():
  globals()['b']=[4,5]
  add_to_globals = {'b':'new', 'c':23}
  globals().update(add_to_globals)
  print ('locals:', locals())
  print ("globals:", globals())
f()
print (b)
print (c)

#====== 99 =====
#To overcome the trap of mutables in a function accumulating the previous results
#use unmuatables
from collections.abc import Iterable
def f(element, to=None):
  if to is None:
    to = []
  #assert isinstance(to, Iterable)
  assert isinstance(to, (list, tuple))
  to=list(to)
  to.append(element)
  return to

a = f(2, (3,))
print (a)

#===== 98 ====
# determine if a variable is iterable
from collections.abc import Iterable
isinstance(2, Iterable)
isinstance((2), Iterable)
isinstance((2,), Iterable)
isinstance([2,3], Iterable)
isinstance({2,3}, Iterable)
isinstance({2:3}, Iterable)
a = {2:3, 4:5}
try:
    iter(a)
except Exception:
    print ("Not an iterable")
else:
    print ("Is an iterable")
#===== 97 =====
to = 2
to_2 = 3
def f(element, to=[]): # to is muatble, which can create some confusion
  # compare global and local variables of the same name
  print ('\nlocals:', locals()['to'], '\n') # global variables won't appear in locals
  print ('globals:', {key:val for key, val in globals().items() if not "__" in key}, '\n')
  to.append(element)
  print ('locals after appending:', locals(), '\n')
  return to
# to is a list, which is mutable and can keep the changes of the previous step
print (f(2), to)
print (f(3), to)
print (f(4), to)
print (f(5, [0]), to)

#In the global scope, globals() and locals() are the same
print ('locals outside:', locals())
print ()
print ('globals outside:', globals())
print (globals() == locals())

#======== 96 =========
# maybe get the user-defined global variables
[key for key in globasl().keys() if not key.startswith)("__")]

#======== 95 ============
b= 3
a='b'
globals()[a] # 3
#========== 94 =========
# create variables from some database using glboals
#NOTE: this can only be global variables, not executed inside a function
data_base = {'s':2, 't':'\"love you\"'}
#use exec to create new varaibles in data_base
for key, val in data_base.items():
  exec ("{}={}".format(key, val))

print ('last key:', key, 'last value:', val)
print (globals())

# remove some variables from the global scope
del(key, val, s, t)
print(globals())

# use globals() to add new variables
globals().update(data_base)
print (globals())
print ('s:', s, 't:', t)

#===== 93 =====
inpt ='''
def f():
  name = input("Please enter your name:")
  return name
name=f()
'''

code = compile(inpt, '', 'exec')
exec(code)
print ("name:", name)

#====== 92 ======
# not sure of the purpose of compile, why not just use exec or eval
a ='''

for i in range(3):
  print (i)
'''

# for filename, we can just leave it as '', not sure of its purpose
exec_code = compile(a, '<string>', 'exec')
exec_code_2 = compile(a, '', 'exec')
print (exec_code)
print ('\n', exec_code_2)

exec(exec_code)
#===== 91 =====
# clear the interactive python screen
ctrl+l
#===== 90 ======
#use '''to create a string without using \ to connect different parts
a = '''sdf
sdf 
print (a)
'''
#===== 89 =====
# get input from control, and it returns a string
a = input("Please input you age:")
print (a) # a is string

#===== 88 ====
# eval
dict_1 = {'x':2}
dict_2 = {'y':3, 'z':4}
y=10
dict_1.update(dict_2)
a = eval("x+y", dict_1, {'y': y}) # the second y overwrites the first one; returns x+y
print (a)

b = eval("print ('inside eval', 3)") #print returns none
print (b)

#======= 87 =====
# exec()
a = "print\
('I LOVE YOU')"
b = exec(a) # exec always return None, so b is None

# define variables through dictionary
bb = "\'xbb\'"
dic = {'a':2, 'b':3, 'bb': bb}
for key, val in dic.items():
    exec("{0} = {1}".format(key, val)
print (a, b, bb)

a = "\
for i in range(N):\
    print (i)\
"
exec(a, {'N':3})
         
b = {"x":3}
exec("a=x; print (a)", b, {"x":4}) # 4 overwrite 3
print (a) #a is not defined. maybe local
         
#====== 86 ========
import tensorflow as tf

dataset = tf.data.Dataset.range(1, 12, 2) #(start, end, increment)
dataset = dataset.shard(3, 2) #(NUM_OF_SPLITS, index) (3,0), (3,1), (3,2)

iterator = dataset.make_one_shot_iterator()
res = iterator.get_next()

# Suppose you have 3 workers in total
with tf.Session() as sess:
    for i in range(2):
        print(sess.run(res))

#=========== 85 =======
from tensorflow.python.platform import gfile
files_reg = os.path.join('/home/zhaolianshui/specml_data/tfrecord', "%s*"%'train')
files = gfile.Glob(files_reg) # return train* files

#======== 84 ========
# join paths to form a single path
import os
os.path.join('/home', 'zhaolianshui', 'source_code') # --> '/home/zhaolianshui/source_code'
os.path.join('/home', '/zhaolianshui', 'source_code') # --> /zhaolianshui/source_code
os.path.join('a', 'b', 'c') # --> a/b/c
os.path.join('a', 'b', 'c', '', '') # --> a/b/c/
#========= 83 ==========
# initialize the global step variable
# the following two lines can not be exchanged
a = tf.get_variable("global_step", trainable=False, initializer = 10)
tf.train.get_or_create_global_step() # it refers to the global_step defined before

#========= 82 ========
# test global_step
import tensorflow.compat.v1 as tf
tf.disable_v2_behavior()

global_step = tf.train.get_or_create_global_step()

a = global_step.assign_add(1)
b = global_step.assign_add(1) # it is meaningless unless it's executed

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    for i in range(10):
        print (sess.run([tf.train.get_global_step()]))#, a])) # construct the graph, then execute and finally output results
        print ("\t", sess.run([a]))

#========= 81 =======
# work in tf1, not in tf2?
tf.disable_v2_behavior()
#======== 80 =======
# __file__: the name of the current file
print (__file__)
print (os.path.)

# ===== 79 =======
# use tf.session in tf>=2.2, tensorboard profiling tool
tf.compat.v1.disable_eager_execution()
tf.profiler.experimental.start('logs')
sess.run(result_1)
tf.profiler.experimental.stop()

#======== 78 =======
# date time in python
import datetime
datetime.datetime.now().strftime('%Y/%m/%d-%H:%M:%S') #'2020/07/16-00:56:05'

# === 77 =======
# json file
import json
f = open('a.json')
data = json.load(f) # dict

# ===== 76 ===
# tf timeline
options = tf.RunOptions(trace_level=tf.RunOptions.FULL_TRACE)
run_metadata = tf.RunMetadata()
sess.run(result, options=options, run_metadata=run_metadata)
fetched_timeline = timeline.Timeline(run_metadata.step_stats)
chrome_trace = fetched_timeline.generate_chrome_trace_format(show_memory=True)
with open('timeline_' + str(i) + '.json', 'w') as f:
    f.write(chrome_trace)

# ======= 75 =======
# uniform random value
data["input"] = tf.random_uniform(shape=[input_batch, input_height, input_width, input_channels],
                                  minval = 0.0, maxval = 1.0, dtype = tf.float32)
#========= 74 =======
# nvprof only part of the code, in command line we need to use flag: --profile-from-start off
import ctypes
_cudart = ctypes.CDLL('libcudart.so') # create a connection between python and cuda library

ret = _cudart.cudaProfilerStart()
if ret != 0:
    raise Exception('cudaProfilerStart returned non-zero.')
sess.run(result)
ret = _cudart.cudaProfilerStop()
if ret != 0:
    raise Exception('cudaProfilerStop returned non-zero.')

#======= 73 ======
# round
round(2.2323, 2)
round(2.5) # int 2
round(2.501) # int 3
#======== 72 ==========
a = tf.get_variable('a', shape = ())
print (a.op._id) # return the index of the order in which the op is created

# ========= 71 ========
# frozenset() does not modify itself, I.E. IMMUTABLE
a = frozenset([2,3])
b = {a:'frozenset_key'} # set can not be a key, but frozenset can be

# ========= 70 ========
import tensorflow.contrib.graph_editor as ge
a = tf.get_variable('zls/a', shape = ())
b = tf.get_variable('b', shape = ())
a.op._set_device('/gpu:2')
b.op._set_device('/gpu:1')
for op in ge.filter_ops_from_regex(tf.get_default_graph().get_operations(), 'zls|b'):
    print (op.name, op.device)

#====== 69 =======
# set the device individually
a = tf.get_variable('a',shape=())
a.op._set_device('/device:GPU:2')

#====== 68 ======
# tf.gradients(ys, xs, grad_ys = [], stop_gradients = [])
a = tf.get_variable('a', shape=(2,))#tf.constant(0.)
b = 2*a
c = tf.stop_gradient(a + b) #i.e. c = a+b, and c is treated as a constant, so its derivative wrt other variables is 0, but dc/dc is 1

y2 = a + b
y1 = y2 + a + b
# grad_ys is the weight multiplied by the gradients
g1 = tf.gradients([y1], [a, b, y2], grad_ys=[[1.0, 1.0]], stop_gradients = [y2])
g2 = tf.gradients(c+a, [a], grad_ys = [[2.0, 3.0]], stop_gradients = [a]) #ys=c will throu an error

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    print (sess.run([g1, g2]))
    print (sess.run([a, c/3]))

#======== 67 ========
from tensorflow.python.framework import ops as tf_ops

isinstance(tf.get_default_graph(), tf_ops.Graph)
a = tf.get_variable('a', shape=())
isinstance(a.op, tf_ops.Operation)

#========== 66 ========
import re
pattern = re.compile('sd|xy')
pattern.search('sdfssfxysdf')

#========== 65 ========
from six import string_types
isinstance('sd|cd', string_types) # is equivalent to isinstance('sd|cd', (str, unicode))

#========= 64 =======
# tf.add_to_collection(name, value), tf.get_collection(name) OR tf.get_collection_ref(name)
tf.reset_default_graph()
a = tf.get_variable('a', shape=())
b = tf.get_variable('b', shape=())

tf.add_to_collection('my_treasure', a)
tf.add_to_collection('my_treasure', [a, b])
tf.add_to_collection('my_treasure', a)

print (tf.get_collection('my_treasure'))
print (tf.get_collection('non_existing_collection'))

#======== 63 ========
# count the time in s (in ns time.perf_counter_ns())
import time
t1 = time.perf_counter()
time.sleep(3)
t2 = time.perf_counter()
print ('time slept:', t2-t1, 's')

#========== 62 =======
# the maximum depth of python stacks
import sys
sys.setrecursionlimit(1000)
print (sys.getrecursionlimit())

#======= 61 ========
a = [2,3,4]
a.insert(1,[7, 8])
print (a)

#========= 60 =========
import os
print (os.path.abspath('./')) # the current directory
print (os.path.abspath('README.md')) #/X/X/X/README.md
print (os.path.dirname('sdf/sdf/f/d/a.txt'))
print (os.path.abspath(os.path.abspath(__file__)+'/../')) # the higher level directory
print ('dirname', os.path.dirname(__file__), 'abspath:', os.path.abspath(os.path.dirname(__file__)))
print (os.path.dirname('../README.md'), os.path.abspath(os.path.dirname('../README.md')))
os.path.append(os.path.abspath(os.path.dirname(__file__)))

#========= 59 =======
a = tf.get_variable('a', initializer=32.0)#, dtype = tf.int32)
b = a/2
#b = tf.multiply(1.0/2, tf.cast(a, tf.float32))

for op in tf.get_default_graph().get_operations():
    print (op.name)

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    print (sess.run([a, b]))

#====== 58 =========
# find the address of a variable
a=2
b=2
print (id(a), id(b))
print (hex(id(a)), hex(id(b)))
#======= 57 ========
# find the shape a list
a = [[2,3,4], [2,3,4]]
import numpy as np
np.shape(a)

#======= 56 ========
# starred expression in the function call
def f(a,b):
    print(a, b)
f(*[2,3]) # unpack the list

#======== 55 =======
# extend list
a = [2,3]
b = [4, 5]
c = []
c.extend(a) # add every element to c
c.extend([b]) # add list b as a whole to c, which is just one element in c

#======= 54 ========
# supervisor
import tensorflow as tf
import os, sys
import numpy as np

log_path = './checkpts/'
x_data = np.random.rand(100)#.astype(np.float32)
y_data = x_data * 0.1 + 0.3

gs = tf.get_variable('gs', initializer=0, trainable=False)
W = tf.Variable(tf.random_uniform([1], -1.0, 1.0))
b = tf.Variable(tf.zeros([1]))
y = W * x_data + b

loss = tf.reduce_mean(tf.square(y - y_data))
optimizer = tf.train.GradientDescentOptimizer(0.5)
#train = optimizer.minimize(loss, global_step = gs)
train = optimizer.minimize(loss, global_step=tf.train.create_global_step())

saver = tf.train.Saver(max_to_keep=30000) # default is 5 checkpts
init = tf.global_variables_initializer()

sv = tf.train.Supervisor(logdir=log_path, init_op=init, saver=saver)
with sv.managed_session() as sess:
    for i in range(201):
        sess.run(train)
        if i % 20 == 0:
            #print(sess.run(gs), sv.global_step, sess.run(W), sess.run(b))
            #sv.saver.save(sess, sv.save_path, sess.run(gs))
            print (sess.run(tf.train.get_global_step()), sess.run(sv.global_step), sess.run(W), sess.run(b))
            #sv.saver.save(sess, log_path+'new_model', sess.run(tf.train.get_global_step()))
            sv.saver.save(sess, sv.save_path, tf.train.get_global_step())

#========= 53 ====
# find out environment variables
import os
print (os.environ)

#=========== 52 ===========
a = list(range(20))
print (a[2:15:3]) # 2, 5, 8, 11, 14

#============= 51 ==========
# test the initial_value
a = tf.get_variable('zls/a', shape = [2,3])
print
with tf.variable_scope('zls', reuse = True):#tf.AUTO_REUSE):
    b = tf.get_variable('a')

for op in tf.get_default_graph().get_operations():
    print (op.name)
with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    print ('they are different due to different sess.run()')
    print (sess.run(a.initial_value))
    print (b.initial_value.eval())
    print ('they are the same due to the same sess.run()')
    print (sess.run([a.initial_value - b.initial_value]))

# =========== 50 ========
import os
os.makedirs('1/2/3')
os.removedirs('1/2/3')
#========= 49 ======
import tensorflow as tf

# all devices
physical_devices = tf.config.experimental.list_physical_devices()#('GPU')

all_types = set()
for dev in physical_devices:
    all_types.add(dev[1])
    print(dev)#dev[0], dev[1])
print (all_types)

type_devices = {ty:[] for ty in all_types}

for dev in physical_devices:
    type_devices[dev[1]].append(dev[0])

for key, value in type_devices.items():
    print (key, len(value), value,'\n')

# get only part of the devices
visible_devices = tf.config.experimental.list_physical_devices('GPU') # device_type must be exact,
                                                                          # among type_devices
print ('>>>')
for vis_dev in visible_devices:
    print (vis_dev)

# set part of the devices visible
tf.config.experimental.set_visible_devices(visible_devices[1:3] +
                                           visible_devices[9:13] +
                                           # CPU has to be there in a session
                                           tf.config.experimental.list_physical_devices('CPU'))
all_devices = tf.config.experimental.get_visible_devices()
print('>>>')
for dev in all_devices:
    print (dev)

with tf.Session() as sess:
    pass
# the gpu indices are reorder in the logical devices
logical_devices = tf.config.experimental.list_logical_devices()
for dev in logical_devices:
    print(dev)

#======= 48 ========
# in different graphs to find out the trainable variables
with def_g.as_default():
  print ('default graph:')
  for var in tf.trainable_variables():
    print ('\t', var.name, var.trainable)

with g1.as_default():
  print ('g1 graph:')
  for var in tf.trainable_variables():
    print ('\t', var.name, var.trainable)

print ('unknown graph (default graph):')
for var in tf.trainable_variables():
  for var in tf.trainable_variables():
    print ('\t', var.name, var.trainable)

#======== 47 ========
# create ops in different graphs. ops in a different graph can not be executed in another graph
g1 = tf.Graph()
def_g = tf.get_default_graph()

# by default, this is added to the default graph
with tf.variable_scope('zls'), tf.device('/gpu:1'):
  a = tf.get_variable('a', shape = [100000, 15000], dtype = tf.float32)
  a = 2*a # about 14GB

# add ops to a different graph
with g1.as_default():
  with tf.device('/gpu:0'):
    #b = tf.scalar_mul(2, a)
    #b = tf.identity(a)
    b = tf.get_variable('b', shape = [100000, 15000], dtype = tf.float32) # about 8 GB
    #b = 2*b
# get the operations in graph g1
for op in g1.get_operations():
    print (op.name)
for ind, g in enumerate([def_g, g1]):
  with tf.Session(graph = g, config = tf.ConfigProto(gpu_options = tf.GPUOptions(allow_growth=True))) as sess:
    sess.run(tf.global_variables_initializer())
    for i in range(30):
      print (i)
      if ind == 0:
        a.eval() #GPU:1
      else:
        b.eval() #GPU:0

#========== 46 =======
#if a string is passed to tf.device(), then op.device is in the form of '/device:GPU(CPU):#'; if a function is passed
#, op.device returns the exact value returned by the function
def set_dev(op):
  if op.type in {'Variable', 'VariableV2'}:
    return '/device:GPU:1'
  else:
    return '/gpu:0'

with tf.device(set_dev):
  a = tf.get_variable('a', shape = [2,3])
  b = tf.constant(2, name = 'b')

with tf.device('/cpu:0'):
  c = tf.get_variable('c', shape=())

print (a, a.device)
print (b, b.device)
print (c, c.device)

#======= 45 =======
#operator.itemgetter()
import operator
print(operator.itemgetter(1)([2,3]))
min([(2,3), (4,5), (0, 1)], key = operator.itemgetter(1))
key = operator.itemgetter(1)
sorted(enumerate([2,3,2,2,2,0]), key=key)

#===== 44 ======
# set the device for each op automatically
def set_dev(op):
  print ('in set_dev:', op.name)
  if op.type in {'VariableV2', 'Variable'}:
    return '/gpu:1'
  else:
    return '/gpu:0'

with tf.device(set_dev): # it seems set_dev is called whenever new actions are created
  a = tf.get_variable('a', shape = [2,3])
  b = tf.scalar_mul(2, a, name = 'b')

for op in tf.get_default_graph().get_operations():
  print (op.name, op.device)

#======= 43 ======
#zip
a = [2, 3, 4]
b = [5, 6, 7]
c = list(zip(a, b))
d = list(zip(*c)) # *c generates each element (2, 5), (3, 6) and (4, 7), and then zip(x, y, z)

#======== 42 ======
# tupe is not mutable, you have to create a new one
a = (2,3)
a += (2,)
#======== 41 =======
# get the soruce code
import inspect
src_code = inspect.getsource(gen_nccl_ops.nccl_all_reduce)
# get the location of a module
import tf.contrib.data.map_and_batch as map_and_batch
print (map_and_batch.__file__)

#======== 40 =======
#get the shape of a list
import numpy as np
np.shape([[2,3], [2,3], [3,2]])

#======= 39 ========
import numpy as np
np.array(range(10), dtype = np.float32).reshape([2,5])
np.formiter(range(10), dtype = np.float32).reshape([2,5])

#======== 38 =======
# or: as long as the first one is not 0, the result will be the first value, otherwise the second value
2 or 9
9 or 9
11 or 9
0 or 9
-1 or 9
#========== 37 =======
import collections
nt = collections.namedtuple('nt', 'name age gender')
p1 = nt(name = 'seth', age = 29, gender = 'male')
p2 = nt(name = 'zhao', age = 30, gender = 'female')
#=========== 36 =======
# shape.merge_with() and shape.is_fully_defined()
a = tf.get_variable('a', shape = [2,3])
b = tf.get_variable('b', shape = [2, 3])

shape_1 = a.shape
shape_2 = shape_1.merge_with(b.shape)
print (shape_1.is_fully_defined())
print (shape_1)
print (shape_2)

#========= 35 =========
# reshape() and concat()
a = tf.constant([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
b = 2*a

with tf.Session() as sess:
  print (a.eval())
  print (b.eval())
  print (tf.concat([a, b], 0).eval())
  print (tf.concat([tf.reshape(a, [-1]), tf.reshape(b, [-1])], 0).eval())

#========= 34 ========
# tf.add_n
sess = tf.Session()
sess.run(tf.global_variables_initializer())
print (sess.run(tf.add_n([[1,2,3], [4,5,6], [7,8,9]])))

#========= 33 ==========
# zip
a = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
for i in zip(*a):
    pritn (i)
#=========== 32 ========
# tf.split()
a = tf.get_variable('a', shape = [10])
b, c = tf.split(a, [4, 6]) # b, c refer to the corresponding memory of a
print (a)
print (b)
print (c)
sess = tf.Session()
sess.run(tf.global_variables_initializer())
print (sess.run([a, b, c]))
sess.run(tf.assign(a, [i for i in range(10)]))
print (sess.run([a, b, c]))

#========= 31 ==========
# get the number of elements of a tensor
a = tf.get_variable('a', shape = [2, 2, 3])
print (a.shape.num_elements())

#=========== 30 =========
#.shape: a tuple
#.shape.as_list(): a list
#.shape.dims: [Dimension(), Dimension()]
#.shape.ndims: rank (scalar is 0)
a = tf.get_variable('a', initializer = 2.0)
b = tf.get_variable('b', initializer = [2])
c = tf.get_variable('c', initializer = [2, 3])
d = tf.get_variable('d', initializer = [[2,3], [4,5]])

print (a, a.shape, a.shape.as_list(), a.shape.dims, a.shape.ndims)
print (b, b.shape, b.shape.as_list(), b.shape.dims, b.shape.ndims)
print (c, c.shape, c.shape.as_list(), c.shape.dims, c.shape.ndims)
print (d, d.shape, d.shape.as_list(), d.shape.dims, d.shape.ndims)

#========== 29 =========
import math
int(math.ceil(23*1.0/3))
int(math.floor(23*1.0/3))
#======== 28 =======
with open('c.py') as f:
    for line in f: #iterable over lines
        print (line, end ='')
with open('c.py') as f:
    sum([1 for _ in f]) # number of lines
#========== 27 ========
if not os.path.exists('test'):
    os.makedirs('test')
else:
    os.removedirs('test')
os.getcwd() # the current working directory
os.listdir(os.getcwd()) # list all stuff in cwd
os.path.isfile('test/a')

#========= 26 ======
# get_operation_by_name and get_tensor_by_name()
with tf.variable_scope('sco'):
  a = tf.get_variable('a', shape = [2])

print (tf.get_default_graph().get_operation_by_name('sco/a'))
print (tf.get_default_graph().get_tensor_by_name('sco/a:0'))

#======== 25 =======
# mimic sleep in linux
import time
time.sleep(3) # 3 seconds
#========== 24 =========
# colocate_with() to make ops on the same device. In optimizer.apply_gradients(), ops.apply_gradients() makes the updating
# of variables reside on the same device as variables
with tf.device('/gpu:2'):
  a = tf.get_variable(name = 'a', shape = [2,3])
with tf.colocate_with(a):
  b = tf.identity(a, name = 'a_copy')

for op in tf.get_default_graph().get_operations():
  print (op.name, op.device, op.type, op.outputs[0].shape.as_list())

with tf.Session(config=tf.ConfigProto(allow_soft_placement=True,
                                      #gpu_options=tf.GPUOptions(per_process_gpu_memory_fraction=0.4),
                                      gpu_options = tf.GPUOptions(allow_growth = True),
                                      log_device_placement=True)) as sess:
  sess.run(tf.global_variables_initializer())
  pass

#========= 23 =======
e = tf.add_n([2,3,4])
f = tf.scalar_mul(2,a)
with tf.Session() as sess:
  sess.run(tf.global_variables_initializer())
  print (e.eval())
  print (a.eval(), '\n', f.eval())

#======== 22 ========
# by testing, tf.identity() does a deep copy, i.e. create a cope in different memory space
tf.enable_eager_execution()

with tf.device('/gpu:0'), tf.variable_scope('sco'):
  a = tf.get_variable('a', initializer = 2.)
  aa = a
  a_cope = tf.identity(a)
  b = tf.get_variable('b', initializer = 2.)
print (id(a), id(a_cope), id(aa))
print (a.numpy(), aa.numpy(), a_cope.numpy())
tf.assign_add(a, 2.)
print (id(a), id(a_cope), id(aa))
print (a.numpy(), aa.numpy(), a_cope.numpy())
print (a.name, aa.name)

#======== 20 =======
tf.enable_eager_execution()
tf.add(2,3)
tf.reduce_mean([2,3,4,9.3])
tf.reduce_sum([2,3, 9.3])

#========== 19 ======
# placeholder is not a variable, just a placeholder
# get_tensor_by_name()
with tf.devcie('/gpu:0'), tf.variable_scope('ph'):
  p1 = tf.placeholder(tf.float32, [2,3], name = 'p1') # dtype is positional argument, so required
  v1 = tf.get_variable('v', shape = [2,2])
print (p1, p1.dtype, p1.op.type)

ts_name = p1.name

print (tf.get_default_graph().get_tensor_by_name(ts_name))
print (tf.get_default_graph().get_tensor_by_name(v1.name))
assert p1.device.endswith('GPU:0')

#========= 18 ========
# in variable_scope(), you can change a reuse=False-variable-scope to a reuse=True-variable-scope, but
# can not the other way
with tf.variable_scope('sco', reuse = False) as var_scope:
  a = tf.get_variable(name = 'var_a', shape = [2,3])
  get_sco = tf.get_variable_scope()

print (var_scope.reuse, var_scope.use_resource)
print (var_scope.name, type(var_scope.name))
print (get_sco.name, get_sco.reuse)

with tf.variable_scope(var_scope, reuse = True) as var_scope_true:
  b = tf.get_variable(name = 'var_a')
assert a is b
print (b)
'''
# can not change reuse to False
with tf.variable_scope(var_scope_true, reuse = False):
  c = tf.get_variable(name = 'c', shape = [2])
'''
with tf.variable_scope('sco', reuse = tf.AUTO_REUSE) as var_scope_auto:
  c = tf.get_variable('var_c', [2,3])
  print (var_scope_auto.reuse)
  var_scope_auto.reuse_variables()
  print (var_scope_auto.reuse)
  '''
  # can not create new variables
  d = tf.get_variable('var_b')
  '''

#======== 17 =========
# assign and control_dependencies([])
import tensorflow as tf
import os

os.environ['CUDA_VISIBLE_DEVICES'] = '15'

a1 = tf.get_variable(name = 'a1', initializer = 2)
a2 = tf.get_variable(name = 'a2', initializer = 3)

assign = tf.assign(a2, 10)

with tf.control_dependencies([assign]):
  b = a2 - a1
for op in tf.get_default_graph().get_operations():
  print (op)

with tf.Session() as sess:
  sess.run(tf.global_variables_initializer())
  print (sess.run(a1+a2)) # does not involve assign
  print (sess.run(b))
  sess.run(assign) # manually run assign
  print (sess.run(a1+a2))

#============ 16 =======
# name_scope and variable_scope contribute to the formation of non-variables names, the order of them matters
with tf.variable_scope('var'), tf.name_scope('test'):#, tf.variable_scope('var'): # order matters for non-variables
  a = tf.get_variable(name = 'input', shape = [2,3], trainable=False, collections=[tf.GraphKeys.LOCAL_VARIABLES])
  b = a*2

print (a)
print (b)

#=========== 15 ==========
# shape of variables
a = tf.get_variable(name = 'aa', shape = (1,1,2,200))
for s in a.shape:
    s.value
#============ 14 =========
# variables created by tf.Variable() can not be shared, so in order to share variables, they must be created by tf.get_variable()
a = tf.Variable(2, name = 'te/a') # CAN NOT BE SHARED
#a = tf.get_variable(name = 'te/a', shape=(2,2)) # CAN BE SHARED
print (a.name)
with tf.variable_scope('te', reuse=True):
    b = tf.get_variable(name = 'a')
    print (b.name)
assert a is b

#============ 13 ===========
# name_scope does not affect the variables created by tf.get_variable(). tf.Variable() is affected by both tf.name_scope()
# and tf.variable_scope()
with tf.name_scope('ns'):
    a = tf.Variable(2, name='aa')
    b = tf.get_variable('bb', shape=(2,3), dtype = 'int32')
    with tf.variable_scope('vs'):
        c = tf.Variable(3, name = 'cc')
        d = tf.get_variable('dd', shape = (1,1), dtype = tf.int32)
    e = tf.Variable(4, name = 'ee')
    f = tf.get_variable('ff', shape = (2,2))
print (a)
print (b)
print (c)
print (d)
print (e)
print (f)
#=========== OUTPUT ===========
#   <tf.Variable 'ns/aa:0' shape=() dtype=int32_ref>
#   <tf.Variable 'bb:0' shape=(2, 3) dtype=int32_ref>
#   <tf.Variable 'ns/vs/cc:0' shape=() dtype=int32_ref>
#   <tf.Variable 'vs/dd:0' shape=(1, 1) dtype=int32_ref>
#   <tf.Variable 'ns/ee:0' shape=() dtype=int32_ref>
#   <tf.Variable 'ff:0' shape=(2, 2) dtype=float32_ref>

#========== 12 ========
# tf.Variable()
a_ref = tf.Variable(1)
print (a_ref, a_ref.name) # <tf.Variable 'Variable:0' shape=() dtype=int32_ref> Variable:0

a_ref = tf.Variable(1.0)
print (a_ref) # <tf.Variable 'Variable_1:0' shape=() dtype=float32_ref>

a_ref = tf.Variable(1, dtype='float32') # Even though the input is 1, its dtype can be float (not losing information)
print (a_ref)

b_ref = tf.Variable(1.0, dtype='float32') # as 1.0 is float, you can not define dtype to be int-- (lossing information)
print (b_ref)

c_ref = tf.Variable(2, name='c')
print (c_ref)

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    print (sess.run([a_ref+b_ref])) #float32 and float16 can not be mixed in an operation

#========== 11 ========
# assert
a = 1
b = 2
assert a == b, '(NotEqual>>) a should be equal to b'
#========== 10 =========
# name scope
import tensorflow as tf

#var1 = tf.Variable(3.,dtype=tf.float64, name="var1")
with tf.variable_scope('x'):
    var1 = tf.get_variable(initializer=tf.constant_initializer(3.), dtype=tf.float64, name="var1", shape=())
    current_scope = tf.contrib.framework.get_name_scope()
print(var1.name)
print ('*'*8, current_scope)
with tf.variable_scope('x/var1', reuse=tf.AUTO_REUSE):
    var2 = tf.get_variable("var2",[],dtype=tf.float64)
    print ('*'*8, tf.contrib.framework.get_name_scope())

with tf.variable_scope('x/var1/var2', reuse=tf.AUTO_REUSE):
    var2 = tf.get_variable("var3",[],dtype=tf.float64)
    print ('*'*8, tf.contrib.framework.get_name_scope())

with tf.variable_scope('x/var1/var2/var3', reuse=tf.AUTO_REUSE):
    var2 = tf.get_variable("var4",[],dtype=tf.float64)
    print ('*'*8, tf.contrib.framework.get_name_scope())

#========== 9 ==========
# name of variables: '/'.join([scope_name, local_name])
with tf.device('/gpu:0'), tf.variable_scope('extra/extra_x/', reuse = tf.AUTO_REUSE): # scope/name: forward slash is automatically added
                                                                                     # manually adding / after scope_name creates different
                                                                                     # variables!!!
    extra_7 = tf.get_variable('x/x', [2, size])   # name is 'extra/extra_x//x/x', not 'extra/extra_x/x/x'

#========== 8 ==========
# local variables, which from I found are inputs. In distributed system, each tower has one to feed inputs
tf.local_variables()
#========== 7 =========
# variable_scope controls the sharing of variables by reuse
with tf.device('/gpu:0'), tf.variable_scope('extra', reuse=False) as ext_reuse: # reuse = tf.AUTO_REUSE
    extra_1 = tf.get_variable('extra_1', [2, 1000000000])
    ext_reuse.reuse_variables() # set reuse to true, so that the same variable can be accessed through multiple names
    extra_2 = tf.get_variable('extra_1', [2, 1000000000])
    assert extra_1 is extra_2

with tf.device('/gpu:0'), tf.variable_scope(ext_reuse, reuse=False): # reuse is overridden by ext_reuse scope
    extra_3 = tf.get_variable('extra_1', [2, 1000000000])
    assert extra_2 is extra_3


with tf.device('/gpu:0'), tf.variable_scope('extra', default_name = 'extra_default', reuse = False) as ext_reuse:
    #extra_4 = tf.get_variable('extra_1', [2, 1000000000]) # variables are identified by their names, as extra/extra_1 already exists, we can not create another copy, but can reuse it.
    ext_reuse.reuse_variables()
    extra_4 = tf.get_variable('extra_1', [2, 1000000000])
    #once reuse_variables(), you can not create any other new variabels in this scope, but you can in different scope
with tf.device('/gpu:0'), tf.variable_scope('extra', reuse = tf.AUTO_REUSE):
    extra_5 = tf.get_variable('extra_5', [2, 1000000000])

#========== 6 =========
# find the operations in a graph
for op in tf.get_default_graph().get_operations():
    print (op)
#======== 5 ===========
import tensorflow as tf
import os

os.environ['CUDA_VISIBLE_DEVICES']='0,1,2,3'

with tf.device('/gpu:2'):
    a = tf.get_variable('a', [20240, 50240], dtype=tf.float32)

with tf.device('/gpu:2'):
    b = tf.get_variable('b', [20240, 50240], dtype=tf.float32)

with tf.device('/gpu:2'):
    c = tf.dtypes.cast(a*b, tf.float32)

config = tf.ConfigProto()
config.gpu_options.allow_growth = True
config.allow_soft_placement = True

with tf.Session(config=config) as sess:
    sess.run(tf.global_variables_initializer())
    for i in range(1000):
        print (i)
        sess.run(c)

# ============ 4 ==========
# __call__
class my_test():
    def __init__(self, a):
        self._aa = a
        print ('init:', self._aa)
    def __call__(self, b):
        self._bb = b
        print ('call:', self._bb)
my_t = my_test(1)
my_t(2) #this object calls __call__(2) as my_t.__call__(2)

#============ 3 ========
# output the shapes of tensors as lists
for ts in tf.trainable_variables():
    print (ts.shape.as_list())
#=========== 2 =========
# Find the gpu devices
from tensorflow.python.client import device_lib
local_gpu_devices = [(x.name, x.memory_limit) for x in device_lib.list_local_devices() if x.device_type == 'GPU']
#========== 1 ============
# Find the total number of trainable variables
num_params = sum([np.prod(v.shape) for v in tf.trainable_variables()])
# Find the total size of the trainable variabels
int(sum([np.prod(v.shape)*v.dtype.size for v in tf.trainable_variables()]))
# Find the total size of the trainable and untrainable (like optimizer states) variables
int(sum([np.prod(v.shape)*v.dtype.size for v in tf.global_variables()]))
#========== 215 ==========
#This is to practice shalow and deep copy
import copy

# immutables (share the same object)
a = 2
"""
