import os

TESTS = {
    "01_assignment": {
        "src": "a <- 10\nb <- 20\nc <- a + b\noutput c\n",
        "expected": "30\n",
    },
    "02_aritmatika": {
        "src": "a <- 10\nb <- 3\noutput a + b\noutput a - b\noutput a * b\noutput a / b\n",
        "expected": "13\n7\n30\n3\n",
    },
    "03_precedence": {
        "src": "output 2 + 3 * 4\noutput (2 + 3) * 4\noutput 10 - 2 - 3\noutput 100 / 10 / 2\n",
        "expected": "14\n20\n5\n5\n",
    },
    "04_perbandingan": {
        "src": "a <- 5\nb <- 10\noutput a = b\noutput a < b\noutput a > b\noutput a <= b\noutput a >= b\noutput a <= 5\noutput a >= 5\n",
        "expected": "0\n1\n0\n1\n0\n1\n1\n",
    },
    "05_if_basic": {
        "src": "x <- 50\nif x > 10 then\n    output 100\nelse\n    output 200\nendif\n",
        "expected": "100\n",
    },
    "06_if_else": {
        "src": "x <- 5\nif x > 10 then\n    output 100\nelse\n    output 200\nendif\n",
        "expected": "200\n",
    },
    "07_if_no_else": {
        "src": "x <- 5\nif x > 10 then\n    output 100\nendif\noutput 999\n",
        "expected": "999\n",
    },
    "08_if_nested": {
        "src": "x <- 5\ny <- 10\nif x > 0 then\n    if y > 5 then\n        output 99\n    else\n        output 88\n    endif\nelse\n    output 77\nendif\n",
        "expected": "99\n",
    },
    "09_while": {
        "src": "i <- 3\nwhile i > 0 do\n    output i\n    i <- i - 1\nendwhile\n",
        "expected": "3\n2\n1\n",
    },
    "10_while_calc": {
        "src": "n <- 5\nhasil <- 1\ni <- 1\nwhile i <= n do\n    hasil <- hasil * i\n    i <- i + 1\nendwhile\noutput hasil\n",
        "expected": "120\n",
    },
    "11_for": {
        "src": "for i <- 1 to 5 do\n    output i\nendfor\n",
        "expected": "1\n2\n3\n4\n5\n",
    },
    "12_for_calc": {
        "src": "total <- 0\nfor i <- 1 to 5 do\n    total <- total + i\nendfor\noutput total\n",
        "expected": "15\n",
    },
    "13_for_nested": {
        "src": "for i <- 1 to 3 do\n    for j <- 1 to 3 do\n        output i * 10 + j\n    endfor\nendfor\n",
        "expected": "11\n12\n13\n21\n22\n23\n31\n32\n33\n",
    },
    "14_for_body_calc": {
        "src": "c <- 0\na <- 10\nb <- 5\nfor i <- 1 to 3 do\n    c <- a + b\n    c <- c - b\n    c <- c * a\n    c <- c / 1\nendfor\noutput c\n",
        "expected": "100\n",
    },
    "15_boolean_true": {
        "src": "x <- true\nif x then\n    output 1\nendif\n",
        "expected": "1\n",
    },
    "16_boolean_false": {
        "src": "x <- false\nif x then\n    output 1\nelse\n    output 0\nendif\n",
        "expected": "0\n",
    },
    "17_input_single": {
        "src": "input(a)\noutput a * 2\n",
        "in": "7\n",
        "expected": "14\n",
    },
    "18_input_multi": {
        "src": "input(a, b, c)\noutput a + b + c\n",
        "in": "1\n2\n3\n",
        "expected": "6\n",
    },
    "19_faktorial": {
        "src": "input(n)\nhasil <- 1\ni <- 1\nwhile i <= n do\n    hasil <- hasil * i\n    i <- i + 1\nendwhile\noutput hasil\n",
        "in": "5\n",
        "expected": "120\n",
    },
    "20_fibonacci": {
        "src": "input(n)\na <- 0\nb <- 1\ni <- 0\nwhile i < n do\n    output a\n    c <- a + b\n    a <- b\n    b <- c\n    i <- i + 1\nendwhile\n",
        "in": "7\n",
        "expected": "0\n1\n1\n2\n3\n5\n8\n",
    },
    "21_div_by_zero": {
        "src": "a <- 10\nb <- 0\noutput a / b\noutput 5\n",
        "expected": "Runtime Error: Pembagian dengan nol terdeteksi. Tidak bisa membagi dengan penyebut 0.\n0\n5\n",
    },
    "22_undefined_var": {
        "src": "output x\noutput 5\n",
        "expected": "Runtime Error: Variabel 'x' belum didefinisikan.\n0\n5\n",
    },
    "23_kitchen_sink": {
        "src": "input(a)\ninput(b)\nc <- 0\nfor i <- 1 to 3 do\n    c <- c + a\nendfor\noutput c\ni <- b\nwhile i > 0 do\n    c <- c - 1\n    i <- i - 1\nendwhile\noutput c\nif c > 0 then\n    output 111\nelse\n    output 222\nendif\n",
        "in": "10\n2\n",
        "expected": "30\n28\n111\n",
    },
    "24_and": {
        "src": "x <- 1\ny <- 1\nif x > 0 AND y > 0 then\n    output 100\nendif\n",
        "expected": "100\n",
    },
    "25_or": {
        "src": "x <- 0\ny <- 1\nif x > 0 OR y > 0 then\n    output 100\nendif\n",
        "expected": "100\n",
    },
    "26_and_or_combo": {
        "src": "a <- 1\nb <- 0\nc <- 1\nif a > 0 AND b > 0 then\n    output 111\nendif\nif a > 0 OR b > 0 then\n    output 222\nendif\nif a > 0 AND b > 0 OR c > 0 then\n    output 333\nendif\n",
        "expected": "222\n333\n",
    },
    "27_mod": {
        "src": "output 10 mod 3\noutput 20 mod 7\noutput 100 mod 10\noutput 7 mod 7\n",
        "expected": "1\n6\n0\n0\n",
    },
    "28_mod_zero": {
        "src": "a <- 5\nb <- 0\noutput a mod b\noutput 99\n",
        "expected": "Runtime Error: Modulo dengan nol terdeteksi.\n0\n99\n",
    },
}

os.makedirs("cases", exist_ok=True)

for name, data in TESTS.items():
    with open(f"cases/{name}.psdc", "w") as f:
        f.write(data["src"])
    with open(f"cases/{name}.expected", "w") as f:
        f.write(data["expected"])
    if "in" in data:
        with open(f"cases/{name}.in", "w") as f:
            f.write(data["in"])

print(f"Generated {len(TESTS)} test cases di tests/cases/")