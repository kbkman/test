package main
import "fmt"

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
	output := "hello world"
	var runne_test string
	runne_test = "abcab"
	var uint8_test uint8
	uint8_test = 128
	fmt.Printf("%s %s %d\n", output, runne_test, uint8_test)

	if uint8_test > 127 {
		fmt.Printf("uint8_test = %d\n", uint8_test)
	}

	if foo(int(uint8_test)) {
		fmt.Printf("foo ok\n")
	} else {
		fmt.Printf("foo failed\n")
	}

	fmt.Printf("sum=%d\n", foo2())
	fmt.Printf("sum=%d\n", foo3())
}

