package main

import (
	"fmt"
	"github.com/pborman/uuid"
)


func main() {
	var uuid uuid.UUID = uuid.NewRandom()

	fmt.Printf("UUID-> %v\n", uuid)
}
