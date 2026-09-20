# Pseudocode Interpreter

Interpreter sederhana untuk bahasa pseudocode. Dibuat sebagai proyek
pembelajaran untuk mata kuliah Teknik Kompilasi.

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

## Batasan

Fitur berikut **belum** didukung:

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

### Windows

```bat
build.bat
```

### Linux / Mac

```sh
make
```

Binary hasil build akan ada di `bin/` (`bin/interpreter.exe` di Windows,
`bin/interpreter` di Linux/Mac).

## Cara Pakai

```sh
bin/interpreter example/faktorial.psdc
```

Untuk Windows:

```bat
bin\interpreter.exe example\faktorial.psdc
```

Contoh program (`example/faktorial.psdc`):

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

Test file ada di folder `tests/`. Setiap file `.psdc` berisi program yang
menguji satu atau lebih fitur interpreter.

Daftar test:

| File | Menguji |
|---|---|
| `assignment.psdc` | Assignment dasar |
| `precedence.psdc` | Urutan operasi aritmatika |
| `test_aritmatika.psdc` | Operasi `+ - * /` |
| `test_perbandingan.psdc` | Operasi `= < > <= >=` |
| `boolean.psdc` | Literal `true` / `false` |
| `if.psdc`, `if_else.psdc`, `if_nested.psdc`, `if_no_else.psdc` | Percabangan |
| `while.psdc` | Perulangan while |
| `for.psdc`, `for_nested.psdc`, `for_calc.psdc` | Perulangan for |
| `input.psdc`, `input_multi.psdc` | Input |
| `divzero.psdc` | Error pembagian nol |
| `faktorial.psdc`, `fibonacci.psdc` | Contoh program |

Jalankan satu test:

```sh
bin/interpreter tests/faktorial.psdc
```

## Struktur Kode

- `Lexer` — memecah source code menjadi token
- `Parser` — membangun AST dari token menggunakan recursive descent
- `Evaluator` — mengeksekusi AST dengan `unordered_map` sebagai environment

## Status

Proyek ini masih dalam tahap pengembangan. Saat ini sudah bisa di-build 
dan menjalankan fitur-fitur dasar, tapi masih ada beberapa bug dan 
keterbatasan yang belum diperbaiki. Lihat bagian Known Issues / TODO.

## Known Issues / TODO

Beberapa hal yang perlu diperbaiki / ditambahkan:

- [ ] Operator `AND` dan `OR` (token sudah ada di Lexer, tinggal ditangani di Parser dan Evaluator)
- [ ] Unary minus (`-5`, `-(a + b)`)
- [ ] String literal
- [ ] Komentar (`//` atau `#`)
- [ ] Modulo `%`
- [ ] `printTree` belum menelusuri `body`, `condition`, `alternative`, `arguments`
- [ ] `true` / `false` belum dikenali di `parseExpression`
- [ ] Input tidak memvalidasi `std::cin` (kalau user input non-angka, bisa loop)
- [ ] Memory leak pada `ASTNode` (tidak pernah di-`delete`)
- [ ] Belum ada test otomatis dengan `expected/` output

## Lisensi

Proyek ini dilisensikan di bawah MIT License — lihat file [LICENSE](LICENSE).