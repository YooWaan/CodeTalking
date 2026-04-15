enum Number {
    One,
    Two,
    Three,
    Four,
    Five,
    Six,
}

impl std::fmt::Debug for Number {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let s = match self {
            Number::One => "1",
            Number::Two => "2",
            Number::Three => "3",
            Number::Four => "4",
            Number::Five => "5",
            Number::Six => "6",
        };
        write!(f, "{}", s)
    }
}

struct Dice {
    number: Number,
    next: Option<Box<Dice>>,
}

struct Hand {}

impl Hand {
    fn new() -> Self {
        Self {}
    }

    fn roll(&self) -> Result<Number, String> {
        match rand::random_range(1..=13) {
            1 | 7 => Ok(Number::One),
            2 | 8 => Ok(Number::Two),
            3 | 9 => Ok(Number::Three),
            4 | 10 => Ok(Number::Four),
            5 | 11 => Ok(Number::Five),
            6 | 12 => Ok(Number::Six),
            _ => Err("invalid number".to_string()),
        }
    }

    fn roll_dice(&self, times: u32) -> Result<Box<Dice>, String> {
        let mut dice = None;
        for _ in (1..times).rev() {
            let new_dice = Dice {
                number: self.roll()?,
                next: dice,
            };
            dice = Some(Box::new(new_dice));
        }

        match dice {
            Some(d) => Ok(d),
            None => Err("No dice rolled".to_string()),
        }
    }
}

fn show(head: Box<Dice>) -> String {
    let mut s: Vec<String> = Vec::new();
    let mut curr = Some(head);
    let mut i = 0;

    while let Some(dice) = curr {
        s.push(format!("n={} [{:?}]", i, dice.number));
        i += 1;
        curr = dice.next
    }

    s.join(", ")
}

fn get_at_3rd(head: Box<Dice>) -> Option<Number> {
    Some(head.next?.next?.number)
}

fn main() {
    let hand = Hand::new();
    match hand.roll() {
        Ok(num) => println!("Rolled: {:?}", num),
        Err(e) => println!("Error rolling dice: {}", e),
    }

    match hand.roll_dice(rand::random_range(1..=10)) {
        Ok(dice) => {
            println!("Dices: {}", show(dice))
        }
        Err(e) => println!("Error: {}", e),
    }

    let dice1 = Box::new(Dice {
        number: Number::One,
        next: Some(Box::new(Dice {
            number: Number::Two,
            next: Some(Box::new(Dice {
                number: Number::Three,
                next: Some(Box::new(Dice {
                    number: Number::Four,
                    next: None,
                })),
            })),
        })),
    });

    let dice2 = Box::new(Dice {
        number: Number::One,
        next: Some(Box::new(Dice {
            number: Number::Two,
            next: None,
        })),
    });

    if let Some(n) = get_at_3rd(dice1) {
        println!("3rd dice number: {:?}", n);
    } else {
        println!("3rd dice not found");
    }
    if let Some(n) = get_at_3rd(dice2) {
        println!("3rd dice number: {:?}", n);
    } else {
        println!("3rd dice not found");
    }
}
