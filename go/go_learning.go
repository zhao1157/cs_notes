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

}

/*
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
