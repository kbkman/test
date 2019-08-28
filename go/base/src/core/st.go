package core

type Student struct {
	Name string
	Age uint8
}

func (a *Student) Get_age() uint8 {
	return a.Age
}

func (a *Student) Set_age(age uint8) {
	a.Age = age
}

