//======= 74 ======
//This is to practice break from for-switch loop
package main

import "fmt"

func main() {
FOR:
	for i := 0; i < 3; i++ {
		switch i {
		case 1:
			fmt.Println("break from the loop")
			break FOR
		case 0:
			fmt.Println("break from the switch")
			break
		}
		fmt.Println(i)
	}
}

/*
//======== 73 =======
//This is to practice break inside multi-layer loop
package main

import "fmt"

func main() {
	//FOR_O
	for o := 0; o < 2; o++ {
		fmt.Println("o_", o)
	FOR_outer:
		for i := 0; i < 5; i++ {
			//FOR_inner:
			for j := 0; j < 5; j++ {
				if j >= 2 {
					fmt.Println("")
					break FOR_outer
				}
				fmt.Print(i, " ")
			}
		}
	}
}


//======== 72 =========
//This is to practice switch and its label
package main

import "fmt"

func main() {
	var a int = 2

	switch a {
	case 2:
		fmt.Println("2")

		if false {
			break
		} else {
			goto end
		}
		//fmt.Println("aftger break, unreachable code")
		fallthrough
	case 1:
		fmt.Println("1")
		//fallthrough // this line enables the direct following case being executed
		// though case is not a match
	default:
		fmt.Println("default")
	}
	fmt.Println("before end")
end:
	fmt.Println("after end")

}


//======= 71 =======
//This is to practice closure
package main

import (
	"fmt"
	"time"
)

func main() {
	for i := 0; i < 10; i++ {
		//the value i closed in the goroutine will be updated when modifed outside
		go func(j int) {
			time.Sleep(time.Second)
			fmt.Println("taken", j, "now", i)
		}(i)

		<-time.After(time.Millisecond * 900)
	}
}


//======== 70 =========
//This is to practice mimicing a certain number of concurrency in go
package main

import (
	"fmt"
	"time"
)

func main() {
	ch := make(chan struct{}, 3)
	end := make(chan struct{})

	for i := 0; i < 100; i++ {
		time.After(time.Microsecond)
		//limit the maximum concurrency to 3
		ch <- struct{}{}

		//go func(i int) {
		go func() {
			<-ch
			time.Sleep(time.Microsecond)
			fmt.Println(i)

			if i == 100 {
				fmt.Println("end", i)
				end <- struct{}{}
			}
		}() //(i) // pass i into the function, if use closure, i will be the value when
		// goroutine executes
	}

	<-end
	<-time.After(time.Second)
}


//========= 69 ========
//This is to practice time.After(), which returns a channel
package main

import (
	"fmt"
	"time"
)

func main() {
	//ch := make(<-chan time.Time)
	//ch = time.After(time.Second)
	ch := make(chan struct{})

	fmt.Println(ch)
	//fmt.Println(<-ch)

	go func() {
		for {
			select {
			case <-ch:
				fmt.Println("here")
			case <-time.After(time.Second):
				fmt.Println("delay 1 second")
				//default:
				//	fmt.Println("no delay")
			}
		}
	}()

	time.Sleep(time.Second * 3)
	for i := 0; i < 10; i++ {
		fmt.Println("___")
		time.Sleep(time.Millisecond * 900)
		//ch = time.After(time.Second)
		ch <- struct{}{}
	}
}


//======== 68 ======
//This is to practice breaking from a for-select
package main

import (
	"fmt"
	"time"
)

func break_for_select(ch chan struct{}) {
	var stop bool = false

	for !stop {
		select {
		case <-ch:
			fmt.Println("got the signal, exit from for-select loop")
			stop = true //perfectly exit from the loop
		default:
			fmt.Println("default")
		}
	}
}

func main() {
	ch := make(chan struct{})

	go break_for_select(ch)
	time.Sleep(time.Millisecond)
	ch <- struct{}{}
	time.Sleep(time.Millisecond)
}


//======= 67 ============
//This is to practice sending quit signal from producer to consumer
package main

import (
	"fmt"
)

func produce(ch_in chan<- int, sig chan<- struct{}) {
	for i := 0; i < 10; i++ {
		ch_in <- i
	}

	fmt.Println("Done producing")
	sig <- struct{}{}
}

func consume(ch_out <-chan int, sig <-chan struct{}, sig_done chan<- struct{}) {
	var val int
FOR:
	for {
		select {
		case val = <-ch_out:
			fmt.Println(val)
		case <-sig:
			fmt.Println("Done consuming")
			//break // this only breaks from the current case, not the for loop
			break FOR // breaks from the for loop
		}

	}
	sig_done <- struct{}{}
}

func main() {
	ch := make(chan int)
	sig := make(chan struct{})
	sig_done := make(chan struct{})

	go produce(ch, sig)

	go consume(ch, sig, sig_done)

	<-sig_done
}


//======= 66 =========
//This is to practice merging multiple channels into one channel, and output
package main

import (
	"fmt"
	"time"
)

func main() {
	ch_1 := make(chan int)
	ch_2 := make(chan int)
	output := make(chan int)

	go func(ch chan int) {
		for i := 1; i <= 9; i += 2 {
			ch <- i
			time.Sleep(time.Millisecond)
		}
		//once closed, reading channel won't be blocked, so zero value will be read
		close(ch)
	}(ch_1)

	go func(ch chan int) {
		for i := 2; i <= 10; i += 2 {
			ch <- i
		}
		// the same goes here, reading channel can read zero values
		close(ch)
	}(ch_2)

	go func(ch_1 <-chan int, ch_2 <-chan int, output chan<- int) {
		//merge the values in ch_1 and ch_2 into output channel
		var val int
		var ok_1, ok_2 bool

		for {
			select {
			case val, ok_1 = <-ch_1:
				//only take the valid values
				if ok_1 {
					output <- val
				}
			case val, ok_2 = <-ch_2:
				// only take the valid values
				if ok_2 {
					output <- val
				}
			}

			if !ok_1 && !ok_2 {
				fmt.Println("both channels are empty now")
				close(output)
				break
			}
		}
	}(ch_1, ch_2, output)

	for ele := range output {
		fmt.Println(ele)
	}

}


//====== 65 ========
//This is to practice closing channel, ok is only false when the channel is closed
package main

import (
	"fmt"
	"time"
)

func produce(ch chan int, stop chan int) {
	for i := 1; i <= 5; i++ {
		ch <- i
		time.Sleep(time.Second)
	}
	fmt.Println("Done inserting into a channel")
	close(ch)

	stop <- 0
}

func consume(ch chan int, stop chan int) {
	for {
		if val, ok := <-ch; ok {
			fmt.Println(val)
		} else {
			fmt.Println(ok, "consumed all values in the channel")
			break
		}
	}
	stop <- 1
}

func main() {
	ch := make(chan int, 5)
	stop := make(chan int, 2)
	go produce(ch, stop)

	go consume(ch, stop)

	<-stop
	<-stop
}


//========= 64 =======
//This is to practice
package main

import "fmt"

type Address struct {
	Country string
	State   string
}

type Person struct {
	name    string
	age     int
	address Address
}

func main() {
	me := Person{"zls", 31, Address{"China", "Jiangsu"}}

	// if the channel contains pointer, the deferenced value will reflect the
	// changes
	ch := make(chan *Person, 1)

	ch <- &me
	me.address = Address{"CHINA", "JIANGSU"}

	fmt.Println(*<-ch)
}


//======== 63 =======
//This is to practice channel
package main

import "fmt"

func main() {
	ch := make(chan int, 4)

	ch <- 2
	ch <- 3
	ch <- 4
	ch <- 5

	fmt.Println(<-ch)
	close(ch)

	a, ok := <-ch
	fmt.Println(a, ok)

	a, ok = <-ch
	fmt.Println(a, ok)

	a, ok = <-ch
	fmt.Println(a, ok)

	a, ok = <-ch
	fmt.Println(a, ok)
}


//======== 62 ======
//This is to practice returning a channel which is a production line
package main

import "fmt"

func produce() chan int {
	ch := make(chan int, 2)
	go func() {
		for i := 0; i < 10; i++ {
			ch <- i * i
		}
		// has to close it if using range in another goroutine
		close(ch)
	}()

	return ch
}

func main() {
	ch := produce()
	for i := range ch {
		fmt.Println(i)
	}
}


//======= 61 =========
//This is to practice signaling by empty struct
package main

import (
	"fmt"
	"time"
)

func main() {
	ch := make(chan struct{})

	go func() {
		fmt.Println("before receiving signal")
		<-ch
		fmt.Println("after receiving signal")
	}()

	fmt.Println("sleeping")
	time.Sleep(time.Second * 2)
	fmt.Println("done sleeping")
	ch <- struct{}{}
}


//===== 60 ========
//This is to practice select
package main

import (
	"fmt"
)

func main() {

	ch_1 := make(chan int, 2)
	ch_2 := make(chan int, 2)

	go func() {
		for i := 1; ; i++ {
			ch_1 <- i
			ch_2 <- i
		}
	}()

	for i := 0; i < 100; i++ {
		select {
		case j := <-ch_1:
			fmt.Println(i, "ch_1", j)
		case j := <-ch_2:
			fmt.Println(i, "ch_2", j)

		}
	}
}


//======== 59 =======
//This is to practice select
package main

import (
	"fmt"
	"time"
)

func test_select(ch_1 chan int, ch_2 chan int) {
	go func() { <-ch_1 }()

	go func() { <-ch_2 }()

	select {
	case ch_1 <- func() int { time.Sleep(100 * time.Millisecond); return 32 }():
		fmt.Println("fed 1")
	case ch_2 <- func() int { time.Sleep(100 * time.Millisecond); return 32 }():
		fmt.Println("fed 2")
	//default:
	//	fmt.Println("not fed")
	default:
		fmt.Println("++++++++++++")
	}
}

func main() {
	ch_1 := make(chan int, 0)
	ch_2 := make(chan int, 0)

	for i := 0; i < 50; i++ {
		fmt.Println("*****", i)
		test_select(ch_1, ch_2)
	}
}


//========= 58 ========
//This is to practice
package main

import (
	"fmt"
	"time"
)

func feed(ch chan int) {
	for _, i := range [2]int{2, 3} {
		ch <- i
		time.Sleep(time.Second)
	}
}

func main() {
	ch := make(chan int)
	go feed(ch)

	if val, ok := <-ch; ok {
		fmt.Println(ok, "val_1", val)
	} else {
		fmt.Println(ok, "1. not valid value")
	}

	//close(ch)

	if val, ok := <-ch; ok {
		fmt.Println(ok, "val_2", val)
	} else {
		fmt.Println(ok, "2. not valid value")
	}

}


//======= 57 ======
//This is to practice channel with restricted permission
package main

import (
	"fmt"
	"time"
)

func main() {
	ch := make(chan int)

	go func() {
		for i := 9; i <= 20; i++ {
			ch <- i
			time.Sleep(time.Second)
		}

		// we need to close the channel explicitly, otherwise deadlock
		close(ch)
	}()

	for i := range ch {
		fmt.Println(i)
	}
}


//======= 56 ==========
//This is to practice unbuffered and buffer size of 1
package main

import (
	"fmt"
	"time"
)

func main() {
	ch1 := make(chan int)
	ch2 := make(chan int, 1)

	go func() {
		fmt.Println("(unbuffered) before sending")
		ch1 <- 2
		fmt.Println("(unbuffered) after sending")
	}()

	time.Sleep(time.Second * 1)
	fmt.Println("receiving")
	fmt.Println(<-ch1)
	time.Sleep(time.Second)

	fmt.Println("_____________")

	go func() {
		fmt.Println("(bufferred) before sending")
		ch2 <- 3
		fmt.Println("(bufferred) after sending")
	}()

	time.Sleep(time.Second)
	fmt.Println(<-ch2)
	time.Sleep(time.Second)
}


//======== 55 =========
//This is to practice buffered channel
package main

import (
	"fmt"
	"time"
)

func main() {
	ch := make(chan int, 2)

	go func() {
		for i := 0; i <= 5; i++ {
			ch <- i
			fmt.Println("xx")
		}
	}()

	fmt.Println("__________")
	time.Sleep(time.Second)
	<-ch
	<-ch
	fmt.Println("________")
	time.Sleep(time.Second)
	<-ch
	<-ch
	fmt.Println("_________")
	time.Sleep(time.Second)
	<-ch
	<-ch
	fmt.Println("___________")

	fmt.Println("ch")

}


//========= 54 =======
//This is to practice using channel to communicate mesasges
package main

import (
	"fmt"
)

func main() {
	ch := make(chan int)

	go func() {
		for i := 0; i <= 4; i++ {
			ch <- i
			fmt.Println("input", i)
		}
	}()

	for i := 0; i <= 4; i++ {
		fmt.Println("output", <-ch)
	}
}


//======== 53 =======
//This is to practice channel
package main

import (
	"fmt"
)

func main() {
	var ch chan int

	fmt.Println(ch)

	ch = make(chan int)

	fmt.Println(ch)

	go func() {
		ch <- 2
	}()
	fmt.Println(<-ch)
}


//======== 52 ======
//This is to practice new
package main

import (
	"fmt"
)

func main() {
	p := new(int)
	*p = 2
	fmt.Println(p, *p)
}

//====== 51 =======
//This is to practice factorial and fibonacci series
package main

import (
	"fmt"
)

func main() {
	fmt.Println(factorial(3))

	for i := 3; i <= 8; i++ {
		fmt.Println(fibonacci(i))
	}

	fmt.Println("_________")
	fmt.Println(cache_fibonacci()(3))
	fmt.Println("_________")
	fmt.Println(cache_fibonacci()(6))
	fmt.Println("________")
	fmt.Println(cache_fibonacci()(7))
}

func cache_fibonacci() func(int) int {
	cache := make(map[int]int)

	var fibonacci_inner func(int) int
	fibonacci_inner = func(m int) int {
		for k, v := range cache {
			if m == k {
				fmt.Printf("\t%d\n", m)
				return v
			}
		}

		if m == 0 {
			return 0
		}

		if m == 1 {
			return 1
		}

		res := fibonacci_inner(m-1) + fibonacci_inner(m-2)
		cache[m] = res
		return res
	}

	return fibonacci_inner
}

func fibonacci(n int) int {
	if n == 0 {
		return 0
	}
	if n == 1 {
		return 1
	}

	return fibonacci(n-1) + fibonacci(n-2)
}

func factorial(n int) int {
	if n == 1 {
		return 1
	}

	return n * factorial(n-1)
}


//======== 50 ======
//This is to practice defer in different goroutines
package main

import (
	"fmt"
	"time"
)

func main() {
	defer func() {
		r := recover()
		fmt.Println("recover", r)
	}()

	go func() {
		time.Sleep(time.Duration(1))
		fmt.Println("before panic")
		// this panic is not caught by the recover() in the main routine
		panic("sub-goroutine")
	}()
	time.Sleep(time.Second * time.Duration(2))
}


//======== 49 =======
//This is to practice one panic multiple recover
package main

import (
	"fmt"
)

func main() {

	defer func() {
		r := recover()
		fmt.Println(0, r)
	}()
	defer func() {
		r := recover()

		fmt.Println(1, r)

		panic("there")
	}()

	panic("here")
}


//======== 48 ========
//This is to practice if recover works in different function
package main

import (
	"fmt"
)

func main() {
	defer_func()
	//this panic is not caught by the recover in another function
	//panic("sdf")
	//defer func() {
	//	r := recover()
	//	fmt.Println(r)
	//}()
	// also this can not be caught by defer_func()
	// it can be caught by explicit defer function, not the one inside
	// a function
	panic_func()
}

func panic_func() {
	panic("here")
}

func defer_func() {
	defer func() {
		r := recover()
		fmt.Println("In defre_func:", r)
	}()
}


//====== 47 ======
//This is to practice panic, defer and recover in different gorountines
package main

import (
	"fmt"
	"time"
)

func main() {
	// in just one goroutine, mimicing fallback onto different branches
	// in different panics
	defer func() {
		r := recover()
		fmt.Printf("%T %v\n", r, r)
		switch r {
		case 1:
			//some branch
			branch_1()
		default:
			// some branch
			fmt.Println("done default branch")
		}

	}()

	//after some execution, we might come to this point
	a := 3
	if a == 3 {
		fmt.Println("before panic")
		panic(1)
	}
	//otherwise do something normal
	//panic(2)
	// since the control returns encountering the first panic, thus the
	// following code
	panic("sd")
}

func branch_1() {
	fmt.Println("We are executing branch 1")
	time.Sleep(time.Second * time.Duration(2))
	fmt.Println("Done branch_1")
}


//======= 46 =======
//This is to practice concurrency
package main

import (
	"fmt"
	"time"
)

func main() {
	for i := 1; i <= 5; i++ {
		go func(j int) {
			time.Sleep(time.Duration(j) * time.Second)
			fmt.Println("Done sleeping for", j, "seconds")
		}(i)
	}

	fmt.Println("******")
	time.Sleep(time.Millisecond * time.Duration(5100))
	fmt.Println("__________")
}


//======== 45 ======
//This is to practice time.Sleep(time.Second)
package main

import (
	"fmt"
	"time"
)

func main() {
	go func() {
		for i := 1; ; i++ {
			time.Sleep(time.Second)
			fmt.Println("goroutine slept", i, "seconds")
		}
	}()

	time.Sleep(time.Millisecond * 5100)
}


//======= 44 ========
//This is to practice if advanced
package main

import (
	"fmt"
)

func main() {
	if a := 2; a > 3 {
		fmt.Println("a > 3")
	} else if a == 2 {
		fmt.Println("a == 3")
	} else {
		fmt.Println("a < 2")
	}
	// a goes out scope, so can not access it
	//fmt.Println(a)
}


//======= 43 =======
//This is to practice multiple defers
//defers are run in the reverse order, i.e. FILO
package main

import (
	"fmt"
)

func main() {
	defer fmt.Println(1)
	defer fmt.Println(2)

	defer func() {
		if r := recover(); r != nil {
			fmt.Println("recovered", r)
		}
	}()

	for i := 3; i < 5; i++ {
		defer fmt.Println(i)
	}

	fmt.Println("______")
	panic("panic")
}


//======== 42 =======
//This is to practice error handling
package main

import (
	"errors"
	"fmt"
	"math"
)

func sqrt(i float64) (float64, error) {
	if i < 0 {
		return 0, errors.New("input is less than 0")
	}
	return math.Sqrt(i), nil
}
func main() {
	s, e := sqrt(2.3)
	fmt.Print(s, e)

	s, e = sqrt(-1.)
	fmt.Println("_______")
	fmt.Print(s, e)
	fmt.Println("_______-")
}


//========== 41 ==========
//This is to practice getting value and pointer interfaces into a slice
package main

import (
	"fmt"
)

type IFACE interface {
	get_name() string
}

type Person struct {
	name string
}
type Animal struct{}

func (p Person) get_name() string {
	return "zls"
}

func (a *Animal) get_name() string {
	return "cat"
}

func main() {
	me := Person{"xx"}
	var dog Animal

	//var all_faces []IFACE = make([]IFACE, 2, 5)
	//all_faces := make([]IFACE, 2, 5)
	all_faces := [2]IFACE{}

	fmt.Println(all_faces)
	all_faces[0] = me
	for _, face := range all_faces {
		if face == nil {
			fmt.Println("\tnil")
		}
	}
	all_faces[1] = &dog

	fmt.Println(all_faces)

	for _, face := range all_faces {
		fmt.Println(face.get_name())
	}
}


//====== 40 =======
//This is to practice interface receiver
// if the receiver is a pointer, the interface has to be pointer
// if the receiver is a value, then interface can be a value or a pointer
package main

import (
	"fmt"
)

type IFACE interface {
	get_name() string
}

type Person struct{}

// the interface can only be pointer
func (p *Person) get_name() string {
	return "zls"
}

type Animal struct{}

// the interface can value or pointer
func (a Animal) get_name() string {
	return "dog"
}

func main() {
	me := Person{}
	a := Animal{}

	var intface IFACE = a // or &me or just declare it without initialization
	// since in Person, get_name() is implemented using a pointer receiver
	// the object passed to interface should be a pointer
	intface = &me
	fmt.Println(intface.get_name())

	intface = a //&a
	fmt.Println(intface.get_name())
}


//======== 39 ======
//This is to practice finding the type of the object represented by
//an interface
package main

import (
	"fmt"
)

type Intface interface {
	get_name() string
}

type Person struct {
	name string
}

func (p Person) get_name() string {
	return p.name
}

type Animal struct {
	name string
}

func (a Animal) get_name() string {
	return a.name
}

func main() {
	me := Person{"zls"}
	var intface Intface
	fmt.Printf("%T\n", intface)
	intface = me
	fmt.Printf("%T %T\n", me, intface)
	//intface := Intface{me}
	fmt.Println(intface.get_name())

	you := Person{"dsy"}
	all_faces := []Intface{me, you}

	dog := Animal{"dog"}
	cat := Animal{"cat"}

	all_faces = append(all_faces, dog)
	all_faces = append(all_faces, cat)

	fmt.Printf("%T\n", all_faces)
	for _, face := range all_faces {
		fmt.Printf("%s %T\n", face.get_name(), face)
	}
}


//======== 38 =======
//This is to practice interface
package main

import (
	"fmt"
)

//for a type to use interface, it has to implement all methods inside
//the interface definition
type Intface interface {
	get_name() string
	//get_age() int
}

type Person struct {
	name string
}

func (p Person) get_name() string {
	return p.name
}

func print_name(intface Intface) {
	fmt.Println(intface.get_name())
}

func main() {
	me := Person{"zls"}
	you := Person{"dsy"}

	var intface []Intface
	intface = append(intface, me)
	intface = append(intface, you)

	for _, inst := range intface {
		//fmt.Println(inst.get_name())
		print_name(inst)
	}
}


//========== 37 =======
//This is to practice variable scope
package main

import "fmt"

func main() {
	//inside the following scope, a is defined and accessed
	{
		var a int = 3
		fmt.Println(a)
	} // can not access a beyond this point

}


//======== 36 ========
//This is to practice type method which does not pass the type by reference
package main

import "fmt"

type Person struct {
	name   map[int]string
	grades [2]int
}

func (p *Person) set_name_p(name string) {
	p.name[0] = name
	p.grades[0] = 111
}

func (p Person) set_name(name string) {
	p.name[0] = name
	p.grades[0] = 100
}

func main() {
	me := Person{map[int]string{1: "x", 2: "y"}, [2]int{90, 95}}

	//slice/map passed by value has the same effect as that of by reference
	me.set_name("zls")
	fmt.Println(me)

	me.set_name_p("zlszls")
	fmt.Println(me)
}


//======= 35 ======
//This is to practice struct method
package main

import "fmt"

type Person struct {
	name   string
	age    int
	grades []float32
}

func (p *Person) set_name(name string) {
	p.name = name
}

func (p *Person) get_age() int {
	return p.age
}

func (p *Person) average_grades() float32 {
	var sum float32 = 0
	for _, grade := range p.grades {
		sum += grade
	}
	return sum / float32(len(p.grades))
}

func main() {
	me := Person{age: 32, grades: []float32{89.9, 92.5, 95.0, 100}}
	me.set_name("zls")
	fmt.Println(me.get_age())

	fmt.Println(me.average_grades())
}


//======== 34 =======
//This is to practice nested struct
package main

import "fmt"

func main() {
	me := Me{&Person{"zls", 32}, "se"}

	//fmt.Println(me, me.name, me.age)
	fmt.Println(me, me.P.name, me.P.age)
}

type Person struct {
	name string
	age  int
}

type Me struct {
	P   *Person
	job string
}


//======== 33 =========
//This is to practice returning a struct from a function
package main

import "fmt"

func main() {
	me := get_me()
	fmt.Println(me.name, me.age)
}

func get_me() *Person {
	var me Person = Person{name: "zls"}
	return &me
}

type Person struct {
	name string
	age  int
}


//======= 32 ======
//This is to practice struct
package main

import "fmt"

type Me struct {
	name string
	age  int
	mix  []int
}

func main() {
	var me Me = Me{"zls", 32, []int{3}}
	fmt.Println(me.name, me.age)

	p := &me
	fmt.Println(p.name, p.age)

	me_2 := me

	f(me, &me_2)
	fmt.Println(me.name, me_2.name)
	fmt.Println(me)

	var t Me
	fmt.Println(t, t.mix == nil)
}

func f(me Me, me_2 *Me) {
	me.name = "changed"
	me_2.name = "changed"
}


//=========== 31 ========
//This is to practice passing pointer to a function
package main

import "fmt"

func main() {
	var a, b int = 2, 3
	var pa, pb *int = &a, &b

	fmt.Printf("%p %d\n", pa, *pa)
	fmt.Printf("%p %d\n", pb, *pb)

	// pass pa by value, pass pb by reference
	test(pa, &pb)

	fmt.Printf("%p %d\n", pa, *pa)
	fmt.Printf("%p %d\n", pb, *pb)

}

func test(pa *int, pb **int) {
	*pa *= 2
	var a int = 99
	*pb = &a
}


//======== 30 =======
//This is to practice pointer to pointer
package main

import "fmt"

func main() {
	var a, b, c int = 2, 3, 4
	var pa, pb, pc *int = &a, &b, &c

	//var all_p [3]**int = [3]**int{&pa, &pb, &pc}

	all_p := [3]**int{&pa, &pb, &pc}

	for _, pp := range all_p {
		fmt.Println(**pp)
	}
}


//====== 29 ======
//This is to practice array of pointers
package main

import (
	"fmt"
)

// can not use := outside of a function
var qq int = 3

const q int = 3

func main() {
	arr := [3]map[string]int{{"x": 1, "y": 2}, {"xx": 3, "yy": 4},
		{"xxx": 5, "yyy": 6}}

	fmt.Println(arr[0])

	arr_p := [3]*map[string]int{&arr[0], &arr[1], &arr[2]}

	for p, ele := range arr_p {
		//fmt.Println(*arr_p[p])
		fmt.Println(p, *ele)
	}

	a := 2
	b := 3
	pp_map := map[int]*int{23: &a, 24: &b}

	fmt.Println(*pp_map[23], *pp_map[24])
}


//====== 28 =========
//This is to practice pointer
package main

import (
	"fmt"
)

func main() {
	var a int = 2
	var ap *int = &a

	fmt.Printf("%p %p %d\n", ap, &a, *ap)

	var bp *float32
	fmt.Println(bp == nil, ap == nil)
}


//======== 27 ======
//This is to practice %p
package main

import (
	"fmt"
)

func main() {
	var a int = 2
	b := a
	fmt.Printf("%p\n%p\n", &a, &b)
}


//====== 26 ==========
//This is to practice nil
package main

import "fmt"

func main() {
	var a int
	var b float32

	//fmt.Println(a == nil, b == nil)
	fmt.Println(a, b)

	var c []int
	var d map[string]int
	fmt.Println(c == nil, d == nil)

	var e string
	fmt.Println(e == "")
}


//========== 25 =========
//This is to practice initializing multiple variables
package main

import (
	"fmt"
)

func main() {
	a, b, c, d, e := 2, "sdf", 3.14, []int{2, 3}, map[string]int{"xx": 2, "yy": 3}
	fmt.Println(a, b, c, d, e)
}


//========== 24 =========
//This is to practice pass array/map/slice by value into a function
package main

import "fmt"

func main() {
	var arr [2]int = [2]int{2, 3}
	var sl []int = []int{4, 5}
	var m map[string]int = make(map[string]int)

	// pass array by value does not modify the original copy
	f1(arr)
	fmt.Println(arr)

	// pass slice by vlaue does modify the origianl copy
	f2(sl)
	fmt.Println(sl)

	f3(m)
	fmt.Println(m)
}

func f3(m map[string]int) {
	m["xx"] = 22
}

func f2(sl []int) {
	sl[0] = 22
}

func f1(arr [2]int) {
	arr[0] = 22
}


//=========== 23 ========
// This is to practice systematically assignment
package main

import "fmt"

func main() {
	fmt.Println("_________")
	//for immutables, they point to the same immutable object
	var i int = 9
	j := i
	//i now points to a different object
	i = 99
	fmt.Println(i, j)

	fmt.Println("____________")
	// string is also a immutable, so the same rule applies
	var s string = "xx"
	ss := s
	ss = "yy"
	fmt.Println(s, ss)

	fmt.Println("________________")
	// though array is a mutable, assignment is just like a hard copy
	var arr [2]int = [2]int{2, 3}
	arrr := arr
	arrr[0] = 22
	fmt.Println(arr, arrr)

	fmt.Println("____________")
	var arr_2 [2][2]int = [2][2]int{{2, 3}, {4, 5}}
	arrr_2 := arr_2
	arr_2[0][0] = 22
	fmt.Println(arr_2, arrr_2)

	fmt.Println("______________")
	//slice is a mutable, assignment is reflected
	var sl []int = []int{2, 3}
	sll := sl
	sl[0] = 22
	fmt.Println(sl, sll)

	fmt.Println("______________")
	// map is a mutable, changes are reflected
	var m map[string]int = make(map[string]int)
	m["xx"] = 2
	m["yy"] = 3
	mm := m
	m["xx"] = 22
	m["zz"] = 222
	fmt.Println(m, mm)

	fmt.Println("_____________")
	var aa [2][]int = [2][]int{{2}, {4, 5}}
	aaa := aa
	aa[0][0] = 22
	fmt.Println(aa, aaa)

	fmt.Println("_____________")
	// 2d-slice is different from 2d-array
	var bb [][2]int = [][2]int{{2, 3}, {4, 5}}
	bbb := bb
	bb[0][0] = 222
	fmt.Println(bb, bbb)
	fmt.Printf("%T %T\n", aa, bb)
}


//========== 22 =========
package main

import (
	"fmt"
)

func main() {
	var arr [2]int = [2]int{2, 3}
	a := arr
	arr[0] = 22
	fmt.Println(arr, a)

	fmt.Println("___________")

	var brr [2]map[string]int = [2]map[string]int{{"x": 2}, {"y": 3}}
	crr := brr
	brr[0]["x"] = 229999999
	fmt.Println(brr, crr)

	m := map[string]int{"xx": 2, "yy": 3}
	fmt.Println(m)
}


//===== 21 =======
//This is to practice function type
package main

import "fmt"

func main() {
	s := func(a int) int {
		return a * a
	}(2)
	fmt.Println(s)

	inner := func(i int) int {
		return 2 * i
	}
	outer(inner)
}

func outer(f func(int) int) {
	fmt.Println(f(9))
}


//========= 20 =========
//This is to practice defer
package main

import "fmt"

func f(a int) int {
	return a
}

func main() {
	defer fmt.Println("the end")
	fmt.Println("before the end")

	fmt.Printf("%T\n", f)
}


//====== 19 =====
//This is to practice function returning multiples vlaues
package main

import "fmt"

func main() {
	x := 2
	y := 9

	s1, s2 := f1(x, y)
	fmt.Println(s1, s2)

	s1, s2 = f2(x+1, y+1)
	fmt.Println(s1, s2)

	var a float32 = 3.14
	fmt.Println(f3(x, y, a))
}

//multiple return values have to be enclosed inside a pair of parenthesis
func f3(x, y int, a float32) (z1, z2 float32) {
	z1 = float32(x + y)
	z2 = float32(z1) - a
	return
}

func f1(x, y int) (z1 int, z2 int) {
	//return x + y, x - y
	z1 = x + y
	z2 = x - y
	//required
	return
}

func f2(x, y int) (z1, z2 int) {
	z1 = x + y
	z2 = x - y
	return
}


//======= 18 ======
//This is to practice function closure
package main

import (
	"fmt"
)

func main() {
	kvs := collect()
	fmt.Println(kvs("x", 1))
	fmt.Println(kvs("y", 2))

	kvs = collect()
	fmt.Println(kvs("xx", 9))
}

func collect() func(string, int) map[string]int {
	kv := make(map[string]int)
	// create a function on the fly
	f := func(k string, v int) map[string]int {
		kv[k] = v
		return kv
	}
	return f
}


//======== 17 ========
//This is to practice creating a function on the fly
package main

import (
	"fmt"
)

var b int = 99

func main() {
	var a int = 9
	var c string = "xx"
	f := func(c *string) {
		a++
		b++
		*c = "yy"
	}

	f(&c)
	fmt.Println(a, b, c)
}


//======== 16 ========
//This is to practice function
package main

import (
	"fmt"
)

func main() {
	var a int = 9
	fmt.Printf("%d\n", f1(a))
	f2(&a)
	fmt.Printf("%d\n", a)
	f2(&a)
	fmt.Printf("%d\n", a)

	var b [3]int
	fill(&b)
	fmt.Printf("%d\n", b)

	var c []int
	c = make([]int, 2, 5)
	fill_slice(&c)
	fmt.Printf("%d\n", c)

	m := make(map[string]int)
	fill_map(&m)
	fmt.Println(m)

	var s string = "xdsf"
	fmt.Println(len(s), s[2:])
	mod_s(&s)
	fmt.Println(s)

	var arr [3]int = [3]int{9, 9, 9}
	fill_arr(&arr)
	fmt.Println(arr)
}

func fill_arr(arr *[3]int) {
	(*arr)[1] = 999
}

func mod_s(s *string) {
	*s = "xx"
}

func fill_map(m *map[string]int) {
	(*m)["xx"] = 2
	(*m)["yyy"] = 3
}

//pass slice by value, but they share the underlying array
//so
func fill_slice(c *[]int) {
	(*c)[0] = 99
	(*c)[1] = 999
	*c = append(*c, 9999)
}

//pass array by reference
func fill(b *[3]int) {
	b[0] = 99
}

//pass by value
func f1(a int) int {
	return a + 1
}

func f2(a *int) {
	//*a = *a + 1
	*a++
}


//========= 15 =======
//This is to practice map
package main

import "fmt"

func main() {
	var m map[string]string
	if m == nil {
		fmt.Println("\tm is nil")
	}
	// can not assign any value to nil map
	// has to use make to enable assignment of map
	m = make(map[string]string)
	if m == nil {
		fmt.Println("m is nil")
	}
	m["xsd"] = "sdf"
	m["yx"] = "xx"
	m["y"] = "yy"
	m["z"] = "zz"

	for k, v := range m {
		fmt.Printf("%5q = %-5q|\n", k, v)
	}

	// delete some elements from map
	delete(m, "z")
	fmt.Printf("\n\t%q\n", m)

	fmt.Println("_______-")
	var mp map[string]int = map[string]int{
		"apple":  2,
		"pear":   3,
		"orange": 9,
	}
	fmt.Println(mp)

	val, ok := mp["appl"]
	fmt.Println(val, ok)
	fmt.Printf("%T %T %t\n", val, ok, ok)
	fmt.Printf("%d\n", len(mp))
}


//======== 14 =========
//This is to practice range
package main

import (
	"fmt"
)

func main() {
	var a []int = []int{2, 3, 4}

	for i, ele := range a {
		fmt.Printf("%d %d\n", i, ele)
	}

	fmt.Println("__________")
	b := make([]string, 3, 5)
	b[0] = "x"
	b[1] = "y"
	b[2] = "z"

	for _, ele := range b {
		fmt.Printf("%q\n", ele)
	}

	fmt.Println("___________")
	c := []int{2, 3, 4, 2, 3, 5, 6}

	for i, _ := range c {
		for _, ele := range c[i+1:] {
			if c[i] == ele {
				fmt.Printf("%d\n", ele)
			}
		}
	}

	fmt.Println("_____________")
	fmt.Printf("%d\n", c[7:])
	for i, ele := range make([]int, 0) {
		fmt.Printf("%d %d\n", i, ele)
	}

	fmt.Println("___________")
	arr := [5]int{2, 3, 4, 5, 6}
	fmt.Printf("%T %T\n", arr, arr[2:])
	fmt.Printf("%d\n", arr[2:])

	sl := arr[2:]
	fmt.Printf("%T %d\n", sl, sl)
	fmt.Println(len(sl), cap(sl))
	sl = append(sl, 99)
	fmt.Println(sl)
}


//========= 13 =========
//This is to practice slices
package main

import (
	"fmt"
)

func main() {
	// this is an array, which should have constant length
	var a [2]int = [2]int{2, 3}
	fmt.Printf("%T\n", a)

	// slices, which have variable length
	var b []int
	fmt.Printf("b is nil? %t\n", b == nil)
	fmt.Printf("%T\n", b)
	fmt.Printf("%d %d\n", len(b), cap(b))
	// modify the original slice
	b = append(b, 2)
	fmt.Printf("%d %d\n", len(b), cap(b))
	b = append(b, 4, 5, 6)
	fmt.Printf("%d\n", b)

	// create a slice using make
	c := make([]int, 2, 5)
	fmt.Printf("%d len = %d; cap = %d\n", c, len(c), cap(c))

	fmt.Printf("%d\n", b[1:])

	d := b[1:]
	fmt.Printf("%T len = %d cap = %d\n", d, len(d), cap(d))

	e := make([]int, len(d), cap(d)*2)
	copy(e, d)
	fmt.Printf("%d\n", e)
	e[2] = 9
	fmt.Printf("%d\n", e)

	f := e
	fmt.Printf("%d\n", f)
	e[2] = 99
	fmt.Printf("%d\n", f) // f and e are the same object?
	f = append(f, 999)    //create a new slice and assign to it
	fmt.Printf("%d ? %d\n", e, f)

	// confirm
	g := make([]int, 2)
	h := g
	g[0] = 3
	g[1] = 4
	fmt.Printf("%d %d\n", g, h)

}

//========== 12 ========
//This is to practice 2d-array
package main

import (
	"fmt"
)

func main() {
	const n int = 3
	const m int = 4
	var a [n][m]int

	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			a[i][j] = (1 + i) * (1 + j)
		}
	}
	fmt.Printf("%d\n", a)
	fmt.Printf("%d\n", len(a))
	fmt.Printf("%d\n", len(a[0]))

	b := [2][3]int{{1, 2, 3}, {4, 5, 6}}
	fmt.Printf("%d\n", b)
	fmt.Printf("%d\n", b[1][2])

	c := [2][3]int{}

	fmt.Printf("%d\n", c)

	d := [][]int{{2}, {3, 4}}
	fmt.Printf("%d\n", d)
	fmt.Printf("%d %d\n", d[0][0], d[1][1])
	fmt.Printf("%d %d %d\n", len(d[0]), len(d[1]), len(d))
}


//======== 11 ========
//This is to practice array, which is not as useful as slices
package main

import "fmt"

func main() {
	// declare an array of two elements
	var a [2]int
	a[0] = 2
	a[1] = 3

	fmt.Println(a)
	fmt.Printf("%d", a)

	//initializing an array
	b := [4]float32{2, 3, 4}
	fmt.Printf("%f\n", b)

	var c int = 9
	var d int = 10
	fmt.Printf("%d\n", [5]int{c, d})

	fmt.Printf("%q", [3]string{"sdf", "ll"})
}

//======== 10 =========
//This is to pracitce relational operators
package main

import (
	"fmt"
)

func main() {
	fmt.Printf("%t\n", 2 > 3)
	fmt.Printf("%t\n", !true)
	fmt.Printf("%t %t\n", !true || true, !(true || true))
}

//======= 9 ========
//This is to practice switch statement
package main

import "fmt"

func main() {
	var ans int = 2

	switch ans {
	case 1:
		fmt.Printf("ans = %d\n", 1)
	case 2, 9:
		fmt.Printf("ans = %d or %d\n", 2, 9)
	default:
		fmt.Printf("default")
	}

	fmt.Println("__________")
	//mimic if else statement
	switch {
	case ans == 9:
		fmt.Printf("ans == 9\n")
	case ans > 9:
		fmt.Printf("ans > 9\n")
	default:
		fmt.Printf("ans < 9\n")
	}

}


//======== 8 ========
//This is to practice for loop (no keyword while)
package main

import "fmt"

func main() {
	var i int = 0
	fmt.Println("_____an infinite while loop_____")
	for {
		fmt.Printf("%d ", i)
		i++
		if i == 3 {
			fmt.Println()
			break
		}
	}
	fmt.Println("_____a while loop_____")
	for i >= 0 {
		fmt.Printf("%d ", i)
		i--
	}
	fmt.Println()

	fmt.Println("_____like the ordinary for-loop____")
	// has to be two semi-colons
	for ; i <= 4; i++ {
		if i < 2 {
			continue
		}
		fmt.Printf("%d ", i)
		if i == 3 {
			break
		}
	}
	fmt.Println()

	fmt.Println("__________")
	// can not do "var b int = 9"
	for b := 9; b < 15; b++ {
		fmt.Printf("%d ", b)
	}
	fmt.Println("\n_________")

	for i, j := 1, 2; i < 3 || j <= 6; i, j = i+1, j+2 {
		fmt.Printf("%d %d\n", i, j)
	}
}


//====== 7 =====
// This is to practice if else if else block
package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	fmt.Printf("Enter your age ")
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Scan()
	var age int64
	age, _ = strconv.ParseInt(scanner.Text(), 10, 32)

	if age > 18 {
		fmt.Println("You are old enough to ride alone!")
	} else if age > 14 {
		fmt.Println("You can ride with your parent")
	} else {
		fmt.Println("You can not ride at all!")
	}
}


//======== 6 =========
package main

import "fmt"

func main() {
	// f2() has to be executed as f1() is false
	fmt.Printf("%t\n", f1() || f2())
	fmt.Println("__________")
	// f1() is not executed as f2() is true so for || no need to
	// run the second operand
	fmt.Printf("%t\n", f2() || f1())

	fmt.Println("_________")
	// f2() is not executed as f1() is false so && must false
	fmt.Printf("%t\n", f1() && f2())

	fmt.Println("_________")
	// f1() has to be executed as && value is not determined yet
	fmt.Printf("%t\n", f2() && f1())
}

func f1() bool {
	fmt.Println("f1")
	return false
}

func f2() bool {
	fmt.Println("f2")
	return true
}


//======== 5 ==========
package main

import "fmt"

func main() {

	var a int32 = 5
	var b float64 = 6.5

	fmt.Printf("%t\n", float64(a)+1.5 == b)
	fmt.Printf("%d\n", int32(b))
}

//========== 4 ==========
package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {

	scanner := bufio.NewScanner(os.Stdin)
	fmt.Printf("Type here ")
	//whatever typed in is string
	scanner.Scan()
	input_1 := scanner.Text()

	fmt.Printf("Type here again ")
	scanner.Scan()
	input_2 := scanner.Text()

	fmt.Printf("You typed %q and %q\n", input_1, input_2)
	fmt.Printf("The type of %q is %T, and the type of %q is %T\n",
		input_1, input_1, input_2, input_2)

	//intput year of born
	fmt.Printf("Enter your year of born ")
	scanner.Scan()
	year, _ := strconv.ParseInt(scanner.Text(), 10, 64)
	fmt.Printf("At 2020 you will be %d years old\n", 2020-year)
}


//======== 3 =========
//This is to practice explicitly and implicitly define variables
package main

import "fmt"

func main() {
	//implitly define a variable
	var a = 9
	b := "love"
	var c bool = false

	fmt.Printf("%T %v\n", a, a)
	fmt.Printf("%T %v\n", b, b)
	fmt.Printf("%T %v\n", c, c)

	var d string = fmt.Sprintf("this is %v %v", a, b)
	fmt.Println(d)
	fmt.Printf("print percent mark %%\n")
	fmt.Printf("%t %t = %v %v", true, false, true, false)
	fmt.Printf("%b %b %b %b", 2, 4, 8, 1024)

	fmt.Println("%b %i", 2, 3)
	//for %e the value has to be decimal?
	fmt.Printf("%e %e %f\n", 23., 232423423.9, 2324234.9)
	fmt.Printf("%s %q\n", "sdfs", "tome cruise")
	fmt.Printf("%f %9f \n%9.2f \n%9.f \n%.f", 23., 23., 23.232423, 23.232, 23.2)
	fmt.Printf("%-9.f>>\n", 23.2)
	fmt.Printf("%9s>>\n", "x")
	fmt.Printf("%-9s>>\n", "x")
	fmt.Printf("%-9.cxx\n", 'c')
}


//========== 2 ===========
package main

import "fmt"

func main() {
	var a int = 9
	var name string = "zhao lianshui"
	var age int
	age = 31

	// not overflow?
	var b int16 = 9999
	fmt.Println(b, a, name, age)

}

//======== 1 ========
// the first program
package main

import "fmt"

// entrypoint of the whole program
func main() {
	// double quotation is a string
	// single quotation is a character
	fmt.Println("Hello GoLang")
}
*/
