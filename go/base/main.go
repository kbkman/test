package main

import "fmt"
import "core"

type Interge int
var mych chan int

func (a Interge) add(b Interge) Interge {

	return a + b
}

func do_something() {
	fmt.Printf("%s\n", "go end")
	mych<-1
}


func foo(x int) bool {
	switch {
	case x >= 0 && x < 127 :
		return true
	case x >= 127 && x < 256 :
		fallthrough
	default :
		return false
	}

}

func foo2() int {
	sum := 0
	for i := 0; i < 100; i++ {
		sum += i
	}
	return sum
}

func foo3() int {
	sum := 0
	i := 0
	for {
		if i >= 100 {
			goto END
		}

		i++
		sum += i

	}
	return sum

END:
	return 8888
}

func main() {
	//defer fmt.Printf("end\n")

	output := "hello world"
	fmt.Printf("%s\n", output)

	stu := core.Student{}
	stu.Name = "blue"
	stu.Age = 16
	fmt.Printf("name=%s,age=%d\n", stu.Name, stu.Get_age())

	stu.Set_age(18)
	fmt.Printf("name=%s,age=%d\n", stu.Name, stu.Get_age())

	const (
		Monday = iota
		Thuesday = iota
		Wesday = iota
	)

	fmt.Printf("%d, %d, %d\n", Monday, Thuesday, Wesday)

	var mya Interge = 3
	var myb Interge = 4
	fmt.Printf("%d + %d = %d\n", mya, myb, mya.add(myb))

	var myc int = 1
	fmt.Printf("%d\n", myc);

	ret:= <-mych
	go do_something()
	fmt.Printf("ret=%d\n", ret)
}

