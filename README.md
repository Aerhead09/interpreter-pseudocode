# Pseudocode Interpreter

Interpreter sederhana untuk bahasa pseudocode bergaya bahasa Indonesia/Inggris. 
Dibuat sebagai proyek pembelajaran untuk mata kuliah Teknik Kompilasi.

## Fitur

- Assignment: `x <- 5`
- Aritmatika: `+ - * /` dengan precedence dan tanda kurung
- Perbandingan: `= < > <= >=`
- Literal boolean: `true`, `false`, `TRUE`, `FALSE`
- Input: `input(x)` atau `input(x, y, z)`
- Output: `output expr`
- Percabangan: `if ... then ... else ... endif`
- Perulangan `while ... do ... endwhile`
- Perulangan `for i <- 1 to N do ... endfor`
- Blok bersarang (nested if/while/for)

## Batasan (belum didukung)

- Operator `AND` / `OR`
- Unary minus (`-5`)
- String literal (`"hello"`)
- Komentar
- Deklarasi `int x`
- Blok `Program ... endprogram`
- Modulo `%`
- `break` / `continue`
- Bilangan pecahan (hanya integer)

## Cara Build

### Windows (MinGW / g++)

```bat
g++ src\Token.h src\Lexer.cpp src\Parser.cpp src\Evaluator.cpp src\main.cpp -o interpreter.exe
```

Atau jalankan:

```bat
build.bat
```

### Linux / Mac

```sh
make
```

Atau manual:

```sh
g++ src/Lexer.cpp src/Parser.cpp src/Evaluator.cpp src/main.cpp -o interpreter
```

## Cara Pakai

```sh
./interpreter examples/faktorial.psdc
```

Untuk Windows:

```bat
interpreter.exe examples\faktorial.psdc
```

Contoh program (`examples/faktorial.psdc`):

```text
input(n)
hasil <- 1
i <- 1
while i <= n do
    hasil <- hasil * i
    i <- i + 1
endwhile
output hasil
```

## Test

Test file ada di folder `tests/`. Setiap file `tNN_*.psdc` punya pasangan 
`tNN_*.expected` yang berisi output yang diharapkan.

Jalankan semua test:

```bat
cd tests
run_tests.bat
```

Atau di Linux/Mac:

```sh
cd tests
./run_tests.sh
```

## Struktur Kode

- `Lexer` — memecah source code menjadi token
- `Parser` — membangun AST dari token menggunakan recursive descent
- `Evaluator` — mengeksekusi AST dengan `unordered_map` sebagai environment

## Known Issues / TODO

Lihat bagian [Improvements](#improvements) di bawah.

## Lisensi

MIT (atau sesuai keinginanmu).