#========= 334 =========
# test whether sorted data can boost performance in python, it turns out no.
import random
import time

data = []
size = 32768

for i in range(size):
    data.append(random.randint(0, 255))

#data = sorted(data)
print (data[:10])

t1 = time.perf_counter()
sub_sum = 0
for _ in range(1000):
    for i in range(size):
        if data[i] < 128:
            sub_sum += data[i]
t2 = time.perf_counter()
print(t2 - t1)

"""
#========== 333 ==========
# This is to practice action in argparse
import argparse

parser = argparse.ArgumentParser(description = "practice action")

parser.add_argument("--store_val", type = int, action = "store")
# default is the value gotten when the argument is missing, action is the action taken when the argument is present
parser.add_argument("--store_const", action = "store_const", const = 24, default = -1, help = "not sure the use cases of this feature")
parser.add_argument("--store_true", action = "store_false") #, default = True) # the default can be automatically set to the inverse of the action value.
parser.add_argument("--foo", action = "append")
# if append to some argument, don't set default in add_argument, use set_defaults()
parser.add_argument("--bar", action = "append_const", dest = "coll", const = "you", default = ["x"])
parser.add_argument("--zoo", action = "append_const", dest = "coll", const = "xx", default = ["y"])
parser.add_argument("--verbose", "-v", action = "count")

parser.set_defaults(coll = ["00"])

args = parser.parse_args("--store_val 23 --foo 2 --foo 5 --verbose --verbose -v --bar --zoo".split(" "))
#args.store_const = 3
#args.store_val = 9

print (args.store_const, args.store_true, args.foo, args.coll, args.verbose)


# ===== 332 =======
# This is to practice taking multiple arguments as one parameter
import argparse
parser = argparse.ArgumentParser(description="pratice nargs")
parser.add_argument("--padding", nargs=4, type=int)
parser.add_argument("--load_balance", action = "store_true", dest = "balance", default = "23")
parser.add_argument("--no-load_balance", action = "store_false", dest = "balance", default = "24")

parser.set_defaults(balance = None) # override the argument-level default

#args = parser.parse_args(["--padding", "2", "2", "3", "4", "--load_balance"])
#args = parser.parse_args("--padding 2 3 4 5 --no-load_balance".split(" "))
args = parser.parse_args("--padding 2 3 4 5".split(" "))


print(args.padding)
print (sum(args.padding))
print (args.balance)


#======= 331 ======
# This is to practice input() funciton
a = input("enter your name: ") # the return value is also a string in python3

#======== 330 ========
# make directories through a given file path
import os

file_name = "a/b/c/a"
os.makedirs(os.path.dirname(file_name), exist_ok = True)
with open(file_name, "w") as f:
    pass

# ========= 329 =========
# get the previous instructions executed
# or just check out ~/.python_history file
import readline

for i in range(25, readline.get_current_history_length()):
    readline.get_history_item(i)

#========== 328 ======
#This is to practice type hinting introduced in python-3.5
# it does not guarantee the type of the arguments or return type
def f(a: int, b: str = "zls") -> float:
    print (a, b)
    return 3.14

print (f("sd", 23))


#===== 327 ======
#This is to practice making a singlton using a classmethod
class Me:
    _singleton = None

    @classmethod
    def make_create_singleton(cls, *args, **kwargs):
        if cls._singleton is None:
            cls._singleton = cls(*args, **kwargs)
        return cls._singleton

print (Me._singleton)
me_1 = Me.make_create_singleton()
print (Me._singleton)
me_2 = Me.make_create_singleton()
print (Me._singleton)
print (me_1 is me_2)


#====== 326 ======
#This is to practice classmethod and staticmethod decorator
class Born(object):
    def __init__(self, year, month, day):
        print (f"Born init {self.is_valid(year, month, day)}")
        self._year, self._month, self._day = year, month, day

    @classmethod
    def from_string(cls, year_month_day):
        year, month, day = map(lambda x: int(x), year_month_day.split("/"))
        #print (cls.is_valid(year, month, day))
        return cls(year, month, day)
    
    @staticmethod
    def is_valid(year, month, day):
        return year <= 2021 and month <= 12 and day <= 31

born = Born.from_string("2021/04/02")
print (Born.__dict__)
print (Born.is_valid(202, 2, 4))


class Me(Born):
    def __init__(self, year, month, day):
        print ("Me init")
        super(Me, self).__init__(year, month, day)
print ("______")
Me.from_string("2021/04/02")


#===== 325 ======
# This is to practice function attribute using decorator
def addattr(run):
    def outer (func):
        if run:
            func.run = True
        else:
            func.run = False
        return func
    return outer

@addattr(True)
def f():
    if f.run:
        print("xx")
    else:
        print (None)

print (f)
f()

@addattr(False)
def g():
    if g.run:
        print ("yy")
    else:
        print (None)
print (g)
g()


#======= 324 ======
#This is to practice function attribute
import functools

class AddAttr(object):
    def __init__(self, run):
        self._run = run
    
    def __call__(self, func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            if self._run:
                func.run = True
            else:
                func.run = False
            print (f"here {func.run}")
            func(*args, **kwargs)
        return wrapper

    #def __call__(self, func):
    #    @functools.wraps(func)
    #    def wrapper(*args, **kwargs):
    #        if self._run:
    #            print ("has attribute")
    #            func(*args, **kwargs)
    #        else:
    #            print ("no attribute")
    #    return wrapper

@AddAttr(True)
def f():
    print (f.__dict__)
    if f.__wrapped__.run:
        print ("xx")
    else:
        print (None)

@AddAttr(False)
def g():
    if g.__wrapped__.run:
        print ("yy")
    else:
        print (None)
print (f)
f()
g()


#===== 323 =====
#Singleton using decorator
import functools

def singleton(cls):
    #instance = None
    @functools.wraps(cls)
    def wrapper(*args, **kwargs):
        #nonlocal instance
        if wrapper.instance is None:
            wrapper.instance = cls(*args, **kwargs)
        return wrapper.instance
    wrapper.instance = None
    return wrapper

@singleton
class Me:
    def __init__(self):
        pass
    
    def show(self):
        print (id(self))
    pass

print (Me) # is a function, not a class any more
me_1 = Me()
me_2 = Me()

print (me_1 is me_2)
print (Me.__dict__)
print (id(me_1))
me_1.show()
me_2.show()



#===== 322 =======
#This is to practice using decorator as a debugging tool
import functools 
import time

def debug(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        all_inputs = [repr(arg)  for arg in args]
        all_inputs += [f"{k}={repr(v)}" for k, v in kwargs.items()]
        all_inputs_repr = ", ".join(all_inputs)
        print (f"calling {func.__name__}({all_inputs_repr})")
        res = func(*args, **kwargs)
        print (f"{func.__name__} returns {res}")
        return res

    return wrapper

@debug
def f(a, b, c, d, e = 2, f = 'xx'):
    print (f"e={e}")
    print (f"f={f}")
    return 223

f(2, 3, 'x', 'sds', e = 2, f = 'xd')


#===== 321 =====
#This is to practice functools.update_wrapper(wrapper, wrapped)
import functools

def outer(func):
    def inner(*args, **kwargs):
        func(*args, **kwargs)
    #functools.update_wrapper(inner, func)
    return inner

@outer
def f():
    pass

print (f)

#======== 320 ======
#This is to practice class decorator
import functools
import time

class Delay(object):
    def __init__(self, intval = 0):
        self._intval = intval
    def __call__(self, func):
        #@functools.wraps(func)
        def wrapper(*args, **kwargs):
            print (f"delaying {self._intval}s")
            time.sleep(self._intval)
            print ("Done delaying")
            func(*args, **kwargs)
        functools.update_wrapper(wrapper, func)
        return wrapper

@Delay(2)
def f():
    print ("xxx")

f()
print (f)

@Delay()
def g():
    print ("yyy")

g()

print (g)


#====== 319 =======
#This is to practice getting decorated by multiple decorators
import functools 
import time

def timeit(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        t1 = time.perf_counter()
        func(*args, **kwargs)
        t2 = time.perf_counter()

        print (f"time taken {t2 - t1} s")
    return wrapper

def repeat_times(num_times):
    def repeat(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            for i in range(num_times):
                print (f"repeat {i+1} times")
                func(*args, **kwargs)
        return wrapper
    return repeat

@timeit
@repeat_times(2)
def f():
    time.sleep(1)

f()

@repeat_times(2)
@timeit
def g():
    time.sleep(1)

g()


#======= 318 =======
#This is to practice decorator on class method
import functools
import time

def repeat_times(func_ = None, num_times = 1):
    def repeat(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            for i in range(num_times):
                print (f"repeat {i+1} time")
                func(*args, **kwargs)
        return wrapper
    if func_ is None:
        return repeat
    else:
        return repeat(func_)

class Me(object):
    def __init__(self):
        self._a = 1

    @repeat_times
    def f1(self):
        time.sleep(self._a)

    @repeat_times(num_times = 2)
    def f2(self):
        time.sleep(self._a)

me = Me()
me.f1()
print ("____")
me.f2()

print (Me.f1)
print (Me.f2)


#====== 317 ======
# This is to practice registering using decorator
all_funcs = {}

def get_all_funcs(func):
    all_funcs[func.__name__] = func
    return func

@get_all_funcs
def f1():
    print ('xf1')

@get_all_funcs
def f2():
    pass

print (all_funcs)
f1()


#====== 316 ======
#This is to practice function decorator with arguments
import functools 
import time

def timeit(func = None, *, intval = 0): # here func and intval can not coexist in the decorator situation
    def outer(func_):
        @functools.wraps(func_)
        def inner(*args, **kwargs):
            t1 = time.perf_counter()
            time.sleep(intval)
            func_(*args, **kwargs)
            t2 = time.perf_counter()
            print (f"time taken {t2 - t1}s")
        return inner
    
    # without argument
    if func is not None:
        return outer(func)
    # with argument intval
    else:
        return outer

@timeit
def f1():
    time.sleep(2)

@timeit(intval = 1)
def f2():
    time.sleep(2)

f1()
print (f1)

f2()
print (f2)


#====== 315 ======
# This is to practice function decorator with arguments
import functools 
def repeat_times(num_times):
    def repeat(func):
        print (func)
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            for i in range(num_times):
                print (f"time {i}")
                func(*args, **kwargs)
        return wrapper
    return repeat

@repeat_times(3)
def f():
    print ("\txxx")

f()
print (f)

#===== 314 =======
#This is to practice nonlocal
def outer(): #(a = [2]):
    a = [2]
    print (id(a))
    def inner():
        nonlocal a
        print (id(a))
        if a[0] == 2:
            a[0] += 1
        else:
            a[0] += 1
        print (a)
    return inner

f = outer()
f()
f()
f()

f = outer()
f()

#====== 313 ======
# This is to practice function attribute
def outer():
    def inner():
        inner._a += 9
    inner._a = 0
    return inner

f = outer()
print (f._a)
print (f, f.__dict__)
f()
f()
print (f._a)

def f():
    f._b += 2
    print (f._b)

f._b = 9
f()
f()


#====== 312 ======
# This is to practice functools.wraps()
from datetime import datetime
import functools

def dt(func):
    print (f"before {func}") # at @ time
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        print (f"inside {func}")
        return func(*args, **kwargs)
    
    return wrapper

@dt
def f():
    return 2

f()
print(f)
print (f.__dict__)
print (f.__name__)
print (dt.__name__)


#===== 311 ======
#This is to practice datetime
from datetime import datetime 

def dt(func):
    def wrapper(*args, **kwargs):
        if 7 <= datetime.now().hour < 18:
            print ("day")
            func(*args, **kwargs)
            print ("Till 18 oclock")
        else:
            print ("night")
    return wrapper

@dt
def work():
    print ("I'm working")

work()



#===== 310 =======
#This is to practice inner function
def outer():
    a = None
    print (f"a: {a}")
    def inner(i):
        nonlocal a
        print (f"inner: {a}")
        a = i
    print (id(inner))
    return inner

inner = outer()
print (f"inner: {id(inner)}")

inner(2)
inner(3)
inner(4)
inner(5)


#==== 309 ======
#This is to practice setattr(obj, attr_name, attr_value)
class Me(object):
    pass

setattr(Me, 'name', 'zls')
print (Me.__dict__)

me = Me()

print (me.__dict__)
setattr(me, 'name', 'ZLS')
print (me.__dict__)
print (Me.__dict__)

delattr(me, 'name')
print (me.__dict__)



#=== 308 =====
#This is to practice use isinstance(obj, classes) in singleton
class Meta(type):
    instance =None
    class_ins = []

    def __call__(cls, *args, **kwargs):
        if not isinstance(cls.instance, cls):
            print (f"old {cls.instance}")
            cls.instance = super(Meta, cls).__call__(*args, **kwargs)
        return cls.instance

    def __new__(mcls, name, bases, attrs):
        cls = super(Meta, mcls).__new__(mcls, name, bases, attrs)
        if cls not in mcls.class_ins:
            mcls.class_ins.append(cls)
        return cls

class Me(metaclass = Meta):
    pass

class You(metaclass =Meta):
    pass 

Me()
Me()
print ("_______")
You()
You()

print ("______")
print (Meta.class_ins)

print (type(Me), type(Meta))
print (type(int))


#===== 307 ======
# This is to practice singleton using a decorator
def singleton(class_):
    class_singleton = {}
    def singleton_inner(*args, **kwargs):
        if class_ not in class_singleton:
            print (class_)
            class_singleton[class_] = class_(*args, **kwargs)
        return class_singleton[class_]
    return singleton_inner

@singleton
class Me(object):
    def __init__(self):
        self._a = 9

@singleton
class You(object):
    def __init__(self, a, b):
        self._a = a
        self._b = b

print (Me)
me_1 = Me()
print (me_1._a)
me_2 = Me()
print (me_2._a)
print (me_1, me_2)

you_1 = You(2, 3)
you_2 = You(4, 5)
print (you_1 is you_2)

print (you_1._a, you_2._a)
print (You)


#==== 306 ======
# This is to practice dynamically add attributes to class and instance
def unique(self):
    self._a = 9
    print ("unique")

class Meta(type):
    def __new__(mcls, name, bases, attrs):
        attrs['__unique__'] = unique
        return super(Meta, mcls).__new__(mcls, name, bases, attrs)

class Me(metaclass = Meta):
    def show(self):
        self.__unique__()
print (Me.__dict__)
me = Me()
me.show()
print (me.__dict__)

Me._val = 99
print (me._val)
print (me.__dict__)

me._b = 999
def get_b(self):
    print (self._b)

Me.get = get_b

me.get()


#==== 305 ======
# This is to practice after modifying the attributes of a class is it affecting the call inside the class
class Meta(type):
    def __new__(mcls, name, bases, attrs):
        attrs_new = {}
        for k, v in attrs.items():
            if not k.startswith("__"):
                k = k.upper()
            attrs_new[k] = v
        return super(Meta, mcls).__new__(mcls, name, bases, attrs_new)

class Me(metaclass = Meta):
    def set(self): # should be called as SET()
        self._a = 9

    def show(self): # should be called as SHOW
        self.SET()
        print (self._a)
print (Me.__dict__)
me = Me()
me.SHOW()


#====== 304 =======
#This is to practice meta class __call__
class Meta(type):
    def __call__(cls, *args, **kwargs):
        print ("calling __new__")
        #ins = super(Meta, cls).__new__(cls, *args, **kwargs)
        ins = super(Meta, cls).__call__(*args, **kwargs)
        #print ("calling __init__")
        #ins.__init__(*args, **kwargs)

class Me(metaclass = Meta):
    def __new__(cls, *args, **kwargs):
        print ("\tMe.__new__")
        return super(Me, cls).__new__(cls) #, *args)
    
    def __init__(self, *args, **kwargs):
        print ("\tMe.__init__")


me = Me(3)


#====== 303 ====== 
#This is to practice meta class __new__
class Meta(type):
    def __new__(mcls, name, bases, attrs):
        print (f"\t{name}\n\t{bases}\n\t{attrs}")
        return super(Meta, mcls).__new__(mcls, name, bases, attrs)

class Me(object, metaclass = Meta):
    _x = None

    def show(self):
        pass
    def __new__(cls, *args, **kwargs):
        print ("Me.__new__")
        return super(Me, cls).__new__(cls) #, *args, **kwargs)

    def __init__(self, a=2):
        print ("Me.__init__")
        self._a = a

me = Me(2)
print (me._a)



#===== 302 =======
# This is to confirm that __init__() is always getting called if __new__() returns its instance
import random

class Meta(type):
    _singleton = None
    def __call__(cls, *args, **kwargs):
        print ("Meta.__call__")
        # we should control the instance creation in __call__, othrewise we can not control when to execute __init__ in the class, which in turn corrupts the instance's attributes
        if True:#Meta._singleton is None:
            Meta._singleton = super(Meta, cls).__call__(*args, **kwargs)
        print ("Done Meta.__call__")
        return Meta._singleton

class Me(metaclass = Meta):
    def __new__(cls, *args, **kwargs):
        print ("Me.__new__")
        if cls._singleton is None:
            print ("\t......")
            cls._singleton = super(Me, cls).__new__(cls, *args, **kwargs)
        return cls._singleton

    def __init__(self):
        # always execute as long as __new__ returns Me instance
        print ("Me.__init__")
        self._a = random.random()
        self._b = random.random()

a = Me()
print (a.__dict__)
b = Me()
print (b.__dict__)
print (id(a) == id(b))



#==== 301 =====
# This is to practice modifying the attributes of a group of classes
class Meta(type):
    def __new__(mcls, name, bases, attrs):
        attrs_new = {}
        for k, v in attrs.items():
            if not k.startswith("__"):
                print (f"{k}: {v}")
                k = k.upper()
            attrs_new[k] = v
            #attrs[k] = v

        return super(Meta, mcls).__new__(mcls, name, bases, attrs_new)

class Me(metaclass = Meta):
    _xy = None
    def show(self):
        print ("upper case")

    def __init__(self):
        pass

print (Me.__dict__)

me = Me()
me.SHOW()


#====== 300 =======
# This is to practice hasattr function
class Me(object):
    _name = "xx"

    def show(self):
        print  ("show")
    def __init__(self):
        self._a = 2
        self._x = 9

print (hasattr(Me, '_name'))
print (hasattr(Me, '_x'))
print (hasattr(Me, 'show'))
print (hasattr(Me, '__init__'))
print (hasattr(Me, '__new__'))
print (hasattr(Me, '__name__'))
print (hasattr(Me, '__dict__'))
print (hasattr(object, "__new__"))
print (hasattr(Me(), '_a'))
me = Me()
print (me.__dict__)
a = getattr(me, '_a')
b = getattr(me, '_x')
print (a, b)


#====== 299 =====
# This is to practice class attributes can not be modified in __call__
class Me(object):
    _val = None
    def __new__(cls, *args, **kwargs):
        print ("Me.__new__")
        cls._val = 99
        #ins = super(Me, cls).__new__(cls, *args, **kwargs)
        ins = object.__new__(cls, *args, **kwargs)
        return ins
    def __call__(self):
        self._val = 3

me = Me()
me()
print (me._val)
print (Me.__dict__)


#======= 298 ========
#This is to practice meta class attributes are not modified by the class created
class Meta(type):
    attrs_cls = []
    attrs_obj = []

    def __new__(mcls, name, bases, attrs):
        print ("meta_new")
        ins = super(Meta, mcls).__new__(mcls, name, bases, attrs)
        mcls.attrs_cls.append(name)
        return ins
    
    def __init__(cls, name, bases, attrs):
        print ("meta_init")

    def __call__(cls, *args, **kwargs):
        print ("\nclass_call")
        obj = super(Meta, cls).__call__(*args, **kwargs) # here it call __new__ and __init__ for object creation
        print (obj)
        # even though class object invokes this function, the class attributes are still modified
        cls.attrs_obj.append(obj)
        return obj

Meta("xx", (), {})

print ("before", Meta.__dict__)
class A(object, metaclass = Meta):
    def __new__(cls):
        print ("A__new__")
        #return 2
        return object.__new__(cls)
    def __init__(self):
        print ("A_init")
class B(object, metaclass = Meta):
    def __init__(self):
        print ("B_init")
        #self._attrs_obj.append(3)


print ("after", Meta.__dict__)
A()
A()
print ("******8")
B()
print (f"one object: {Meta.__dict__}")


#======= 297 ======
#This is to practice metaclass 
meta_classes = {}

class Meta(type):
    _meta_classes = {}
    # type(name, bases, attrs)
    def __new__(mcls, name, bases, attrs):
        print ("Meta.__new__")
        print (f"\t{name}, {bases}, {attrs}")
        #cls = super(Meta, mcls).__new__(mcls, name, bases, attrs)
        cls = type.__new__(mcls, name, bases, attrs)
        mcls._meta_classes[name] = cls
        return cls
    
    def __init__(self, name, bases, attrs):
        print (f"\t{self.__name__}")

class Me(object, metaclass = Meta):
    def show(self):
        pass

class You(object, metaclass = Meta):
    pass

class F(Me): 
    pass

print (meta_classes)
print (Meta._meta_classes)


# ========== 296 =============
# This is to practice rewriting type.__call__()
class Meta(type):
    _instance = None
    def __call__(cls, *args, **kwargs):
        # it's called whenever creating instance is invoked
        print ("Meta.__call__ for instance creation")
        if cls._instance is None:
            cls._instance = super(Meta, cls).__call__(*args, **kwargs)
        return cls._instance

    def __new__(cls, *args, **kwargs):
        print ("Meta.__new__ for class creation")
        return super(Meta, cls).__new__(cls, *args, **kwargs)

    def __init__(cls, *args, **kwargs):
        print ("Meta.__init__")

# class statement invokes Meta.__new__
class Me(object, metaclass = Meta):
    def __new__(cls, *args, **kwargs):
        print (f"Me.__new__ {cls}")
        # return super(Me, cls).__new__(cls)
        return object.__new__(cls)


print ("_______________")
a = Me()
b = Me(1)
print (id(a) == id(b))


#===== 295 =====
# This is to practice Singleton
class Me(object):
    # it's reflected if modified in __new__
    _singleton = None

    def __new__(cls, *args, **kwargs):
        if cls._singleton is None:
            cls._singleton = super(Me, cls).__new__(cls)
        return cls._singleton
    
    def __init__(self):
        print ("Me init")

print (Me.__dict__)

a = Me()
b = Me()

print (Me.__dict__)
print (id(a) == id(b), id(a) == id(Me._singleton), id(a) == id(a._singleton))


#======= 294 =======
# This is to practice class creation using type.__new__() and cl.__init__()
# when creating objects, i.e. class or class instance, __new__() is the underlying mechanism
# when creating class, __init__ attribute of class should not be called as it's for class instance creation
# when creating class instance, __init__ is just optional depending on the necessity of executing it
def init(self, a, b):
    print ("init")
    self._a = a
    self._b = b

def new(cls, *args, **kwargs):
    ins = cls.__new__(cls)
    print ("new")
    return ins

def show_a(self):
    print (self._a) 

def show_b(self):
    print (self._b)

# cl = type('Mex', (object,), {...}) # returns a class with name, base class and attributes
cl = type.__new__(type, "Mex", (object,), {'__nnew__': new, '__init__': init, 'show_a': show_a, 'SHOW_B': show_b})
# cl.__init__() # not right as __init__() is used for class instance initialization, not for class initialization

print(type(cl))
print (cl)
print (cl.__dict__)
print (cl.__name__, cl.__bases__)

#me = cl(2, 3)
me = cl.__new__(cl)
me.__init__(2, 3)
me.show_a()
me.SHOW_B()

me = cl.__new__(cl)
print ("_____")
me.__init__(2, 3)

#====== 293 ======
# This is to practice if add function as an object's attribute
class Me(object):
    def __init__(self):
        self._a = 3

me = Me()

me.show = print
print (me.__dict__)

me.show(f"xxx")

def f(self):
    print (self._a)

# to add a method attribute to the object, it's better do it in the class level, not the object level
#me.f = f
#me.f(me)
print (me.__dict__)

me.show(f"{me._a}")

# add f as an attribute of the class
Me.f = f
me.f()



#====== 292 ======
# This is to practice class creation
cl = type("Me_x", (object,), {})

print (type(cl))

me = cl()
print (type(me))
print (me)
print (cl.__dict__)
def f1(self):
    print ("f1")

cl.__init__ = f1
print (cl.__dict__)

me.__init__()

cl.show = f1
print (cl.__dict__)

me.show()
cl.show(me)

def new(cls, *args, **kwargs):
    ins = object.__new__(cls)
    print ("cl new")
    return ins

cl.__new__ = new

print (cl.__dict__)
print ("_____")
cl()

print (cl.__dict__)
print (dir(cl))
print (cl.__class__)
print (cl.__dir__)
print (cl.__doc__)
print (cl.__init__)
print (cl.__new__)
print (cl.__name__)

#====== 291 ======
# This is to practice class creation
class Me(object):
    _val = None
    def get(self):
        self._val = 9
        print (self._val)

#Me.get()
print (Me._val)

me = Me()
me.get() # . implicitly put the object as the first argument in the method
print (Me._val) # if an object attempts to modify a class attribute, it simply redefines its own copy, not the one in the class

#===== 290 ======
#This is to practice creating objects with argument
class Me(object):
    def __new__(cls, *args, **kwargs):
        print (f"Me new {args}")
        ins = super(Me, cls).__new__(cls) #, *args, **kwargs) # only one argument, i.e. the type to instantiate
        return ins
    
    def __init__(self, a):
        print ("Me init")
        self._a = a

me = Me(2)
print ()
me = Me.__new__(Me, 3)
me.__init__(3)

    
#====== 289 ======
# This is to practice executing methods as they are added
# attributes of a class are always bound to the class object, so as the attributes of the class are added, they are reflected
# on the object
class Me(object):
    pass

me = Me()

print (f"Me: {Me.__dict__}")
def f1(self):
    print ("f1")

Me.f1 = f1

me.f1()
print (me.__dict__)
print (f"Me: {Me.__dict__}")
def init(self):
    self._a = 2

Me.__init__ = init

me.__init__()
print (me.__dict__)
print (f"Me: {Me.__dict__}")

def f2(self):
    print (self._a)

Me._f2 = f2

me._f2()
print (me.__dict__)
print (f"Me: {Me.__dict__}")

print (super(Me, me))
print (me.__module__)


#====== 288 =====
#This is to practice creating attributes of a class and an object dynamically
class Me(object):
    def __new__(cls, *args, **kwargs):
        print ("new")
        ins = super(Me, cls).__new__(cls, *args, **kwargs)
        return ins


print (Me.__dict__)

def get_cl(self):
    print ("get_cl")

print()

Me.GET_CL = get_cl
print (Me.__dict__)
me = Me()
Me.GET_CL(me)
me.GET_CL()

def show(self, a):
    print (a)
# even though show() is added later as an attribute, the object created before can still call it
Me.show = show
Me.show(22, 233) # the first argument is just an object, its type is not defined, so we can just use an object
me.show(23)
me.__new__(Me) # can not be (me), as it requires a type object


#====== 287 ======
# This is to practice creating an object with the usual way and the underlying way
class Me(object):
    # instantiate an object
    def __new__(cls, *args, **kwargs):
        instance = super(Me, cls).__new__(cls)
        print ("Me __new__")
        return instance
    # initialize the object created by __new__ 
    def __init__(self):
        print ("Me __init__")

me = Me()
print (Me.__dict__)
# an equivalent way
me = Me.__new__(Me)
me.__init__()


#===== 286 ======
#This is to practice __dict__ for both class and its object
class Me(object):
    # an attribute of the class
    _val = -1111111111

    def __init__(self):
        # an attribute of the object if and only if __init__() is executed
        self._x = 0
        pass

    def get(self):
        # an attribute of the object if and only if get() is executed
        self.y = 0
        print (self._x)


if __name__ == "__main__":
    print (Me.__dict__)
    print ("\n\n")

    # the attributes of a class object are the ones defined inside the methods with self.
    # __init__() is called automatically after instantiation, so self._x=0 is executed
    me = Me()
    print (dir(me))
    print (f"before get: {me.__dict__}")
    # after executing self.get(), we have self.y attribute
    me.get()
    print (f"after get: {me.__dict__}")
    #me._val = 9
    # _val is not an attribute of me object, but it searches outside of its scope to the class level
    print (f"_val: {me._val}")
    # this does not modify _val in the class scope, as it only redefines _val in the object scope
    me._val = 9
    print (f"after _val: {me.__dict__}")
    me._x = 8
    print (f"after me._x: {me.__dict__}")
    me.get()
    print (Me.__dict__)


#===== 285 ======
class Me(object):
    val = None
    val_per = None

    def __new__(cls, *args, **kwargs):
        # ins is a new object, which should be different each time
        ins = super(Me, cls).__new__(cls)
        print (id(ins))
        # here val_per is incremented everytime Me() is called
        # while val is consistently None whenever Me() is called
        if cls.val_per is None:
            cls.val_per = 1
        else:
            cls.val_per += 1
        return ins
    
    def get(self):
        if self.val is None:
            self.val = 1
            self.val_per += 1
        else:
            self.val += 1
            self.val_per += 1
        return self.val

for __ in range(2):
    me = Me()
    print (id(me))
    print (f"\t{Me.val} {Me.val_per}")
    for _ in range(3):
        print (me.get(), me.val_per)


#====== 284 ======
# This is to practice metaclass 
def count(self):
    self._count += 1
def __init__(self):
    #self._count = 0
    pass
def get(self):
    self.ct()
    return self._count

# inside the class the visible names are the keys of __dict__, not the original function/object name
cl = type("cl_zls", (object,), {'ct': count, '__init__': __init__, "gt": get, "_count": 10}) # _count gets reassigned everytime a new object is created, so does not bind to the class itself

print (cl.__dict__)
obj = cl()
#obj.it()
for _ in range(3):
    #obj.ct()
    print (obj.gt())
print (cl.__dict__)
print (obj.__dict__)


#====== 283 =======
# This is to practice setting restrictions on the object creation
class Me(object):
    _singleton = None

    def __new__(cls, *args, **kwargs):
        if not cls._singleton:
            #print (cls._singleton)
            cls._singleton = super(Me, cls).__new__(cls)
        #cls._singleton.__init__(*args, **kwargs)
        return cls._singleton
    def __init__(self, a):
        self._a = a
        print ("Me init")
    def get(self):
        return self._a

# even it's a singleton, __init__ always gets called if __new__() returns a class object
print ("+++++")
print (f"{Me._singleton}")
me_1 = Me(2)
print (f"{Me._singleton}")
me_2 = Me(3)
print (f"{Me._singleton}")

print (id(me_1) == id(me_2))
print (me_1.get(), me_2.get())

print (dir(Me))
print (Me.__dict__)

#====== 282 =======
#This is to practice __new__ and __init__, the former creates an object and the latter instantiates the object
class T:
    def __init__(self):
        print ("T initializer")

class Me:
    # here cls can be any variable, e.g. self
    def __new__(cls, *args, **kwargs):
        #instance = super(Me, cls).__new__(cls) 
        instance = object.__new__(cls)
        return instance # the object is returned to the caller
        #return 2
        #return T() # returns a different class object

    # initialization is called if __new__ returns the class object
    def __init__(self, a):
        print (f"Me init {a}")

# when python interpreter encounters this line, it first calls __call__() of type class, which in turn calls
# __new__() and __init__ if __new__() returns the class object
print (Me(2))


#======= 281 ======
#This is to practice creating class through type(name, bases, attrs_dict)
# create a class through type()
def get(self):
    return self.val

cl = type("cl_name", (object,), {'val': 2, 'GET': get})
print (dir(cl))
print (cl.__name__)
print (f"dict: {cl.__dict__}")
obj = cl()
print (cl.val, cl.GET(obj), obj.GET())

class M(object):
    def __init__(self, a = 3):
        self._a = a
    def Get(self):
        return self._a

me = M()
print (me.Get(), M.Get(me))

cl = type("cl_me", (M,), {'_a': 8, '_aa': 9}) # here _a is overwritten by the object instantiation
print (f"{cl().Get()}")
o = cl()
print (o._aa, o._a, cl._a) # without object instantiation, _a retains its original value
print (dir(cl))



#====== 280 ======
#This is to practice metaclass, which is the class of a class, i.e. class factory whereas class is an object factory
a = 2
print (type(a), a.__class__, type(a) is a.__class__)

# all python built-in classes are objects of class type
for cs in int, float, list, dict, tuple:
    print (type(cs))

print (int(3.2))
print (float(2))

#====== 279 ======
#This is to practice multiprocessing.map, which keeps the order of the outputs as that of the inputs, but the execution can be arbitrary
import multiprocessing as mp
import time

def f(x):
    print (f"{mp.current_process().name}")
    time.sleep(3)
    print (f"{mp.current_process().name} done")
    return x**2

if __name__ == "__main__":
    with mp.Pool(processes = mp.cpu_count()) as pool:
        # just like apply_async(), it submits ${processes} tasks simultaneously
        res = pool.map(f, range(6))
        print (res)
        #[pool.apply(f, args=(x,)) for x in range(6)] # meaningless for multiprocessing as it does not support parallel execution 


#======= 278 =======
#This is to practice multiprocessing.Pool
import multiprocessing as mp
import time

def f(x):
    print (f"sleeping {x}")
    time.sleep(1)
    return x**2

if __name__ == "__main__":
    np = mp.cpu_count()
    with mp.Pool(processes = np) as pool:
        # apply_async() submits ${processes} processes at once
        res = [pool.apply_async(f, args = (i,)) for i in range(9)]
        print([r.get() for r in res])


#====== 277 =======
# This is to practice multiprocessing.Pool
import multiprocessing as mp
import time

def f(t):
    print ("\tx")
    time.sleep(t)

if __name__ == "__main__":
    with mp.Pool(processes = 3) as pool:
        print ("before")
        # the main process wait till the child process finishes
        #pool.apply(f, args = (2,)) # does not work for lambda function
        for i in range(3):
            print (f"{i} before")
            pool.apply(f, args = (1,))
            print (f"{i} after")
        print ("done")


#===== 276 =======
# This is to practice multiprocessing.Manager() supports "with" block
import multiprocessing as mp

def f(val):
    val.value += 1

with mp.Manager() as manager:
    val = manager.Value('i', 0)
    p = mp.Process(target = f, args = (val,))
    p.start()
    p.join()
    
    # can not be used outside of the block as manager will be terminated
    print (val.value)

#===== 275 =====
# This is to practice map which returns an iterator
f = map(lambda x: x**2, range(3))
for ele in f:
    print (ele)

def fun(a):
    print (a)
f = map(fun, range(3))
for _ in f:
    pass

def fun(a, b):
    return a*b

f = map(fun, range(5), range(8))
for ele in f:
    print (ele, end = " ")
print ()

#====== 274 ======
#This is to practice synchronizing APIs in multiprocessing.Manager()
import multiprocessing as mp
import time

def test():
    #barrier.wait()
    with lock:
    #with cv:
        print (f"{mp.current_process().name} got the lock at {time.ctime()}")
        time.sleep(1)


if __name__ == "__main__":
    #manager = mp.Manager()

    #barrier = manager.Barrier(3) # does not work well
    #lock = manager.Lock() # does not work well
    lock = mp.Lock()
    #cv = manager.Condition() # does not work well
    cv = mp.Condition()

    for i in range(3):
        mp.Process(target = test, name = f"p_{i}").start()



#===== 273 =====
# This is to practice multiprocessing.Manager().list()/dict()
import multiprocessing as mp
import time

def test():
    l.extend([2, 3, 4, 0])
    d.update({2:3, "4":"5"})
    print (f"{mp.current_process().name} ready")
    time.sleep(3)
    event.set()

if __name__ == "__main__":
    manager = mp.Manager()
    event = manager.Event()

    l = manager.list()
    d = manager.dict()

    mp.Process(target = test, name = "p").start()
    event.wait()
    print (l, d)


#====== 272 =======
#This is to practice multiprocessing.Manger()
import multiprocessing as mp
import time

def test():
    #global counter
    #global arr

    for i in range(len(arr)):
        counter.value += i
        arr[i] = counter.value

if __name__ == "__main__":
    manager = mp.Manager()
    counter = manager.Value('i', 2)
    arr = manager.Array('d', [0 for _ in range(5)])

    p = mp.Process(target = test)

    p.start()
    p.join()

    print (counter.value)
    print (arr[1], arr[4])


#===== 271 ======
#This is to practice multiprocessing.Array().get_lock()
import multiprocessing as mp
import time

def prod(mul, barrier):
    global num
    global arr
    while num.value <= 5:
        with num.get_lock():
            print (num.value)
            arr[num.value] *= mul
            num.value += 1
            # deal with the first and the last
            if num.value != 1 and num.value != 6:
                barrier_inner.wait()
        barrier_inner.wait()
    print ("exiting")
    barrier.wait()


if __name__ == "__main__":
    num = mp.Value('i', 0)
    arr = mp.Array("d", [1, 1, 1, 1, 1, 1])
    barrier = mp.Barrier(3)
    barrier_inner = mp.Barrier(2)

    for mul in range(2, 4):
        mp.Process(target = prod, args = (mul, barrier)).start()

    barrier.wait()
    print (arr[:])


#====== 270 ======
# This is to practice multiprocessing.Array
import multiprocessing as mp
import time


if __name__ == "__main__":
    arr = mp.Array("c", 5)
    arr[0] = b"x"
    arr[2] = b"y"
    arr[3] = 114 # ???
    print (arr[0], arr[2], arr[3])


#====== 269 ====
# This is to practice multiprocessing.Array()
import multiprocessing as mp
import time

def prod(array, event, barrier):
    for i in range(len(array)):
        print ("*****")
        array[i] += 1
        event.set()

        time.sleep(2)
    barrier.wait()

def cons(array, event, barrier):
    for i in range(len(array)):
        print ("waiting")
        event.wait()
        array[i] *= 2
        print ("done double")
        event.clear()
    barrier.wait()
    

if __name__ == "__main__":
    array = mp.Array('f', [2.3, 3.14, 2])
    
    event = mp.Event()
    barrier = mp.Barrier(3)

    mp.Process(target = prod, args = (array, event, barrier)).start()
    mp.Process(target = cons, args = (array, event, barrier)).start()

    barrier.wait()

    print (array[:])


#====== 268 =======
#This is to practice shared memory for a character
import multiprocessing as mp
import time

def master():
    barrier = mp.Barrier(2)
    c = mp.Value("c")
    n = 3
    mp.Process(target = slave, args = (barrier, c, n)).start()

    for i in range(n):
        c.value = f"{i}".encode("utf-8")
        barrier.wait()

def slave(barrier, c, n):

    for _ in range(n):
        barrier.wait()
        print (c.value.decode("utf-8"))


if __name__ == "__main__":
    p_master = mp.Process(target = master) 

    p_master.start()


#====== 267 =======
#This is to practice shared memory to share info among processes
import multiprocessing as mp
import time

def inc(counter, barrier):
    for _ in range(4):
        with counter.get_lock():
            print (f"{mp.current_process().name}")
            counter.value += 1
            time.sleep(1)
    barrier.wait()

if __name__ == "__main__":
    counter = mp.Value("i", 0) # by default its lock is created
    barrier = mp.Barrier(3)

    for i in range(2):
        mp.Process(target = inc, args = (counter, barrier), name = f"p_{i}").start()

    barrier.wait()
    print (f"the final counter {counter.value}")


#====== 266 =======
# This is to practice multiprocessing.RLock()
import multiprocessing as mp
import time

class ProcessLock(mp.Process):
    def __init__(self, name = None, lock = None):
        super(ProcessLock, self).__init__(name = name)
        self._lock = lock

    def _first_lock(self):
        with self._lock:
            print ("lock_1")

    def run(self):
        with self._lock:
            print ("lock_2")
            self._first_lock()
        print ("done lock")

if __name__ == "__main__":
    lock = mp.Lock()
    # rlock allows the same process re-acquires the lock again before releasing it
    rlock = mp.RLock()

    p = ProcessLock("p_1", rlock) #.start()
    p.start()

    p.join()
    
    print (">>>>")
    p._first_lock()


#====== 265 =======
# This is to practice multiprocessing.Lock()
import multiprocessing as mp
import time

def mp_lock(lock, lt, barrier):
    with lock:
        print (f"{mp.current_process().name} got the lock, before appending {lt}")
        lt.append(mp.current_process().pid)
        time.sleep(3)
        print (f"\t{mp.current_process().name} exiting")
    barrier.wait()

if __name__ == "__main__":
    lt = [2]
    barrier = mp.Barrier(4)
    lock = mp.Lock()

    for ind in range(3):
        mp.Process(target = mp_lock, name = f"p_{ind}", args = (lock, lt, barrier)).start()
    barrier.wait()
    # lt is not shared among processes, so changes made by each process is not reflected on the other copies of lt
    print (f"after processes are done {lt}")
    

#===== 264 =======
# This is to practice kill the processes after a few loops
import multiprocessing as mp
import time

class ProcessBarrier(mp.Process):
    def __init__(self, name, barrier_1, barrier_2):
        super(ProcessBarrier, self).__init__(name = name)
        self._barrier_1 = barrier_1
        self._barrier_2 = barrier_2

    def run(self):
        while True:
            print (f"{self._name} barrier_1")
            self._barrier_1.wait()
            print (f"{self._name} barrier_12")
            time.sleep(2)
            self._barrier_2.wait()
            print (f"{self._name} barrier_2")



if __name__ == "__main__":
    barrier_1 = mp.Barrier(3)
    barrier_2 = mp.Barrier(3)
    
    all_p = []
    for ind in range(2):
        all_p.append(ProcessBarrier(f"p_{ind}", barrier_1, barrier_2))

    for p in all_p:
        p.start()
    
    for ind in range(3):
        print (f"\n\n____________")
        barrier_1.wait()
        time.sleep(3)
        barrier_2.wait()

    print ("terminate all")
    for p in all_p:
        p.terminate()


#======= 263 =======
# This is to practice multiprocessing.Barrier()
import multiprocessing as mp
import time

class ProcessBarrier(mp.Process):
    def __init__(self, name, timeout, barrier):
        super(ProcessBarrier, self).__init__(name = name)
        self._timeout = timeout
        self._barrier = barrier

    def run(self):
        print (f"{self._name} started")
        time.sleep(self._timeout)
        print (f"\t{self._name} before wait")
        self._barrier.wait()
        time.sleep(self._timeout - 2)
        print (f"\t{self._name} after wait")


if __name__ == "__main__":
    barrier = mp.Barrier(4)

    for timeout in range(3):
        ProcessBarrier(f"p_{timeout}", 2+timeout, barrier).start()

    time.sleep(8)
    print ("ready go")
    barrier.wait()


#====== 262 =======
# This is to practice mltiprocessing.Event()
import threading
import multiprocessing as mp
import time

class ProcessEvent(mp.Process):
    def __init__(self, name, event = None):
        super(ProcessEvent, self).__init__(name = name)
        self._event = event
    def run(self):
        print ("process {} waiting".format(mp.current_process().pid))
        time.sleep(2)
        self._event.wait()
        print ("{} done waiting".format(self._name))

if __name__ == "__main__":
    #mp.set_start_method("fork") # for python3.8 on mac
    event = mp.Event()
    ProcessEvent("event", event).start()
    
    event.set()
    print (f"main process id {mp.current_process().pid} main thread {threading.current_thread().name} set")


#==== 261 ======
# This is to practice implementing a customized Process
import threading
import multiprocessing as mp
import time

class MyProcess(mp.Process):
    def __init__(self, name, timeout):
        super(MyProcess, self).__init__(name = name)
        self._timeout = timeout
    def run(self):
        time.sleep(self._timeout)
        print ("{} {} {}".format(self._name, time.ctime(), mp.current_process().pid))

if __name__ == "__main__":
    p1 = MyProcess("p1", 1)
    p2 = MyProcess("p2", 2)

    p1.start()
    p2.start()

    p1.join()
    p2.join()

    print (f"main process name {mp.current_process().name}")
    print (f"main thread name {threading.current_thread().name}") # getName()


# ======= 260 ======
# This is to practice multiprocessing.Process
import multiprocessing as mp
import time

def task(timeout):
    time.sleep(timeout)
    print (mp.current_process().name)

if __name__ == "__main__":
    p1 = mp.Process(target = task, args = (2,), name = "p1") #.start()
    p2 = mp.Process(target = task, args = (1,), name = "p2") #.start()

    p1.start()
    p2.start()

    time.sleep(1.2)
    p2.terminate()
    
    p1.join()
    p2.join()

    print ("main process name {}".format(mp.current_process().name))


#====== 259 ======
# This is to practice consuming elements from a list using multi-threading
import threading
import time
import random

def f(all_eles):
    barrier.wait()
    
    while len(all_eles):
        with cv:
            if len(all_eles):
                print ("{} got {}".format(threading.current_thread().getName(), all_eles.pop()))
            else:
                print ("{} empty".format(threading.current_thread().getName()))
                break
        time.sleep(random.random())

if __name__ == "__main__":
    all_eles = [2, 3, 4, 0, -2, -3]
    barrier = threading.Barrier(4)
    cv = threading.Condition()
    #cv = threading.Lock()

    for ind in range(3):
        threading.Thread(target = f, name = "td_" + str(ind), args = (all_eles,)).start()
    
    print ("ready, go ...")
    barrier.wait()

#===== 258 ======
# This is to practice threading.Condition().wait_for(predicate, timeout)
import threading
import time

def f():
    #global cv
    #global status

    def cond():
        print ("\t{} {}".format(status, time.ctime()))
        return status
    with cv:
        s = cv.wait_for(cond, 5) # the total time it can wait, not the time it waits every time
    print ("done {}".format(s))

if __name__ == "__main__":
    lock = threading.Lock()
    cv = threading.Condition(lock)
    status = False

    threading.Thread(target = f).start()

    for i in range(5):
        time.sleep(1)
        status = True if i == 3 else False
        with cv:
            cv.notify()
    print ("end")


#====== 257 =====
# This is to ensure Barrier can be reused
import threading
import time

def b(barrier, ind):
    while True:
        print ("before {}".format(ind))
        barrier.wait()
        print ("after {}".format(ind))

if __name__ == "__main__":
    barrier = threading.Barrier(3)

    threading.Thread(target = b, args = (barrier, 0), daemon = True).start()
    threading.Thread(target = b, args = (barrier, 1), daemon = True).start()

    for _ in range(3):
        barrier.wait()
        time.sleep(2)
        print ("*******\n")

#===== 256 ======
# This is to practice threading.Barrier().wait(timeout)
import threading
import time

def barrier_wait(barrier, timeout):
    barrier.wait(timeout)

if __name__ == "__main__":
    barrier = threading.Barrier(2)

    threading.Thread(target = barrier_wait, args = (barrier, 1), name = "td_1").start() # brokenbarriererror
    time.sleep(2)
    threading.Thread(target = barrier_wait, args = (barrier, 2), name = "td_2").start()


#====== 255 ======
# This is to practice threading.Event().wait(timeout)
import threading
import time

def event_wait(event, timeout = None):
    status = event.wait(timeout)
    print ("{}: {}".format(threading.current_thread().getName(), status))

if __name__ == "__main__":
    event = threading.Event()

    # wait times out before set(), thus status is False
    threading.Thread(target = event_wait, args = (event, 0), name = "to_0").start()
    threading.Thread(target = event_wait, args = (event, 2), name = "to_2").start()

    # wait is still in progress when set() is called, thus status is True
    threading.Thread(target = event_wait, args = (event, 4), name = "to_4").start()

    time.sleep(3)
    event.set()
    print ("done set")


#====== 254 =======
#This is to practice Lock and Condition
import threading
import time

def test_lock(lock):
    #global lock

    with lock:
        print ("raw lock acquired", lock.locked())
        time.sleep(3)
    print ("raw lock released")

def test_cv(lock, cv):
    #global cv
    #global lock
    
    time.sleep(1.5)
    print ("just before cv")
    with cv:
        print ("*** cv acquired lock", lock.locked())


if __name__ == "__main__":
    lock = threading.Lock()
    cv = threading.Condition(lock)

    threading.Thread(target = test_lock, args = (lock,)).start()
    threading.Thread(target = test_cv, args = (lock, cv)).start()

#====== 253 =======
# This is to practice threading.Condition().wait_for()
import threading
import time

def cond(lock):
    global val
    print ("\t", val, lock.locked())
    return val == 3

def f(cv, lock):
    print ("before wait_for (False) {}".format(lock.locked()))
    with cv:
        print ("acquired lock {}".format(lock.locked()))
        cv.wait_for(lambda : cond(lock))
    print ("after wait_for")

if __name__ == "__main__":
    lock = threading.Lock()
    cv = threading.Condition(lock)
    val = -1

    threading.Thread(target = f, args = (cv, lock)).start()
    
    time.sleep(1)
    for val in range(5):
        print (val)
        with cv:
            #print ("_____ {}".format(lock.locked()))
            print ("_____", lock.locked())
            cv.notify()
        time.sleep(1)

#====== 252 ======
#This is to practice threading.Condition
import threading
import time

class ThreadCondition(threading.Thread):
    def __init__(self, name, cv, intval):
        super(ThreadCondition, self).__init__(name = name)
        self._cv = cv
        self._intval = intval
        #self.start()

    def run(self):
        time.sleep(self._intval)
        with self._cv:
            print ("{} got the lock".format(self._name))
            print ("\t{} releasing the lock".format(self._name))
            self._cv.wait()
            print ("{} got the lock again".format(self._name))
            time.sleep(2)


if __name__ == "__main__":
    lock = threading.Lock()
    cv_1 = threading.Condition(lock)
    cv_2 = threading.Condition(lock)

    status = False

    th_1 = ThreadCondition("td_1", cv_1, 1)
    th_2 = ThreadCondition("td_2", cv_1, 2)

    th_1.start()
    th_2.start()
    
    time.sleep(3.5)

    with cv_1:
        print ("**** notify all ****")
        # make sure the lock is acquired when calling notify()
        #cv_1.notify(2)
        cv_1.notify_all() # only notify the threads that are already waiting, not notify the future ones
    #th_1.start()
    #th_2.start()


#======= 251 ========
#This is to practice context manager for threading.Lock
import threading
import time

def f(lock, barrier):
    # barrier ensures the threads are racing at the same starting line
    barrier.wait()
    with lock:
        print ("{}: {} {}".format(time.ctime(), threading.current_thread().getName(), lock.locked()))
        time.sleep(.5)

if __name__ == "__main__":
    lock = threading.Lock()
    barrier = threading.Barrier(4)

    for i in range(4):
        threading.Thread(target = f, args = (lock, barrier), name = "td_" + str(i)).start()


#======== 250 =======
#This is to practice threading.RLock, which can be reacquired multiple times 
#without releasing it before reacquirring it again
import threading
import time

class TestRlock(object):
    def __init__(self):
        self._rlock = threading.RLock()

    def A(self):
        i = self._rlock.acquire()
        print ("A", i)
        #self._rlock.release()
    
    def B(self):
        i = self._rlock.acquire()
        print ("B", i)
        #self._rlock.release()

    def AB(self):
        i = self._rlock.acquire()
        print ("{} acquired lock".format(threading.current_thread().getName()), i)
        self.A()
        self.B()
        print ("{} releasing lock".format(threading.current_thread().getName()))
        # the number of release() calls has to be the same as the number of acqure() calls
        # otherwise the rlock will not be released by the current thread
        self._rlock.release()
        self._rlock.release()
        self._rlock.release()



if __name__ == "__main__":
    rlock = TestRlock()

    th_1 = threading.Thread(name = "x_1", target = rlock.AB)
    threading.Thread(name = "x_2", target = rlock.AB).start()
    th_1.start()


#===== 249 =======
#This is to practice threading.Lock
import threading
import time

class Counter:
    def __init__(self, lock, barrier):
        self._count = 0
        self._lock = lock
        self._barrier = barrier

    def __call__(self):
        for _ in range(3):
            self._lock.acquire()
            print ("{} got the lock".format(threading.current_thread().getName()))
            self._count += 1
            time.sleep(1)
            print ("\t{} released the lock".format(threading.current_thread().getName()))
            self._lock.release()
        self._barrier.wait()

    def get_value(self):
        print ("final value {}".format(self._count))

if __name__ == "__main__":
    lock = threading.Lock()
    barrier = threading.Barrier(3)
    counter = Counter(lock, barrier)
    
    threading.Thread(name = "t_1", target = counter).start()
    threading.Thread(name = "t_2", target = counter).start()
    
    print ("{} waiting".format(threading.current_thread().getName()))
    barrier.wait()
    print ("{} done waiting".format(threading.current_thread().getName()))

    counter.get_value()


#====== 248 ======
#This is to practice return values from threads
import threading
import time

def f(lt, barrier):
    lt.append(2)
    lt.extend([3, 4])
    print ("f barrier")
    barrier.wait()
    print ("\tf barrier")

def g(barrier):
    global val
    val = 9
    print ("g barrier")
    barrier.wait()
    print ("\tg barrier")

if __name__ == "__main__":
    barrier = threading.Barrier(3)
    lt = []
    val = None

    threading.Thread(target = f, args = (lt, barrier)).start()
    threading.Thread(target = g, args = (barrier,)).start()

    time.sleep(2)
    barrier.wait()
    print ("done wait")
    print (lt, val)



#===== 247 =====
#This is to practice Event (does not guarantee simultaneousness), Barrier (guarantee simultaneousness) 
#and global immutable to coordinate threads
import threading
import time

class ThreadEB(threading.Thread):
    def __init__(self, name, intval, e, b):
        super(ThreadEB, self).__init__(name = name)
        self._intval = intval
        self._event = e
        self._barrier = b

    def run(self):
        while True:
            print ("\t{} sleeps for {}s".format(self._name, self._intval))
            time.sleep(self._intval)
            print ("\t{} slept for {}s".format(self._name, self._intval))

            self._event.wait()
            print ("\t{} finished event waiting".format(self._name))

            self._barrier.wait()
            print ("**** cross barrier {}".format(self._name))

if __name__ == "__main__":
    event = threading.Event()
    barrier = threading.Barrier(3)

    ThreadEB("1p0", 1, event, barrier).start()
    ThreadEB("2p0", 5, event, barrier).start()
    
    for _ in range(3):
        print ("{} sleep for 1.5s".format(threading.current_thread().getName()))
        time.sleep(1.5)
        print ("before set")
        event.set()
        print ("after set")
        barrier.wait()
        print ("clear")
        event.clear()
        time.sleep(1)
        print ("\n\n__________________\n")


#====== 246 =========
#This is to practice exchanging info through a global variable among threads
import threading
import time

def f(intval):
    #global status # since we do not assign status to new value, it's always referenced to the status in the immediate outer scope
    for i in range(500):
        print ("{}: {}".format(threading.current_thread().getName(), i))
        time.sleep(intval)
        if status:
            print ("{} break".format(threading.current_thread().getName()))
            break
def g():
    #global status # without declaring global status, it's defined as a local variable below
    time.sleep(2)
    print ("{} before setting status".format(threading.current_thread().getName()))
    status = True
    print ("{} after setting status".format(threading.current_thread().getName()))

if __name__ == "__main__":
    status = False
    threading.Thread(name = "p5", target = f, args = (.5,)).start()
    threading.Thread(name = "p8", target = g).start()

    #time.sleep(2)
    #print ("before setting status")
    #status = True
    #print ("after setting status")


#======== 245 =========
# This is to practice how to modify a global variable in a function

def f():
    global a
    a += 2
    print (a)

if __name__ == "__main__":
    a = 2
    f()
    print (a)


#===== 244 =====
# This is to practice threading.Barrier
import threading
import time

class ThreadBarrier(threading.Thread):
    def __init__(self, name, barrier, timeout):
        super(ThreadBarrier, self).__init__(name = name)
        self._barrier = barrier
        self._timeout = timeout
        self._cycles = 0

    def run(self):
        while True:
            time.sleep(self._timeout)
            print ("\t{} waiting {}/{}".format(self._name, self._barrier.n_waiting, self._barrier.parties))
            try:
                td_ind = self._barrier.wait()
                print ("{}: {}".format(self._name, td_ind))
            except : # BrokenBarrierError: # does not work
                print ("broken")
            
            self._cycles += 1
            if self._cycles == 3:
                break

if __name__ == "__main__":
    barrier = threading.Barrier(3)
    td_1 = ThreadBarrier("td_1", barrier, 1)
    td_2 = ThreadBarrier("td_2", barrier, 1.5)

    td_1.start()
    td_2.start()

    for _ in range(3):
        time.sleep(.5)
        print ("before reset {}/{}".format(barrier.n_waiting, barrier.parties))
        try:
            barrier.wait()
        except: #BrokenBarrierError:
            print ("broken")
        print ("\tafter wait {}".format(barrier.n_waiting))
        if barrier.n_waiting == barrier.parties:
            raise ValueError("here")
            barrier.reset()
        barrier.abort()
        print ("after reset")


#====== 243 =====
# This is to practice threading.Barrier() which is used as a synchronizing mechanism
# Barrier().n_waiting() returns the number of threads that are currently waiting on the barrier
# Barrier.parties() returns the total number of threads that should call wait()
import threading
import time

class ThreadBarrier(threading.Thread):
    def __init__(self, name, barrier, timeout):
        super(ThreadBarrier, self).__init__(name = name)
        self._barrier = barrier
        self._timeout = timeout

    def run(self):
        time.sleep(self._timeout)
        print ("before barrier {} {}/{}".format(threading.current_thread().getName(), self._barrier.n_waiting, self._barrier.parties))
        self._barrier.wait()
        print ("after barrier {}".format(threading.current_thread().getName()))

if __name__ == "__main__":
    barrier = threading.Barrier(3)

    th_1 = ThreadBarrier("th_1", barrier, 1)
    th_2 = ThreadBarrier("th_2", barrier, 2)
    
    print ("before wait")
    th_1.start()
    th_2.start()
    barrier.wait()
    time.sleep(1)
    print ("after wait")


#===== 242 =====
#This is to practice Event.wait(timeout)
import threading
import time

class ThreadEvent(threading.Thread):
    def __init__(self, name, e, timeout):
        super(ThreadEvent, self).__init__(name = name)
        self._event = e
        self._timeout = timeout

    def run(self):
        while not self._event.is_set():
            print ("x")
            event_is_set = self._event.wait(self._timeout)
            print ("\t{}".format(event_is_set))
        self._event.clear()
        print ("out")
        event_is_set = self._event.wait(2)
        print ("exit {}".format(event_is_set))

if __name__ == "__main__":
    event = threading.Event()
    ThreadEvent("event", event, .5).start()

    time.sleep(2)
    event.set()
    print ("Done set")


#===== 241 ====
#This is to practice implementing a more complex synchronizing mechanism using Event
import threading
import time

class ThreadEvent(threading.Thread):
    def __init__(self, name, e, total_times, daemon = False):
        super(ThreadEvent, self).__init__(name = name, daemon = daemon)
        self._event = e
        self._times = 0
        self._total_times = total_times

    def run(self):
        while self._times != self._total_times:
            print ("set times {}".format(self._times))
            while not self._event.is_set():
                print ("\tx")
                time.sleep(0.5)
            e.clear() # reset the event to false
            self._times += 1
            print ("\t{}".format(self._times))

if __name__ == "__main__":
    e = threading.Event()

    ThreadEvent("Event", e, 2).start()
    
    print ("sleep 2s")
    time.sleep(2)
    e.set()

    time.sleep(1)
    e.set()
    
#===== 240 =====
#This is to practice Event synchronizing mechanism
import threading
import time

def wait_no_block(e):
    print ("({}) waiting".format(threading.current_thread().getName()))
    e_is_set = e.wait()
    print ("({}) done waiting {}".format(threading.current_thread().getName(), e_is_set))

def wait_block(e, intval):
    print ("({}) waiting".format(threading.current_thread().getName()))
    e_is_set = e.wait(intval)
    print ("({}) done waiting {}".format(threading.current_thread().getName(), e_is_set))

if __name__ == "__main__":
    event = threading.Event()

    th_1 = threading.Thread(name = "no_block", target = wait_no_block, args = (event,))
    th_2 = threading.Thread(name = "block", target = wait_block, daemon = False, args = (event, 2))

    th_1.start()
    th_2.start()

    for i in range(4):
        print ("\t{}".format(i))
        time.sleep(1)
    event.set()



#====== 239 =====
#This is to practice using shared variable to exchange info
import threading
import time

#shared_status = False # it is an immutable, so changing its value does not impact the others;
                       # immutables can not be used as a signal/status variable
shared_status = [False]

def signal():
    time.sleep(3)
    shared_status[0] = True
    print ("signal setting done")

def work():
    print ("working")
    i = 0
    while not shared_status[0]:
        i += 1
        print ("\t{}: {}".format(i, shared_status[0]))
        time.sleep(.5)

th_1 = threading.Thread(target = signal)
th_2 = threading.Thread(target = work)

th_1.start()
th_2.start()


# ======== 238 =======
num = 9

def f():
    # num is a global variable, or in an outer scope, it can not be assigned in an inner scope, can only be refrenced
    print (num)
    num += 1 # once num is assigned, it is defined as a local variable, so the above statement will throw 
             # "referenced before assignment" error

if __name__ == "__main__":
    f()


#====== 237 =========
#This is to practice produce-consumer 
import threading
import time

class ProducerThread(threading.Thread):
    def __init__(self, name = "producer"):
        super(ProducerThread, self).__init__(name = name)

    def run(self):
        print (num)
        for i in range(5):
            num[0] += 1
            time.sleep(0.5)


class ConsumerThread(threading.Thread):
    def __init__(self, name = "Cosumer"):
        super(ConsumerThread, self).__init__(name = name)

    def run(self):
        for i in range(5):
            print ("\t{}".format(num))
            num_prev = num[0]
            loop = 0
            while True:
                loop += 1
                if num_prev != num[0]:
                    break
                print (num)
                time.sleep(0.1)
                
                if loop > 5:
                    break


if __name__ == "__main__":
    num = [1]

    prod_thread = ProducerThread()
    cons_thread = ConsumerThread()

    prod_thread.start()
    cons_thread.start()


#===== 236 =========
#This is to practice accessing the main thread in the background thread
import threading
import time

class MyThread(threading.Thread):
    def __init__(self, name, args = None, main_t_name = None):
        super(MyThread, self).__init__() #(name = name)
        self._args = args
        self._main_t_name = main_t_name

    def run(self):
        print ("The main thread name is {} while the background thread has name of {}".format(self._main_t_name, self._name))
        for i in range(self._args):
            print ("\t{}".format(i))
            time.sleep(0.5)

if __name__ == "__main__":
    # set the main thread name
    #threading.current_thread().setName("main_thread")
    my_thread = MyThread("zls", 4, threading.current_thread().getName())
    print (my_thread.getName())
    my_thread.start() # automatically execute 
    time.sleep(1)
    print (22)
    # the program won't stop until the background thread finishes
    # if it's set as daemonic thread, the program finishes when the main thread is done


# ========= 235 ======
# This is to review the multithreading
import threading
import time

def f(ind, count):
    with open("/home/inspur/zls/cs_notes/python" + "/thread_"+str(ind), "w") as f:
        for i in range(count):
            print (i)
            f.write(threading.current_thread().getName() + ": " + str(i)+"\n")
            time.sleep(1)

bg_thread_1 = threading.Thread(name = "t1", target = f, args = (0, 4), daemon = True)
print ("bg_thread_1 name: {}".format(bg_thread_1.getName()))
bg_thread_1.start()

bg_thread_2 = threading.Thread(name = "t2", target = f, args = (1, 2), daemon = True)
print ("bg_thread_2 name: {}".format(bg_thread_2.getName()))
bg_thread_2.start()

for i in range(12):
    print ("\t{}".format(i))
    time.sleep(.5)

# ======= 234 =======
# This is to practice setattr
def f():
    pass

text = "xxx"
setattr(f, "__doc__", text)

#====== 233 =======
#This is to practice closure
def outer():
    print ("outer")
    a = 2
    b = 3
    c = 4
    def inner():
        print ("inner", a, b)
    return inner

f_1 = outer()
f_2 = outer()
# always creates different objects
print (id(f_1) == id(f_2))
print (f_1.__closure__[0].cell_contents)
print (f_2.__closure__[1].cell_contents)


#====== 232 ======
#This is to practice dis
import dis
def swap(a, b):
    a, b = b, a

def swap_2(a, b):
    temp = a
    a = b
    b = temp
dis.dis(swap)
print ("________")
dis.dis(swap_2)

#====== 231 ======
# This is to practice context manager that does no return anything
class CM:
    def __enter__(self):
        print ("enter\n")
    def __exit__(self, *args):
        print ("exit\n")

if __name__ == "__main__":
    with CM():
        print ("middle\n")

#====== 230 ======
# This is to practice context manager class
class CManager:
    def __init__(self, filename, mode):
        self._filename = filename
        self._mode = mode
        self._file_handler = None
    def __enter__(self):
        self._file_handler = open(self._filename, self._mode)
        return self._file_handler
    def __exit__(self, excp_type, excp_value, excp_traceback):
        self._file_handler.close()
        print ("excp_type: {}".format(excp_type))
        print ("excp_value: {}".format(excp_value))
        #print ("excp_traceback: {}".format(excp_trace_back))

if __name__ == "__main__":
    with CManager("a.txt", "w") as f:
        f.write("xx\n");
        raise ValueError("throw an error\n")


#======== 229 ========
# This is to practice default mutables in a function argument
def f(a = []): # the object referenced by a is always there whenever no parameter is passed
    a.append(2)
    print (a)

b = [3]
f()
f()
f(b)
f()

#======= 228 ======
a = [] or [2] # a is assigned to [2]

#========= 227 =======
# this is to practice mutables in an default argument
def f(a = [2,3]):
    print (a)
    a.append(3)

f([99])
f([99])
f()
f()
f()

#========= 226 =======
def f():
    # a is not defined inside the function, but as long 
    # as it's defined before f() is called, it is okay
    print (a)

a = 2
f()

#======== 225 =======
# Find out the number of cores
import multiprocessing
print (multiprocessing.cpu_count())
#====== 224 ======
#This is to practice glob
import glob

glob = glob.glob("*.py")
print (glob)

#========= 223 =========
#This is to practice sys.stdout.flush()
import sys
import time

for i in range(5):
    print (i)
    sys.stdout.flush() # does not see the difference w/o this line
    time.sleep(1)


#============ 222 ============
# This is to practice super()
# in python 2, we need to use super(Class_name, self) syntax
# in python 3. if we just call the immediate parent functions, we can just use super(), ignoring the two arguments
# when refer to the functions above the immediate parent class, use super(Desired_class, self)._f_(...)
# super() is like a type conversion (up) in c++
class A(object):
    a = 9
    def __init__(self):
        print ("A __init__")

    def get(self):
        print  ("Get A")


class B(A):
    a = 11
    def __init__(self, i):
        print ("____ 1 ____")
        #super(B, self).__init__();
        A.__init__(self) # if an instance, need to put self here, just a.__init__()
        print ("____ 2 ____")

    def get(self):
        super(B, self).get()
        print ("Get B", super(B, self).a, self.a)

class C(B):
    a = 13
    def getB(self):
        super(C, self).get()

    def getA(self):
        super(B, self).get()
    def get(self):
        print (super(B, self).a, super(C, self).a, self.a)

class D(C):
    a = 15
    def get(self):
        print (super(B, self).a)
        super(B, self).get()

if __name__ == "__main__":
    b = B(3)
    b.get()

    c = C(2)
    c.getB()
    c.getA()
    print (b.a)
    c.get()

    d = D(3)
    print ("xxxx")
    d.get()

    b.__init__(9)

#========= 221 ======
# Also multiprocessing.Manager() creates an object to hold python objects, like list, dict, etc. to communicate among processes
#====== 220 ========
# This is to practice shared memory between processes to communicate
import multiprocessing
import time

def f(num, arr):
    time.sleep(5)
    num.value = True
    for i in range(9, 9+10):
        arr[i-9] = i


if __name__ == "__main__":
    num = multiprocessing.Value('b', False, lock = True)
    arr = multiprocessing.Array('i', 10, lock = True)
    procs = multiprocessing.Process(target = f, args = (num, arr))
    procs.start()
    # observe the waiting process
    while not num.value:
        print ("waiting ...")
        time.sleep(1)
    procs.join()
    print (num.value, arr[:])

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
