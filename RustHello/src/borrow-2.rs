fn line(title: &str) {
    println!("--- {title}:: {:->50}", "");
}

struct Number {
    value: i32,
}

impl Drop for Number {
    fn drop(&mut self) {
        println!("Dropping Number [{:p}] with value: {}", self, self.value);
    }
}

fn main() {
    {
        line("let Number");
        let num = Number { value: 10 };

        // cannot modify num.value
        // num.value += 5;
        // println!("Number value: {}", num.value);

        println!(
            "     let Number: {:p}, Value: [{:p}]: {}",
            &num, &num.value, num.value
        );
    }

    {
        line("let mut Number");
        let mut num = Number { value: 20 };
        // can modify num.value
        num.value += 5;
        println!(
            "Mutable  Number: {:p}, Value: [{:p}]: {}",
            &num, &num.value, num.value
        );
        num.value += 10;
        println!(
            "Mutable  Number: {:p}, Value: [{:p}]: {}",
            &num, &num.value, num.value
        );
    }

    {
        line("RefCall Number with reference");
        let num = std::cell::RefCell::new(Number { value: 30 }); // Box to allocate num on the heap
        num.borrow_mut().value += 5; // Modify the value through mutable reference
        println!(
            "Mutable  Number: {:p}, Value: [{:p}]: {}",
            &num,
            &num.borrow().value,
            num.borrow().value
        );
        num.borrow_mut().value += 10; // Modify the value through mutable reference again
        println!(
            "Mutable  Number: {:p}, Value: [{:p}]: {}",
            &num,
            &num.borrow().value,
            num.borrow().value
        );
    }

    {
        line("Rc<Number>");
        let num = std::rc::Rc::new(Number { value: 40 });

        let s: &Number = &num;
        println!("Rc<Number>: {:p}", s);

        {
            let num_clone = std::rc::Rc::clone(&num);
            println!(
                "Rc<Number> Clone: {:p} {}, Strong Count: {}",
                std::rc::Rc::as_ptr(&num_clone),
                &num_clone.value,
                std::rc::Rc::strong_count(&num_clone)
            );
        }

        {
            let num_clone = std::rc::Rc::clone(&num);
            println!(
                "Rc<Number> Clone: {:p} {}, Strong Count: {}",
                std::rc::Rc::as_ptr(&num_clone),
                &num_clone.value,
                std::rc::Rc::strong_count(&num_clone)
            );
        }
    }
}
