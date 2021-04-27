//========== 12 ========
//This is to practice 2d-array
package main

import (
	"fmt"
)

func main() {
	const n int = 3
	var a [n][n]int

	fmt.Printf("%d", a)
}

/*
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
