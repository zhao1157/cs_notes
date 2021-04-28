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

/*
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
